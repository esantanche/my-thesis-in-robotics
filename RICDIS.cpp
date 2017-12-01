/*
NOME_FILE:RICDIS
PROGETTO:Thesis
AUTORE:Emanuele Maria Santanché
DATA_INIZ:Ott 10'92
FILES DOCUMENTAZIONE:THMODULI.DOC, THGRUPPI.DOC, RICDISDF.DOC
NOMI FUNZIONI:
   Gruppo PARTAG
      Partiziona_taglio()
   Gruppo TAPBUC
      Tappa_buchi_dist()
   Gruppo VALRUM
      Valuta_rumore()
   Gruppo TRODIS
      Trova_discontinuita()
*/

#include "thvarie.h"
#include "thstruct.h"
#include "thprotot.h"
#include "thextern.h"

/////////////////////////////////////////////////////////////////////////
//   Partiziona_taglio
/////////////////////////////////////////////////////////////////////////
void Partiziona_taglio(struct taglio_rett_int huge *t,
                       struct elenco_part *e)
{
BOOL indef;
int i_part,i;

if (t->n_punti < 3) {
   e->n_part=0;
   return;
}
if (t->p[0].pr.indefinito)
   indef=TRUE;
else
   indef=FALSE;
i_part=0;
e->part[i_part].da=0;
e->part[i_part].a=0;
e->part[i_part].stato=indef;
e->part[i_part].lungh=1;
e->part[i_part].n_stato=1;
for (i=1;;i++) {
   for (;(t->p[i].pr.indefinito == indef) &&
         (i<t->n_punti);i++) {
      e->part[i_part].a++;
      e->part[i_part].lungh++;
      e->part[i_part].n_stato++;
   }
   if (i+2>=t->n_punti) break;
   if ((t->p[i+1].pr.indefinito != indef) &&
       (t->p[i+2].pr.indefinito != indef)) {
      if (e->part[i_part].lungh < 3) {
         e->part[i_part].stato=!e->part[i_part].stato;
         indef=!indef;
         e->part[i_part].n_stato=1;
      }
      else {
         indef=!indef;
         i_part++;
         e->part[i_part].da=i;
         e->part[i_part].a=i-1;
         e->part[i_part].lungh=0;
         e->part[i_part].stato=indef;
         e->part[i_part].n_stato=1;
      }
   }
   e->part[i_part].a++;
   e->part[i_part].lungh++;
}
if (i<t->n_punti) {
   if (t->p[i].pr.indefinito == indef) e->part[i_part].n_stato++;
   if (i+1<t->n_punti)
      if (t->p[i+1].pr.indefinito == indef) e->part[i_part].n_stato++;
}
e->part[i_part].a=t->n_punti-1;
e->part[i_part].lungh=e->part[i_part].a-e->part[i_part].da+1;
e->n_part=i_part+1;
}

/////////////////////////////////////////////////////////////////////////
//   Tappa_buchi_dist
/////////////////////////////////////////////////////////////////////////
void Tappa_buchi_dist(struct taglio_rett_int huge *t,
                      struct elenco_part *e)
{
float riemp_inizio,riemp_fine,delta;
int ultimo_inizio,ultimo_fine;
int i,j;

for (i=0;i<e->n_part;i++) {
   if (e->part[i].stato) continue;
   // trattamento inizio partizione
   for (j=0;
        (j < e->part[i].lungh) &&
        (t->p[e->part[i].da+j].pr.indefinito);
        j++);
   if (j > 0) {
      riemp_inizio=t->p[e->part[i].da+j].dist_r;
      ultimo_inizio=j;
      for (j=0;j<ultimo_inizio;j++) {
         t->p[e->part[i].da+j].dist_r=riemp_inizio;
         t->p[e->part[i].da+j].pr.indefinito=FALSE;
      }
   }
   // trattamento fine partizione
   for (j=e->part[i].lungh-1;
        (j >= 0) &&
        (t->p[e->part[i].da+j].pr.indefinito);
        j--);
   if (j < e->part[i].lungh-1) {
      riemp_fine=t->p[e->part[i].da+j].dist_r;
      ultimo_fine=j;
      for (j=e->part[i].lungh-1;j>ultimo_fine;j--) {
         t->p[e->part[i].da+j].dist_r=riemp_fine;
         t->p[e->part[i].da+j].pr.indefinito=FALSE;
      }
   }
   // trattamento buchi
   for (j=0;j<e->part[i].lungh;j++) {
      if (t->p[e->part[i].da+j].pr.indefinito) {
         if (!t->p[e->part[i].da+j+1].pr.indefinito) {
            t->p[e->part[i].da+j].pr.indefinito=FALSE;
            t->p[e->part[i].da+j].dist_r=(
               t->p[e->part[i].da+j-1].dist_r +
               t->p[e->part[i].da+j+1].dist_r)/2;
            j++;
         }
         else {
            t->p[e->part[i].da+j].pr.indefinito=FALSE;
            t->p[e->part[i].da+j+1].pr.indefinito=FALSE;
            delta=(t->p[e->part[i].da+j+2].dist_r-
                  t->p[e->part[i].da+j-1].dist_r)/3;
            t->p[e->part[i].da+j].dist_r=
               t->p[e->part[i].da+j-1].dist_r+delta;
            t->p[e->part[i].da+j+1].dist_r=
               t->p[e->part[i].da+j-1].dist_r+2*delta;
            j+=2;
         }
      }
   }
}
}

/////////////////////////////////////////////////////////////////////////
//   Valuta_rumore
/////////////////////////////////////////////////////////////////////////
void Valuta_rumore(struct taglio_rett_int huge *t,   // buchi già attappati
                   struct elenco_part *e,       // già calcolato
                   double huge *rumore)
{
double huge *somma_rumori;
double huge *coeff;
int huge *num_contributi;
BOOL huge *invalido;
int i,j,k,l;
BOOL accettato;
double sqme,prob,rum_att,start,end,delta;

invalido=ivector(0,t->n_punti-1);
somma_rumori=vector(0,t->n_punti-1);
num_contributi=ivector(0,t->n_punti-1);
coeff=vector(0,descr_filtri[0].ord_fitt);
for (i=0;i<t->n_punti;i++) {
   somma_rumori[i]=0.0;
   num_contributi[i]=0;
   invalido[i]=FALSE;
}
for (i=0;i<e->n_part;i++) {
   if (e->part[i].stato) continue;
   if (e->part[i].lungh < descr_filtri[0].lungh_supp) continue;
   for (j=e->part[i].da;
        j<=e->part[i].a-descr_filtri[0].lungh_supp+1;
        j++) {
      Esegui_fitting(t,
                     TRUE,     //BOOL rum_indef,
                     rumore,
                     j,        //int punto_inizio,
                     0,        //int num_filtro,
                     TRUE,     //BOOL avanti,
                     coeff,
                     &sqme,
                     &prob,
                     &accettato);
      rumore[j]=sqme;
   }
   if (e->part[i].lungh >= MINIMO_PER_CORR) {
      for (j=e->part[i].da;
           j+SUPP_CORR_A-1<=e->part[i].a-descr_filtri[0].lungh_supp+1;
           j++) {
         if (!invalido[j+2]) {
            rum_att=rumore[j+2]/RAPP_RUMORE_A;
            if ( (rum_att > rumore[j])   &&
                 (rum_att > rumore[j+4])  )  {
               invalido[j+1]=TRUE;
               invalido[j+2]=TRUE;
               invalido[j+3]=TRUE;
            }
         }
      }
      for (j=e->part[i].da;
           j+SUPP_CORR_B-1<=e->part[i].a-descr_filtri[0].lungh_supp+1;
           j++) {
         if (!invalido[j+4]) {
            rum_att=rumore[j+4]/RAPP_RUMORE_B;
            if ( (rum_att > rumore[j])     &&
                 (rum_att > rumore[j+1])   &&
                 (rum_att > rumore[j+7])   &&
                 (rum_att > rumore[j+8])  )  {
               invalido[j+2]=TRUE;
               invalido[j+3]=TRUE;
               invalido[j+4]=TRUE;
               invalido[j+5]=TRUE;
               invalido[j+6]=TRUE;
            }
         }
      }
      for (j=e->part[i].da;
           j<e->part[i].a-descr_filtri[0].lungh_supp+1;
           j++) {
         if (!invalido[j+1]) continue;
         start=rumore[j];
         for (k=j+1;
              (k<=e->part[i].a) && (invalido[k]);
              k++);
         end=rumore[k];
         delta=(end-start)/(k-j);
         for (l=j+1;l<k;l++)
            rumore[l]=(l-j)*delta+start;
         j=k-1;
      }
   }
   for (j=e->part[i].da;
        j<=e->part[i].a-descr_filtri[0].lungh_supp+1;
        j++) {
      for (k=j;k<j+descr_filtri[0].lungh_supp;k++) {
         somma_rumori[k]+=rumore[j];
         num_contributi[k]++;
      }
   }
   for (j=e->part[i].da;j<=e->part[i].a;j++) {
      rumore[j]=(somma_rumori[j]/num_contributi[j]);
      if (rumore[j] < SOGLIA_MIN_RUMORE) rumore[j]=RUMORE_DI_DEFAULT;
      rumore[j]*=GAUSS_VERSO_UNIF*MARG_SICUR_RUMORE;
   }
}
free_vector(somma_rumori,0);
free_ivector(num_contributi,0);
free_vector(coeff,0);
free_ivector(invalido,0);
}

/////////////////////////////////////////////////////////////////////////
//   Trova_discontinuita
/////////////////////////////////////////////////////////////////////////
void Trova_discontinuita(
                  struct taglio_rett_int huge *t,   // buchi già attappati
                  struct elenco_part *e,            // già calcolato
                  double huge *rumore,                   // già valutato
                  int huge *discontinuita)
{
double huge *coeff_dum;
double sqme,prob;
BOOL accettato,uscire,trov_disc;
int i,j,k,l,lun_supp;

coeff_dum=vector(0,descr_filtri[NUM_FILTRI_GROSS-1].ord_fitt);
for (i=0;i<t->n_punti;i++) discontinuita[i]=0;
for (i=0;i<e->n_part;i++) {
   if (e->part[i].stato) continue;
   for (j=1;j<NUM_FILTRI_GROSS;j++) {
      lun_supp=descr_filtri[j].lungh_supp;
      if (e->part[i].lungh < lun_supp) break;
      for (k=e->part[i].da,uscire=FALSE;
           !uscire;
           k+=lun_supp/2) {
         if (k+lun_supp-1 > e->part[i].a) {
            k=e->part[i].a-lun_supp+1;
            uscire=TRUE;
         }
         Esegui_fitting(t,
                        FALSE,     //BOOL rum_indef,
                        rumore,
                        k,        //int punto_inizio,
                        j,        //int num_filtro,
                        TRUE,     //BOOL avanti,
                        coeff_dum,
                        &sqme,
                        &prob,
                        &accettato);
         if (accettato) {
            for (l=k+lun_supp/2-lun_supp/4;
                 l<=k+lun_supp/2-1+lun_supp/4;
                 l++) {
               if (j-discontinuita[l] <= SOGLIA_CANC_DISC)
                  discontinuita[l]=0;
            }
         }
         else {
            trov_disc=FALSE;
            for (l=k;l<=k+lun_supp-1;l++) {
               if (discontinuita[l] != 0) {
                  trov_disc=TRUE;
                  break;
               }
            }
            if (!trov_disc) {
               discontinuita[k+lun_supp/2-1]=j;
               discontinuita[k+lun_supp/2]=j;
            }
         }
      }
   }
}
free_vector(coeff_dum,0);
}

/*
/////////////////////////////////////////////////////////////////////////
//   Correggi_rumore
/////////////////////////////////////////////////////////////////////////
void Correggi_rumore(struct taglio_rett_int *t,   // buchi già attappati
                     struct elenco_part *e,       // già calcolato
                     double *rumore)
{
int *invalido;
int i,j,k,l;
double start,end,delta,rum_att;

invalido=ivector(0,t->n_punti-1);
for (i=0;i<t->n_punti;i++) invalido[i]=FALSE;
for (i=0;i<e->n_part;i++) {
   if (e->part[i].stato) continue;
   if (e->part[i].lungh < MINIMO_PER_CORR) continue;
   for (j=e->part[i].da;
        j+MINIMO_PER_CORR-1<=e->part[i].a;
        j++) {
      if (invalido[j+3]) continue;
      rum_att=rumore[j+3]/RAPP_RUMORE;
      if ( (rum_att > rumore[j])   &&
           (rum_att > rumore[j+1]) &&
           (rum_att > rumore[j+5]) &&
           (rum_att > rumore[j+6]) )  {
         invalido[j+2]=TRUE;
         invalido[j+3]=TRUE;
         invalido[j+4]=TRUE;
      }
   }
   for (j=e->part[i].da;j<e->part[i].a;j++) {
      if (!invalido[j+1]) continue;
      start=rumore[j];
      for (k=j+1;
           (k<=e->part[i].a) && (invalido[k]);
           k++);
      end=rumore[k];
      delta=(end-start)/(k-j);
      for (l=j+1;l<k;l++)
         rumore[l]=(l-j)*delta+start;
      j=k-1;
   }
}
free_ivector(invalido,0);
}
*/