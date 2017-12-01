/*
NOME_FILE:TAGLIO
PROGETTO:Thesis
AUTORE:Emanuele Maria Santanché
DATA_INIZ:Set 14'92
FILES DOCUMENTAZIONE:THMODULI.DOC, THGRUPPI.DOC, TAGLIODF.DOC
NOMI FUNZIONI:
   Gruppo CREAZI
      Crea_taglio_rett_int()
      Crea_taglio_rett_file()
      Alloca_taglio()
      Dealloca_taglio()
   Gruppo GESFIL
      Creaz_e_salvat_taglio_rett_inter()
      Creaz_e_salvat_taglio_rett_cas()
      Genera_cas_rette_taglio()
      Scegli_file_taglio_rett()
      Scegli_e_carica_taglio_rett()
      Carica_taglio_rett()
      Esiste_file_tagli()
   Gruppo VISUAL
      Carica_e_visual_taglio_rett()
      Visual_dati_taglio_rett()
      Visual_graf_taglio_rett()
*/

#include "thvarie.h"
#include "thstruct.h"
#include "thprotot.h"
#include "thextern.h"

/////////////////////////////////////////////////////////////////////////
//   Crea_taglio_rett_int
/////////////////////////////////////////////////////////////////////////
void Crea_taglio_rett_int(struct punto *pp,
                          struct punto pv,
                          struct retta rt,
                          int n_punti,
                          struct taglio_rett_int huge *t)
{
float interv,dist_i,dist_r,par;
int i;
struct retta rp;
struct punto prt,pi,pr;

if (n_punti == 0)
   Error("Nessun punto!","Crea_taglio_rett_int","taglio");
if (n_punti > NUM_MAX_PUNTI_INT)
   Error("Troppi punti !","Crea_taglio_rett_int","taglio");
interv=1/(double) n_punti;
t->n_punti=n_punti;
for (i=0;i<n_punti;i++) {
   prt=Punto_da_retta(rt,interv*i);
   rp=Crea_retta(pp->x,pp->y,pp->z,
                 prt.x,prt.y,prt.z);
   Triangola_modpol(rp,pv,&pi,&dist_i,&par,&pr,&dist_r);
   if (!pi.indefinito) {
      t->p[i].pi=pi;
      t->p[i].dist_i=dist_i;
   }
   else {
      t->p[i].pi.indefinito=TRUE;
   }
   if (!pr.indefinito) {
      t->p[i].pr=pr;
      t->p[i].dist_r=dist_r;
   }
   else {
      t->p[i].pr.indefinito=TRUE;
   }
}
} // Crea_taglio_rett_int

/*
/////////////////////////////////////////////////////////////////////////
//   Crea_taglio_rett_file
/////////////////////////////////////////////////////////////////////////
void Crea_taglio_rett_file(int n_modello,
                           struct modello_rotondo *m,
                           struct punto *pp,
                           struct punto pv,
                           struct retta rt,
                           int n_punti,
                           struct taglio_rett_file *t,
                           BOOL no_rum_mod)
{
struct date data;
struct time ora;
char sdata[9];
char sora[9];
struct taglio_rett_int huge *ti;
int i;

if (n_punti > NUM_MAX_PUNTI_FILE)
   Error("Troppi punti !","Crea_taglio_rett_file","taglio");
// data e ora di creazione vengono scritti nel taglio
ti=Alloca_taglio();
getdate(&data);
gettime(&ora);
sprintf(sdata,"%02d/%02d/%02d",data.da_day,data.da_mon,data.da_year%100);
sprintf(sora,"%02d:%02d:%02d",ora.ti_hour,ora.ti_min,ora.ti_sec);
Crea_campo(t->data,sdata,8);
Crea_campo(t->ora,sora,8);
t->n_punti=n_punti;
t->pp=*pp;
t->pv=pv;
t->rt=rt;
t->n_modello=n_modello;
Crea_taglio_rett_int(m,pp,pv,rt,n_punti,ti,no_rum_mod);
for (i=0;i<n_punti;i++) {
   if (!ti->p[i].pi.indefinito) {
      t->p[i].pi=ti->p[i].pi;
      t->p[i].dist_i=ti->p[i].dist_i;
   }
   else {
      t->p[i].pi.indefinito=TRUE;
   }
   if (!ti->p[i].pr.indefinito) {
      t->p[i].pr=ti->p[i].pr;
      t->p[i].dist_r=ti->p[i].dist_r;
   }
   else {
      t->p[i].pr.indefinito=TRUE;
   }
}
Dealloca_taglio(ti);
} // Crea_taglio_rett_file
*/

/////////////////////////////////////////////////////////////////////////
//   Alloca_taglio
/////////////////////////////////////////////////////////////////////////
struct taglio_rett_int huge *Alloca_taglio(void)
{
struct taglio_rett_int huge *taglio;

taglio=(struct taglio_rett_int huge *)
        malloc(sizeof(struct taglio_rett_int));
if (taglio == NULL)
   Error("Impossibile malloc di taglio","Alloca_taglio","taglio");
return(taglio);
/*
*hTaglio = GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT,
                   (DWORD) sizeof(struct taglio_rett_int));
taglio = (struct taglio_rett_int huge *) GlobalLock(*hTaglio);
*/
}

/////////////////////////////////////////////////////////////////////////
//   Dealloca_taglio
/////////////////////////////////////////////////////////////////////////
void Dealloca_taglio(struct taglio_rett_int huge *t)
{

free((void huge *) t);
/*GlobalUnlock(*hTaglio);
GlobalFree(*hTaglio);*/
}

/*
/////////////////////////////////////////////////////////////////////////
//   Creaz_e_salvat_taglio_rett_inter
/////////////////////////////////////////////////////////////////////////
void Creaz_e_salvat_taglio_rett_inter(void)
{
FILE *taglio_file;
int num,n_punti;
struct taglio_rett_file t;
float ptx,pty,ptz,atx,aty,atz;
struct punto pp,pv;
struct retta rt;
struct modello_rotondo m;
BOOL non_ok;
char lettere[3];
char path[40];
struct time tm;
long double t1,t2;

clrscr();
printf("\n   Generazione interattiva di tagli di modelli rotondi.\n\n");
printf(
"   Questa funzione genera tagli di modelli rotondi e li salva nei file\n");
printf("   del tipo %s??.fl\n\n",PATH_FILE_TAGLIO);
//printf("   Tali sistemi rimarranno permanentemente nel file per cui\n");
//printf("   eseguire la funzione solo se sicuri.\n\n");
printf("   Sei sicuro di voler eseguire la funzione (S/N) ? ");
if (toupper(getch()) != 'S') return;
clrscr();
printf("\n   Inserimento dati per la creazione dei tagli");
do {
   gotoxy(4,4);
   printf("Numero del modello rotondo da tagliare: ");
   scanf("%d",&num);
   non_ok=Carica_modrot(num,&m);
} while (non_ok);
do {
   gotoxy(4,6);
   printf("Numero di punti da produrre (10-%d): ",NUM_MAX_PUNTI_FILE);
   scanf("%d",&n_punti);
} while ((n_punti < 10) || (n_punti > NUM_MAX_PUNTI_FILE));
printf("\n   Ultime due lettere del nome del file da usare: ");
scanf("%2s",lettere);
printf("\n   Punto di proiezione x: ");
scanf("%f",&pp.x);
printf("                       y: ");
scanf("%f",&pp.y);
printf("                       z: ");
scanf("%f",&pp.z);
pp.indefinito=FALSE;
printf("   Punto di vista x: ");
scanf("%f",&pv.x);
printf("                  y: ");
scanf("%f",&pv.y);
printf("                  z: ");
scanf("%f",&pv.z);
pv.indefinito=FALSE;
do {
   gotoxy(1,16);
   printf("   Punto di partenza della retta di taglio x: ");
   clreol();
   scanf("%f",&ptx);
   printf("                                           y: ");
   clreol();
   scanf("%f",&pty);
   printf("                                           z: ");
   clreol();
   scanf("%f",&ptz);
   printf("   Punto di arrivo della retta di taglio x: ");
   clreol();
   scanf("%f",&atx);
   printf("                                         y: ");
   clreol();
   scanf("%f",&aty);
   printf("                                         z: ");
   clreol();
   scanf("%f",&atz);
   rt=Crea_retta(ptx,pty,ptz,atx,aty,atz);
} while (rt.cd < 1);
gotoxy(4,23);
printf("I dati sono corretti (S/N) ? ");
if (toupper(getch()) == 'N') return;
strcpy(path,PATH_FILE_TAGLIO);
strcat(path,lettere);
strcat(path,".fl");
taglio_file=fopen(path,"a+b");
if (taglio_file == NULL)
   Error("Non riesco ad aprire il file dei tagli",
         "Creaz_e_salvat_taglio_rett_inter","taglio");
gettime(&tm);
t1=(((long double)tm.ti_hour)*360000+((long double)tm.ti_min)*6000+
    ((long double)tm.ti_sec)*100+((long double)tm.ti_hund));
Crea_taglio_rett_file(num,&m,&pp,pv,rt,n_punti,&t,FALSE);
gettime(&tm);
t2=(((long double)tm.ti_hour)*360000+((long double)tm.ti_min)*6000+
    ((long double)tm.ti_sec)*100+((long double)tm.ti_hund));
fwrite(&t,sizeof(struct taglio_rett_file),1,taglio_file);

gotoxy(4,23);
clreol();
printf("Ho creato il taglio n. %3d (nel file)\n",
       (ftell(taglio_file)+1)/sizeof(struct taglio_rett_file));
printf("   Tempo impiegato (sec): %5.2Lf",(t2-t1)/100);
printf("   Premi return per continuare. ");
Aspetta_return();
fclose(taglio_file);
}  // Creaz_e_salvat_sist_triang
*/
/*
/////////////////////////////////////////////////////////////////////////
//   Creaz_e_salvat_taglio_rett_cas
/////////////////////////////////////////////////////////////////////////
void Creaz_e_salvat_taglio_rett_cas(void)
{
static char *tipo_base_line[4] = {
   "Assiale superiore ",
   "Assiale inferiore ",
   "Laterale superiore",
   "Laterale inferiore"
};
FILE *taglio_file;
FILE *report;
int num_primo_mo,num_ultimo_mo,num_primo_st,num_ultimo_st,n_tagli;
struct taglio_rett_file t;
struct punto pp,pv;
struct retta rt;
struct modello_rotondo m;
struct sistema_triang st;
struct sist_triang_riloc str;
BOOL non_ok;
char lettere[3];
char path[40],path_report[40];
struct time tm;
long double t1,t2;
float tempo;
int ore,minuti,secondi,tagli,n_mo,n_st,n_b,offset,n_t;
struct date data;
struct time ora;
char sdata[9];
char sora[9];
int n_righe,n_pag,da,a;
float occupazione;

clrscr();
printf("\n   Generazione casuale di tagli di modelli rotondi.\n\n");
printf(
"   Questa funzione genera tagli di modelli rotondi e li salva nei file\n");
printf("   del tipo %s??.fl\n\n",PATH_FILE_TAGLIO);
printf("   Sei sicuro di voler eseguire la funzione (S/N) ? ");
if (toupper(getch()) != 'S') return;
clrscr();
printf("\n   Inserimento dati per la creazione dei tagli");
do {
   gotoxy(4,4);
   printf("Numero  del   primo modello rotondo da tagliare: ");
   clreol();
   scanf("%d",&num_primo_mo);
   non_ok=Carica_modrot(num_primo_mo,&m);
} while (non_ok);
do {
   gotoxy(4,5);
   printf("Numero dell' ultimo modello rotondo da tagliare: ");
   clreol();
   scanf("%d",&num_ultimo_mo);
   if (num_ultimo_mo < num_primo_mo) {
      non_ok=TRUE;
      continue;
   }
   non_ok=Carica_modrot(num_ultimo_mo,&m);
} while (non_ok);
do {
   gotoxy(4,7);
   printf("Numero  del   primo sistema di triangolazione da usare: ");
   clreol();
   scanf("%d",&num_primo_st);
   non_ok=Carica_sist_triang(num_primo_st,&st);
} while (non_ok);
do {
   gotoxy(4,8);
   printf("Numero dell' ultimo sistema di triangolazione da usare: ");
   clreol();
   scanf("%d",&num_ultimo_st);
   if (num_ultimo_st < num_primo_st) {
      non_ok=TRUE;
      continue;
   }
   non_ok=Carica_sist_triang(num_ultimo_st,&st);
} while (non_ok);
do {
   gotoxy(4,10);
   printf("Numero di tagli da generare per ognuna delle 8 base line di");
   gotoxy(4,11);
   printf("ogni sistema di triangolazione (1-10): ");
   clreol();
   scanf("%d",&n_tagli);
} while ((n_tagli < 1) || (n_tagli > 10));
tagli=(num_ultimo_mo-num_primo_mo+1)*(num_ultimo_st-num_primo_st+1)*
      8*n_tagli;
tempo=tagli*TEMPO_PER_TAGLIO;
ore=tempo/3600;
tempo-=ore*3600.0;
minuti=tempo/60;
tempo-=minuti*60;
secondi=tempo;
occupazione=tagli*7276.0;
printf("\n   L' esecuzione di questi %d tagli richiererà\n",tagli);
printf("   %d ore %d minuti %d secondi, il file occuperà %ld Kbytes,\n",
       ore,minuti,secondi,(long) (occupazione/1000));
printf("   sei sicuro di voler avviare l'esecuzione (S/N) ? ");
if (toupper(getch()) != 'S') return;
printf("\n\n   Ultime due lettere del nome del file da usare: ");
scanf("%2s",lettere);
strcpy(path,PATH_FILE_TAGLIO);
strcat(path,lettere);
strcat(path,".fl");
taglio_file=fopen(path,"a+b");
if (taglio_file == NULL)
   Error("Non riesco ad aprire il file dei tagli",
         "Creaz_e_salvat_taglio_rett_cas","taglio");
strcpy(path_report,PATH_FILE_TAGLIO);
strcat(path_report,lettere);
strcat(path_report,".flr");
report=fopen(path_report,"wt");
if (report == NULL)
   Error("Non riesco ad aprire file report dei tagli",
         "Creaz_e_salvat_taglio_rett_cas","taglio");
pp.indefinito=FALSE;
pv.indefinito=FALSE;

getdate(&data);
gettime(&ora);
sprintf(sdata,"%02d/%02d/%02d",data.da_day,data.da_mon,data.da_year%100);
sprintf(sora,"%02d:%02d:%02d",ora.ti_hour,ora.ti_min,ora.ti_sec);
fprintf(report,"\n\n\n\nReport creazione casuale tagli - %s - %s\n",
        sdata,sora);
fprintf(report,"Il file dei tagli creato ha path: %s\n\n",path);
fprintf(report,"Dal  Al   Num. mod.  Num. sist. Tipo\n");
fprintf(report,"          rotondo    triangol.  base line\n");
n_righe=0;
n_pag=0;

clrscr();
gettime(&tm);
t1=(((long double)tm.ti_hour)*360000+((long double)tm.ti_min)*6000+
    ((long double)tm.ti_sec)*100+((long double)tm.ti_hund));
for (n_mo=num_primo_mo;n_mo<=num_ultimo_mo;n_mo++) {
   non_ok=Carica_modrot(n_mo,&m);
   if (non_ok)
      Error("Impossibile caricare modello rotondo",
            "Creaz_e_salvat_taglio_rett_cas","taglio");
   for (n_st=num_primo_st;n_st<=num_ultimo_st;n_st++) {
      non_ok=Carica_sist_triang(n_st,&st);
      if (non_ok)
         Error("Impossibile caricare sist. triang.",
               "Creaz_e_salvat_taglio_rett_cas","taglio");
      str=Riloca_sist_triang(&st,&m);
      for (n_b=0;n_b<4;n_b++) {
         if (n_righe > 55) {
            n_pag++;
            fprintf(report,"\n\nPagina %d\f",n_pag);
            fprintf(report,
               "\n\n\n\nReport creazione casuale tagli - %s - %s\n",
               sdata,sora);
            fprintf(report,
               "Il file dei tagli creato ha path: %s\n\n",path);
            fprintf(report,
               "Dal  Al   Num. mod.  Num. sist. Tipo\n");
            fprintf(report,
               "          rotondo    triangol.  base line\n");
            n_righe=0;
         }
         da=(ftell(taglio_file)+1)/(sizeof(struct taglio_rett_file))+1;
         a=da+n_tagli*2-1;
         fprintf(report,"%4d %4d   %4d       %4d     %s\n",
                 da,a,n_mo,n_st,tipo_base_line[n_b]);
         n_righe++;
         for (n_t=1;n_t<=n_tagli;n_t++) {
            Screen_saver((float) (ftell(taglio_file)/occupazione));
            rt=Genera_cas_rette_taglio(n_b,&m);
            for (offset=0;offset<5;offset+=4) {
               pp.x=str.pp[n_b+offset].x;
               pp.y=str.pp[n_b+offset].y;
               pp.z=str.pp[n_b+offset].z;
               pv.x=str.pv[n_b+offset].x;
               pv.y=str.pv[n_b+offset].y;
               pv.z=str.pv[n_b+offset].z;
               Crea_taglio_rett_file(n_mo,&m,&pp,pv,rt,
                                     NUM_MAX_PUNTI_FILE,&t,FALSE);
               fwrite(&t,sizeof(struct taglio_rett_file),1,taglio_file);
            }
         }
      }
   }
}
gettime(&tm);
t2=(((long double)tm.ti_hour)*360000+((long double)tm.ti_min)*6000+
    ((long double)tm.ti_sec)*100+((long double)tm.ti_hund));
for (;n_righe<56;n_righe++) fprintf(report,"\n");
n_pag++;
fprintf(report,"\n\nPagina %d\f",n_pag);
fclose(taglio_file);
fclose(report);
tempo=(t2-t1)/100;
ore=tempo/3600;
tempo-=ore*3600.0;
minuti=tempo/60;
tempo-=minuti*60;
secondi=tempo;
clrscr();
printf("\n\n   Tempo impiegato %d ore, %d minuti, %d secondi.\n",
       ore,minuti,secondi);
printf("   Premi return per continuare.");
Aspetta_return();
}  //  Creaz_e_salvat_taglio_rett_cas
*/
/*
/////////////////////////////////////////////////////////////////////////
//   Genera_cas_rette_taglio
/////////////////////////////////////////////////////////////////////////
struct retta Genera_cas_rette_taglio(int n_base_line,
                                     struct modello_rotondo *m)
{
float p1,p2,ptx,pty,ptz,atx,aty,atz;

switch (n_base_line) {
   case 0:
   case 1:
      p1=Ranf(-m->max_x-ALL_RETTA,m->max_x+ALL_RETTA);
      p2=Ranf(-m->max_x-ALL_RETTA,m->max_x+ALL_RETTA);
      if (Ranf(-1,1) > 0) {
         ptx=-m->max_x-ALL_RETTA;
         pty=p1;
         atx=m->max_x+ALL_RETTA;
         aty=p2;
      }
      else {
         ptx=p1;
         pty=-m->max_x-ALL_RETTA;
         atx=p2;
         aty=m->max_x+ALL_RETTA;
      }
      break;
   case 2:
   case 3:
      if ((2*m->max_x) > (m->max_z-m->min_z)) {
         p1=Ranf(m->min_z-ALL_RETTA,m->max_z+ALL_RETTA);
         p2=Ranf(m->min_z-ALL_RETTA,m->max_z+ALL_RETTA);
         ptx=-m->max_x-ALL_RETTA;
         ptz=p1;
         atx=m->max_x+ALL_RETTA;
         atz=p2;
      }
      else {
         p1=Ranf(-m->max_x-ALL_RETTA,m->max_x+ALL_RETTA);
         p2=Ranf(-m->max_x-ALL_RETTA,m->max_x+ALL_RETTA);
         ptx=p1;
         ptz=m->min_z-ALL_RETTA;
         atx=p2;
         atz=m->max_z+ALL_RETTA;
      }
      pty=aty=m->max_x;
      break;
}
switch (n_base_line) {
   case 0:
      ptz=atz=m->max_z;
      break;
   case 1:
      ptz=atz=m->min_z;
}
return(Crea_retta(ptx,pty,ptz,atx,aty,atz));
}
*/
/*
/////////////////////////////////////////////////////////////////////////
//   Scegli_file_taglio_rett
/////////////////////////////////////////////////////////////////////////
BOOL Scegli_file_taglio_rett(char lettere[3])
{
BOOL esiste;

do {
   gotoxy(4,5);
   printf("Inserisci le ultime due lettere del file ('+' per uscire): ");
   clreol();
   scanf("%2s",lettere);
   if (lettere[0]=='+') return(TRUE);
   esiste=Esiste_file_tagli(lettere);
} while (!esiste);
return(FALSE);
} // Scegli_file_taglio_rett

/////////////////////////////////////////////////////////////////////////
//   Scegli_e_carica_taglio_rett
/////////////////////////////////////////////////////////////////////////
int Scegli_e_carica_taglio_rett(char lettere[3],struct taglio_rett_file *t)
{
long num;
BOOL non_ok;

do {
   gotoxy(4,7);
   printf("Scegli il taglio da caricare (0 per uscire): ");
   clreol();
   scanf("%ld",&num);
   if ((num < 1) || (num > 10000)) return(0);
   non_ok=Carica_taglio_rett(lettere,(int) num,t);
} while (non_ok);
return(num);
} // Scegli_e_carica_taglio_rett

/////////////////////////////////////////////////////////////////////////
//   Carica_taglio_rett
/////////////////////////////////////////////////////////////////////////
BOOL Carica_taglio_rett(char lettere[3],int num_taglio,
                        struct taglio_rett_file *t)
{
FILE *taglio_file;
BOOL non_ok;
char path[40];

if ((num_taglio < 1) || (num_taglio > 10000)) return(TRUE);
strcpy(path,PATH_FILE_TAGLIO);
strcat(path,lettere);
strcat(path,".fl");
taglio_file=fopen(path,"r+b");
if (taglio_file == NULL)
   Error("Non riesco ad aprire file tagli",
         "Carica_taglio_rett","taglio");
non_ok=fseek(taglio_file,((long) (sizeof(struct taglio_rett_file)))*
                      ((long) (num_taglio-1)),SEEK_SET);
if ( (non_ok)  ||
     (feof(taglio_file)) ) {
   fclose(taglio_file);
   return(TRUE);
}
if (!fread(t,sizeof(struct taglio_rett_file),1,taglio_file)) {
   fclose(taglio_file);
   return(TRUE);
}
fclose(taglio_file);
return(FALSE);
} // Carica_taglio_rett

/////////////////////////////////////////////////////////////////////////
//   Esiste_file_tagli
/////////////////////////////////////////////////////////////////////////
BOOL Esiste_file_tagli(char lettere[3])
{
FILE *taglio_file;
char path[40];

strcpy(path,PATH_FILE_TAGLIO);
strcat(path,lettere);
strcat(path,".fl");
taglio_file=fopen(path,"r+b");
if (taglio_file == NULL)
   return(FALSE);
else {
   fclose(taglio_file);
   return(TRUE);
}
}

/////////////////////////////////////////////////////////////////////////
//   Carica_e_visual_taglio_rett
/////////////////////////////////////////////////////////////////////////
void Carica_e_visual_taglio_rett(void)
{
int n;
struct taglio_rett_file t;
BOOL fine;
char lettere[3],path[40];

for (;;) {
   clrscr();
   gotoxy(4,3);
   printf("Caricamento e visualizzazione di taglio: scelta file");
   fine=Scegli_file_taglio_rett(lettere);
   if (fine) break;
   for (;;) {
      clrscr();
      gotoxy(4,3);
      printf("Caricamento e visualizzazione di taglio: scelta taglio");
      gotoxy(4,5);
      strcpy(path,PATH_FILE_TAGLIO);
      strcat(path,lettere);
      strcat(path,".fl");
      printf("File in uso: %s",path);
      n=Scegli_e_carica_taglio_rett(lettere,&t);
      if (!n) break;
      Visual_dati_taglio_rett(lettere,n,&t);
      Visual_graf_taglio_rett(lettere,n,&t);
   }
}
} // Carica_e_visual_taglio_rett

/////////////////////////////////////////////////////////////////////////
//   Visual_dati_taglio_rett
/////////////////////////////////////////////////////////////////////////
void Visual_dati_taglio_rett(char lettere[3],int num_taglio,
                             struct taglio_rett_file *t)
{
char sdata[9],sora[9];

clrscr();
Crea_str_da_campo(t->data,sdata,8);
Crea_str_da_campo(t->ora,sora,8);
printf("\n   Lettere file: %s  Num:%4d    Data: %s   Ora: %s\n\n",
       lettere,num_taglio,sdata,sora);
printf("   Numero del modello tagliato: %3d\n",t->n_modello);
printf("   Numero di punti calcolati: %3d\n\n",t->n_punti);
printf("   Coordinate punto di proiezione_: %6.1f %6.1f %6.1f\n",
       t->pp.x,t->pp.y,t->pp.z);
printf("   Coordinate punto di vista______: %6.1f %6.1f %6.1f\n",
       t->pv.x,t->pv.y,t->pv.z);
printf("   Retta di taglio: punto di partenza: %6.1f %6.1f %6.1f\n",
       t->rt.xp,t->rt.yp,t->rt.zp);
printf("                    punto di arrivo  : %6.1f %6.1f %6.1f\n",
       t->rt.xp+t->rt.xap,t->rt.yp+t->rt.yap,t->rt.zp+t->rt.zap);

printf("\n\n   Premi return per continuare. ");
Aspetta_return();
} // Visual_dati_taglio_rett

/////////////////////////////////////////////////////////////////////////
//   Visual_graf_taglio_rett
/////////////////////////////////////////////////////////////////////////
void Visual_graf_taglio_rett(char lettere[3],int num_taglio,
                             struct taglio_rett_file *t)
{
char titolo_finestra[40];
char snum[4];
BOOL inv_clip;
struct riferimento_2d rif;
double min_x,min_y,min_z,max_x,max_y,max_z;
double dx,dy,dz,axy,axz,ayz,ax,ay,az;
double max_d,min_d,d,cent;
double s_x,s_y,s_z,s_x2,s_y2,s_z2,s_xy,s_xz,s_yz;
double gx,gy,gz,jx,jy,jz,jxy,jxz,jyz;
double rcx,rcy,rdx,rdy;
float dis_cent;
int i,tipo,n_definiti;

clrscr();
printf("\n\n   Visualizzazione grafico punti del taglio n. %s/%d",
       lettere,num_taglio);
gotoxy(4,15);
printf("I punti singoli sono i punti di intersezione ideale, le");
gotoxy(4,16);
printf("crocette sono i punti affetti da errore di misura.");
gotoxy(4,10);
printf("Vuoi inviare alla clipboard il grafico dei punti (S/N) ? ");
if (toupper(getch()) == 'S')
   inv_clip=INVIA_A_CLIPBOARD;
else
   inv_clip=NON_INV_A_CLIPBOARD;
sprintf(snum,"%d",num_taglio);
strcpy(titolo_finestra,"Taglio n. ");
strcat(titolo_finestra,lettere);
strcat(titolo_finestra,"/");
strcat(titolo_finestra,snum);


// valuto quale vista ortogonale usare
min_x=1E38;
max_x=-1E38;
min_y=1E38;
max_y=-1E38;
min_z=1E38;
max_z=-1E38;
n_definiti=0;
s_x=0;
s_y=0;
s_z=0;
s_x2=0;
s_y2=0;
s_z2=0;
s_xy=0;
s_xz=0;
s_yz=0;
for (i=0;i<t->n_punti;i++) {
   if (!t->p[i].pi.indefinito) {
      n_definiti++;
      if (t->p[i].pi.x < min_x) min_x=t->p[i].pi.x;
      if (t->p[i].pi.y < min_y) min_y=t->p[i].pi.y;
      if (t->p[i].pi.z < min_z) min_z=t->p[i].pi.z;
      if (t->p[i].pi.x > max_x) max_x=t->p[i].pi.x;
      if (t->p[i].pi.y > max_y) max_y=t->p[i].pi.y;
      if (t->p[i].pi.z > max_z) max_z=t->p[i].pi.z;
      s_x+=t->p[i].pi.x;
      s_y+=t->p[i].pi.y;
      s_z+=t->p[i].pi.z;
      s_x2+=pow(t->p[i].pi.x,2);
      s_y2+=pow(t->p[i].pi.y,2);
      s_z2+=pow(t->p[i].pi.z,2);
      s_xy+=t->p[i].pi.x*t->p[i].pi.y;
      s_xz+=t->p[i].pi.x*t->p[i].pi.z;
      s_yz+=t->p[i].pi.y*t->p[i].pi.z;
   }
   if (!t->p[i].pr.indefinito) {
      n_definiti++;
      if (t->p[i].pr.x < min_x) min_x=t->p[i].pr.x;
      if (t->p[i].pr.y < min_y) min_y=t->p[i].pr.y;
      if (t->p[i].pr.z < min_z) min_z=t->p[i].pr.z;
      if (t->p[i].pr.x > max_x) max_x=t->p[i].pr.x;
      if (t->p[i].pr.y > max_y) max_y=t->p[i].pr.y;
      if (t->p[i].pr.z > max_z) max_z=t->p[i].pr.z;
      s_x+=t->p[i].pr.x;
      s_y+=t->p[i].pr.y;
      s_z+=t->p[i].pr.z;
      s_x2+=pow(t->p[i].pr.x,2);
      s_y2+=pow(t->p[i].pr.y,2);
      s_z2+=pow(t->p[i].pr.z,2);
      s_xy+=t->p[i].pr.x*t->p[i].pr.y;
      s_xz+=t->p[i].pr.x*t->p[i].pr.z;
      s_yz+=t->p[i].pr.y*t->p[i].pr.z;
   }
}
if (n_definiti == 0) {
   printf("\n\n   Nessun punto definito. Premi return.");
   Aspetta_return();
   return;
}
gx=s_x/n_definiti;
gy=s_y/n_definiti;
gz=s_z/n_definiti;
jx=s_x2/n_definiti-pow(gx,2);
jy=s_y2/n_definiti-pow(gy,2);
jz=s_z2/n_definiti-pow(gz,2);
jxy=s_xy/n_definiti-gx*gy;
jxz=s_xz/n_definiti-gx*gz;
jyz=s_yz/n_definiti-gy*gz;
dx=max_x-min_x;
dy=max_y-min_y;
dz=max_z-min_z;
axy=jx*jy-pow(jxy,2);
axz=jx*jz-pow(jxz,2);
ayz=jy*jz-pow(jyz,2);
if (axy > axz)                 // tipo=1 proiettare su piano x-y
   if (ayz > axy)              // tipo=2 proiettare su piano x-z
      tipo=3;                  // tipo=3 proiettare su piano y-z
   else
      tipo=1;
else
   if (ayz > axz)
      tipo=3;
   else
      tipo=2;
switch (tipo) {
   case 1:
   strcat(titolo_finestra,"  x-y");
   break;
   case 2:
   strcat(titolo_finestra,"  x-z");
   break;
   case 3:
   strcat(titolo_finestra,"  y-z");
   break;
}
Apri_fin_graf((LPSTR) titolo_finestra);
// calcolo ed uso il riferimento 2d per le funzioni di disegno
switch (tipo) {
   case 1:
   ax=dx*0.025;
   ay=dy*0.025;
   rif.xl=min_x-ax;
   rif.xh=max_x+ax;
   rif.yl=min_y-ay;
   rif.yh=max_y+ay;
   break;
   case 2:
   ax=dx*0.025;
   az=dz*0.025;
   rif.xl=min_x-ax;
   rif.xh=max_x+ax;
   rif.yl=min_z-az;
   rif.yh=max_z+az;
   break;
   case 3:
   ay=dy*0.025;
   az=dz*0.025;
   rif.xl=min_y-ay;
   rif.xh=max_y+ay;
   rif.yl=min_z-az;
   rif.yh=max_z+az;
   break;
}
rcx=(rif.xl+rif.xh)/2;
rcy=(rif.yl+rif.yh)/2;
rdx=rif.xh-rif.xl;
rdy=rif.yh-rif.yl;
if (rdy/rdx > 0.75)
   rdx*=(rdy/rdx)/0.75;
else
   rdy*=0.75/(rdy/rdx);
rif.xl=rcx-rdx/2;
rif.xh=rcx+rdx/2;
rif.yl=rcy-rdy/2;
rif.yh=rcy+rdy/2;
Usa_rif_2d(rif);
// disegno indicazioni dei centimetri
Cerchio_vuoto(0,0,2);
dis_cent=0;
if (rif.xl > 0) dis_cent=rif.xl;
if (rif.xh < 0) dis_cent=rif.xh-rdx/300;
for (cent=ceil(rif.yl/10)*10,(Lz(cent)) ? cent+=10 : 0;
     cent<rif.yh;
     cent+=10,(Lz(cent)) ? cent+=10 : 0)
   Croce(dis_cent,cent,2);
dis_cent=0;
if (rif.yl > 0) dis_cent=rif.yl+rdy/400;
if (rif.yh < 0) dis_cent=rif.yh;
for (cent=ceil(rif.xl/10)*10,(Lz(cent)) ? cent+=10 : 0;
     cent<rif.xh;
     cent+=10,(Lz(cent)) ? cent+=10 : 0)
   Croce(cent,dis_cent,2);
// traccio i punti
for (i=0;i<t->n_punti;i++) {
   switch (tipo) {
      case 1:
      if (!t->p[i].pi.indefinito) Croce(t->p[i].pi.x,t->p[i].pi.y,0);
      if (!t->p[i].pr.indefinito) Croce(t->p[i].pr.x,t->p[i].pr.y,1);
      break;
      case 2:
      if (!t->p[i].pi.indefinito) Croce(t->p[i].pi.x,t->p[i].pi.z,0);
      if (!t->p[i].pr.indefinito) Croce(t->p[i].pr.x,t->p[i].pr.z,1);
      break;
      case 3:
      if (!t->p[i].pi.indefinito) Croce(t->p[i].pi.y,t->p[i].pi.z,0);
      if (!t->p[i].pr.indefinito) Croce(t->p[i].pr.y,t->p[i].pr.z,1);
      break;
   }
}

Mostra_disegno();
clrscr();
printf("\n\n   %s\n   Premi return per continuare. ",titolo_finestra);
Aspetta_return();
Chiudi_fin_graf(inv_clip);
clrscr();
printf("\n\n   Visualizzazione grafico distanze del taglio n. %s/%d",
       lettere,num_taglio);
gotoxy(3,15);
printf("L'istogramma indica le distanze ideali, le crocette sono");
gotoxy(3,16);
printf("le distanze affette da rumore.");
gotoxy(3,10);
printf("Vuoi inviare alla clipboard il grafico delle distanze (S/N) ? ");
if (toupper(getch()) == 'S')
   inv_clip=INVIA_A_CLIPBOARD;
else
   inv_clip=NON_INV_A_CLIPBOARD;
strcpy(titolo_finestra,"Taglio n. ");
strcat(titolo_finestra,lettere);
strcat(titolo_finestra,"/");
strcat(titolo_finestra,snum);
Apri_fin_graf((LPSTR) titolo_finestra);
max_d=0;
min_d=1E38;
for (i=0;i<t->n_punti;i++) {
   if (!t->p[i].pi.indefinito) {
      if (t->p[i].dist_i > max_d) max_d=t->p[i].dist_i;
      if (t->p[i].dist_i < min_d) min_d=t->p[i].dist_i;
   }
   if (!t->p[i].pr.indefinito) {
      if (t->p[i].dist_r > max_d) max_d=t->p[i].dist_r;
      if (t->p[i].dist_r < min_d) min_d=t->p[i].dist_r;
   }

}

d=(max_d-min_d)*0.025;
rif.xl=0;
rif.xh=(float) t->n_punti;
rif.yl=min_d-d;
rif.yh=max_d+d;
Usa_rif_2d(rif);
// disegno le croci dei centimetri
for (cent=ceil(rif.yl/10)*10;
     cent<rif.yh;
     cent+=10,(cent==0) ? cent+=10 : 0)
   Croce(0,cent,1);
if (!t->p[0].pi.indefinito) {
   Vai_a(0,t->p[0].dist_i);
   Linea_a(1,t->p[0].dist_i);
}
for (i=1;i<t->n_punti;i++) {
   if (!t->p[i].pi.indefinito) {
      if (!t->p[i-1].pi.indefinito) {
         Vai_a(i,t->p[i-1].dist_i);
         Linea_a(i,t->p[i].dist_i);
      }
      Vai_a(i,t->p[i].dist_i);
      Linea_a(i+1,t->p[i].dist_i);
   }
}
for (i=0;i<t->n_punti;i++) {
   if (!t->p[i].pr.indefinito)
      Croce(i+0.5,t->p[i].dist_r,2);
}
Mostra_disegno();
clrscr();
printf("\n\n   %s\n   Premi return per continuare. ",titolo_finestra);
Aspetta_return();
Chiudi_fin_graf(inv_clip);
} //  Visual_graf_taglio_rett
*/

