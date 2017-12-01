/*
NOME_FILE:MODPOL
PROGETTO:Thesis
AUTORE:Emanuele Maria Santanché
DATA_INIZ:Gen 6'93
FILES DOCUMENTAZIONE:THMODULI.DOC, THGRUPPI.DOC, MODPOLDF.DOC
NOMI FUNZIONI:
   Gruppo IMPOST
      Imposta poliedro()
   Gruppo INTERS
      Triangola_modpol()
   Gruppo RUMORE
      Aggiungi_rumore_misura()
*/

#include "thvarie.h"
#include "thstruct.h"
#include "thprotot.h"
#include "thextern.h"

/////////////////////////////////////////////////////////////////////////
//   Imposta poliedro
/////////////////////////////////////////////////////////////////////////
void Imposta_poliedro(void)
{

clrscr();
printf("\n   Impostazione poliedro in uso.\n\n");
//printf("   Sei sicuro di voler eseguire la funzione (S/N) ? ");
//if (toupper(getch()) != 'S') return;

do {
   gotoxy(4,10);
   printf("Numero poliedro ? (1-2) ");
   clreol();
   scanf("%d",&POLI);
} while ((POLI < 1) || (POLI > 2));

POLI--;

POL[0].n_vertici=6;
POL[0].n_facce=3;
POL[0].v[0].indefinito=FALSE;
POL[0].v[0].x=70.0;     POL[0].v[0].y=-100.0;   POL[0].v[0].z=0.0;
POL[0].v[1].indefinito=FALSE;
POL[0].v[1].x=10.0;     POL[0].v[1].y=-100.0;   POL[0].v[1].z=100.0;
POL[0].v[2].indefinito=FALSE;
POL[0].v[2].x=20.0;     POL[0].v[2].y=-30.0;    POL[0].v[2].z=0.0;
POL[0].v[3].indefinito=FALSE;
POL[0].v[3].x=25.0;     POL[0].v[3].y=45.0;     POL[0].v[3].z=0.0;
POL[0].v[4].indefinito=FALSE;
POL[0].v[4].x=21.088952;POL[0].v[4].y=74.594070;POL[0].v[4].z=110.324744;
POL[0].v[5].indefinito=FALSE;
POL[0].v[5].x=65.0;     POL[0].v[5].y=100.0;    POL[0].v[5].z=0.0;
POL[0].f[0].n_vert=3;
POL[0].f[0].nv[0]=0;
POL[0].f[0].nv[1]=2;
POL[0].f[0].nv[2]=1;
POL[0].f[0].n.indefinito=FALSE;
POL[0].f[0].n.a=0.731232523845;
POL[0].f[0].n.b=0.522308945603;
POL[0].f[0].n.c=0.438739514307;
POL[0].f[0].d=-(POL[0].f[0].n.a*POL[0].v[0].x+
                POL[0].f[0].n.b*POL[0].v[0].y+POL[0].f[0].n.c*POL[0].v[0].z);
POL[0].f[1].n_vert=4;
POL[0].f[1].nv[0]=1;
POL[0].f[1].nv[1]=2;
POL[0].f[1].nv[2]=3;
POL[0].f[1].nv[3]=4;
POL[0].f[1].n.indefinito=FALSE;
POL[0].f[1].n.a=0.996375358272;
POL[0].f[1].n.b=-0.0664250238848;
POL[0].f[1].n.c=0.0531400191079;
POL[0].f[1].d=-(POL[0].f[1].n.a*POL[0].v[2].x+
                POL[0].f[1].n.b*POL[0].v[2].y+POL[0].f[1].n.c*POL[0].v[2].z);
POL[0].f[2].n_vert=3;
POL[0].f[2].nv[0]=5;
POL[0].f[2].nv[1]=4;
POL[0].f[2].nv[2]=3;
POL[0].f[2].n.indefinito=FALSE;
POL[0].f[2].n.a=0.795035843166;
POL[0].f[2].n.b=-0.578207885939;
POL[0].f[2].n.c=0.183285702446;
POL[0].f[2].d=-(POL[0].f[2].n.a*POL[0].v[3].x+
                POL[0].f[2].n.b*POL[0].v[3].y+POL[0].f[2].n.c*POL[0].v[3].z);

DIE[0].n1=POL[0].f[0].n;
DIE[0].n2=POL[0].f[1].n;
DIE[0].n3=POL[0].f[2].n;
DIE[0].fi=0.872444966513;
DIE[0].d1=217.342890993;
DIE[0].d2=194.537112928;
DIE[0].fi1=0.734526125079;
DIE[0].fi2=0.582281308174;

POL[1].n_vertici=6;
POL[1].n_facce=3;
POL[1].v[0].indefinito=FALSE;
POL[1].v[0].x=63.448237;POL[1].v[0].y=-87.164707;POL[1].v[0].z=0.0;
POL[1].v[1].indefinito=FALSE;
POL[1].v[1].x=40.436550;POL[1].v[1].y=-74.981785;POL[1].v[1].z=93.159988;
POL[1].v[2].indefinito=FALSE;
POL[1].v[2].x=30.0;POL[1].v[2].y=-50.0;POL[1].v[2].z=0.0;
POL[1].v[3].indefinito=FALSE;
POL[1].v[3].x=15.0;POL[1].v[3].y=35.0;POL[1].v[3].z=0.0;
POL[1].v[4].indefinito=FALSE;
POL[1].v[4].x=10.0;POL[1].v[4].y=100;POL[1].v[4].z=100.0;
POL[1].v[5].indefinito=FALSE;
POL[1].v[5].x=70.0;POL[1].v[5].y=100.0;POL[1].v[5].z=0.0;
POL[1].f[0].n_vert=3;
POL[1].f[0].nv[0]=0;
POL[1].f[0].nv[1]=2;
POL[1].f[0].nv[2]=1;
POL[1].f[0].n.indefinito=FALSE;
POL[1].f[0].n.a=0.739884113265;
POL[1].f[0].n.b=0.665895701937;
POL[1].f[0].n.c=0.0956786971077;
POL[1].f[0].d=-(POL[1].f[0].n.a*POL[1].v[0].x+
                POL[1].f[0].n.b*POL[1].v[0].y+POL[1].f[0].n.c*POL[0].v[0].z);

POL[1].f[1].n_vert=4;
POL[1].f[1].nv[0]=1;
POL[1].f[1].nv[1]=2;
POL[1].f[1].nv[2]=3;
POL[1].f[1].nv[3]=4;
POL[1].f[1].n.indefinito=FALSE;
POL[1].f[1].n.a=0.982790317886;
POL[1].f[1].n.b=0.173433585509;
POL[1].f[1].n.c=-0.0635923146867;
POL[1].f[1].d=-(POL[1].f[1].n.a*POL[1].v[2].x+
                POL[1].f[1].n.b*POL[1].v[2].y+POL[1].f[1].n.c*POL[1].v[2].z);

POL[1].f[2].n_vert=3;
POL[1].f[2].nv[0]=5;
POL[1].f[2].nv[1]=4;
POL[1].f[2].nv[2]=3;
POL[1].f[2].n.indefinito=FALSE;
POL[1].f[2].n.a=0.694046871841;
POL[1].f[2].n.b=-0.587270430019;
POL[1].f[2].n.c=0.416428123105;
POL[1].f[2].d=-(POL[1].f[2].n.a*POL[1].v[3].x+
                POL[1].f[2].n.b*POL[1].v[3].y+POL[1].f[2].n.c*POL[1].v[3].z);

DIE[1].n1=POL[1].f[0].n;
DIE[1].n2=POL[1].f[1].n;
DIE[1].n3=POL[1].f[2].n;
DIE[1].fi=0.850370306195;
DIE[1].d1=193.421130232;
DIE[1].d2=229.884991174;
DIE[1].fi1=0.522043288373;
DIE[1].fi2=0.737906765854;

}

/////////////////////////////////////////////////////////////////////////
//   Triangola_modpol
/////////////////////////////////////////////////////////////////////////
void Triangola_modpol(struct retta r,struct punto pv,
                      struct punto *pi,float *distanza,float *param_retta,
                      struct punto *pir,float *dist_rum)
{
struct punto p_i,p_da,p_a,pp;
struct vettore vets,veti,pvsi;
struct vettore n_def,vers_r,vers_rv;
int i,j,da,a,fac;
BOOL dentro,non_ok_vis;
struct retta rv; // retta punto di vista - punto di interezione con il
                 // modello
double c1,c2,t,psnb,dist_i;

pp.indefinito=FALSE;
pp.x=r.xp;
pp.y=r.yp;
pp.z=r.zp;
*distanza=1E38;
*param_retta=0.0;
fac=-1;
pi->indefinito=TRUE;
pir->indefinito=TRUE;
for (i=0;i<POL[POLI].n_facce;i++) {
   // intersezione retta piano i
   t=-(POL[POLI].f[i].n.a*r.xp+POL[POLI].f[i].n.b*r.yp+
       POL[POLI].f[i].n.c*r.zp+POL[POLI].f[i].d)/
       (POL[POLI].f[i].n.a*r.xap+POL[POLI].f[i].n.b*r.yap+
        POL[POLI].f[i].n.c*r.zap);
   p_i=Punto_da_retta(r,t);
   // controllo che il punto sia dentro la faccia
   dentro=TRUE;
   for (j=0;j<POL[POLI].f[i].n_vert;j++) {
       da=POL[POLI].f[i].nv[j];
       if (j<POL[POLI].f[i].n_vert-1)
          a=POL[POLI].f[i].nv[j+1];
       else
          a=POL[POLI].f[i].nv[0];
       p_da=POL[POLI].v[da];
       p_a=POL[POLI].v[a];
       vets=Vett_tra_punti(p_da,p_a);
       veti=Vett_tra_punti(p_da,p_i);
       pvsi=Prod_vett(vets,veti);
       psnb=Prod_scal(pvsi,POL[POLI].f[i].n);
       if (psnb < 0) {
          dentro=FALSE;
          exit;
       }
   }
   if (dentro) {
      dist_i=sqrt(pow(pp.x-p_i.x,2)+pow(pp.y-p_i.y,2)+pow(pp.z-p_i.z,2));
      if (dist_i < *distanza) {
         fac=i;
         *pi=p_i;
         n_def=POL[POLI].f[fac].n;
         *distanza=dist_i;
      }
   }
} // fine ciclo facce ricerca intersezione
if (fac == -1) {
   pi->indefinito=TRUE;
   pir->indefinito=TRUE;
   return;
}

rv=Crea_retta(pv.x,pv.y,pv.z,pi->x,pi->y,pi->z);
non_ok_vis=FALSE;
for (i=0;i<POL[POLI].n_facce;i++) {
   if (i == fac) continue;
   // intersezione retta piano i
   t=-(POL[POLI].f[i].n.a*rv.xp+POL[POLI].f[i].n.b*rv.yp+
       POL[POLI].f[i].n.c*rv.zp+POL[POLI].f[i].d)/
       (POL[POLI].f[i].n.a*rv.xap+POL[POLI].f[i].n.b*rv.yap+
        POL[POLI].f[i].n.c*rv.zap);
   p_i=Punto_da_retta(rv,t);
   // controllo che il punto sia dentro la faccia
   dentro=TRUE;
   for (j=0;j<POL[POLI].f[i].n_vert;j++) {
       da=POL[POLI].f[i].nv[j];
       if (j < POL[POLI].f[i].n_vert-1)
          a=POL[POLI].f[i].nv[j+1];
       else
          a=POL[POLI].f[i].nv[0];
       p_da=POL[POLI].v[da];
       p_a=POL[POLI].v[a];
       vets=Vett_tra_punti(p_da,p_a);
       veti=Vett_tra_punti(p_da,p_i);
       pvsi=Prod_vett(vets,veti);
       psnb=Prod_scal(pvsi,POL[POLI].f[i].n);
       if (psnb < 0) {
          dentro=FALSE;
          exit;
       }
   }
   if (dentro) {
      if (t < 0.99999) {
         non_ok_vis=TRUE;
         exit;
      }
   }
} // fine ciclo facce controllo visibilità
if (non_ok_vis) {
   pi->indefinito=TRUE;
   pir->indefinito=TRUE;
   return;
}

// controllo "doppia faccia"
vers_r=Versore_da_retta(r);
vers_rv=Versore_da_retta(rv);
c1=Coseno_tra_versori(n_def,vers_r);
c2=Coseno_tra_versori(n_def,vers_rv);
if ((c1*c2) < 0) {
   pi->indefinito=TRUE;
   pir->indefinito=TRUE;
   return;
}
Aggiungi_rumore_misura(r,n_def,*pi,pv,pir);
*dist_rum=sqrt(pow(pp.x-pir->x,2)+pow(pp.y-pir->y,2)+pow(pp.z-pir->z,2));
} // Triangola_modrot


/////////////////////////////////////////////////////////////////////////
//   Aggiungi_rumore_misura
/////////////////////////////////////////////////////////////////////////
void Aggiungi_rumore_misura(struct retta rp,struct vettore n,
                            struct punto pi,struct punto pv,
                            struct punto *pr)
{
struct vettore vrp,agg_cas,vrv,vnrv,vnrp,base_line,vt1,vt2,vq1,vq2;
double rxy,ca,sa,segno;
struct retta new_rp,rv,new_rv;
struct punto pit,pp,p1,p2;
double alfa,modulo,scal_retta_normale_piano,dp,ti,psvp,den,t,q;

pp.indefinito=FALSE;
pp.x=rp.xp;
pp.y=rp.yp;
pp.z=rp.zp;
vrp=Versore_da_retta(rp);
// aggiunta deviazione casuale a retta di proiezione laser
alfa=Ranf(0,M_PI);
segno=((Ranf(-1,1) < 0) ? -1 : 1);
modulo=Ranf(0,DEV_ANG_MAX_LASER);
ca=cos(alfa);
sa=sqrt(1-pow(ca,2));
rxy=sqrt(pow(vrp.a,2)+pow(vrp.b,2));
if (!Lz(rxy)) {
   agg_cas.a=(-(vrp.c*ca*vrp.a+vrp.b*sa*segno)/rxy)*modulo;
   agg_cas.b=((-vrp.c*ca*vrp.b+vrp.a*sa*segno)/rxy)*modulo;
   agg_cas.c=ca*rxy*modulo;
}
else {
   agg_cas.a=modulo*ca;
   agg_cas.b=modulo*sa*segno;
   agg_cas.c=0;
}
new_rp=Crea_retta(rp.xp,rp.yp,rp.zp,
                     rp.xp+vrp.a+agg_cas.a,
                     rp.yp+vrp.b+agg_cas.b,
                     rp.zp+vrp.c+agg_cas.c);
// interseco con il piano linearizzazione della superficie del modello
// nel punto di intersezione
scal_retta_normale_piano=n.a*new_rp.xap+n.b*new_rp.yap+n.c*new_rp.zap;
// se scal_retta_normale_piano è nullo, vuol dire che la retta di
// proiezione del laser (rp) giace sul piano tangente alla superficie
// del modello nel punto di intersezione. Tale punto di intersezione
// venne ovviamente trovato convenzionalmente da Interseca_retta_cono
// o Interseca_retta_cilindro o Interseca_retta_piano perchè in realtà
// ovviamente non esiste
if (!Lz(scal_retta_normale_piano)) {
   dp=-(n.a*pi.x+n.b*pi.y+n.c*pi.z);
   ti=-(dp+n.a*new_rp.xp+n.b*new_rp.yp+n.c*new_rp.zp)/
        scal_retta_normale_piano;
   pit.x=new_rp.xp+new_rp.xap*ti;
   pit.y=new_rp.yp+new_rp.yap*ti;
   pit.z=new_rp.zp+new_rp.zap*ti;
   rv=Crea_retta(pv.x,pv.y,pv.z,
                 pit.x,pit.y,pit.z);
   // aggiunta deviazione casuale a retta di vista
   vrv=Versore_da_retta(rv);
   alfa=Ranf(0,M_PI);
   segno=((Ranf(-1,1) < 0) ? -1 : 1);
   modulo=Ranf(0,DEV_ANG_MAX_PSD);
   ca=cos(alfa);
   sa=sqrt(1-pow(ca,2));
   rxy=sqrt(pow(vrv.a,2)+pow(vrv.b,2));
   if (!Lz(rxy)) {
      agg_cas.a=(-(vrv.c*ca*vrv.a+vrv.b*sa*segno)/rxy)*modulo;
      agg_cas.b=((-vrv.c*ca*vrv.b+vrv.a*sa*segno)/rxy)*modulo;
      agg_cas.c=ca*rxy*modulo;
   }
   else {
      agg_cas.a=modulo*ca;
      agg_cas.b=modulo*sa*segno;
      agg_cas.c=0;
   }
   new_rv=Crea_retta(rv.xp,rv.yp,rv.zp,
                     rv.xp+vrv.a+agg_cas.a,
                     rv.yp+vrv.b+agg_cas.b,
                     rv.zp+vrv.c+agg_cas.c);
   // formula per parametro t
   vnrp=Versore_da_retta(new_rp);
   vnrv=Versore_da_retta(new_rv);
   base_line=Vett_tra_punti(pp,pv);
   psvp=Prod_scal(vnrp,vnrv);
   den=1-pow(psvp,2);
   vt1=Vett_per_scal(psvp,vnrv);
   vt2=Sott_vett(vt1,vnrp);
   t=Prod_scal(base_line,vt2)/den/new_rp.cd;
   vq1=Vett_per_scal(psvp,vnrp);
   vq2=Sott_vett(vq1,vnrv);
   q=-Prod_scal(base_line,vq2)/den/new_rv.cd;
   p1=Punto_da_retta(new_rp,t);
   p2=Punto_da_retta(new_rv,q);
   pr->indefinito=FALSE;
   pr->x=(p1.x+p2.x)/2;
   pr->y=(p1.y+p2.y)/2;
   pr->z=(p1.z+p2.z)/2;
   if ( (pow(pr->x-pi.x,2)+pow(pr->y-pi.y,2)+pow(pr->z-pi.z,2))
         > MAX_ALLONTANAMENTO_PER_RUMORE )
      pr->indefinito=TRUE;
}
else
   pr->indefinito=TRUE;
} // Aggiungi_rumore_misura

