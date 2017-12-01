/*
NOME_FILE:LOCDIS
PROGETTO:Thesis
AUTORE:Emanuele Maria Santanché
DATA_INIZ:Ott 16'92
FILES DOCUMENTAZIONE:THMODULI.DOC, THGRUPPI.DOC, LOCDISDF.DOC
NOMI FUNZIONI:
   Gruppo LOCBAS
      Localizza_una_discontinuita()
      Partiziona_accettati()              FATT_SOGLIA_LUNGH_PATT_PART
*/


#include "thvarie.h"
#include "thstruct.h"
#include "thprotot.h"
#include "thextern.h"

/////////////////////////////////////////////////////////////////////////
//   Localizza_una_discontinuita
/////////////////////////////////////////////////////////////////////////
void Localizza_una_discontinuita(struct taglio_rett_int huge *t,
                                 struct elenco_part *e,
                                 double huge *rumore,
                                 int pos_disc,
                                 int fil_disc,
                                 int *tipo_disc,
                                 int *pos_fin_disc,
                                 int *filtro_fin,
                                 double *valore_disc,
                                 double huge *coeff_dx,
                                 double huge *coeff_sx)
{
double huge *prob_sx;
double huge *prob_dx;
double huge *prob_compl;
double huge *err_fit_sx;
double huge *err_fit_dx;
double huge *coeff_fit;
double huge **coeff_memo_sx;
double huge **coeff_memo_dx;
int huge *acc_sx;
int huge *acc_dx;
int huge *acc_compl;
double rum_dx,rum_sx,salto,angolo,soglia_salto,soglia_angolo,sqme,prob,
       valore_memo_salto,valore_memo_snr_salto,valore_memo_angolo,
       valore_memo_snr_angolo,valore_max_prob_salto,valore_max_prob_angolo;
BOOL ok_pos_disc,disc_non_trovata,
     c_e_salto,c_e_angolo,accettato,assegna_salto;
int part_disc,i,j,p_da,p_a,fil_disc_fine,fil_di_part,filtro,
    lun_supp,punto_partenza_dx,punto_partenza_sx,punto_arrivo_dx,
    punto_arrivo_sx,pif,pos_disc_trov_salto,ultimo_filtro,conta_punti_acc,
    pos_disc_trov_angolo,min_pos_fin_disc,max_pos_fin_disc,max_ord_fitt,
    conta_punti_disc;

ok_pos_disc=FALSE;
for (i=0;i<e->n_part;i++) {
   if (e->part[i].stato) continue;
   if ((pos_disc >= e->part[i].da) && (pos_disc <= e->part[i].a)) {
      part_disc=i;
      ok_pos_disc=TRUE;
   }
}
if (!ok_pos_disc)
   Error("Punto indefinito","Localizza_una_discontinuita","locdis");
p_da=e->part[part_disc].da;
p_a=e->part[part_disc].a;

// individuo i filtri da usare per primo e per ultimo
fil_disc_fine=descr_filtri[fil_disc].fil_fine;
if (fil_disc_fine > SOGLIA_FILTRI_GRANDI)  {
   fil_di_part=fil_disc_fine+PRIMO_FILTRO_GRANDI;
   ultimo_filtro=fil_disc_fine+ULTIMO_FILTRO_GRANDI;
}
else {
   fil_di_part=fil_disc_fine+PRIMO_FILTRO_PICCOLI;
   ultimo_filtro=fil_disc_fine+ULTIMO_FILTRO_PICCOLI;
}
if (ultimo_filtro>=NUM_FILTRI_FINE) ultimo_filtro=NUM_FILTRI_FINE-1;
if (e->part[part_disc].lungh < 2*descr_filtri[fil_disc_fine].lungh_supp) {
   *tipo_disc=NON_TROVATA;
   return;
}

max_ord_fitt=descr_filtri[NUM_FILTRI_FINE-1].ord_fitt;

prob_dx=vector(0,t->n_punti-1);
prob_sx=vector(0,t->n_punti-1);
prob_compl=vector(0,t->n_punti-1);
err_fit_dx=vector(0,t->n_punti-1);
err_fit_sx=vector(0,t->n_punti-1);
acc_dx=ivector(0,t->n_punti-1);
acc_sx=ivector(0,t->n_punti-1);
acc_compl=ivector(0,t->n_punti-1);
coeff_memo_dx=matrix(0,max_ord_fitt,0,t->n_punti-1);
coeff_memo_sx=matrix(0,max_ord_fitt,0,t->n_punti-1);
coeff_fit=vector(0,max_ord_fitt);
for (i=0;i<=max_ord_fitt;i++) {
   coeff_fit[i]=0.0;
   for (j=0;j<t->n_punti;j++) {
	   coeff_memo_dx[i][j]=0.0;
      coeff_memo_sx[i][j]=0.0;
	}
}
// inizio del ciclo che usa diversi filtri in successione per trovare la
// discontinuità

disc_non_trovata=TRUE;
max_pos_fin_disc=0;
min_pos_fin_disc=NUM_MAX_PUNTI_INT;
for (filtro=ultimo_filtro;
     (filtro>=fil_di_part) && (filtro<NUM_FILTRI_FINE);
     filtro--) {
   printf("\n   Filtro n.%2d ",filtro);
   for (i=0;i<t->n_punti;i++) {
      prob_dx[i]=-1.0;
      prob_sx[i]=-1.0;
      prob_compl[i]=-1.0;
      acc_dx[i]=INDEF;
      acc_sx[i]=INDEF;
      acc_compl[i]=INDEF;
   }
   lun_supp=descr_filtri[filtro].lungh_supp;
   punto_partenza_dx=pos_disc+2*lun_supp;
   if (punto_partenza_dx+lun_supp-1 > p_a)
      punto_partenza_dx=p_a-lun_supp+1;
   punto_arrivo_dx=pos_disc-2*lun_supp;
   if (punto_arrivo_dx < p_da)
      punto_arrivo_dx=p_da;
   for (pif=punto_partenza_dx;pif>=punto_arrivo_dx;pif--) {
      Esegui_fitting(t,FALSE,rumore,pif,filtro,TRUE,coeff_fit,
                     &sqme,&prob,&accettato);
      prob_dx[pif]=prob;
      acc_dx[pif]=accettato;
      err_fit_dx[pif]=sqme;
      for (j=0;j<=max_ord_fitt;j++)
         coeff_memo_dx[j][pif]=coeff_fit[j];
   }
   punto_partenza_sx=pos_disc-2*lun_supp;
   if (punto_partenza_sx-lun_supp+1 < p_da)
      punto_partenza_sx=p_da+lun_supp-1;
   punto_arrivo_sx=pos_disc+2*lun_supp;
   if (punto_arrivo_sx >= p_a)
      punto_arrivo_sx=p_a-1;
   for (pif=punto_partenza_sx;pif<=punto_arrivo_sx;pif++) {
      Esegui_fitting(t,FALSE,rumore,pif,filtro,FALSE,coeff_fit,
                     &sqme,&prob,&accettato);
      prob_sx[pif+1]=prob;
      acc_sx[pif+1]=accettato;
      err_fit_sx[pif+1]=sqme;
      for (j=0;j<=max_ord_fitt;j++)
         coeff_memo_sx[j][pif+1]=coeff_fit[j];
   }
   for (i=p_da;i<=p_a;i++) {
      if ((acc_dx[i] != INDEF) && (acc_sx[i] != INDEF)) {
         acc_compl[i]=(acc_dx[i] && acc_sx[i]);
         prob_compl[i]=prob_dx[i]*prob_sx[i];
      }
   }
   for (i=p_da;i<=p_a;i++)
      if (acc_compl[i] != INDEF) break;
   if (i > p_a) {
      printf(" Tutti indefiniti");
      continue;
   }

   valore_max_prob_salto=-1.0;
   valore_max_prob_angolo=-1.0;
   valore_memo_salto=0.0;
   valore_memo_angolo=0.0;
   pos_disc_trov_salto=-1;
   pos_disc_trov_angolo=-1;
   conta_punti_acc=0;
   conta_punti_disc=0;
   for (j=p_da;j<=p_a;j++) {
      if ((acc_compl[j] == INDEF) || (acc_compl[j] == FALSE)) continue;
      conta_punti_acc++;
      // rumore destro e sinistro
      rum_dx=err_fit_dx[j];
      if (rum_dx < SOGLIA_MIN_RUMORE) rum_dx=RUMORE_DI_DEFAULT;
      rum_dx*=GAUSS_VERSO_UNIF*MARG_SICUR_RUMORE;
      rum_sx=err_fit_sx[j];
      if (rum_sx < SOGLIA_MIN_RUMORE) rum_sx=RUMORE_DI_DEFAULT;
      rum_sx*=GAUSS_VERSO_UNIF*MARG_SICUR_RUMORE;
      // test discontinuita a salto
      salto=coeff_memo_dx[0][j]-coeff_memo_sx[0][j];
      // per angolo si fa una somma di coeff012 ... perchè i due
      // coeff. sono opposti quando indicano la stessa inclinazione
      angolo=coeff_memo_dx[1][j]+coeff_memo_sx[1][j];
      soglia_angolo=2*(rum_dx+rum_sx)/lun_supp;
      soglia_salto=rum_dx+rum_sx;
      c_e_salto=(fabs(salto) >= (soglia_salto*SICUR_SALTO));
      c_e_angolo=(fabs(angolo) >= (soglia_angolo*SICUR_ANGOLO));
      if (!c_e_salto && !c_e_angolo) continue;
      conta_punti_disc++;
      if (c_e_salto) {    //Xfabs(salto) > valore_max_salto
         if (prob_compl[j] > valore_max_prob_salto) {
            valore_max_prob_salto=prob_compl[j];
            pos_disc_trov_salto=j;
            //Xvalore_max_salto=fabs(salto);
            valore_memo_salto=salto;
            valore_memo_snr_salto=fabs(salto)/fabs(soglia_salto);
         }
      }
      else {  //Xfabs(angolo) > valore_max_angolo
         if (prob_compl[j] > valore_max_prob_angolo) {
            valore_max_prob_angolo=prob_compl[j];
            pos_disc_trov_angolo=j;
            //Xvalore_max_angolo=fabs(angolo);
            valore_memo_angolo=angolo;
            valore_memo_snr_angolo=fabs(angolo)/fabs(soglia_angolo);
         }
      }
   }
   printf("a %2d d %2d",conta_punti_acc,conta_punti_disc);
   if ((pos_disc_trov_salto == -1) && (pos_disc_trov_angolo == -1)) {
      printf(" Non trovata");
      continue;
   }
   if ((pos_disc_trov_salto != -1) && (pos_disc_trov_angolo == -1))
      assegna_salto=TRUE;
   if ((pos_disc_trov_salto == -1) && (pos_disc_trov_angolo != -1))
      assegna_salto=FALSE;
   if ((pos_disc_trov_salto != -1) && (pos_disc_trov_angolo != -1)) {
      if (valore_memo_snr_salto > valore_memo_snr_angolo)
         assegna_salto=TRUE;
      else
         assegna_salto=FALSE;
   }
   if (assegna_salto) {
      *tipo_disc=SALTO;
      *valore_disc=valore_memo_salto;
      *pos_fin_disc=pos_disc_trov_salto;
      printf(" Trovato salto %d %6.2lf ",pos_disc_trov_salto,
                                        valore_memo_salto);
      printf("(angolo: %d %7.4lf) ",pos_disc_trov_angolo,
                                   valore_memo_angolo);
   }
   else {
      *tipo_disc=ANGOLO;
      *valore_disc=valore_memo_angolo;
      *pos_fin_disc=pos_disc_trov_angolo;
      printf(" Trovato angolo %d %7.4lf ",pos_disc_trov_angolo,
                                         valore_memo_angolo);
      printf("(salto: %d %6.2lf) ",pos_disc_trov_salto,
                                  valore_memo_salto);
   }
   if (*pos_fin_disc > max_pos_fin_disc) max_pos_fin_disc=*pos_fin_disc;
   if (*pos_fin_disc < min_pos_fin_disc) min_pos_fin_disc=*pos_fin_disc;
   *filtro_fin=filtro;
   for (j=0;j<=descr_filtri[NUM_FILTRI_FINE-1].ord_fitt;j++) {
      coeff_sx[j]=coeff_memo_sx[j][*pos_fin_disc];
      coeff_dx[j]=coeff_memo_dx[j][*pos_fin_disc];
   }
   if (disc_non_trovata) {
      disc_non_trovata=FALSE;
      break;
   }
}
if (disc_non_trovata)
   *tipo_disc=NON_TROVATA;
/*
else
   if ((max_pos_fin_disc-min_pos_fin_disc) >
       8000 descr_filtri[*filtro_fin].lungh_supp ) {
       *tipo_disc=NON_TROVATA;
       printf("\n      Rigettata perchè distanza disc = %d",
              (max_pos_fin_disc-min_pos_fin_disc));
   }
*/

free_vector(prob_dx,0);
free_vector(prob_sx,0);
free_vector(prob_compl,0);
free_vector(err_fit_dx,0);
free_vector(err_fit_sx,0);
free_ivector(acc_dx,0);
free_ivector(acc_sx,0);
free_ivector(acc_compl,0);
free_matrix(coeff_memo_dx,0,descr_filtri[NUM_FILTRI_FINE-1].ord_fitt,0);
free_matrix(coeff_memo_sx,0,descr_filtri[NUM_FILTRI_FINE-1].ord_fitt,0);
free_vector(coeff_fit,0);
} // Localizza_una_discontinuita

/*
/////////////////////////////////////////////////////////////////////////
//   Localizza_una_discontinuita     VECCHIO
/////////////////////////////////////////////////////////////////////////
void Localizza_una_discontinuita(struct taglio_rett_int huge *t,
                                 struct elenco_part *e,
                                 double huge *rumore,
                                 int pos_disc,
                                 int fil_disc,
                                 int *tipo_disc,
                                 int *pos_fin_disc,
                                 int *filtro_fin,
                                 double *valore_disc,
                                 double huge *coeff_dx,
                                 double huge *coeff_sx)
{
double huge *prob_sx;
double huge *prob_dx;
double huge *err_fit_sx;
double huge *err_fit_dx;
double huge *coeff_fit;
double huge **coeff_memo_sx;
double huge **coeff_memo_dx;
int huge *acc_sx;
int huge *acc_dx;
int huge *acc_compl;
double max_prob_in_disc,temp,rum_dx,rum_sx,salto,angolo,
       soglia_angolo,sqme,prob;
BOOL ok_pos_disc,disc_non_trovata,no_pattern_part,
     c_e_salto,c_e_angolo,accettato;
int part_disc,i,j,p_da,p_a,fil_disc_fine,fil_di_part,filtro,
    lun_supp,punto_partenza_dx,punto_partenza_sx,punto_arrivo_dx,
    punto_arrivo_sx,pif,p_da_disc,p_a_disc,
    pos_disc_trov,pos_disc_trov_da,pos_disc_trov_a;
struct elenco_part elenc_part_accett;

ok_pos_disc=FALSE;
for (i=0;i<e->n_part;i++) {
   if (e->part[i].stato) continue;
   if ((pos_disc >= e->part[i].da) && (pos_disc <= e->part[i].a)) {
      part_disc=i;
      ok_pos_disc=TRUE;
   }
}
if (!ok_pos_disc)
   Error("Punto indefinito","Localizza_una_discontinuita","locdis");
p_da=e->part[part_disc].da;
p_a=e->part[part_disc].a;

// individuo il filtro da usare per primo
fil_disc_fine=descr_filtri[fil_disc].fil_fine;
if (fil_disc_fine > FILTRI_IN_MENO)
   fil_di_part=fil_disc_fine-FILTRI_IN_MENO;
else
   fil_di_part=1;
if (e->part[part_disc].lungh < 2*descr_filtri[fil_disc_fine].lungh_supp) {
   *tipo_disc=NON_TROVATA;
   return;
}

prob_dx=vector(0,t->n_punti-1);
prob_sx=vector(0,t->n_punti-1);
err_fit_dx=vector(0,t->n_punti-1);
err_fit_sx=vector(0,t->n_punti-1);
acc_dx=ivector(0,t->n_punti-1);
acc_sx=ivector(0,t->n_punti-1);
acc_compl=ivector(0,t->n_punti-1);
coeff_memo_dx=matrix(0,descr_filtri[NUM_FILTRI_FINE-1].ord_fitt,
                     0,t->n_punti-1);
coeff_memo_sx=matrix(0,descr_filtri[NUM_FILTRI_FINE-1].ord_fitt,
                     0,t->n_punti-1);
coeff_fit=vector(0,descr_filtri[NUM_FILTRI_FINE-1].ord_fitt);
for (i=0;i<t->n_punti;i++) {
   prob_dx[i]=-1.0;
   prob_sx[i]=-1.0;
   acc_dx[i]=INDEF;
   acc_sx[i]=INDEF;
   acc_compl[i]=INDEF;
}

// inizio del ciclo che usa diversi filtri in successione per trovare la
// discontinuità
for (filtro=fil_di_part;
     (filtro<=fil_disc_fine+FILTRI_IN_PIU) && (filtro<NUM_FILTRI_FINE);
     filtro++) {
   printf(" fil=%d ",filtro); //X
   disc_non_trovata=FALSE;
   lun_supp=descr_filtri[filtro].lungh_supp;
   //ord_fit=descr_filtri[filtro].ord_fitt;
   punto_partenza_dx=pos_disc+2*lun_supp;
   if (punto_partenza_dx+lun_supp-1 > p_a)
      punto_partenza_dx=p_a-lun_supp+1;
   punto_arrivo_dx=pos_disc-2*lun_supp;
   if (punto_arrivo_dx < p_da)
      punto_arrivo_dx=p_da;
   for (pif=punto_partenza_dx;pif>=punto_arrivo_dx;pif--) {
      Esegui_fitting(t,FALSE,rumore,pif,filtro,TRUE,coeff_fit,
                     &sqme,&prob,&accettato);
      prob_dx[pif]=prob;
      acc_dx[pif]=accettato;
      err_fit_dx[pif]=sqme;
      for (j=0;j<=descr_filtri[NUM_FILTRI_FINE-1].ord_fitt;j++)
         coeff_memo_dx[j][pif]=coeff_fit[j];
   }
   punto_partenza_sx=pos_disc-2*lun_supp;
   if (punto_partenza_sx-lun_supp+1 < p_da)
      punto_partenza_sx=p_da+lun_supp-1;
   punto_arrivo_sx=pos_disc+2*lun_supp;
   if (punto_arrivo_sx >= p_a)
      punto_arrivo_sx=p_a-1;
   for (pif=punto_partenza_sx;pif<=punto_arrivo_sx;pif++) {
      Esegui_fitting(t,FALSE,rumore,pif,filtro,FALSE,coeff_fit,
                     &sqme,&prob,&accettato);
      prob_sx[pif+1]=prob;
      acc_sx[pif+1]=accettato;
      err_fit_sx[pif+1]=sqme;
      for (j=0;j<=descr_filtri[NUM_FILTRI_FINE-1].ord_fitt;j++)
         coeff_memo_sx[j][pif]=coeff_fit[j];
   }
   for (i=p_da;i<=p_a;i++) {
      if ((acc_dx[i] == INDEF) || (acc_sx[i] == INDEF))
         acc_compl[i]=INDEF;
      else
         acc_compl[i]=(acc_dx[i] && acc_sx[i]);
   }
   for (i=p_da;i<=p_a;i++)
      if (acc_compl[i] != INDEF) break;
   if (i > p_a) {
      printf("tutti indef "); //X
      disc_non_trovata=TRUE;
      continue;
   }
   Partiziona_accettati(acc_compl,p_da,p_a,&elenc_part_accett);
   if (elenc_part_accett.n_part < 3) {
      printf("n_part<3 "); //X
      disc_non_trovata=TRUE;
      continue;
   }
   no_pattern_part=TRUE;
   for (i=1;i<elenc_part_accett.n_part-1;i++) {
      if ( (elenc_part_accett.part[i].stato == TRUE) &&
           (elenc_part_accett.part[i-1].stato == FALSE) &&
           (elenc_part_accett.part[i+1].stato == FALSE) ) {
         if (elenc_part_accett.part[i].lungh+
             elenc_part_accett.part[i-1].lungh+
             elenc_part_accett.part[i+1].lungh <
             FATT_SOGLIA_LUNGH_PATT_PART*lun_supp)
            continue;
         else {
            no_pattern_part=FALSE;
            break;
         }
      }
   }
   if (no_pattern_part) {
      printf("no_patt_part "); //X
      disc_non_trovata=TRUE;
      continue;
   }
   //part_con_disc=i;
   p_da_disc=elenc_part_accett.part[i].da;
   p_a_disc=elenc_part_accett.part[i].a;
   //lungh_part_disc=elenc_part_accett.part[i].lungh;
   max_prob_in_disc=0;
   pos_disc_trov=-1;
   for (i=p_da_disc;i<=p_a_disc;i++) {
      if ((temp=prob_dx[i]*prob_sx[i]) > max_prob_in_disc) {
         max_prob_in_disc=temp;
         pos_disc_trov_da=i;
      }
   }
   pos_disc_trov_a=pos_disc_trov_da;
   for (i=pos_disc_trov_da+1;i<=p_a_disc;i++) {
      if (!Lz(prob_dx[i]*prob_sx[i]-max_prob_in_disc)) {
         pos_disc_trov_a=i-1;
         break;
      }
   }
   pos_disc_trov=(pos_disc_trov_da+pos_disc_trov_a)/2;
   // rumore destro e sinistro
   rum_dx=err_fit_dx[pos_disc_trov];
   if (rum_dx < SOGLIA_MIN_RUMORE) rum_dx=RUMORE_DI_DEFAULT;
   rum_dx*=GAUSS_VERSO_UNIF*MARG_SICUR_RUMORE;
   rum_sx=err_fit_sx[pos_disc_trov];
   if (rum_sx < SOGLIA_MIN_RUMORE) rum_sx=RUMORE_DI_DEFAULT;
   rum_sx*=GAUSS_VERSO_UNIF*MARG_SICUR_RUMORE;
   // test discontinuita a salto
   salto=coeff_memo_dx[0][pos_disc_trov]-coeff_memo_sx[0][pos_disc_trov];
   // per angolo si fa una somma di coeff012 ... perchè i due
   // coeff. sono opposti quando indicano la stessa inclinazione
   angolo=coeff_memo_dx[1][pos_disc_trov]+coeff_memo_sx[1][pos_disc_trov];
   soglia_angolo=2*(rum_dx+rum_sx)/lun_supp;
   c_e_salto=(fabs(salto) >= (rum_dx+rum_sx)*SICUR_SALTO);
   c_e_angolo=(fabs(angolo) >= soglia_angolo*SICUR_ANGOLO);
   printf("\nsal=%lf ang=%lf cesal=%d ceang=%d\n",
          salto,angolo,c_e_salto,c_e_angolo);   //X
   if (!c_e_salto && !c_e_angolo) {
      printf(" nosal&noang "); //X
      disc_non_trovata=TRUE;
      continue;
   }
   if (c_e_salto) {
      *tipo_disc=SALTO;
      *valore_disc=salto;
   }
   else {
      *tipo_disc=ANGOLO;
      *valore_disc=angolo;
   }
   *pos_fin_disc=pos_disc_trov;
   *filtro_fin=filtro;
   for (j=0;j<=descr_filtri[NUM_FILTRI_FINE-1].ord_fitt;j++) {
      coeff_sx[j]=coeff_memo_sx[j][pos_disc_trov];
      coeff_dx[j]=coeff_memo_dx[j][pos_disc_trov];
   }
}
if (disc_non_trovata) *tipo_disc=NON_TROVATA;

free_vector(prob_dx,0);
free_vector(prob_sx,0);
free_vector(err_fit_dx,0);
free_vector(err_fit_sx,0);
free_ivector(acc_dx,0);
free_ivector(acc_sx,0);
free_ivector(acc_compl,0);
free_matrix(coeff_memo_dx,0,descr_filtri[NUM_FILTRI_FINE-1].ord_fitt,0);
free_matrix(coeff_memo_sx,0,descr_filtri[NUM_FILTRI_FINE-1].ord_fitt,0);
free_vector(coeff_fit,0);
} // Localizza_una_discontinuita
*/
/*
/////////////////////////////////////////////////////////////////////////
//   Partiziona_accettati
/////////////////////////////////////////////////////////////////////////
void Partiziona_accettati(BOOL huge *acc,int inizio,int fine,
                          struct elenco_part *e)
{
BOOL accett;
int i_part,i,n_punti;

for (i=inizio;i<=fine;i++)
   if (acc[i] != INDEF) break;
inizio=i;
for (i=fine;i>=inizio;i--)
   if (acc[i] != INDEF) break;
fine=i;
n_punti=fine-inizio+1;
printf("pa%d",n_punti);//X
if (n_punti < 3) {
   e->n_part=0;
   return;
}
accett=acc[inizio];
i_part=0;
e->part[i_part].da=inizio;
e->part[i_part].a=inizio;
e->part[i_part].stato=accett;
e->part[i_part].lungh=1;
e->part[i_part].n_stato=1;
for (i=inizio+1;;i++) {
   for (;(acc[i] == accett) &&
         (i<=fine);i++) {
      e->part[i_part].a++;
      e->part[i_part].lungh++;
      e->part[i_part].n_stato++;
   }
   if (i+2>=fine+1) break;
   if ((acc[i+1] != accett) &&
       (acc[i+2] != accett)) {
      if (e->part[i_part].lungh < 3) {
         e->part[i_part].stato=!e->part[i_part].stato;
         accett=!accett;
         e->part[i_part].n_stato=1;
      }
      else {
         accett=!accett;
         i_part++;
         e->part[i_part].da=i;
         e->part[i_part].a=i-1;
         e->part[i_part].lungh=0;
         e->part[i_part].stato=accett;
         e->part[i_part].n_stato=1;
      }
   }
   e->part[i_part].a++;
   e->part[i_part].lungh++;
}
if (i<=fine) {
   if (acc[i] == accett) e->part[i_part].n_stato++;
   if (i+1 <= fine)
      if (acc[i+1] == accett) e->part[i_part].n_stato++;
}
e->part[i_part].a=fine;
e->part[i_part].lungh=e->part[i_part].a-e->part[i_part].da+1;
e->n_part=i_part+1;
}  // Partiziona_accettati
*/
