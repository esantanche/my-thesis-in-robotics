/*
NOME_FILE:FITTIN
PROGETTO:Thesis
AUTORE:Emanuele Maria Santanché
DATA_INIZ:Ott 11'92
FILES DOCUMENTAZIONE:THMODULI.DOC, THGRUPPI.DOC, FITTINDF.DOC
NOMI FUNZIONI:
   Gruppo INIZIA
      Inizializza_filtri()
      Dealloca_filtri()
   Gruppo ESTRAI
      Estrai_segmento()
   Gruppo DOFITT
      Esegui_fitting()

*/


#include "thvarie.h"
#include "thstruct.h"
#include "thprotot.h"
#include "thextern.h"

/////////////////////////////////////////////////////////////////////////
//   Inizializza_filtri
/////////////////////////////////////////////////////////////////////////
void Inizializza_filtri(void)
{
double huge **X;
double huge **Xt;
double huge **XtX;
double huge **XtXi;
int i,j,k,ord,lun;

// i supporti devono essere tutti pari, gli ordini devono essere
// crescenti (descr_filtri[13].ord_fitt deve essere il max)
descr_filtri[ 0].lungh_supp= 4;    descr_filtri[ 0].ord_fitt=1;
descr_filtri[ 1].lungh_supp= 6;    descr_filtri[ 1].ord_fitt=1;
descr_filtri[ 2].lungh_supp= 8;    descr_filtri[ 2].ord_fitt=1;
descr_filtri[ 3].lungh_supp=10;    descr_filtri[ 3].ord_fitt=1;
descr_filtri[ 4].lungh_supp=14;    descr_filtri[ 4].ord_fitt=1;
descr_filtri[ 5].lungh_supp=18;    descr_filtri[ 5].ord_fitt=1;
descr_filtri[ 6].lungh_supp=24;    descr_filtri[ 6].ord_fitt=1;
descr_filtri[ 7].lungh_supp=30;    descr_filtri[ 7].ord_fitt=1;
descr_filtri[ 8].lungh_supp=36;    descr_filtri[ 8].ord_fitt=1;
descr_filtri[ 9].lungh_supp=44;    descr_filtri[ 9].ord_fitt=1;
descr_filtri[10].lungh_supp=52;    descr_filtri[10].ord_fitt=2;
descr_filtri[11].lungh_supp=60;    descr_filtri[11].ord_fitt=2;
descr_filtri[12].lungh_supp=68;    descr_filtri[12].ord_fitt=2;
descr_filtri[13].lungh_supp=76;    descr_filtri[13].ord_fitt=2;

descr_filtri[ 0].soglia=  3/  4.0; descr_filtri[ 0].fil_fine= 0;
descr_filtri[ 1].soglia=  5/  6.0; descr_filtri[ 1].fil_fine= 1;
descr_filtri[ 2].soglia=  7/  8.0; descr_filtri[ 2].fil_fine= 2;
descr_filtri[ 3].soglia=  9/ 10.0; descr_filtri[ 3].fil_fine= 3;
descr_filtri[ 4].soglia= 13/ 14.0; descr_filtri[ 4].fil_fine= 4;
descr_filtri[ 5].soglia= 16/ 18.0; descr_filtri[ 5].fil_fine= 5;
descr_filtri[ 6].soglia= 22/ 24.0; descr_filtri[ 6].fil_fine= 6;
descr_filtri[ 7].soglia= 27/ 30.0; descr_filtri[ 7].fil_fine= 7;
descr_filtri[ 8].soglia= 33/ 36.0; descr_filtri[ 8].fil_fine= 8;
descr_filtri[ 9].soglia= 41/ 44.0; descr_filtri[ 9].fil_fine= 9;
descr_filtri[10].soglia= 47/ 52.0; descr_filtri[10].fil_fine=10;
descr_filtri[11].soglia= 54/ 60.0; descr_filtri[11].fil_fine=11;
descr_filtri[12].soglia= 62/ 68.0; descr_filtri[12].fil_fine=12;
descr_filtri[13].soglia= 69/ 76.0; descr_filtri[13].fil_fine=13;

for (i=0;i<NUM_FILTRI_FINE;i++) {
   ord=descr_filtri[i].ord_fitt;
   lun=descr_filtri[i].lungh_supp;
   descr_filtri[i].filtro=matrix(0,ord,0,lun-1);
   X=matrix(0,lun-1,0,ord);
   Xt=matrix(0,ord,0,lun-1);
   XtX=matrix(0,ord,0,ord);
   XtXi=matrix(0,ord,0,ord);
   for (j=1;j<=ord;j++) X[0][j]=0.0;
   for (j=0;j<lun;j++) X[j][0]=1.0;
   for (j=1;j<lun;j++)
      for (k=1;k<=ord;k++) X[j][k]=pow(j,k);
   Trasposta(X,lun,ord+1,Xt);
   Prod_matr(Xt,ord+1,lun,X,lun,ord+1,XtX);
   Inversa(XtX,ord+1,XtXi);
   Prod_matr(XtXi,ord+1,ord+1,Xt,ord+1,lun,descr_filtri[i].filtro);
   free_matrix(X,0,lun-1,0);
   free_matrix(Xt,0,ord,0);
   free_matrix(XtX,0,ord,0);
   free_matrix(XtXi,0,ord,0);
}
}

/////////////////////////////////////////////////////////////////////////
//   Dealloca_filtri
/////////////////////////////////////////////////////////////////////////
void Dealloca_filtri(void)
{
int i;

for (i=0;i<NUM_FILTRI_FINE;i++)
   free_matrix(descr_filtri[i].filtro,0,descr_filtri[i].ord_fitt,0);
}

/////////////////////////////////////////////////////////////////////////
//   Estrai_segmento
/////////////////////////////////////////////////////////////////////////
void Estrai_segmento(struct taglio_rett_int huge *t,
                     BOOL rum_indef,
                     double huge *rumore,
                     int punto_inizio,
                     int lungh,
                     BOOL avanti,
                     double huge *seg_distanze,
                     double huge *seg_rumore)
{
int i;

if (  ( (avanti)  && (t->n_punti <= (punto_inizio+lungh-1)) ) ||
      ( (!avanti) && (0 > (punto_inizio-lungh+1))           )  )
   Error("Segmento fuori taglio","Estrai_segmento","fittin");
if (avanti) {
   for (i=0;i<lungh;i++)
      seg_distanze[i]=t->p[i+punto_inizio].dist_r;
   if (!rum_indef)
      for (i=0;i<lungh;i++)
         seg_rumore[i]=rumore[i+punto_inizio];
}
else {
   for (i=0;i<lungh;i++)
      seg_distanze[i]=t->p[punto_inizio-i].dist_r;
   if (!rum_indef)
      for (i=0;i<lungh;i++)
         seg_rumore[i]=rumore[punto_inizio-i];
}
}

/////////////////////////////////////////////////////////////////////////
//   Esegui_fitting
/////////////////////////////////////////////////////////////////////////
void Esegui_fitting(struct taglio_rett_int huge *t,
                    BOOL rum_indef,
                    double huge *rumore,
                    int punto_inizio,
                    int num_filtro,
                    BOOL avanti,
                    double huge *coeff,
                    double *sqme,
                    double *prob,
                    BOOL *accettato)
{
int lungh,ord,i;
double huge *seg_distanze;
double huge *seg_rumore;
double huge **mat_distanze;
double huge **mat_coeff;
double num_interni;

if ((num_filtro >= NUM_FILTRI_FINE) || (num_filtro < 0))
   Error("num_filtro invalido","Esegui_fitting","fittin");

lungh=descr_filtri[num_filtro].lungh_supp;
ord=descr_filtri[num_filtro].ord_fitt;
seg_distanze=vector(0,lungh-1);
seg_rumore=vector(0,lungh-1);
Estrai_segmento(t,rum_indef,rumore,punto_inizio,
                lungh,avanti,seg_distanze,seg_rumore);

mat_distanze=matrix(0,lungh-1,0,0);
for (i=0;i<lungh;i++) mat_distanze[i][0]=seg_distanze[i];
mat_coeff=matrix(0,ord,0,0);
Prod_matr(descr_filtri[num_filtro].filtro,ord+1,lungh,
          mat_distanze,lungh,1,mat_coeff);
for (i=0;i<=ord;i++) coeff[i]=mat_coeff[i][0];

*sqme=0.0;
for (i=0;i<lungh;i++)
   *sqme+=pow(Valuta_polinomio(ord,i,coeff)-seg_distanze[i],2);
*sqme=sqrt(*sqme/(lungh-ord-1));

if (rum_indef) {
   free_matrix(mat_distanze,0,lungh-1,0);
   free_matrix(mat_coeff,0,ord,0);
   free_vector(seg_distanze,0);
   free_vector(seg_rumore,0);
   return;
}

num_interni=0;
for (i=0;i<lungh;i++)
   if (fabs(Valuta_polinomio(ord,i,coeff)-seg_distanze[i])
       < seg_rumore[i]) num_interni++;
*prob=num_interni/lungh;
if (*prob >= descr_filtri[num_filtro].soglia)
   *accettato=TRUE;
else
   *accettato=FALSE;
free_matrix(mat_distanze,0,lungh-1,0);
free_matrix(mat_coeff,0,ord,0);
free_vector(seg_distanze,0);
free_vector(seg_rumore,0);
}
