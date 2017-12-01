/*
NOME_FILE:MATEMA
PROGETTO:Thesis
AUTORE:Emanuele Maria Santanché
DATA_INIZ:Ott 11'92
FILES DOCUMENTAZIONE:THMODULI.DOC, THGRUPPI.DOC, MATEMADF.DOC
NOMI FUNZIONI:
   Gruppo OPEMAT
      Prod_matr()
   Gruppo POLINO
      Valuta_polinomio()
   Gruppo SUPCOM
      Mnewt()
      Rotazione_quaternionica()
*/

#include "thvarie.h"
#include "thstruct.h"
#include "thprotot.h"
#include "thextern.h"

/////////////////////////////////////////////////////////////////////////
//   Prod_matr
/////////////////////////////////////////////////////////////////////////
void Prod_matr(double huge **m1,int r1,int c1,
               double huge **m2,int r2,int c2,
               double huge **mr)
{
double sum;
int i,j,k;

if (r2 != c1)
   Error("Matrici non moltiplicabili","Prod_matr","matema");
for (i=0;i<r1;i++) {
   for (j=0;j<c2;j++) {
      sum=0.0;
      for (k=0;k<c1;k++) {
         sum += m1[i][k]*m2[k][j];
      }
      mr[i][j]=sum;
   }
}
}

/////////////////////////////////////////////////////////////////////////
//   Trasposta
/////////////////////////////////////////////////////////////////////////
void Trasposta(double huge **m,int r,int c,
               double huge **mr)
{
int i,j;

for (i=0;i<r;i++)
   for (j=0;j<c;j++) mr[j][i]=m[i][j];
}

/////////////////////////////////////////////////////////////////////////
//   Inversa
/////////////////////////////////////////////////////////////////////////
void Inversa(double huge **m,int n,double huge **mr)
{
int i,j;
double d;
int huge *indx;
BOOL singolare;
double huge **y;
double huge *col;

y=matrix(0,n-1,0,n-1);
for (i=0;i<n;i++)
   for (j=0;j<n;j++) y[i][j]=m[i][j];
indx=ivector(0,n-1);
col=vector(0,n-1);
singolare=ludcmp(y,n,indx,&d);
if (singolare)
   Error("Matrice singolare","Inversa","matema");
for (j=0;j<n;j++) {
   for (i=0;i<n;i++) col[i]=0.0;
   col[j]=1.0;
   lubksb(y,n,indx,col);
   for (i=0;i<n;i++) mr[i][j]=col[i];
}
free_ivector(indx,0);
free_vector(col,0);
free_matrix(y,0,n-1,0);
}

/////////////////////////////////////////////////////////////////////////
//   Valuta_polinomio
/////////////////////////////////////////////////////////////////////////
double Valuta_polinomio(int ord,double x,double huge *coeff)
{
double ris,xi;
int i;

if ((ord > 3) || (ord < 1))
   Error("ord>3","Valuta_polinomio","matema");
ris=coeff[0];
xi=x;
for (i=1;i<=ord;i++) {
   ris += xi*coeff[i];
   xi*=x;
}
return(ris);
}

/////////////////////////////////////////////////////////////////////////
//   Mnewt
/////////////////////////////////////////////////////////////////////////
void Mnewt(int ntrial, double huge *x, int n, float tolx, float tolf,
           struct vettore *s1,struct vettore *s2,struct vettore *s3,
           int die)
{
int huge *indx;
int k,i;
double errx,errf,d;
double huge *bet;
double huge **alpha;

indx=ivector(0,n-1);
bet=vector(0,n-1);
alpha=matrix(0,n-1,0,n-1);
for (k=1;k<=ntrial;k++) {
   Rotazione_quaternionica(x,alpha,bet,s1,s2,s3,die);
   errf=0.0;
   for (i=0;i<n;i++) errf += fabs(bet[i]);
   if (errf <= tolf) {
	   free_matrix(alpha,0,n-1,0);
      free_vector(bet,0);
      free_ivector(indx,0);
      printf("Mnewt esce da f iteraz. %d\n",k);
      return;
	}
   ludcmp(alpha,n,indx,&d);
   lubksb(alpha,n,indx,bet);
   errx=0.0;
   for (i=0;i<n;i++) {
       errx+=fabs(bet[i]);
       x[i]+=bet[i];
   }
   if (errx <= tolx) {
	   free_matrix(alpha,0,n-1,0);
      free_vector(bet,0);
      free_ivector(indx,0);
      printf("Mnewt esce da x iteraz. %d\n",k);
      return;
	}
}
free_matrix(alpha,0,n-1,0);
free_vector(bet,0);
free_ivector(indx,0);
printf("Mnewt iteraz. %d\n",k);
return;
}

/////////////////////////////////////////////////////////////////////////
//   Rotazione_quaternionica
/////////////////////////////////////////////////////////////////////////
void Rotazione_quaternionica(double huge *q,
                             double huge **alpha,
                             double huge *bet,
                             struct vettore *s1,
                             struct vettore *s2,
                             struct vettore *s3, int die)
{
double huge **A;

A=matrix(0,3,0,3);

// Prima equazione
A[0][0]=DIE[die].n1.a*s1->a+DIE[die].n1.b*s1->b+DIE[die].n1.c*s1->c;
A[0][1]=-DIE[die].n1.c*s1->b+DIE[die].n1.b*s1->c;
A[0][2]=DIE[die].n1.c*s1->a-DIE[die].n1.a*s1->c;
A[0][3]=-DIE[die].n1.b*s1->a+DIE[die].n1.a*s1->b;
A[1][0]=A[0][1];
A[1][1]=DIE[die].n1.a*s1->a-DIE[die].n1.b*s1->b-DIE[die].n1.c*s1->c;
A[1][2]=DIE[die].n1.b*s1->a+DIE[die].n1.a*s1->b;
A[1][3]=DIE[die].n1.c*s1->a+DIE[die].n1.a*s1->c;
A[2][0]=A[0][2];
A[2][1]=A[1][2];
A[2][2]=-DIE[die].n1.a*s1->a+DIE[die].n1.b*s1->b-DIE[die].n1.c*s1->c;
A[2][3]=DIE[die].n1.c*s1->b+DIE[die].n1.b*s1->c;
A[3][0]=A[0][3];
A[3][1]=A[1][3];
A[3][2]=A[2][3];
A[3][3]=-DIE[die].n1.a*s1->a-DIE[die].n1.b*s1->b+DIE[die].n1.c*s1->c;

alpha[0][0]=2*(q[0]*A[0][0]+q[1]*A[0][1]+q[2]*A[0][2]+q[3]*A[0][3]);
alpha[0][1]=2*(q[0]*A[1][0]+q[1]*A[1][1]+q[2]*A[1][2]+q[3]*A[1][3]);
alpha[0][2]=2*(q[0]*A[2][0]+q[1]*A[2][1]+q[2]*A[2][2]+q[3]*A[2][3]);
alpha[0][3]=2*(q[0]*A[3][0]+q[1]*A[3][1]+q[2]*A[3][2]+q[3]*A[3][3]);

bet[0]=-( pow(q[0],2)*A[0][0]+pow(q[1],2)*A[1][1]+
          pow(q[2],2)*A[2][2]+pow(q[3],2)*A[3][3]+
          2*( q[0]*q[1]*A[0][1]+q[0]*q[2]*A[0][2]+q[0]*q[3]*A[0][3]+
              q[1]*q[2]*A[1][2]+q[1]*q[3]*A[1][3]+q[2]*q[3]*A[2][3] ) );

// Seconda equazione
A[0][0]=DIE[die].n2.a*s2->a+DIE[die].n2.b*s2->b+DIE[die].n2.c*s2->c;
A[0][1]=-DIE[die].n2.c*s2->b+DIE[die].n2.b*s2->c;
A[0][2]=DIE[die].n2.c*s2->a-DIE[die].n2.a*s2->c;
A[0][3]=-DIE[die].n2.b*s2->a+DIE[die].n2.a*s2->b;
A[1][0]=A[0][1];
A[1][1]=DIE[die].n2.a*s2->a-DIE[die].n2.b*s2->b-DIE[die].n2.c*s2->c;
A[1][2]=DIE[die].n2.b*s2->a+DIE[die].n2.a*s2->b;
A[1][3]=DIE[die].n2.c*s2->a+DIE[die].n2.a*s2->c;
A[2][0]=A[0][2];
A[2][1]=A[1][2];
A[2][2]=-DIE[die].n2.a*s2->a+DIE[die].n2.b*s2->b-DIE[die].n2.c*s2->c;
A[2][3]=DIE[die].n2.c*s2->b+DIE[die].n2.b*s2->c;
A[3][0]=A[0][3];
A[3][1]=A[1][3];
A[3][2]=A[2][3];
A[3][3]=-DIE[die].n2.a*s2->a-DIE[die].n2.b*s2->b+DIE[die].n2.c*s2->c;

alpha[1][0]=2*(q[0]*A[0][0]+q[1]*A[0][1]+q[2]*A[0][2]+q[3]*A[0][3]);
alpha[1][1]=2*(q[0]*A[1][0]+q[1]*A[1][1]+q[2]*A[1][2]+q[3]*A[1][3]);
alpha[1][2]=2*(q[0]*A[2][0]+q[1]*A[2][1]+q[2]*A[2][2]+q[3]*A[2][3]);
alpha[1][3]=2*(q[0]*A[3][0]+q[1]*A[3][1]+q[2]*A[3][2]+q[3]*A[3][3]);

bet[1]=-( pow(q[0],2)*A[0][0]+pow(q[1],2)*A[1][1]+
          pow(q[2],2)*A[2][2]+pow(q[3],2)*A[3][3]+
          2*( q[0]*q[1]*A[0][1]+q[0]*q[2]*A[0][2]+q[0]*q[3]*A[0][3]+
              q[1]*q[2]*A[1][2]+q[1]*q[3]*A[1][3]+q[2]*q[3]*A[2][3] ) );

// Terza equazione
A[0][0]=DIE[die].n3.a*s3->a+DIE[die].n3.b*s3->b+DIE[die].n3.c*s3->c;
A[0][1]=-DIE[die].n3.c*s3->b+DIE[die].n3.b*s3->c;
A[0][2]=DIE[die].n3.c*s3->a-DIE[die].n3.a*s3->c;
A[0][3]=-DIE[die].n3.b*s3->a+DIE[die].n3.a*s3->b;
A[1][0]=A[0][1];
A[1][1]=DIE[die].n3.a*s3->a-DIE[die].n3.b*s3->b-DIE[die].n3.c*s3->c;
A[1][2]=DIE[die].n3.b*s3->a+DIE[die].n3.a*s3->b;
A[1][3]=DIE[die].n3.c*s3->a+DIE[die].n3.a*s3->c;
A[2][0]=A[0][2];
A[2][1]=A[1][2];
A[2][2]=-DIE[die].n3.a*s3->a+DIE[die].n3.b*s3->b-DIE[die].n3.c*s3->c;
A[2][3]=DIE[die].n3.c*s3->b+DIE[die].n3.b*s3->c;
A[3][0]=A[0][3];
A[3][1]=A[1][3];
A[3][2]=A[2][3];
A[3][3]=-DIE[die].n3.a*s3->a-DIE[die].n3.b*s3->b+DIE[die].n3.c*s3->c;

alpha[2][0]=2*(q[0]*A[0][0]+q[1]*A[0][1]+q[2]*A[0][2]+q[3]*A[0][3]);
alpha[2][1]=2*(q[0]*A[1][0]+q[1]*A[1][1]+q[2]*A[1][2]+q[3]*A[1][3]);
alpha[2][2]=2*(q[0]*A[2][0]+q[1]*A[2][1]+q[2]*A[2][2]+q[3]*A[2][3]);
alpha[2][3]=2*(q[0]*A[3][0]+q[1]*A[3][1]+q[2]*A[3][2]+q[3]*A[3][3]);

bet[2]=-( pow(q[0],2)*A[0][0]+pow(q[1],2)*A[1][1]+
          pow(q[2],2)*A[2][2]+pow(q[3],2)*A[3][3]+
          2*( q[0]*q[1]*A[0][1]+q[0]*q[2]*A[0][2]+q[0]*q[3]*A[0][3]+
              q[1]*q[2]*A[1][2]+q[1]*q[3]*A[1][3]+q[2]*q[3]*A[2][3] ) );

// Quarta equazione
alpha[3][0]=2*q[0];
alpha[3][1]=2*q[1];
alpha[3][2]=2*q[2];
alpha[3][3]=2*q[3];

bet[3]=-( pow(q[0],2)+pow(q[1],2)+pow(q[2],2)+pow(q[3],2)-1 );

free_matrix(A,0,3,0);
}