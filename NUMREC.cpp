/*
NOME_FILE:NUMREC
PROGETTO:Thesis
AUTORE:Emanuele Maria Santanché
DATA_INIZ:Ott 7'92
FILES DOCUMENTAZIONE:THMODULI.DOC, THGRUPPI.DOC, NUMRECDF.DOC
NOMI FUNZIONI:
   Gruppo SISLIN
      ludcmp()
      lubksb()
   Gruppo UTILIT
      vector()
      ivector()
      nrerror()
      free_vector()
      free_ivector()
      matrix()
      free_matrix()
      imatrix()
      free_imatrix()
*/

#include "thvarie.h"
#include "thstruct.h"
#include "thprotot.h"
#include "thextern.h"

/////////////////////////////////////////////////////////////////////////
//   ludcmp
/////////////////////////////////////////////////////////////////////////
BOOL ludcmp(double huge **a,int n,int huge *indx,double *d)
{
int i,imax,j,k;
double big,dum,sum,temp;
double huge *vv;

vv=vector(0,n-1);
*d=1.0;
for (i=0;i<n;i++) {
   big=0.0;
   for (j=0;j<n;j++)
      if ((temp=fabs(a[i][j])) > big) big=temp;
   if (Lz(big)) {
      free_vector(vv,0);
      return(TRUE);
   }
   vv[i]=1.0/big;
}
for (j=0;j<n;j++) {
   for (i=0;i<j;i++) {
      sum=a[i][j];
      for (k=0;k<i;k++) sum -= a[i][k]*a[k][j];
      a[i][j]=sum;
   }
   big=0.0;
   for (i=j;i<n;i++) {
      sum=a[i][j];
      for (k=0;k<j;k++)
         sum -= a[i][k]*a[k][j];
      a[i][j]=sum;
      if ((dum=vv[i]*fabs(sum)) >= big) {
         big=dum;
         imax=i;
      }
   }
   if (j != imax) {
      for (k=0;k<n;k++) {
         dum=a[imax][k];
         a[imax][k]=a[j][k];
         a[j][k]=dum;
      }
      *d=-(*d);
      vv[imax]=vv[j];
   }
   indx[j]=imax;
   if (Lz(a[j][j])) {
      free_vector(vv,0);
      return(TRUE);
   }
   if (j != (n-1)) {
      dum=1.0/(a[j][j]);
      for (i=j+1;i<n;i++) a[i][j] *= dum;
   }
}
free_vector(vv,0);
return(FALSE);
}

/////////////////////////////////////////////////////////////////////////
//   lubksb
/////////////////////////////////////////////////////////////////////////
void lubksb(double huge **a,int n,int huge *indx,double huge *b)
{
int i,ii,ip,j;
double sum;

ii=-1;
for (i=0;i<n;i++) {
   ip=indx[i];
   sum=b[ip];
   b[ip]=b[i];
   if (ii != -1)
      for (j=ii;j<=i-1;j++) sum -= a[i][j]*b[j];
   else if (sum != 0.0) ii=i;
   b[i]=sum;
}
for (i=n-1;i>=0;i--) {
   sum=b[i];
   for (j=i+1;j<n;j++) sum -= a[i][j]*b[j];
   b[i]=sum/(a[i][i]);
}
}

/////////////////////////////////////////////////////////////////////////
//   vector
/////////////////////////////////////////////////////////////////////////
double huge *vector(int nl,int nh)
{
double huge *v;

v=(double huge *) farmalloc((unsigned long) (nh-nl+1)*sizeof(double));
if (!v) nrerror("allocation failure in vector()");
return(v-nl);
}

/////////////////////////////////////////////////////////////////////////
//   ivector
/////////////////////////////////////////////////////////////////////////
int huge *ivector(int nl,int nh)
{
int huge *v;

v=(int huge *) farmalloc((unsigned long) (nh-nl+1)*sizeof(int));
if (!v) nrerror("allocation failure in ivector()");
return(v-nl);
}

/////////////////////////////////////////////////////////////////////////
//   nrerror
/////////////////////////////////////////////////////////////////////////
void nrerror(char error_text[])
{

Error(error_text,"nrerror","numrec");
}

/////////////////////////////////////////////////////////////////////////
//   free_vector
/////////////////////////////////////////////////////////////////////////
void free_vector(double huge *v,int nl)
{

farfree((void huge *) (v+nl));
}

/////////////////////////////////////////////////////////////////////////
//   free_ivector
/////////////////////////////////////////////////////////////////////////
void free_ivector(int huge *v,int nl)
{

farfree((void huge *) (v+nl));
}

/////////////////////////////////////////////////////////////////////////
//   matrix
/////////////////////////////////////////////////////////////////////////
double huge **matrix(int nrl,int nrh,int ncl,int nch)
{
int i;
double huge **m;

m=(double huge **)
   farmalloc((unsigned long) (nrh-nrl+1)*sizeof(double huge *));
if (!m) nrerror("allocation failure 1 in matrix()");
m -= nrl;
for (i=nrl;i<=nrh;i++) {
   m[i]=(double huge *)
        farmalloc((unsigned long) (nch-ncl+1)*sizeof(double));
   if (!m[i]) nrerror("allocation failure 2 in matrix()");
   m[i] -= ncl;
}
return(m);
}

/////////////////////////////////////////////////////////////////////////
//   free_matrix
/////////////////////////////////////////////////////////////////////////
void free_matrix(double huge **m,int nrl,int nrh,int ncl)
{
int i;

for (i=nrh;i>=nrl;i--) farfree((void huge *) (m[i]+ncl));
farfree((void huge *) (m+nrl));
}

/////////////////////////////////////////////////////////////////////////
//   imatrix
/////////////////////////////////////////////////////////////////////////
int huge **imatrix(int nrl,int nrh,int ncl,int nch)
{
int i;
int huge **m;

m=(int huge **)
   farmalloc((unsigned long) (nrh-nrl+1)*sizeof(int huge *));
if (!m) nrerror("allocation failure 1 in imatrix()");
m -= nrl;
for (i=nrl;i<=nrh;i++) {
   m[i]=(int huge *)
        farmalloc((unsigned long) (nch-ncl+1)*sizeof(int));
   if (!m[i]) nrerror("allocation failure 2 in imatrix()");
   m[i] -= ncl;
}
return(m);
}

/////////////////////////////////////////////////////////////////////////
//   free_imatrix
/////////////////////////////////////////////////////////////////////////
void free_imatrix(int huge **m,int nrl,int nrh,int ncl)
{
int i;

for (i=nrh;i>=nrl;i--) farfree((void huge *) (m[i]+ncl));
farfree((void huge *) (m+nrl));
}
