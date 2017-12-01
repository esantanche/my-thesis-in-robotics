/*
NOME_FILE:ANADIS
PROGETTO:Thesis
AUTORE:Emanuele Maria Santanché
DATA_INIZ:Ott 18'92
FILES DOCUMENTAZIONE:THMODULI.DOC, THGRUPPI.DOC, ANADISDF.DOC
NOMI FUNZIONI:
   Gruppo ANADIS
      Analizza_discontinuita
      Calcola_retta_fine
   Gruppo ALLELD
      Alloca_elenco_disc
      Dealloca_elenco_disc
*/


#include "thvarie.h"
#include "thstruct.h"
#include "thprotot.h"
#include "thextern.h"

/////////////////////////////////////////////////////////////////////////
//   Analizza_discontinuita
/////////////////////////////////////////////////////////////////////////
void Analizza_discontinuita(struct punto *pp,
                            struct punto pv,
                            struct retta rt,
                            struct taglio_rett_int huge *t,
                            struct elenco_part *e,
                            double huge *rumore,
                            int huge *discontinuita,
                            struct elenco_disc huge *ed)
{
struct taglio_rett_int huge *tf;
struct elenco_part ef;
struct retta rtf,r_pp_p_rtf;
struct punto p_rtf,punto_disc;
struct vettore vers_disc;
double huge *coeff_dx;
double huge *coeff_sx;
double huge *coeff;
double huge *coeff_memo;
double huge *rumore_f;
double sqme,prob,valore_disc,derivata,curvatura,dist_disc,dist_disc_dx,
       dist_disc_sx,par_retta;
int punto_inizio,part,p_dis,i,tipo_disc,filtro,k,indice_disc,fil_disc,
    n_punti,filtro_fin,lun_part,j,pos_fin_disc,temp;
BOOL no_part_def,avanti,accettato,da_inseguire,senso_opposto;

if (e->n_part == 0)
   Error("Non ci sono partizioni da esaminare",
         "Analizza_discontinuita","anadis");
ed->n_disc=0;
tf=Alloca_taglio();
coeff_dx=vector(0,descr_filtri[NUM_FILTRI_FINE-1].ord_fitt);
coeff_sx=vector(0,descr_filtri[NUM_FILTRI_FINE-1].ord_fitt);
coeff=vector(0,descr_filtri[NUM_FILTRI_FINE-1].ord_fitt);
coeff_memo=vector(0,descr_filtri[NUM_FILTRI_FINE-1].ord_fitt);
// analisi delle discontinuità interne (tra punti tutti definiti)
for (part=0;(part < e->n_part) && (ed->n_disc < NUM_MAX_DISC);part++) {
   if (e->part[part].stato) continue;

   // analisi discontinuità di bordo sinistra
   lun_part=e->part[part].lungh;
   if (lun_part < descr_filtri[1].lungh_supp) continue;
   punto_inizio=e->part[part].da;
   avanti=TRUE;
   for (filtro=1;
        (filtro<NUM_FILTRI_BORDO) &&
        (lun_part >= descr_filtri[filtro].lungh_supp);
        filtro++) {
      for (k=0;k<NUM_TENTATIVI_FITT_BORDO;k++) {
         Esegui_fitting(t,FALSE,rumore,punto_inizio,filtro,avanti,
                        coeff,&sqme,&prob,&accettato);
         if (accettato) break;
      }
      if (!accettato)
         break;
      else
         for (i=0;i<=descr_filtri[filtro].ord_fitt;i++)
            coeff_memo[i]=coeff[i];
   }
   if (!((filtro == 1) && (!accettato))) {
      filtro_fin=filtro-1;
      derivata=coeff_memo[1]/PASSO_GROSS;
      curvatura=
         (coeff_memo[2]/pow(PASSO_GROSS,2))/pow(1+pow(derivata,2),1.5);
      if ( (curvatura < SOGLIA_CURVATURA) &&
           (derivata > SOGLIA_DERIVATA) )
         da_inseguire=FALSE;
      else
         da_inseguire=TRUE;
      dist_disc=Valuta_polinomio(descr_filtri[filtro_fin].ord_fitt,
                                       -0.5,coeff_memo);
      par_retta=(punto_inizio-0.5)/t->n_punti;
      p_rtf=Punto_da_retta(rt,par_retta);
      r_pp_p_rtf=Crea_retta(pp->x,pp->y,pp->z,
                            p_rtf.x,p_rtf.y,p_rtf.z);
      if (r_pp_p_rtf.cd < 0.001)
         Error("r_pp_p_rtf.cd = 0 #2","Analizza_discontinuita","anadis");
      punto_disc=Punto_da_retta(r_pp_p_rtf,(dist_disc/r_pp_p_rtf.cd));
      vers_disc=Versore_da_retta(rt);
      temp=ed->n_disc;
      ed->d[temp].interna=FALSE;
      ed->d[temp].tipo_disc=TRUE;
      ed->d[temp].da_inseguire=da_inseguire;
      ed->d[temp].vers_disc=vers_disc;
      ed->d[temp].supporto=descr_filtri[filtro_fin].lungh_supp*PASSO_GROSS;
      ed->d[temp].curvatura=curvatura;
      ed->d[temp].derivata_dx=derivata;
      ed->d[temp].derivata_sx=0;
      ed->d[temp].valore_disc=0;
      ed->d[temp].punto_disc=punto_disc;
      ed->n_disc++;
   }

   // analisi discontinuità interne alla partizione
   for (i=e->part[part].da;
        (i<e->part[part].a) && (ed->n_disc < NUM_MAX_DISC);
        i++) {
      if (discontinuita[i] == 0) continue;
      if (discontinuita[i+1] != 0) i++;
      indice_disc=i;
      fil_disc=discontinuita[i];
      Calcola_retta_fine(t,rt,indice_disc,fil_disc,&rtf,&n_punti);
      Crea_taglio_rett_int(pp,pv,rtf,n_punti,tf);
      Partiziona_taglio(tf,&ef);
      if (ef.n_part == 0) continue;
      no_part_def=TRUE;
      for (j=0;j<ef.n_part;j++)
         if (!ef.part[j].stato) {
            no_part_def=FALSE;
            break;
         }
      if (no_part_def) continue;
      Tappa_buchi_dist(tf,&ef);
      p_dis=tf->n_punti/2;
      if (tf->p[p_dis].pr.indefinito) continue;
      rumore_f=vector(0,tf->n_punti-1);
      Valuta_rumore(tf,&ef,rumore_f);
      printf("\nPart n. %d punto n. %d",part,i);
      Localizza_una_discontinuita(tf,&ef,rumore_f,p_dis,fil_disc,
                                  &tipo_disc,&pos_fin_disc,&filtro_fin,
                                  &valore_disc,coeff_dx,coeff_sx);
      free_vector(rumore_f,0);
      if (tipo_disc == NON_TROVATA) continue;

      // studio della discont.
      da_inseguire=TRUE;
      vers_disc=Versore_da_retta(rtf);
      derivata=0.0;
      curvatura=0.0;
      senso_opposto=FALSE;

      if (tipo_disc == SALTO) {
         if (valore_disc > 0) {
            senso_opposto=TRUE;
            vers_disc.a=-vers_disc.a;
            vers_disc.b=-vers_disc.b;
            vers_disc.c=-vers_disc.c;
            derivata=coeff_sx[1]/PASSO_FINE;
            curvatura=
               (coeff_sx[2]/pow(PASSO_FINE,2))/pow(1+pow(derivata,2),1.5);
            dist_disc=Valuta_polinomio(descr_filtri[filtro_fin].ord_fitt,
                                       -0.5,coeff_sx);
         }
         else {
            derivata=coeff_dx[1]/PASSO_FINE;
            curvatura=
               (coeff_dx[2]/pow(PASSO_FINE,2))/pow(1+pow(derivata,2),1.5);
            dist_disc=Valuta_polinomio(descr_filtri[filtro_fin].ord_fitt,
                                       -0.5,coeff_dx);
         }
         if ( (curvatura < SOGLIA_CURVATURA) &&
              (derivata > SOGLIA_DERIVATA)   )
            da_inseguire=FALSE;
      }
      else { // la discontinuita è un angolo
         dist_disc_sx=Valuta_polinomio(descr_filtri[filtro_fin].ord_fitt,
                                       -0.5,coeff_sx);
         dist_disc_dx=Valuta_polinomio(descr_filtri[filtro_fin].ord_fitt,
                                       -0.5,coeff_dx);
         dist_disc=(dist_disc_sx+dist_disc_dx)/2;
      }
      par_retta=(pos_fin_disc-0.5)/n_punti;
      p_rtf=Punto_da_retta(rtf,par_retta);
      r_pp_p_rtf=Crea_retta(pp->x,pp->y,pp->z,
                            p_rtf.x,p_rtf.y,p_rtf.z);
      if (r_pp_p_rtf.cd < 0.001)
         Error("r_pp_p_rtf.cd = 0 #1","Analizza_discontinuita","anadis");
      punto_disc=Punto_da_retta(r_pp_p_rtf,(dist_disc/r_pp_p_rtf.cd));
      temp=ed->n_disc;
      ed->d[temp].interna=TRUE;
      ed->d[temp].tipo_disc=tipo_disc;
      ed->d[temp].da_inseguire=da_inseguire;
      ed->d[temp].vers_disc=vers_disc;
      ed->d[temp].supporto=descr_filtri[filtro_fin].lungh_supp*
                           2*PASSO_FINE;
      ed->d[temp].curvatura=curvatura;
      ed->d[temp].derivata_dx=coeff_dx[1]*(senso_opposto ? -1 : 1)/
                              PASSO_FINE;
      ed->d[temp].derivata_sx=coeff_sx[1]*(senso_opposto ? 1 : -1)/
                              PASSO_FINE;
      ed->d[temp].valore_disc=((tipo_disc == SALTO) ?
                               (valore_disc) : (valore_disc/PASSO_FINE));
      ed->d[temp].punto_disc=punto_disc;
      ed->n_disc++;
   } // fine ciclo di analisi di una partizione del taglio grossolano


   // analisi discontinuità di bordo destra
   punto_inizio=e->part[part].a;
   avanti=FALSE;
   for (filtro=1;
        (filtro<NUM_FILTRI_BORDO) &&
        (lun_part >= descr_filtri[filtro].lungh_supp);
        filtro++) {
      for (k=0;k<NUM_TENTATIVI_FITT_BORDO;k++) {
           Esegui_fitting(t,FALSE,rumore,punto_inizio,filtro,avanti,
                        coeff,&sqme,&prob,&accettato);
           if (accettato) break;
      }
      if (!accettato)
         break;
      else
         for (i=0;i<=descr_filtri[filtro].ord_fitt;i++)
            coeff_memo[i]=coeff[i];
   }
   if (!((filtro == 1) && (!accettato))) {
      filtro_fin=filtro-1;
      derivata=coeff_memo[1]/PASSO_GROSS;
      curvatura=
         (coeff_memo[2]/pow(PASSO_GROSS,2))/pow(1+pow(derivata,2),1.5);
      if ( (curvatura < SOGLIA_CURVATURA) &&
           (derivata > SOGLIA_DERIVATA) )
         da_inseguire=FALSE;
      else
         da_inseguire=TRUE;
      dist_disc=Valuta_polinomio(descr_filtri[filtro_fin].ord_fitt,
                                       -0.5,coeff_memo);
      par_retta=(punto_inizio+0.5)/t->n_punti;
      p_rtf=Punto_da_retta(rt,par_retta);
      r_pp_p_rtf=Crea_retta(pp->x,pp->y,pp->z,
                            p_rtf.x,p_rtf.y,p_rtf.z);
      if (r_pp_p_rtf.cd < 0.001)
         Error("r_pp_p_rtf.cd = 0 #3","Analizza_discontinuita","anadis");
      punto_disc=Punto_da_retta(r_pp_p_rtf,(dist_disc/r_pp_p_rtf.cd));
      vers_disc=Versore_da_retta(rt);
      vers_disc.a=-vers_disc.a;
      vers_disc.b=-vers_disc.b;
      vers_disc.c=-vers_disc.c;
      temp=ed->n_disc;
      ed->d[temp].interna=FALSE;
      ed->d[temp].tipo_disc=FALSE;
      ed->d[temp].da_inseguire=da_inseguire;
      ed->d[temp].vers_disc=vers_disc;
      ed->d[temp].supporto=descr_filtri[filtro_fin].lungh_supp*PASSO_GROSS;
      ed->d[temp].curvatura=curvatura;
      ed->d[temp].derivata_dx=0;
      ed->d[temp].derivata_sx=-derivata;
      ed->d[temp].valore_disc=0;
      ed->d[temp].punto_disc=punto_disc;
      ed->n_disc++;
   }

} // fine ciclo di analisi dell' intero taglio grossolano

free_vector(coeff_dx,0);
free_vector(coeff_sx,0);
free_vector(coeff,0);
free_vector(coeff_memo,0);

Dealloca_taglio(tf);

}

/////////////////////////////////////////////////////////////////////////
//   Calcola_retta_fine
/////////////////////////////////////////////////////////////////////////
void Calcola_retta_fine(struct taglio_rett_int huge *t,
                        struct retta rt,
                        int indice_disc,
                        int fil_disc,
                        struct retta *rtf,
                        int *n_punti)
{
struct punto p_disc,p_inizio,p_fine;
struct vettore vers,v_avanti,v_indietro;
double supp;

if (fil_disc >= NUM_FILTRI_FINE)
   Error("Numero di filtro invalido","Calcola_retta_fine","anadis");
p_disc=t->p[indice_disc].pr;
supp=descr_filtri[fil_disc].lungh_supp*PASSO_GROSS*INCREM_SUPP;
vers=Versore_da_retta(rt);
v_avanti=Vett_per_scal(supp,vers);
v_indietro.indefinito=FALSE;
v_indietro.a=-v_avanti.a;
v_indietro.b=-v_avanti.b;
v_indietro.c=-v_avanti.c;
p_fine=Punto_piu_vett(p_disc,v_avanti);
p_inizio=Punto_piu_vett(p_disc,v_indietro);
*rtf=Crea_retta(p_inizio.x,p_inizio.y,p_inizio.z,p_fine.x,p_fine.y,p_fine.z);
if (rtf->cd < 1)
   Error("Retta fine troppo piccola","Calcola_retta_fine","anadis");
*n_punti=rtf->cd/PASSO_FINE;
}

/////////////////////////////////////////////////////////////////////////
//   Alloca_elenco_disc
/////////////////////////////////////////////////////////////////////////
struct elenco_disc huge *Alloca_elenco_disc(void)
{
struct elenco_disc huge *ed;

ed=(struct elenco_disc huge *)
        malloc(sizeof(struct elenco_disc));
if (ed == NULL)
   Error("Impossibile malloc di elenco disc",
         "Alloca_elenco_disc","anadis");
return(ed);
}

/////////////////////////////////////////////////////////////////////////
//   Dealloca_elenco_disc
/////////////////////////////////////////////////////////////////////////
void Dealloca_elenco_disc(struct elenco_disc huge *ed)
{

free((void huge *) ed);
}