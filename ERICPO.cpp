/*
NOME_FILE:ERICPO
PROGETTO:Thesis
AUTORE:Emanuele Maria Santanché
DATA_INIZ:Ott 20'92
FILES DOCUMENTAZIONE:THMODULI.DOC, THGRUPPI.DOC, ERICPODF.DOC
NOMI FUNZIONI:
   Gruppo ERICPO
      Esperimento_di_ric_poliedri()
      Presentazione_e_parametri()
      Esamina_un_modello()
*/


#include "thvarie.h"
#include "thstruct.h"
#include "thprotot.h"
#include "thextern.h"


/////////////////////////////////////////////////////////////////////////
//   Esperimento_di_ric_poliedri
/////////////////////////////////////////////////////////////////////////
void Esperimento_di_ric_poliedri(void)
{
FILE *r;
BOOL non_ok,inter;
char nome_report[9];
char path[40];
long double t1,t2;
float tempo;
struct date data;
struct time tm;
double st_errore_medio;
double errore;
int successi,ore,minuti,secondi;
int st_fascia1,st_fascia2,st_fascia3,st_fascia4,
    n_riusciti,iter,pol_ric,riuscito,iterazioni;

clrscr();
printf("\n   Esperimento di riconoscimento dei poliedri.\n\n");
printf("   Questa funzione lancia un esperimento di \n");
printf("   riconoscimento dei poliedri.\n\n");
printf("   Sei sicuro di voler eseguire la funzione (S/N) ? ");
if (toupper(getch()) != 'S') return;
clrscr();

gotoxy(4,4);
printf("Numero  dei tentativi: ");
clreol();
scanf("%d",&iterazioni);

printf("\n   0=Automatico, 1=Return ad ogni iterazione: ");
scanf("%d",&inter);
printf("\n   Sei sicuro di voler avviare l'esecuzione (S/N) ? ");
if (toupper(getch()) != 'S') return;
do {
   gotoxy(4,17);
   printf("Nome del file di report da creare (senza estensione): ");
   clreol();
   scanf("%8s",nome_report);
   strcpy(path,PATH_REPORT_ERICPO);
   strcat(path,nome_report);
   strcat(path,".rpt");
   r=fopen(path,"rt");
   if (r == NULL)
      non_ok=FALSE;
   else {
      non_ok=TRUE;
      fclose(r);
   }
} while (non_ok);


r=fopen(path,"wt");
if (r == NULL)
   Error("Non riesco ad aprire il file del report",
         "Esperimento_di_ric_poliedri","ericpo");

Inizializza_filtri();

Presentazione_e_parametri(r,path,iterazioni);

getdate(&data);
gettime(&tm);
t1=(((long double)data.da_day)*8640000+((long double)tm.ti_hour)*360000+
    ((long double)tm.ti_min)*6000+((long double)tm.ti_sec)*100+
    ((long double)tm.ti_hund));

st_errore_medio=0.0;
st_fascia1=0;
st_fascia2=0;
st_fascia3=0;
st_fascia4=0;
n_riusciti=0;
successi=0;

clrscr();

for (iter=0;iter<iterazioni;iter++) {
   printf("Iterazione n. %4d <<<<<<<<<<<<<<<<<<<<<<\n",iter+1);
   Esegui_un_riconoscimento(&errore,&pol_ric,&riuscito);
   if (inter) Aspetta_return();
   if (riuscito) {
      n_riusciti++;
      if (pol_ric == POLI) {
         st_errore_medio+=errore;
         successi++;
         if (errore < 1.0) st_fascia1++;
         if ((errore >= 1.0) && (errore <= 2.0)) st_fascia2++;
         if ((errore >= 2.0) && (errore <= 4.0)) st_fascia3++;
         if (errore > 4.0) st_fascia4++;
      }
   }
}
if (successi == 0) {
   fprintf(r,"\n");
   fprintf(r,"Nessun successo\n");
   fclose(r);
   Dealloca_filtri();
   return;
}
st_errore_medio/=successi;

fprintf(r,"\n");
fprintf(r,"Errore medio commesso nel riconoscimento\n");
fprintf(r,
"del poliedro (°)______________________________:    %6.3lf\n",
   st_errore_medio);
fprintf(r,"Percentuale dei successi nel riconoscimento\n");
fprintf(r,
"del poliedro (%%)______________________________:    %4.1lf\n",
   (100.0*successi)/n_riusciti);
fprintf(r,"Percentuale dei tentativi in cui si sono\n");
fprintf(r,"trovati i punti necessari al riconoscimento\n");
fprintf(r,
"del poliedro (%%)______________________________:    %4.1lf\n",
   100.0*n_riusciti/iterazioni);
fprintf(r,"Percentuali errori nelle fascie \n");

fprintf(r,"0°-1°, 1°-2°, 2°-4°, 4°- (%%)__________________:");
fprintf(r,"    %4.1lf %4.1lf %4.1lf %4.1lf\n",
   (100.0*st_fascia1)/successi,(100.0*st_fascia2)/successi,
   (100.0*st_fascia3)/successi,(100.0*st_fascia4)/successi);

fprintf(r,"\n");
getdate(&data);
gettime(&tm);
t2=(((long double)data.da_day)*8640000+((long double)tm.ti_hour)*360000+
    ((long double)tm.ti_min)*6000+((long double)tm.ti_sec)*100+
    ((long double)tm.ti_hund));
tempo=(t2-t1)/100;
ore=tempo/3600;
tempo-=ore*3600.0;
minuti=tempo/60;
tempo-=minuti*60;
secondi=tempo;
fprintf(r,
"Tempo impiegato (hhh:mm:ss)___________________:  %03d:%02d:%02d\n",
   ore,minuti,secondi);
fprintf(r,
"Ora fine (hh:mm:ss)___________________________:  %02d:%02d:%02d\n",
   tm.ti_hour,tm.ti_min,tm.ti_sec);
fprintf(r,"\n");
fclose(r);
Dealloca_filtri();
}

/////////////////////////////////////////////////////////////////////////
//   Presentazione_e_parametri
/////////////////////////////////////////////////////////////////////////
void Presentazione_e_parametri(FILE *r,char path[40],
                               int iterazioni)
{
struct date data;
struct time ora;
char sdata[9];
char sora[9];
int i;

getdate(&data);
gettime(&ora);
sprintf(sdata,"%02d/%02d/%02d",data.da_day,data.da_mon,data.da_year%100);
sprintf(sora,"%02d:%02d:%02d",ora.ti_hour,ora.ti_min,ora.ti_sec);
fprintf(r,"\n");
fprintf(r,
"######################################################################\n");
fprintf(r,
"######################################################################\n");
fprintf(r,"##   Report di un esperimento di localiz. e ricon. poliedri\n");
fprintf(r,
"######################################################################\n");
fprintf(r,
"######################################################################\n");
fprintf(r,"\n");
fprintf(r,
"   Data: %s   Ora: %s\n",sdata,sora);
fprintf(r,
"   Path di questo file: %s\n",path);
fprintf(r,"\n");
fprintf(r,
"######################################################################\n");
fprintf(r,"##   Parametri usati nell' esperimento\n");
fprintf(r,
"######################################################################\n");
fprintf(r,"\n");
fprintf(r,
"//////////////////////////////////////////////////////////////////////\n");
fprintf(r,
"//   Parametri usati nella simulazione del modello\n");
fprintf(r,
"//////////////////////////////////////////////////////////////////////\n");
fprintf(r,"\n");
fprintf(r,
"Massima deviazione angolare complessiva del laser (mrad)_: %7.3f\n",
  (float) DEV_ANG_MAX_LASER*2000);
fprintf(r,
"Massima deviazione angolare complessiva del PSD (mrad)___: %7.3f\n",
  (float) DEV_ANG_MAX_PSD*2000);
fprintf(r,
"Massimo allontanamento per rumore (mm)___________________: %7.3f\n",
  (float) sqrt(MAX_ALLONTANAMENTO_PER_RUMORE));
fprintf(r,"\n");
fprintf(r,
"//////////////////////////////////////////////////////////////////////\n");
fprintf(r,"//   Parametri usati nella ricerca delle discontinuità\n");
fprintf(r,
"//////////////////////////////////////////////////////////////////////\n");
fprintf(r,"\n");
fprintf(r,
"Margine di sicurezza del rumore (#)______________________: %7.3f\n",
  (float) MARG_SICUR_RUMORE);
fprintf(r,"Lunghezza minima del supporto per poter operare la\n");
fprintf(r,
"correzione di massimi locali del rumore (#)______________: %3d\n",
  MINIMO_PER_CORR);
fprintf(r,"Lunghezza del supporto usato per la prima modalità di\n");
fprintf(r,
"correzione dei massimi locali del rumore (#)_____________: %3d\n",
  SUPP_CORR_A);
fprintf(r,"Rapporto tra punto di massimo e adiacenti nella prima\n");
fprintf(r,
"modalità di correzione del rumore (#)____________________: %7.3f\n",
  (float) RAPP_RUMORE_A);
fprintf(r,"Lunghezza del supporto usato per la seconda modalità di\n");
fprintf(r,
"correzione dei massimi locali del rumore (#)_____________: %3d\n",
  SUPP_CORR_B);
fprintf(r,"Rapporto tra punto di massimo e adiacenti nella seconda\n");
fprintf(r,
"modalità di correzione del rumore (#)____________________: %7.3f\n",
  (float) RAPP_RUMORE_B);
fprintf(r,"Numero massimo di filtri di ordine superione abilitati\n");
fprintf(r,
"alla soppressione delle discontinuità inferiori (#)______: %3d\n",
  SOGLIA_CANC_DISC);
fprintf(r,"Soglia per la correzione dei valori del rumore\n");
fprintf(r,
"utilizzando stime a priori (mm)__________________________: %7.3f\n",
  (float) SOGLIA_MIN_RUMORE);
fprintf(r,
"Valore di correzione per i valori sotto la soglia (mm)___: %7.3f\n",
  (float) RUMORE_DI_DEFAULT);
fprintf(r,"\n");
fprintf(r,
"//////////////////////////////////////////////////////////////////////\n");
fprintf(r,"//   Descrizione dei filtri di fitting\n");
fprintf(r,
"//////////////////////////////////////////////////////////////////////\n");
fprintf(r,"\n");
fprintf(r,
"Numero di filtri per il fitting grossolano (#)___________: %3d\n",
  NUM_FILTRI_GROSS);
fprintf(r,
"Numero di filtri per il fitting fine (#)_________________: %3d\n",
  NUM_FILTRI_FINE);
fprintf(r,"\n");
fprintf(r,"Num. filtro  Lungh. supp. Ordine fitt. Filtro fine  Soglia\n");
for (i=0;i<NUM_FILTRI_FINE;i++) {
   fprintf(r,
      "   %3d          %3d          %3d          %3d          %8.6lf\n",
      i,descr_filtri[i].lungh_supp,descr_filtri[i].ord_fitt,
      descr_filtri[i].fil_fine,descr_filtri[i].soglia);
}
fprintf(r,"\n");
fprintf(r,
"//////////////////////////////////////////////////////////////////////\n");
fprintf(r,"//   Parametri usati nella localizzazione delle discontinuità\n");
fprintf(r,
"//////////////////////////////////////////////////////////////////////\n");
fprintf(r,"\n");

fprintf(r,
"Numero dell' ultimo filtro \"piccolo\" (#)_________________: %3d\n",
   SOGLIA_FILTRI_GRANDI);
fprintf(r,
"Con riferimento al filtro nominale (quando \"piccolo\"),\n");
fprintf(r,
"numero del più basso filtro esaminato (#)________________: %3d\n",
   PRIMO_FILTRO_PICCOLI);
fprintf(r,
"Con riferimento al filtro nominale (quando \"piccolo\"),\n");
fprintf(r,
"numero del più alto filtro esaminato (#)_________________: %3d\n",
   ULTIMO_FILTRO_PICCOLI);
fprintf(r,
"Con riferimento al filtro nominale (quando \"grande\"),\n");
fprintf(r,
"numero del più basso filtro esaminato (#)________________: %3d\n",
   PRIMO_FILTRO_GRANDI);
fprintf(r,
"Con riferimento al filtro nominale (quando \"grande\"),\n");
fprintf(r,
"numero del più alto filtro esaminato (#)_________________: %3d\n",
   ULTIMO_FILTRO_GRANDI);
fprintf(r,"Fattore di incremento della soglia oltre la quale si\n");
fprintf(r,
"rileva una discontinuità a salto (#)_____________________: %7.3f\n",
   (float) SICUR_SALTO);
fprintf(r,"Fattore di incremento della soglia oltre la quale si\n");
fprintf(r,
"rileva una discontinuità ad angolo (#)___________________: %7.3f\n",
   (float) SICUR_ANGOLO);
fprintf(r,"\n");
fprintf(r,
"//////////////////////////////////////////////////////////////////////\n");
fprintf(r,"//   Parametri usati nell' analisi discontinuità\n");
fprintf(r,
"//////////////////////////////////////////////////////////////////////\n");
fprintf(r,"\n");
fprintf(r,"Passo grossolano di intervallazione dei punti sulla\n");
fprintf(r,
"retta di taglio (mm)_____________________________________: %7.3f\n",
   (float) PASSO_GROSS);
fprintf(r,"Passo fine di intervallazione dei punti sulla\n");
fprintf(r,
"retta di taglio (mm)_____________________________________: %7.3f\n",
   (float) PASSO_FINE);
fprintf(r,"Soglia di curvatura minima necessaria per dichiarare\n");
fprintf(r,
"che la discontinuità non è uno spigolo reale (1/mm)______: %7.3f\n",
   (float) SOGLIA_CURVATURA);
fprintf(r,"Soglia di angolazione minima necessaria per dichiarare\n");
fprintf(r,
"che la discontinuità non è uno spigolo reale (#)_________: %7.3f\n",
   (float) SOGLIA_DERIVATA);
fprintf(r,"Numero di tentativi di fitting per discontinuità di\n");
fprintf(r,
"bordo (#)________________________________________________: %3d\n",
   NUM_TENTATIVI_FITT_BORDO);
fprintf(r,"Numero di filtri usati per il fitting per discontinuità\n");
fprintf(r,
"di bordo (#)_____________________________________________: %3d\n",
   NUM_FILTRI_BORDO);
fprintf(r,"Fattore di incremento del numero dei punti del taglio\n");
fprintf(r,
"fine eseguito per localizzare ogni discontinuità (#)_____: %7.3f\n",
   (float) INCREM_SUPP);
fprintf(r,"\n");
fprintf(r,
"//////////////////////////////////////////////////////////////////////\n");
fprintf(r,
"//   Poliedro esaminato e iterazioni\n");
fprintf(r,
"//////////////////////////////////////////////////////////////////////\n");
fprintf(r,"\n");
fprintf(r,
"Numero del poliedro in esame_____________________________: %3d\n",
   POLI+1);
fprintf(r,
"Numero delle iterazioni da compiere______________________: %3d\n",
   iterazioni);
fprintf(r,"\n");
fprintf(r,"\n");
fprintf(r,
"######################################################################\n");
fprintf(r,"##   Risultati dell' esperimento\n");
fprintf(r,
"######################################################################\n");
fprintf(r,"\n");
}

#define FREERETURN {Dealloca_taglio(t);Dealloca_elenco_disc(ed);\
                    free_vector(rumore,0);free_ivector(discontinuita,0);\
                    free_vector(x,0);free_matrix(R,0,2,0);return;}

/////////////////////////////////////////////////////////////////////////
//   Esegui_un_riconoscimento
/////////////////////////////////////////////////////////////////////////
void Esegui_un_riconoscimento(double *errore,
                              int *pol_ric,
                              BOOL *riuscito)
{
struct taglio_rett_int huge *t;
struct elenco_part e;
struct elenco_disc huge *ed;
struct retta rt;
struct punto pp,pv;
double huge *rumore;
double huge **R;
int huge *discontinuita;
int i,n_punti,n_definiti,ass,die,
    cand_per_1,cand_per_2;
double huge *x;
struct vettore na1,na2,na3,s1,s2,s3,pv12,pv23;
double co122,se122,co232,se232,co233,se233,sefi1,sefi2,d1p,d2p,
       co121,se121;
double fi1[2],fi2[2],dist_da_1[2],dist_da_2[2];

*riuscito=FALSE;
t=Alloca_taglio();
ed=Alloca_elenco_disc();
rumore=vector(0,NUM_MAX_PUNTI_INT-1);
discontinuita=ivector(0,NUM_MAX_PUNTI_INT-1);
x=vector(0,3);
R=matrix(0,2,0,2);

// imposto il punto di proiezione laser (pp) e il punto di vista (pv)
pp.indefinito=FALSE;
pv.indefinito=FALSE;
pp.x=500;
pp.y=0;
pp.z=40;
pv.x=500;
pv.y=0;
pv.z=540;

// creo la retta di taglio
rt=Crea_retta(70.0,-120.0,Ranf(10.0,70.0),70.0,120.0,Ranf(10.0,70.0));
n_punti=rt.cd/PASSO_GROSS;
printf("Numero punti: %5d   ",n_punti);
if (n_punti > NUM_MAX_PUNTI_INT) n_punti=NUM_MAX_PUNTI_INT;
// creo il taglio ed esco se ci sono meno del 10% di punti definiti
Crea_taglio_rett_int(&pp,pv,rt,n_punti,t);
n_definiti=0;
for (i=0;i<t->n_punti;i++) if (!t->p[i].pr.indefinito) n_definiti++;
printf("Perc. definiti:  %4.1f",(float) (100.0*n_definiti/t->n_punti));
if (((float) n_definiti)/t->n_punti < PERC_DEFINITI) FREERETURN

// cerco le discontinuità ed esco se le disc. non sono 4
Partiziona_taglio(t,&e);
Tappa_buchi_dist(t,&e);
Valuta_rumore(t,&e,rumore);
Trova_discontinuita(t,&e,rumore,discontinuita);
Analizza_discontinuita(&pp,pv,rt,t,&e,rumore,discontinuita,ed);
printf("\nDisc. trovate: %3d\n",ed->n_disc);
if (ed->n_disc != 4) FREERETURN

// visualizzo l'elenco delle discont.
for (ass=0;ass<ed->n_disc;ass++)  {
   printf("Disc n.%2d: int=%d tip=%d dains=%d sup=%4.1lf",ass,
                   ed->d[ass].interna,ed->d[ass].tipo_disc,
                   ed->d[ass].da_inseguire,ed->d[ass].supporto);
   printf(" val=%7.3lf x=%5.1f y=%5.1f z=%5.1f\n",
                   ed->d[ass].valore_disc,ed->d[ass].punto_disc.x,
                   ed->d[ass].punto_disc.y,ed->d[ass].punto_disc.z);
}

// calcolo i vettori che congiungono le discont. (l1,l2,l3 della tesi)
// e ne visualizzo i moduli
s1=Vett_tra_punti(ed->d[0].punto_disc,ed->d[1].punto_disc);
s2=Vett_tra_punti(ed->d[1].punto_disc,ed->d[2].punto_disc);
s3=Vett_tra_punti(ed->d[2].punto_disc,ed->d[3].punto_disc);
printf("Moduli   s1=%7.3f   s2=%7.3f   s3=%7.3f\n",
       Modulo(s1),Modulo(s2),Modulo(s3));

// tento di riconoscere nel poliedro in uso, prima il poliedro n.ro 0,
// poi il poliedro n.ro 1
for (die=0;die<2;die++) {
   // questo è il valore iniziale del quaternione
   x[0]=1.0;x[1]=x[2]=x[3]=0.0;
   // qui si visualizzano i prodotti scalari delle normali con i vettori
   // che congiungono le discontinuità, prodotti scalari che dovrebbero
   // essere vicini a zero se le normali sono quelle del poliedro giusto,
   // perché i vettori che congiungono le discontinuità giaciono (a meno di
   // errori di misura) sulle facce alle quali le normali sono appunto
   // ortogonali
   printf("ProdScal   s1.n1=%8.4f    s2.n2=%8.4f    s3.n3=%8.4f\n",
      Prod_scal(s1,DIE[die].n1)/Modulo(s1),
      Prod_scal(s2,DIE[die].n2)/Modulo(s2),
      Prod_scal(s3,DIE[die].n3)/Modulo(s3));
   // ora si eseguono le iterazioni che conducono alla ricerca del
   // quaternione risolvente che viene poi visualizzato
   Mnewt(100,           //int ntrial,
         x,             //double huge *x,
         4,             //int n,
         1E-30,         //float tolx,
         1E-15,         //float tolf,
         &s1,&s2,&s3,   //struct vettore *s1,*s2,*s3
         die            //int die
         );
   printf("Quaternione n. %3d:    %9.6lf   %9.6lf   %9.6lf   %9.6lf\n",die+1,
          x[0],x[1],x[2],x[3]);
   // si calcola la matrice di rotazione che permette di ottenere le normali
   // ruotate a partire da quelle di riferimento secondo la rotazione
   // espressa dal quaternione. Si veda la (49) della tesi (§ 12.2.3 pg.
   // 141).
   R[0][0]=pow(x[0],2)+pow(x[1],2)-pow(x[2],2)-pow(x[3],2);
   R[0][1]=2*(-x[0]*x[3]+x[1]*x[2]);
   R[0][2]=2*(x[0]*x[2]+x[1]*x[3]);
   R[1][0]=2*(x[0]*x[3]+x[1]*x[2]);
   R[1][1]=pow(x[0],2)-pow(x[1],2)+pow(x[2],2)-pow(x[3],2);
   R[1][2]=2*(-x[0]*x[1]+x[2]*x[3]);
   R[2][0]=2*(-x[0]*x[2]+x[1]*x[3]);
   R[2][1]=2*(x[0]*x[1]+x[2]*x[3]);
   R[2][2]=pow(x[0],2)-pow(x[1],2)-pow(x[2],2)+pow(x[3],2);
   // ecco quindi le tre nuove normali
   na1.indefinito=na2.indefinito=na3.indefinito=FALSE;
   na1.a=R[0][0]*DIE[die].n1.a+R[0][1]*DIE[die].n1.b+R[0][2]*DIE[die].n1.c;
   na1.b=R[1][0]*DIE[die].n1.a+R[1][1]*DIE[die].n1.b+R[1][2]*DIE[die].n1.c;
   na1.c=R[2][0]*DIE[die].n1.a+R[2][1]*DIE[die].n1.b+R[2][2]*DIE[die].n1.c;
   na2.a=R[0][0]*DIE[die].n2.a+R[0][1]*DIE[die].n2.b+R[0][2]*DIE[die].n2.c;
   na2.b=R[1][0]*DIE[die].n2.a+R[1][1]*DIE[die].n2.b+R[1][2]*DIE[die].n2.c;
   na2.c=R[2][0]*DIE[die].n2.a+R[2][1]*DIE[die].n2.b+R[2][2]*DIE[die].n2.c;
   na3.a=R[0][0]*DIE[die].n3.a+R[0][1]*DIE[die].n3.b+R[0][2]*DIE[die].n3.c;
   na3.b=R[1][0]*DIE[die].n3.a+R[1][1]*DIE[die].n3.b+R[1][2]*DIE[die].n3.c;
   na3.c=R[2][0]*DIE[die].n3.a+R[2][1]*DIE[die].n3.b+R[2][2]*DIE[die].n3.c;
   // ora si avviano i calcoli che portano ad esprimere fi1 e fi2 come detto
   // alla fine di pg 141 della tesi
   pv12=Prod_vett(na2,na1);
   co122=Prod_scal(s2,pv12)/(Modulo(s2)*Modulo(pv12));
   se122=sqrt(1-pow(co122,2));
   if (fabs(se122) > 1.0) printf("se122 > 1\n");
   d2p=se122*Modulo(s2)/sin(DIE[die].fi);
   pv23=Prod_vett(na2,na3);
   co232=Prod_scal(s2,pv23)/(Modulo(s2)*Modulo(pv23));
   se232=sqrt(1-pow(co232,2));
   if (fabs(se232) > 1.0) printf("se232 > 1\n");
   d1p=se232*Modulo(s2)/sin(DIE[die].fi);
   printf("d1p=%7.3lf  d2p=%7.3lf   ",d1p,d2p);
   co233=Prod_scal(s3,pv23)/(Modulo(s3)*Modulo(pv23));
   se233=sqrt(1-pow(co233,2));
   if (fabs(se233) > 1.0) printf("se233 > 1\n");
   co121=Prod_scal(s1,pv12)/(Modulo(s1)*Modulo(pv12));
   se121=sqrt(1-pow(co121,2));
   printf("co233=%9.7lf  co121=%9.7lf\n",co233,co121);
   sefi2=(Modulo(s3)*se233)/
          sqrt(pow(DIE[die].d2-d2p,2)+pow(Modulo(s3),2)-
               2*(DIE[die].d2-d2p)*Modulo(s3)*co233);
   sefi1=(Modulo(s1)*se121)/
          sqrt(pow(DIE[die].d1-d1p,2)+pow(Modulo(s1),2)-
               2*(DIE[die].d1-d1p)*Modulo(s1)*co121);
   // questi sono gli angoli fi1 e fi2 ottenuti tentando il riconoscimento
   // del poliedro n.ro 'die'
   fi1[die]=asin(sefi1)*RAD_GRA;
   fi2[die]=asin(sefi2)*RAD_GRA;
   printf("Diedro n. %3d    fi1=%7.3lf   fi2=%7.3lf\n",
          die+1,fi1[die],fi2[die]);
   // qui si calcolano le distanze della coppia fi1,fi2 relativa al
   // riconoscimento del poliedro 'die' dalle coppie fi1,fi2 dei due
   // poliedri
   dist_da_1[die]=sqrt(pow(DIE[0].fi1*RAD_GRA-fi1[die],2)+
                       pow(DIE[0].fi2*RAD_GRA-fi2[die],2));
   dist_da_2[die]=sqrt(pow(DIE[1].fi1*RAD_GRA-fi1[die],2)+
                       pow(DIE[1].fi2*RAD_GRA-fi2[die],2));
}
// si decide quindi quale dei due poliedri viene riconosciuto (si veda § 13
// della tesi)
if (dist_da_1[0] < dist_da_1[1])
   cand_per_1=0;
else
   cand_per_1=1;
if (dist_da_2[0] < dist_da_2[1])
   cand_per_2=0;
else
   cand_per_2=1;
*riuscito=TRUE;
if (dist_da_1[cand_per_1] < dist_da_2[cand_per_2]) {
   *errore=dist_da_1[cand_per_1];
   *pol_ric=0;
}
else {
   *errore=dist_da_2[cand_per_2];
   *pol_ric=1;
}
printf("Poliedro ric. n. %3d (1-2)   Errore %7.3lf  ",*pol_ric+1,*errore);
if (*pol_ric==POLI) printf("SUCCESSO"); else printf("INSUCCESSO");
printf("\n");

FREERETURN
} // Esegui_un_riconoscimento
