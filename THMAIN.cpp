/*
NOME_FILE:THMAIN
PROGETTO:Thesis
AUTORE:Emanuele Maria Santanché
DATA_INIZ:Lug 26'92
FILES DOCUMENTAZIONE:THMODULI.DOC, THGRUPPI.DOC, THMAIN.DOC
NOMI FUNZIONI:
   Gruppo MAINFN
      WinMain()
   Gruppo PRESEN
      Presentazione()
   Gruppo PROVEF
      Prove_1()
      Prove_2()
*/

#include "thvarie.h"
#include "thstruct.h"
#include "thprotot.h"
#include "thextern.h"
#include "thvarglo.h"

////////////////////////////////////////////////////////////////////////////
//   WinMain
////////////////////////////////////////////////////////////////////////////
int PASCAL WinMain(HANDLE hInst, HANDLE hPrevInst, LPSTR lpCmdLine,
                   int nCmdShow)
{
static char *op[20] = {
   "Procedura di inizializzazione poliedro in uso.",
   "Procedura di creazione immagini.",
   "Procedura di visualizzazione immagini.",
   "Procedura di lancio di esperimento di loc. e ric. poliedri.",
   "",
   "",
   "",
   "",
   "","","","","","","","","","","",
   "Fine lavoro."
};
static char test[] = "Menù principale del sistema.";
int m;
char c;

// inizializzazioni spicciole
h_programma=hInst;
randomize();
Inizializza_grafica();

Presentazione();
c=getch();
switch (c) {
   case '1':
      Prove_1();
      return(0);
   case '2':
      Prove_2();
      return(0);
}

for (;;) {
   m=Menu(test,op);

   switch (m) {
      case 1:
         Imposta_poliedro();   // modulo MODPOL
         break;
      case 2:
         Crea_immagine();  // modulo IMMAGI
         break;
      case 3:
         Visual_immagine();  // modulo IMMAGI
         break;
      case 4:
         Esperimento_di_ric_poliedri();  // modulo ERICPO
         break;
      case 5:
      case 6:
         break;
      case 7:
         break;
      case 8:
         break;
      case 9:
         break;
      case 11:
         break;
      case 13:
         break;
      case 20:
         clrscr();
         gotoxy(10,10);
         printf("Sei sicuro di voler uscire dal programma (S/N) ? ");
         if (toupper(getche()) != 'S') break;
         fcloseall();
         return 0;
   }
}

}

/*
////////////////////////////////////////////////////////////////////////////
//   Menu_1
////////////////////////////////////////////////////////////////////////////
void Menu_1(void)
{
static char *op[20] = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "","","","",
   "Ritorno al menù principale."
       };
static char test[] =
   "Menù di ";
int m;

for (;;) {
   m=Menu(test,op);

   switch (m) {
      case 1:
         break;
      case 2:
         break;
      case 3:
         break;
      case 4:
         break;
      case 5:
         break;
      case 7:
         break;
      case 8:
         break;
      case 9:
      case 10:
         break;
      case 11:
         break;
      case 12:
         break;
      case 14:
         break;
      case 15:
         break;
      case 16:
         break;
      case 17:
         break;
      case 18:
         break;
      case 19:
         break;
      case 20:
         return;
   }
}

}

////////////////////////////////////////////////////////////////////////////
//   Menu_2
////////////////////////////////////////////////////////////////////////////
void Menu_2(void)
{
static char *op[20] = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "Ritorno al menù principale."
       };
static char test[] =
   "Menù 2                                            ."; // non oltre
                                                          // col. 56
int m;

for (;;) {
   m=Menu(test,op);

   switch (m) {
      case 1:
         break;
      case 2:
         break;
      case 3:
         break;
      case 5:
         break;
      case 6:
         break;
      case 7:
         break;
      case 9:
         break;
      case 10:
         break;
      case 11:
         break;
      case 13:
         break;
      case 14:
         break;
      case 15:
         break;
      case 17:
         break;
      case 18:
         break;
      case 20:
         return;
   }
}
}
*/

////////////////////////////////////////////////////////////////////////////
//   Presentazione
////////////////////////////////////////////////////////////////////////////
void Presentazione(void)
{

clrscr();
gotoxy(1,5);
printf(
"              Laboratorio  software per  la localizzazione e  il\n\n");
printf(
"              riconoscimento  di  poliedri  tramite  ottenimento\n\n");
printf(
"              di   misure  tridimensionali  per  triangolazione.");
gotoxy(1,14);
printf(
"              Autore: Emanuele Maria Santanché (matr. 581501)\n");
gotoxy(1,20);
printf(
"              Premi un tasto per continuare. ");
}

////////////////////////////////////////////////////////////////////////////
//   Prove_1
////////////////////////////////////////////////////////////////////////////
void Prove_1(void)
{
//LPSTR titolo = "Prova";
//int i;
//float x,y;
//struct modello_rotondo mo;
//long double t1,t2;
//struct time tm;
//float c;
//int i;
//FILE *prova;
//FILE *f1;
//FILE *f2;
//int d,i,j;
//long int i,k;
//struct taglio_rett_int t;
//struct elenco_part e;
//int i,j;
//float pro;
//double **m,**mi,**mr;
//int i,j,k;
//double err;
//struct modello_rotondo m;
//struct taglio_rett_int huge *t;
//struct elenco_part e;
//double huge *coeff;
//double huge *rumore_m;
//int huge *discontinuita;
//int i,npun;
//,sal_ram;
//double discor,discos;
//struct retta r;
//struct punto pp,pv;
//unsigned long l, dime;

clrscr();
printf("Hai attivato la sezione prove n.1\n");

/*
//do {
//   Screen_saver(1.7);
//} while (getch() != 'e');
//return;
//scanf("%lu",&dime);
//rumore=(double huge *) farcalloc(dime,sizeof(double));
//if (rumore == NULL) {printf("ciccia");return;}
//for (l=0L;l<dime;l++) rumore[l]=(double) l;
//for (l=0L;l<dime;l+=10000L) printf("%lf\n",rumore[l]);
//getch();
//printf("ok!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
//farfree(rumore);
//return;

Carica_modrot(1,&m);
Inizializza_filtri();
//printf("salto=0 rampa=1 ");
//scanf("%d",&sal_ram);

for (;;) {

clrscr();

npun=60;
rumore_m=vector(0,npun-1);
//coeff=vector(0,15);
discontinuita=ivector(0,npun-1);
t=Alloca_taglio();
t->n_punti=npun;
pp.indefinito=FALSE;
pp.x=0;
pp.y=0;
pp.z=-500;
pv.indefinito=FALSE;
pv.x=0;
pv.y=200;
pv.z=-500;
r=Crea_retta(0,0,0,20,0,0);

Crea_taglio_rett_int(&pp,pv,r,npun,t);
//for (i=0;i<16;i++) coeff[i]=0.0;
//coeff[0]=500.0;
//coeff[1]=0.2;
//coeff[2]=0.002;
//discor=0.0;
//discos=0.0;
//if (sal_ram) {
//   printf("disc ramp: ");
//   scanf("%lf",&discor);
//}
//else {
//   printf("disc salt: ");
//   scanf("%lf",&discos);
//}
//for (i=0;i<t->n_punti;i++) {
//   t->p[i].dist_r=Valuta_polinomio(2,i,coeff)+Ranf(-1,1)
//                 +((i>25) ? (discor*(i-25)+discos) : 0);    //Ranf(-2,2)
//   t->p[i].pr.indefinito=FALSE;
//}
for (i=30;i<t->n_punti;i++) {
   t->p[i].dist_r+=0;
}
Partiziona_taglio(t,&e);
Valuta_rumore(t,       // buchi già attappati
              &e,       // già calcolato
              rumore_m);
Trova_discontinuita(t,   // buchi già attappati
                    &e,            // già calcolato
                    rumore_m,                   // già valutato
                    discontinuita);
for (i=0;i<t->n_punti;i++) {
   if (!(i%10)) printf("\n");
   if (!t->p[i].pr.indefinito)
      printf("%7.2lf",t->p[i].dist_r);
   else
      printf("       ");
}
for (i=0;i<t->n_punti;i++) {
   if (!(i%10)) printf("\n");
   printf("%7.2lf",rumore_m[i]);
}
//printf("%7d",t->n_punti);
for (i=0;i<t->n_punti;i++) {
   if (!(i%10)) printf("\n");
   if (discontinuita[i] !=0)
      printf("%7d",discontinuita[i]);
   else
      printf("     . ");
}

free_ivector(discontinuita,0);
//free_vector(coeff,0);
free_vector(rumore_m,0);
Dealloca_taglio(t);

if (getch() == 'e') break;

}

Dealloca_filtri();




//sqme=0.0;
//for (i=0;i<10000;i++) sqme+=pow(Ranf(-1,1),2);
//sqme=sqrt(sqme/10000);
//printf("s=%lf (teor=%lf)",sqme,1/sqrt(3));getch();

Inizializza_filtri();

for (;;) {

clrscr();
t.n_punti=100;
coeff=vector(0,10);
coeff_fit=vector(0,10);
rumore=vector(0,t.n_punti-1);
//seg_distanze=vector(0,t.n_punti-1);
//seg_rumore=vector(0,t.n_punti-1);
printf("b\n");
for (i=0;i<11;i++) coeff[i]=0.0;
for (i=0;i<11;i++) coeff_fit[i]=0.0;
//for (i=0;i<t.n_punti;i++) seg_distanze[i]=0.0;
//for (i=0;i<t.n_punti;i++) seg_rumore[i]=0.0;
coeff[0]=500.0;
coeff[1]=0.2;
coeff[2]=0.002;
printf("inizio filtro disc: ");
scanf("%d %d %lf",&inizio,&nf,&disco);
avanti=FALSE;
lungh=descr_filtri[nf].lungh_supp;
for (i=0;i<t.n_punti;i++)
   t.p[i].dist_r=Valuta_polinomio(2,i,coeff)+Ranf(-1,1)
                 +((i>50) ? disco : 0);
for (i=0;i<t.n_punti;i++) rumore[i]=1.0;
printf("a\n");

Esegui_fitting(&t,
                    FALSE,
                    rumore,
                    inizio,         //inizio
                    nf,         //int num_filtro,
                    avanti,      //BOOL avanti,
                    coeff_fit, //double *coeff,
                    &sqme,     //double *sqme,
                    &prob,      //double *prob,
                    &accett);     // BOOL *accettato)
printf("c");
if (avanti)
   for (i=inizio;i<inizio+lungh;i++) {
      if (!(i%10)) printf("\n");
      printf("%7.2lf",t.p[i].dist_r);
   }
else
   for (i=inizio;i>inizio-lungh;i--) {
      if (!(i%10)) printf("\n");
      printf("%7.2lf",t.p[i].dist_r);
   }
printf("\nbbb");
for (i=0;i<7;i++) {
   if (!(i%4)) printf("\n");
   printf("%15.6lf",coeff_fit[i]);
}
printf("\nsqme=%lf intern=%d supp=%d  acc=%d ",
        sqme,(int) (prob*lungh+0.1),lungh,accett);
//printf("\nbbb\n");
//for (i=0;i<20;i++) {
//   if (!(i%10)) printf("\n");
//   printf("%7.3lf",seg_rumore[i]);
//}
free_vector(coeff,0);
free_vector(coeff_fit,0);
free_vector(rumore,0);
//free_vector(seg_distanze,0);
//free_vector(seg_rumore,0);

if (getch() == 'e') break;

}

Dealloca_filtri();


Inizializza_filtri();

for (i=0;i<NUM_FILTRI;i++) {
   clrscr();
   printf("ord=%d lungh=%d",descr_filtri[i].ord_fitt,
                            descr_filtri[i].lungh_supp);
   for (j=0;j<=descr_filtri[i].ord_fitt;j++)
      for (k=0;k<min(descr_filtri[i].lungh_supp,10);k++) {
         gotoxy(k*8,j+3);
         printf("%7.3lf",descr_filtri[i].filtro[j][k]);
      }
   getch();
}
Dealloca_filtri();

printf("N=");
scanf("%d",&n);
if (n==0) return;
m=matrix(0,n-1,0,n-1);
mi=matrix(0,n-1,0,n-1);
mr=matrix(0,n-1,0,n-1);

for (;;) {

for (i=0;i<n;i++)
   for (j=0;j<n;j++) {
      //gotoxy(j*10,i+4);
      m[i][j]=Ranf(-1000,1000);
      //scanf("%lf",&m[i][j]);
   }
Inversa(m,n,mi);
Prod_matr(m,n,n,mi,n,n,mr);
for (i=0;i<n;i++)
   for (j=0;j<n;j++) {
      gotoxy(j*10,i+6+n);
      printf("%9.3lf",mi[i][j]);
   }
for (i=0;i<n;i++)
   for (j=0;j<n;j++) {
      gotoxy(j*10,i+8+2*n);
      printf("%9.5lf",mr[i][j]);
   }
err=0.0;
for (i=0;i<n;i++)
   for (j=0;j<n;j++)
      err+=fabs(mr[i][j]-((i==j) ? 1.0 : 0.0));
printf("err= %lE\n",err);
//gotoxy(20,1);
//printf("%lf",d);
if (getch() == 'e') break;

}

free_matrix(m,0,n-1,0);
free_matrix(mi,0,n-1,0);
free_matrix(mr,0,n-1,0);


for (;;) {

scanf("%f",&pro);
if (pro < 0) break;
t.n_punti=100;
for (i=0;i<t.n_punti;i++) {
   t.p[i].pr.indefinito=(Ranf(0,1) > pro ? TRUE : FALSE);
   t.p[i].dist_r=Ranf(0,100);
}
Partiziona_taglio(&t,&e);
for (i=0;i<50;i++) printf("%1d",i/10);
printf("\n");
for (i=0;i<50;i++) printf("%1d",i%10);
printf("\n");
for (i=0;i<t.n_punti;i++) {
   if (i==50) printf("\n");
   printf("%1d",t.p[i].pr.indefinito);
}
printf("\n\n");
j=0;
for (i=0;i<e.n_part;i++) {
   if (j==4) {
      j=0;
      printf("\n");
   }
   j++;
   printf("%1d %3d %3d %3d %3d|",e.part[i].stato,e.part[i].da,
                             e.part[i].a,e.part[i].lungh,e.part[i].n_stato);
}
printf("\n");
Tappa_buchi_dist(&t,&e);
for (i=0;i<50;i++) printf("%1d",i/10);
printf("\n");
for (i=0;i<50;i++) printf("%1d",i%10);
printf("\n");
for (i=0;i<t.n_punti;i++) {
   if (i==50) printf("\n");
   printf("%1d",t.p[i].pr.indefinito);
}
printf("\n");
for (i=0;i<25;i++) printf("%3d",i/10);
printf("\n");
for (i=0;i<25;i++) printf("%3d",i%10);
printf("\n");
for (i=0;i<t.n_punti;i++) {
   if (!(i%25)) printf("\n");
   printf("%3.0f",t.p[i].dist_r);
}
printf("\n\n");
}

Crea_immagine();

k=WinExec((LPSTR) "c:\\dos\\qbasic.exe /run c:\\thbas\\visuimg.bas",0);
for (i=0;i<20000L;i++);
printf("ok? %ld\n",k);
Aspetta_return();

Immagine();

f1=fopen("c:\\thdata\\m5-1.img","rb");
f2=fopen("c:\\thdata\\nuovo.img","wb");
for (i=0;i<200;i++) {
   for (j=0;j<320;j++) {
      fread(&d,sizeof(int),1,f1);
      if (d == 31590) d=0;
      fwrite(&d,sizeof(int),1,f2);
   }
}
fclose(f1);
fclose(f2);

Apri_fin_graf((LPSTR) "Prova");
printf("driverversion=%X\n",GetDeviceCaps(DC_fin_graf,DRIVERVERSION));
printf("horzres=%d\n",GetDeviceCaps(DC_fin_graf,HORZRES));
printf("vertres=%d\n",GetDeviceCaps(DC_fin_graf,VERTRES));
printf("bitspixel=%d\n",GetDeviceCaps(DC_fin_graf,BITSPIXEL));
printf("colorres=%d\n",GetDeviceCaps(DC_fin_graf,COLORRES));
printf("rastercaps=%X\n",GetDeviceCaps(DC_fin_graf,RASTERCAPS));
Chiudi_fin_graf(0);

prova=fopen("c:\\temp\\provates.del","wt");
fprintf(prova,"prova di stampa su file\n");
fprintf(prova,"prova di stampa su file2\n\f");
fprintf(prova,"prova di stampa su file dopo f\n");
fclose(prova);

t1=20;
t2=30;
t1=t2=300;
printf("%Lf %Lf\n",t1,t2);

c=1E15;
//printf("8087=%d\n",_8087);
//printf("bioseq=%o\n",biosequip());
gettime(&tm);
t1=(((long double)tm.ti_hour)*360000+((long double)tm.ti_min)*6000+
    ((long double)tm.ti_sec)*100+((long double)tm.ti_hund));
for (i=0;i<10000;i++) {
   c=pow(c,1.99);
   c=sqrt(c);
   c=c+M_PI;
   c=c/M_E;
}
gettime(&tm);
t2=(((long double)tm.ti_hour)*360000+((long double)tm.ti_min)*6000+
    ((long double)tm.ti_sec)*100+((long double)tm.ti_hund));
printf("time1=  %Lf\ntime2=  %Lf\ntime= %Lf\nc=  %f",t1,t2,t2-t1,c);

printf("%d %d %d",sizeof(float),sizeof(double),sizeof(long double));
do {
mo=Crea_modello_rotondo();
if (toupper(getch()) == 'V') {
   Visual_dati_modrot(0,&mo);
   Visual_spezz_modrot(0,&mo);
}
printf("Ancora?");
} while (toupper(getch()) == 'S');
do {
   scanf("%f %f",&x,&y);
   printf("%f\n",RAD_GRA*atan2(y,x));
}  while ((x != 1.5));
return;
for (i=0;i<100;i++) {
   gotoxy(10,10);
   printf("%3d",i);
   mo=Crea_modello_rotondo();
}
return;
printf("\n\n\n %d",sizeof(struct modello_rotondo));
printf("\n\nraggio ");
scanf("%d",&i);
Apri_fin_graf(titolo);
Vai_a(-100,0);
Linea_a(100,00);
Cerchio_vuoto(0,0,i);
Vai_a(0,-100);
Linea_a(100,0);
Cerchio_pieno(50,-50,i);
Mostra_disegno();
Aspetta_return();
Chiudi_fin_graf(NON_INV_A_CLIPBOARD);
return;
*/
return;
} // Prove_1

////////////////////////////////////////////////////////////////////////////
//   Prove_2
////////////////////////////////////////////////////////////////////////////
void Prove_2(void)
{
//struct modello_rotondo m;
//struct retta rt;
//struct punto pp,pv;
//,pi,pir;
//float distanza,param_retta,dist_rum;
//double sum_err,sum_quad_err,sum_err_dist,sum_quad_err_dist,err,err_dist,
//       med_err,dev_err,med_err_dist,dev_err_dist;
//long i,mo;
//struct elenco_spigoli es;
//double ascis;
//double huge *co;

clrscr();
printf("Hai attivato la sezione prove n.2\n");

/*
co=vector(0,5);
co[0]=501.8050;
co[1]=0.05306;
co[2]=-0.045;
co[3]=0.0057;
mo=0;
for (i=0;i<50000;i++)
   if (fabs(Valuta_polinomio(3,-0.5,co)) > 1000) mo++;
printf("%d",mo);
//for (i=0;i<10000;i++) ascis=pow(Ranf(-1,-0.001),1.5);
//for (i=0;i<10000;i++) ascis=pow(Ranf(-100,-0.001),1.5);
//for (i=0;i<50000;i++) ascis=pow(Ranf(0.001,1.001),1.5);
//for (i=0;i<50000;i++) ascis=pow(Ranf(0.001,100.001),1.5);
free_vector(co,0);


do {
   printf("mod=");
   scanf("%d",&mo);
   if (mo == 0) return;
   printf("x=");
   scanf("%lf",&ascis);
   Carica_modrot(mo,&m);
   pp.indefinito=FALSE;
   pv.indefinito=FALSE;
   pp.x=0;
   pp.y=0;
   pp.z=500;
   pv.x=200;
   pv.y=0;
   pv.z=500;
   rt=Crea_retta(-ascis,0,0,ascis,0,0);
   Cerca_spigoli_teorici_in_taglio(&m,pp,pv,&rt,&es);
   printf("nspig=%d\n",es.n_spigoli);
   for (i=0;i<es.n_spigoli;i++) {
      printf("n=%3d x=%7.3f y=%7.3f z=%7.3f elem=%3d\n",
             i,es.spigolo[i].x,es.spigolo[i].y,es.spigolo[i].z,
             es.spigolo[i].elem);
   }
} while (TRUE);

do {

r=Crea_retta(42.2,0.0,-500.0,42.2,0.0,0.0);
pv.indefinito=FALSE;
pv.x=42.2;
pv.y=500.0;
pv.z=-500.0;
Carica_modrot(1,&m);
sum_err=0.0;
sum_quad_err=0.0;
sum_err_dist=0.0;
sum_quad_err_dist=0.0;
for (i=0;i<1000;i++) {
   Triangola_modrot(&m,r,pv,
                 &pi,&distanza,&param_retta,
                 &pir,&dist_rum,
                 TRUE);
   err=sqrt(pow(pi.x-pir.x,2)+pow(pi.y-pir.y,2)+pow(pi.z-pir.z,2));
   err_dist=distanza-dist_rum;
   sum_err+=err;
   sum_err_dist+=err_dist;
   sum_quad_err+=pow(err,2);
   sum_quad_err_dist+=pow(err_dist,2);
}
med_err=sum_err/1000;
dev_err=sqrt(sum_quad_err/1000-pow(med_err,2));
med_err_dist=sum_err_dist/1000;
dev_err_dist=sqrt(sum_quad_err_dist/1000-pow(med_err_dist,2));
printf("med err     =%7.3lf   dev err     =%7.3lf\n",med_err,dev_err);
printf("med err dist=%7.3lf   dev err dist=%7.3lf\n",
       med_err_dist,dev_err_dist);

} while (getch() != '1');
*/
}