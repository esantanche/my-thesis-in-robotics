/*
NOME_FILE:GEOMET
PROGETTO:Thesis
AUTORE:Emanuele Maria Santanché
DATA_INIZ:Set 4'92
FILES DOCUMENTAZIONE:THMODULI.DOC, THGRUPPI.DOC, GEOMET.DOC
NOMI FUNZIONI:
   Gruppo INTRET
      Interseca_cono_retta()
      Calcola_normale_cono()
      Interseca_cilindro_retta()
      Calcola_normale_cilindro()
      Interseca_piano_retta()
   Gruppo VISIBI
      Visibilita_cono_retta()
      Visibilita_cilindro_retta()
      Visibilita_piano_retta()
   Gruppo INTSEG
      Interseca_segmenti()
      Distanza_segmenti()
   Gruppo INTPIA
      Interseca_piano_cerchio()
   Gruppo CRERET
      Crea_retta()
      Punto_da_retta()
   Gruppo PIANO3
      Piano_per_tre_punti()
   Gruppo VETTOR
      Versore_da_retta()
      Coseno_tra_versori()
      Vett_tra_punti()
      Prod_scal()
      Prod_vett()
      Vett_per_scal()
      Sott_vett()
      Somma_vett()
      Modulo()
*/

#include "thvarie.h"
#include "thstruct.h"
#include "thprotot.h"
#include "thextern.h"

/////////////////////////////////////////////////////////////////////////
//   Interseca_cono_retta
/////////////////////////////////////////////////////////////////////////
void Interseca_cono_retta(float x0,float z0,float x1,float z1,
                          struct retta r,
                          struct punto *p,
                          struct vettore *n,
                          float *distanza,float *param_retta)
{
double D,A,B,G1,G2,D1,D2,a,q,t,c,b,d,xa,ya,za,xb,yb,zb,ds,zv,qi;
double t1,t2,qa,qb,sol,rq;
BOOL ok_a,ok_b;

if (Lz(x0-x1))
   Error("Il cono non è un cono","Interseca_cono_retta","geomet");
zv=z0+x0*(z1-z0)/(x0-x1);
if (!Lz(r.zap)) {
   D=1/r.zap;
   A=(zv-r.zp)*D;
   B=(z1-zv)*D;
   G1=r.xp+r.xap*A;
   G2=r.yp+r.yap*A;
   D1=r.xap*B;
   D2=r.yap*B;
   a=pow(x1,2)-pow(D1,2)-pow(D2,2);
   b=G1*D1+G2*D2;
   if (Lz(a)) { // se a=0 vuol dire che la retta è parallela a
                // una direttrice del cono
      if (Lz(b)) {
         if (Lz(G1) && Lz(G2)) { // la retta coincide
                                                     // con una direttrice
                                                     // del cono
            p->z=(z0+z1)/2;
            qi=(p->z-r.zp)/r.zap;
            if (qi < 0) {
               p->indefinito=TRUE;
               n->indefinito=TRUE;
               *distanza=0;
               *param_retta=0;
               return;
            }
            p->x=r.xp+r.xap*qi;
            p->y=r.yp+r.yap*qi;
            p->indefinito=FALSE;
            *distanza=r.cd*qi;
            *param_retta=qi;
            Calcola_normale_cono(x0,z0,x1,z1,p,n);
            return;
         }
         else {
            Error("Caso impossibile di intersezione cono-retta",
                  "Interseca_cono_retta","geomet");
         }
      }
      else { // b != 0
         c=pow(G1,2)+pow(G2,2);
         t=-0.5*c/b;
         q=A+B*t;
         if (q < 0) {
            p->indefinito=TRUE;
            n->indefinito=TRUE;
            *distanza=0;
            *param_retta=0;
            return;
         }
         p->z=r.zp+r.zap*q;
         if (  ( (z0 < z1) && ((p->z < z0) || (p->z > z1)) )  ||
               ( (z1 < z0) && ((p->z < z1) || (p->z > z0)) )  ) {
               p->indefinito=TRUE;
               n->indefinito=TRUE;
               *distanza=0;
               *param_retta=0;
               return;
         }
         p->x=r.xp+r.xap*q;
         p->y=r.yp+r.yap*q;
         p->indefinito=FALSE;
         *distanza=r.cd*q;
         *param_retta=q;
         Calcola_normale_cono(x0,z0,x1,z1,p,n);
         return;
      } // b = 0  oppure  b != 0
   }
   else { // a != 0
      c=pow(G1,2)+pow(G2,2);
      d=pow(b,2)+a*c;
      if (d < 0) { // se d < 0 le soluzioni sono immaginarie
         p->indefinito=TRUE;
         n->indefinito=TRUE;
         *distanza=0;
         *param_retta=0;
         return;
      }
      else {
         ds=sqrt(d);
         t1=(b+ds)/a;
         t2=(b-ds)/a;
         qa=A+B*t1;
         qb=A+B*t2;
         xa=r.xp+r.xap*qa;
         ya=r.yp+r.yap*qa;
         za=r.zp+r.zap*qa;
         xb=r.xp+r.xap*qb;
         yb=r.yp+r.yap*qb;
         zb=r.zp+r.zap*qb;
         if (  ( (z0 < z1) && ((za < z0) || (za > z1)) )  ||
               ( (z1 < z0) && ((za < z1) || (za > z0)) )  ||
               (qa < 0) )
            ok_a=FALSE;
         else
            ok_a=TRUE;
         if (  ( (z0 < z1) && ((zb < z0) || (zb > z1)) )  ||
               ( (z1 < z0) && ((zb < z1) || (zb > z0)) )  ||
               (qb < 0) )
            ok_b=FALSE;
         else
            ok_b=TRUE;
         if ((!ok_a) && (!ok_b)) {
            p->indefinito=TRUE;
            n->indefinito=TRUE;
            *distanza=0;
            *param_retta=0;
            return;
         }
         if (ok_a && ok_b)
            if (qa > qb)
               sol=2;
            else
               sol=1;
         else
            if (ok_a)
               sol=1;
            else
               sol=2;
         if (sol == 1) {
            p->x=xa;
            p->y=ya;
            p->z=za;
            *distanza=r.cd*qa;
            *param_retta=qa;
         }
         else {
            p->x=xb;
            p->y=yb;
            p->z=zb;
            *distanza=r.cd*qb;
            *param_retta=qb;
         }
         p->indefinito=FALSE;
         Calcola_normale_cono(x0,z0,x1,z1,p,n);
         return;
      } // d = 0  oppure  d != 0
   } // a = 0 oppure a != 0
}
else { // caso za=zp (r.zap==0) cioè la retta si trova su di un piano
       // parallelo al piano x-y
   if (  ( (z0 < z1) && ((r.zp < z0) || (r.zp > z1)) )  ||
         ( (z1 < z0) && ((r.zp < z1) || (r.zp > z0)) )  ) {
      p->indefinito=TRUE;
      n->indefinito=TRUE;
      *distanza=0;
      *param_retta=0;
      return;
   }
   a=pow(r.xap,2)+pow(r.yap,2);
   b=r.xp*r.xap+r.yp*r.yap;
   rq=pow(x1*(r.zp-zv)/(z1-zv),2);
   c=pow(r.xp,2)+pow(r.yp,2)-rq;
   d=pow(b,2)-a*c;
   if (d < 0) {
      p->indefinito=TRUE;
      n->indefinito=TRUE;
      *distanza=0;
      *param_retta=0;
      return;
   }
   else {
      ds=sqrt(d);
      q=(-b-ds)/a;
      if (q < 0) {
         q=(-b+ds)/a;
      }
      if (q < 0) {
         p->indefinito=TRUE;
         n->indefinito=TRUE;
         *distanza=0;
         *param_retta=0;
         return;
      }
      p->x=r.xp+r.xap*q;
      p->y=r.yp+r.yap*q;
      p->z=r.zp;
      p->indefinito=FALSE;
      *distanza=r.cd*q;
      *param_retta=q;
      Calcola_normale_cono(x0,z0,x1,z1,p,n);
      return;
   }
}
} // Interseca_cono_retta

/////////////////////////////////////////////////////////////////////////
//   Calcola_normale_cono
/////////////////////////////////////////////////////////////////////////
void Calcola_normale_cono(float x0,float z0,float x1,float z1,
                          struct punto *p,struct vettore *n)
{
double a,b,cr;

n->indefinito=FALSE;
if (Lz(p->x) && Lz(p->y)) {
   n->a=0;
   n->b=0;
   n->c=1;
   return;
}
a=atan2((double) (z1-z0),(double) (x1-x0));
a=a+M_PI_2;
cr=cos(a);
n->c=sin(a);
b=atan2((double) p->y,(double) p->x);
n->a=cr*cos(b);
n->b=cr*sin(b);
}

/////////////////////////////////////////////////////////////////////////
//   Interseca_cilindro_retta
/////////////////////////////////////////////////////////////////////////
void Interseca_cilindro_retta(float xc,float z0,float z1,
                              struct retta r,
                              struct punto *p,
                              struct vettore *n,
                              float *distanza,float *param_retta)
{
double a,b,c,d,q,ds,qa,qb;

a=pow(r.xap,2)+pow(r.yap,2);
b=r.xp*r.xap+r.yp*r.yap;
c=pow(r.xp,2)+pow(r.yp,2)-pow(xc,2);
d=pow(b,2)-a*c;
if (d < 0) {
   p->indefinito=TRUE;
   n->indefinito=TRUE;
   *distanza=0;
   *param_retta=0;
   return;
}
else {
   if (Lz(a)) {
      if (Lz(c)) {
         p->z=(z0+z1)/2;
         q=(p->z-r.zp)/r.zap;
         if (q < 0) {
            p->indefinito=TRUE;
            n->indefinito=TRUE;
            *distanza=0;
            *param_retta=0;
            return;
         }
         p->indefinito=FALSE;
         p->x=r.xp;
         p->y=r.yp;
         *distanza=r.cd*q;
         *param_retta=q;
         Calcola_normale_cilindro(xc,z0,z1,p,n);
         return;
      }
      else {
         p->indefinito=TRUE;
         n->indefinito=TRUE;
         *distanza=0;
         *param_retta=0;
         return;
      }
   }
   else {
      ds=sqrt(d);
      qa=(-b+ds)/a;
      qb=(-b-ds)/a;
      p->z=r.zp+r.zap*qb;
      if (( ( (z0 < z1) && ((p->z >= z0) && (p->z <= z1)) )  ||
            ( (z1 < z0) && ((p->z >= z1) && (p->z <= z0)) ) ) &&
            (qb >= 0)  ) {
         p->x=r.xp+r.xap*qb;
         p->y=r.yp+r.yap*qb;
         p->indefinito=FALSE;
         *distanza=r.cd*qb;
         *param_retta=qb;
         Calcola_normale_cilindro(xc,z0,z1,p,n);
         return;
      }
      else {
         p->z=r.zp+r.zap*qa;
         if (( ( (z0 < z1) && ((p->z >= z0) && (p->z <= z1)) )  ||
               ( (z1 < z0) && ((p->z >= z1) && (p->z <= z0)) ) ) &&
               (qa >= 0)  ) {
            p->x=r.xp+r.xap*qa;
            p->y=r.yp+r.yap*qa;
            p->indefinito=FALSE;
            *distanza=r.cd*qa;
            *param_retta=qa;
            Calcola_normale_cilindro(xc,z0,z1,p,n);
            return;
         }
         else {
            p->indefinito=TRUE;
            n->indefinito=TRUE;
            *distanza=0;
            *param_retta=0;
            return;
         }
      }
   }
}
}

/////////////////////////////////////////////////////////////////////////
//   Calcola_normale_cilindro
/////////////////////////////////////////////////////////////////////////
void Calcola_normale_cilindro(float xc,float z0,float z1,
                              struct punto *p,struct vettore *n)
{
double cr;

n->indefinito=FALSE;
if (z1 > z0)
   cr=-1;
else
   cr=1;
n->a=cr*p->x/xc;
n->b=cr*p->y/xc;
n->c=0;
}

/////////////////////////////////////////////////////////////////////////
//   Interseca_piano_retta
/////////////////////////////////////////////////////////////////////////
void Interseca_piano_retta(float x0,float x1,float zr,
                           struct retta r,
                           struct punto *p,
                           struct vettore *n,
                           float *distanza,float *param_retta)
{
double qi,d;

if (Lz(r.zap)) {
   p->indefinito=TRUE;
   n->indefinito=TRUE;
   *distanza=0;
   *param_retta=0;
   return;
}
else {
   qi=(zr-r.zp)/r.zap;
   if (qi < 0) {
      p->indefinito=TRUE;
      n->indefinito=TRUE;
      *distanza=0;
      *param_retta=0;
      return;
   }
   p->x=r.xp+r.xap*qi;
   p->y=r.yp+r.yap*qi;
   d=sqrt(pow(p->x,2)+pow(p->y,2));
   if ( ( (x0 < x1) && ((d >= x0) && (d <= x1)) )  ||
        ( (x1 < x0) && ((d >= x1) && (d <= x0)) ) ) {
      p->z=zr;
      p->indefinito=FALSE;
      *distanza=r.cd*qi;
      *param_retta=qi;
      n->a=0;
      n->b=0;
      n->c=((x1 > x0) ? 1 : -1);
      n->indefinito=FALSE;
      return;
   }
   else {
      p->indefinito=TRUE;
      n->indefinito=TRUE;
      *distanza=0;
      *param_retta=0;
      return;
   }
}
}

/////////////////////////////////////////////////////////////////////////
//   Visibilita_cono_retta
/////////////////////////////////////////////////////////////////////////
BOOL Visibilita_cono_retta(float x0,float z0,float x1,float z1,
                           struct retta r,BOOL stesso)
{
double D,A,B,G1,G2,D1,D2,a,q,t,c,b,d,za,zb,ds,zv,qi,zt;
double t1,t2,qa,qb,rq,lim;
BOOL ok_a,ok_b;

lim=1-0.001*stesso;
if (Lz(x0-x1))
   Error("Il cono non è un cono","Visibilita_cono_retta","geomet");
zv=z0+x0*(z1-z0)/(x0-x1);
if (!Lz(r.zap)) {
   D=1/r.zap;
   A=(zv-r.zp)*D;
   B=(z1-zv)*D;
   G1=r.xp+r.xap*A;
   G2=r.yp+r.yap*A;
   D1=r.xap*B;
   D2=r.yap*B;
   a=pow(x1,2)-pow(D1,2)-pow(D2,2);
   b=G1*D1+G2*D2;
   if (Lz(a)) { // se a=0 vuol dire che la retta è parallela a
                        // una direttrice del cono
      if (Lz(b)) {
         if (Lz(G1) && Lz(G2)) { // la retta coincide
                                                     // con una direttrice
                                                     // del cono
            qi=((z0+z1)/2-r.zp)/r.zap;
            if ((qi < 0) || (qi > lim))
               return(FALSE);
            else
               return(TRUE);
         }
         else {
            Error("Caso impossibile di intersezione cono-retta",
                  "Visibilità_cono_retta","geomet");
            return(FALSE);
         }
      }
      else { // b != 0
         c=pow(G1,2)+pow(G2,2);
         t=-0.5*c/b;
         q=A+B*t;
         if ((q < 0) || (q > lim))
            return(FALSE);
         zt=r.zp+r.zap*q;
         if (  ( (z0 < z1) && ((zt < z0) || (zt > z1)) )  ||
               ( (z1 < z0) && ((zt < z1) || (zt > z0)) )  )
            return(FALSE);
         return(TRUE);
      } // b = 0  oppure  b != 0
   }
   else { // a != 0
      c=pow(G1,2)+pow(G2,2);
      d=pow(b,2)+a*c;
      if (d < 0)  // se d < 0 le soluzioni sono immaginarie
         return(FALSE);
      else {
         ds=sqrt(d);
         t1=(b+ds)/a;
         t2=(b-ds)/a;
         qa=A+B*t1;
         qb=A+B*t2;
         za=r.zp+r.zap*qa;
         zb=r.zp+r.zap*qb;
         if (  ( (z0 < z1) && ((za < z0) || (za > z1)) )  ||
               ( (z1 < z0) && ((za < z1) || (za > z0)) )  ||
               (qa < 0) || (qa > lim) )
            ok_a=FALSE;
         else
            ok_a=TRUE;
         if (  ( (z0 < z1) && ((zb < z0) || (zb > z1)) )  ||
               ( (z1 < z0) && ((zb < z1) || (zb > z0)) )  ||
               (qb < 0) || (qb > lim) )
            ok_b=FALSE;
         else
            ok_b=TRUE;
         if ((!ok_a) && (!ok_b))
            return(FALSE);
         else
            return(TRUE);
      } // d = 0  oppure  d != 0
   } // a = 0 oppure a != 0
}
else { // caso za=zp cioè la retta si trova su di un piano parallelo
       // al piano x-y
   if (  ( (z0 < z1) && ((za < z0) || (za > z1)) )  ||
         ( (z1 < z0) && ((za < z1) || (za > z0)) )  )
      return(FALSE);
   a=pow(r.xap,2)+pow(r.yap,2);
   b=r.xp*r.xap+r.yp*r.yap;
   rq=pow(x1*(r.zp-zv)/(z1-zv),2);
   c=pow(r.xp,2)+pow(r.yp,2)-rq;
   d=pow(b,2)-a*c;
   if (d < 0)
      return(FALSE);
   else {
      ds=sqrt(d);
      q=(-b-ds)/a;
      if (q < 0) {
         q=(-b+ds)/a;
      }
      if (q < 0)
         return(FALSE);
      if (q > lim)
         return(FALSE);
      else
         return(TRUE);
   }
}
}

/////////////////////////////////////////////////////////////////////////
//   Visibilita_cilindro_retta
/////////////////////////////////////////////////////////////////////////
BOOL Visibilita_cilindro_retta(float xc,float z0,float z1,
                               struct retta r,BOOL stesso)
{
double a,b,c,d,q,ds,qa,qb,zt,lim;

lim=1-0.00001*stesso;
a=pow(r.xap,2)+pow(r.yap,2);
b=r.xp*r.xap+r.yp*r.yap;
c=pow(r.xp,2)+pow(r.yp,2)-pow(xc,2);
d=pow(b,2)-a*c;
if (d < 0)
   return(FALSE);
else {
   if (Lz(a)) {
      if (Lz(c)) {
         q=((z0+z1)/2-r.zp)/r.zap;
         if (q < 0)
            return(FALSE);
         if (q > lim)
            return(FALSE);
         else
            return(TRUE);
      }
      else
         return(FALSE);
   }
   else {
      ds=sqrt(d);
      qa=(-b+ds)/a;
      qb=(-b-ds)/a;
      zt=r.zp+r.zap*qb;
      if (( ( (z0 < z1) && ((zt >= z0) && (zt <= z1)) )  ||
            ( (z1 < z0) && ((zt >= z1) && (zt <= z0)) ) ) &&
            (qb >= 0)  && !(qb > lim))
         return(TRUE);
      else {
         zt=r.zp+r.zap*qa;
         if (( ( (z0 < z1) && ((zt >= z0) && (zt <= z1)) )  ||
               ( (z1 < z0) && ((zt >= z1) && (zt <= z0)) ) ) &&
               (qa >= 0) && !(qa > lim))
            return(TRUE);
         else
            return(FALSE);
      }
   }
}
}

/////////////////////////////////////////////////////////////////////////
//   Visibilita_piano_retta
/////////////////////////////////////////////////////////////////////////
BOOL Visibilita_piano_retta(float x0,float x1,float zr,
                            struct retta r,BOOL stesso)
{
double a,b,qi,d,lim;

lim=1-0.00001*stesso;
if (Lz(r.zap))
   return(FALSE);
else {
   qi=(zr-r.zp)/r.zap;
   if ((qi < 0) || (qi > lim))
      return(FALSE);
   a=r.xp+r.xap*qi;
   b=r.yp+r.yap*qi;
   d=sqrt(pow(a,2)+pow(b,2));
   if ( ( (x0 < x1) && ((d >= x0) && (d <= x1)) )  ||
        ( (x1 < x0) && ((d >= x1) && (d <= x0)) ) )
      return(TRUE);
   else
      return(FALSE);
}
}


/////////////////////////////////////////////////////////////////////////
//   Interseca_segmenti
/////////////////////////////////////////////////////////////////////////
BOOL Interseca_segmenti(float x1,float z1, float x2,float z2,
                        float x3,float z3, float x4,float z4)
{
double x21,x31,x43,z21,z31,z43;
double p;
double t,q;

x21=x2-x1;
x31=x3-x1;
x43=x4-x3;
z21=z2-z1;
z31=z3-z1;
z43=z4-z3;
p=z21*x43-x21*z43;
if (Lz(p)) return(FALSE); // se i segmenti sono paralleli
                                  // non hanno intersezioni
t=(z31*x43-x31*z43)/p;
q=(z31*x21-z21*x31)/p;
// se t e q sono compresi tra 0 e 1, vuol dire che l' intersezione
// tra le rette dei segmenti, cade dentro ai segmenti ovvero c'è
// effettiva intersezione tra i segmenti
if ( ((t >= 0) && (t <= 1)) && ((q >= 0) && (q <= 1)) )
   return(TRUE);
return(FALSE);
}

/////////////////////////////////////////////////////////////////////////
//   Distanza_segmenti
/////////////////////////////////////////////////////////////////////////
BOOL Distanza_segmenti(float x1,float z1, float x2,float z2,
                       float x3,float z3, float x4,float z4)
{
double x21,x31,x41,x23,x24,x43,z21,z31,z41,z23,z24,z43;
double la,lb;
double d13,d14,d23,d24;

x21=x2-x1;
x31=x3-x1;
x41=x4-x1;
x23=x2-x3;
x24=x2-x4;
x43=x4-x3;
z21=z2-z1;
z31=z3-z1;
z41=z4-z1;
z23=z2-z3;
z24=z2-z4;
z43=z4-z3;
la=sqrt(pow(x21,2)+pow(z21,2));  // lunghezza segmento 1-2
lb=sqrt(pow(x43,2)+pow(z43,2));  // lunghezza segmento 3-4
d13=sqrt(pow(x31,2)+pow(z31,2));  // distanza punto 1 - punto 3
d14=sqrt(pow(x41,2)+pow(z41,2));  // distanza punto 1 - punto 4
d23=sqrt(pow(x23,2)+pow(z23,2));  // distanza punto 2 - punto 3
d24=sqrt(pow(x24,2)+pow(z24,2));  // distanza punto 2 - punto 4
// il punto 1 deve distare da 3 e da 4 almeno la lunghezza del segmento
// 3-4, il punto 2 idem, i punti 3 e 4 devono distare almeno la lunghezza
// di 1-2 da 1 e da 2.
if ( ((d13 > lb) || (d14 > lb)) && ((d23 > lb) || (d24 > lb)) &&
     ((d13 > la) || (d23 > la)) && ((d14 > la) || (d24 > la))  )
   return(FALSE);
else
   return(TRUE);
} // Distanza_segmenti

/////////////////////////////////////////////////////////////////////////
//   Interseca_piano_cerchio
/////////////////////////////////////////////////////////////////////////
void Interseca_piano_cerchio(struct piano piano,
                             float z_cerchio,
                             float raggio,
                             struct punto *p1,
                             struct punto *p2)
{
double k,x,y,xq,x1,x2,ab,ds,t1,t2,y1,y2;

if (Lz(piano.a) && Lz(piano.b)) {
   p1->indefinito=TRUE;
   p2->indefinito=TRUE;
   return;
}
if (Lz(piano.a)) {
   k=piano.c*z_cerchio+piano.d;
   y=-k/piano.b;
   xq=pow(raggio,2)-pow(y,2);
   if (xq < 0) {
      p1->indefinito=TRUE;
      p2->indefinito=TRUE;
      return;
   }
   x1=sqrt(xq);
   x2=-x1;
   p1->indefinito=FALSE;
   p1->x=x1;
   p1->y=y;
   p1->z=z_cerchio;
   if (!Lz(x1))  {
      p2->indefinito=FALSE;
      p2->x=x2;
      p2->y=y;
      p2->z=z_cerchio;
   }
   else
      p2->indefinito=TRUE;
   return;
}
k=piano.c*z_cerchio+piano.d;
ab=pow(piano.a,2)+pow(piano.b,2);
ds=pow(raggio,2)*ab-pow(k,2);
if (ds < 0) {
   p1->indefinito=TRUE;
   p2->indefinito=TRUE;
   return;
}
if (Lz(ds)) {
   y=-piano.b*k/ab;
   x=-((piano.b*y+k)/piano.a);
   p1->indefinito=FALSE;
   p1->x=x;
   p1->y=y;
   p1->z=z_cerchio;
   p2->indefinito=TRUE;
   return;
}
t1=-piano.b*k/ab;
t2=piano.a*sqrt(ds)/ab;
y1=t1+t2;
y2=t1-t2;
x1=-((piano.b*y1+k)/piano.a);
x2=-((piano.b*y2+k)/piano.a);
p1->indefinito=FALSE;
p1->x=x1;
p1->y=y1;
p1->z=z_cerchio;
p2->indefinito=FALSE;
p2->x=x2;
p2->y=y2;
p2->z=z_cerchio;
return;
}

/////////////////////////////////////////////////////////////////////////
//   Crea_retta
/////////////////////////////////////////////////////////////////////////
struct retta Crea_retta(float xp,float yp,float zp,
                        float xa,float ya,float za)
{
struct retta r;

r.xp=xp;
r.yp=yp;
r.zp=zp;
r.xap=xa-xp;
r.yap=ya-yp;
r.zap=za-zp;
r.cd=sqrt(pow(r.xap,2)+pow(r.yap,2)+pow(r.zap,2));
return(r);
}

/////////////////////////////////////////////////////////////////////////
//   Punto_da_retta
/////////////////////////////////////////////////////////////////////////
struct punto Punto_da_retta(struct retta r,float t)
{
struct punto p;

if (Lz(r.cd))
   Error("Retta inesistente!","Punto_da_retta","geomet");
p.indefinito=FALSE;
p.x=r.xp+r.xap*t;
p.y=r.yp+r.yap*t;
p.z=r.zp+r.zap*t;
return(p);
}

/////////////////////////////////////////////////////////////////////////
//   Piano_per_tre_punti
/////////////////////////////////////////////////////////////////////////
struct piano Piano_per_tre_punti(struct punto p1,
                                 struct punto p2,
                                 struct punto p3)
{
struct vettore v12,v13,norm;
struct piano piano;

v12=Vett_tra_punti(p1,p2);
v13=Vett_tra_punti(p1,p3);
norm=Prod_vett(v12,v13);
if (Lz(Modulo(norm)))
   Error("Punti allineati","Piano_per_tre_punti","geomet");
piano.indefinito=FALSE;
piano.a=norm.a;
piano.b=norm.b;
piano.c=norm.c;
piano.d=-(piano.a*p1.x+piano.b*p1.y+piano.c*p1.z);
return(piano);

/*
origine.indefinito=FALSE;
origine.x=0;
origine.y=0;
origine.z=0;
indx=ivector(1,3);
v12=Vett_tra_punti(p1,p2);
v13=Vett_tra_punti(p1,p3);
if (Lz(Modulo(Prod_vett(v12,v13))))
   Error("Punti allineati","Piano_per_tre_punti","geomet");
matr_coeff=matrix(1,3,1,3);
matr_coeff[1][1]=p1.x;matr_coeff[1][2]=p1.y;matr_coeff[1][3]=p1.z;
matr_coeff[2][1]=p2.x;matr_coeff[2][2]=p2.y;matr_coeff[2][3]=p2.z;
matr_coeff[3][1]=p3.x;matr_coeff[3][2]=p3.y;matr_coeff[3][3]=p3.z;
singolare=ludcmp(matr_coeff,3,indx,&d);
if (singolare) { // il piano passa per l'origine
   vo1=Vett_tra_punti(origine,p1);
   vo2=Vett_tra_punti(origine,p2);
   norm=Prod_vett(vo1,vo2);
   piano.indefinito=FALSE;
   piano.a=norm.a;
   piano.b=norm.b;
   piano.c=norm.c;
   piano.d=0;
   free_matrix(matr_coeff,1,3,1);
   free_ivector(indx,1);
   return(piano);
}
b=vector(1,3);
b[1]=1;b[2]=1;b[3]=1;
lubksb(matr_coeff,3,indx,b);
piano.indefinito=FALSE;
piano.a=b[1];
piano.b=b[2];
piano.c=b[3];
piano.d=1;
free_vector(b,1);
free_matrix(matr_coeff,1,3,1);
free_ivector(indx,1);
return(piano);
*/
}

/////////////////////////////////////////////////////////////////////////
//   Versore_da_retta
/////////////////////////////////////////////////////////////////////////
struct vettore Versore_da_retta(struct retta r)
{
struct vettore n;

if (r.cd < 0.001)
   Error("La retta è troppo corta!","Versore_da_retta","geomet");
n.indefinito=FALSE;
n.a=r.xap/r.cd;
n.b=r.yap/r.cd;
n.c=r.zap/r.cd;
return(n);
}

/////////////////////////////////////////////////////////////////////////
//   Coseno_tra_versori
/////////////////////////////////////////////////////////////////////////
float Coseno_tra_versori(struct vettore v1,struct vettore v2)
{

if (v1.indefinito || v2.indefinito)
   Error("Vettore/i indefinito/i","Coseno_tra_versori","geomet");
return(v1.a*v2.a+v1.b*v2.b+v1.c*v2.c);
}

/////////////////////////////////////////////////////////////////////////
//   Vett_tra_punti
/////////////////////////////////////////////////////////////////////////
struct vettore Vett_tra_punti(struct punto p1,struct punto p2)
{
struct vettore v;

if (p1.indefinito || p2.indefinito)
   Error("Punto/i indefinito/i","Vett_tra_punti","geomet");
v.indefinito=FALSE;
v.a=p1.x-p2.x;
v.b=p1.y-p2.y;
v.c=p1.z-p2.z;
return(v);
}

/////////////////////////////////////////////////////////////////////////
//   Prod_scal
/////////////////////////////////////////////////////////////////////////
float Prod_scal(struct vettore v1,struct vettore v2)
{

if (v1.indefinito || v2.indefinito)
   Error("Vettore/i indefinito/i","Prod_scal","geomet");
return(v1.a*v2.a+v1.b*v2.b+v1.c*v2.c);
}

/////////////////////////////////////////////////////////////////////////
//   Prod_vett
/////////////////////////////////////////////////////////////////////////
struct vettore Prod_vett(struct vettore v1,struct vettore v2)
{
struct vettore vr;

vr.a=v1.b*v2.c-v1.c*v2.b;
vr.b=-v1.a*v2.c+v1.c*v2.a;
vr.c=v1.a*v2.b-v1.b*v2.a;
vr.indefinito=FALSE;
return(vr);
}

/////////////////////////////////////////////////////////////////////////
//   Vett_per_scal
/////////////////////////////////////////////////////////////////////////
struct vettore Vett_per_scal(float s,struct vettore v)
{
struct vettore r;

if (v.indefinito)
   Error("Vettore indefinito","Vett_per_scal","geomet");
r.indefinito=FALSE;
r.a=v.a*s;
r.b=v.b*s;
r.c=v.c*s;
return(r);
}

/////////////////////////////////////////////////////////////////////////
//   Sott_vett
/////////////////////////////////////////////////////////////////////////
struct vettore Sott_vett(struct vettore v1,struct vettore v2)
{
struct vettore r;

if (v1.indefinito || v2.indefinito)
   Error("Vettore/i indefinito/i","Sott_vett","geomet");
r.indefinito=FALSE;
r.a=v1.a-v2.a;
r.b=v1.b-v2.b;
r.c=v1.c-v2.c;
return(r);
}

/////////////////////////////////////////////////////////////////////////
//   Somma_vett
/////////////////////////////////////////////////////////////////////////
struct vettore Somma_vett(struct vettore v1,struct vettore v2)
{
struct vettore r;

if (v1.indefinito || v2.indefinito)
   Error("Vettore/i indefinito/i","Somma_vett","geomet");
r.indefinito=FALSE;
r.a=v1.a+v2.a;
r.b=v1.b+v2.b;
r.c=v1.c+v2.c;
return(r);
}

/////////////////////////////////////////////////////////////////////////
//   Punto_piu_vett
/////////////////////////////////////////////////////////////////////////
struct punto Punto_piu_vett(struct punto p,struct vettore v)
{
struct punto pr;

if (p.indefinito || v.indefinito)
   Error("Vettore o punto indefinito/i","Punto_piu_vett","geomet");
pr.indefinito=FALSE;
pr.x=p.x+v.a;
pr.y=p.y+v.b;
pr.z=p.z+v.c;
return(pr);
}

/////////////////////////////////////////////////////////////////////////
//   Modulo
/////////////////////////////////////////////////////////////////////////
float Modulo(struct vettore v)
{

if (v.indefinito)
   Error("Vettore indefinito","Modulo","geomet");
return(sqrt(pow(v.a,2)+pow(v.b,2)+pow(v.c,2)));
}