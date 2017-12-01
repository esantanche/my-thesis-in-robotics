/*
NOME_FILE:IMMAGI
PROGETTO:Thesis
AUTORE:Emanuele Maria Santanché
DATA_INIZ:Ott 7'92
FILES DOCUMENTAZIONE:THMODULI.DOC, THGRUPPI.DOC, IMMAGIDF.DOC
NOMI FUNZIONI:
   Gruppo CREAZI
      Crea_immagine()
   Gruppo VISUAL
      Visual_immagine()
*/

#include "thvarie.h"
#include "thstruct.h"
#include "thprotot.h"
#include "thextern.h"

/////////////////////////////////////////////////////////////////////////
//   Crea_immagine
/////////////////////////////////////////////////////////////////////////
void Crea_immagine(void)
{
long z;
HANDLE hMem;
float huge *array;
struct punto pp,pv,ps,ppsti,ppsts,psi,pss;
struct taglio_rett_int huge *t;
struct retta rt;
int i,j,allineamento;
char d;
FILE *imm_file;
float delta,max_d,min_d,deviazione;
double altezza,larghezza,ca,sa,rxy;
char nome[9],path[40],riga[320],s_allin[2],stipo[2],ctipo;
BOOL non_ok;
struct vettore vers_zeta,vers_sguardo,asse_oriz_imm,asse_imm;

clrscr();
printf("\n   Generazione interattiva di immagini di distanza.\n\n");
printf(
"   Questa funzione genera una immagine di distanza e la salva in un file\n");
printf("   di nome dato ed estensione %s.\n",ESTENSIONE_IMMAGINI);
printf("   La directory di salvataggio è %s.\n",DIRECTORY_IMMAGINI);
printf("   Tenere presente che la creazione di una immagine richiede\n");
printf("   tra i 15 e i 30 minuti di tempo.\n\n");
printf("   Sei sicuro di voler eseguire la funzione (S/N) ? ");
if (toupper(getch()) != 'S') return;
clrscr();
printf("\n   Inserimento dati per la creazione dell' immagine");
do {
   gotoxy(4,4);
   printf("Nome dell' immagine (max 8 caratteri): ");
   clreol();
   scanf("%8s",nome);
   strcpy(path,DIRECTORY_IMMAGINI);
   strcat(path,nome);
   strcat(path,ESTENSIONE_IMMAGINI);
   imm_file=fopen(path,"rb");
   if (imm_file != NULL) {
      non_ok=TRUE;
      fclose(imm_file);
   }
   else
      non_ok=FALSE;
} while (non_ok);

printf("   Punto di proiezione x: ");
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
printf("   Punto dove \"posare lo sguardo\" x: ");
scanf("%f",&ps.x);
printf("                                  y: ");
scanf("%f",&ps.y);
printf("                                  z: ");
scanf("%f",&ps.z);
ps.indefinito=FALSE;
printf("   Larghezza immagine: ");
scanf("%lf",&larghezza);
vers_zeta.indefinito=FALSE;
vers_zeta.a=0;
vers_zeta.b=0;
vers_zeta.c=1;
vers_sguardo=Versore_da_retta(Crea_retta(pp.x,pp.y,pp.z,
                                         ps.x,ps.y,ps.z));
if (fabs(Coseno_tra_versori(vers_zeta,vers_sguardo)) <
    RAD2_DIV_2) {
   allineamento=ALL_Z;
   strcpy(s_allin,"z");
}
else {
   allineamento=ALL_X;
   strcpy(s_allin,"x");
}
printf("\n   Inserire la deviazione dell' asse verticale dell' immagine\n");
printf("   rispetto all' asse %s tra -180° e 180° dove gli angoli\n",
       s_allin);
printf("   positivi significano rotazioni verso la destra dell'\n");
printf("   osservatore: ");
scanf("%f",&deviazione);
deviazione*=GRA_RAD;
do {
   gotoxy(4,22);
   printf("Inserire I per immagine ideale e R per immagine reale: ");
   clreol();
   scanf("%1s",stipo);
   ctipo=toupper(stipo[0]);
} while ((ctipo != 'I') && (ctipo != 'R'));
gotoxy(4,24);
printf("I dati sono corretti (S/N) ? ");
if (toupper(getch()) != 'S') return;

altezza=larghezza*0.75;
asse_imm.indefinito=FALSE;
if (allineamento == ALL_Z) {
   ca=cos(deviazione);
   sa=sqrt(1-pow(ca,2))*(deviazione > 0 ? -1 : 1);
   rxy=sqrt(pow(vers_sguardo.a,2)+pow(vers_sguardo.b,2));
   asse_imm.a=(-(vers_sguardo.c*ca*vers_sguardo.a+vers_sguardo.b*sa)/rxy);
   asse_imm.b=((-vers_sguardo.c*ca*vers_sguardo.b+vers_sguardo.a*sa)/rxy);
   asse_imm.c=ca*rxy;
}
else {
   ca=cos(deviazione);
   sa=sqrt(1-pow(ca,2))*(deviazione > 0 ? -1 : 1);
   rxy=sqrt(pow(vers_sguardo.b,2)+pow(vers_sguardo.c,2));
   asse_imm.a=ca*rxy;
   asse_imm.b=(-(vers_sguardo.a*ca*vers_sguardo.b+vers_sguardo.c*sa)/rxy);
   asse_imm.c=((-vers_sguardo.a*ca*vers_sguardo.c+vers_sguardo.b*sa)/rxy);
}
asse_oriz_imm=Prod_vett(vers_sguardo,asse_imm);
ppsti=Punto_piu_vett(Punto_piu_vett(ps,
                                    Vett_per_scal(-larghezza/2,
                                                  asse_oriz_imm)),
                     Vett_per_scal(-altezza/2,
                                   asse_imm));
ppsts=Punto_piu_vett(Punto_piu_vett(ps,
                                    Vett_per_scal(-larghezza/2,
                                                  asse_oriz_imm)),
                     Vett_per_scal(altezza/2,
                                   asse_imm));

clrscr();

hMem = GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT, 64000L * sizeof(float));
array = (float huge *) GlobalLock(hMem);
for (z=0; z < 64000L; z++) array[z] = 0;
max_d=0;
min_d=1E38;

t=Alloca_taglio();
for (i=0;i<320;i++) {
   if (i%8) Screen_saver((float) i/320.0);
   psi=Punto_piu_vett(ppsti,Vett_per_scal(i*larghezza/320,asse_oriz_imm));
   pss=Punto_piu_vett(ppsts,Vett_per_scal(i*larghezza/320,asse_oriz_imm));
   rt=Crea_retta(pss.x,pss.y,pss.z,psi.x,psi.y,psi.z);
   Crea_taglio_rett_int(&pp,pv,rt,200,t);
   if (ctipo == 'I') {
      for (j=0;j<200;j++) {
         if (!t->p[j].pi.indefinito) {
            array[((long) j)*320L+((long) i)]=t->p[j].dist_i;
            if (t->p[j].dist_i > max_d) max_d=t->p[j].dist_i;
            if (t->p[j].dist_i < min_d) min_d=t->p[j].dist_i;
         }
      }
   }
   else {
      for (j=0;j<200;j++) {
         if (!t->p[j].pr.indefinito) {
            array[((long) j)*320L+((long) i)]=t->p[j].dist_r;
            if (t->p[j].dist_r > max_d) max_d=t->p[j].dist_r;
            if (t->p[j].dist_r < min_d) min_d=t->p[j].dist_r;
         }
      }
   }
}
delta=max_d-min_d;
clrscr();
printf("\n   Immagine %s in corso di creazione",path);
gotoxy(4,5);
printf("Differenza massima nelle distanze: %8.3f\n",delta);
printf("   Distanza minima : %8.3f\n",min_d);
printf("   Distanza massima: %8.3f\n",max_d);
Dealloca_taglio(t);
imm_file=fopen(path,"wb");
for (i=0;i<200;i++) {
   for (j=0;j<320;j++) {
      if ( array[((long) i)*320L+((long) j)] <= 1 )
         d=0;
      else {
         d=((max_d-array[((long) i)*320L+((long) j)])/delta)*63.99999;
         if (d < 0) d=0;
         if (d > 63) d=63;
      }
      riga[j]=d;
   }
   fwrite(riga,sizeof(char[320]),1,imm_file);
}
fclose(imm_file);

GlobalUnlock(hMem);
GlobalFree(hMem);

gotoxy(4,20);
printf("Premi return. ");
Aspetta_return();
}

/////////////////////////////////////////////////////////////////////////
//   Visual_immagine
/////////////////////////////////////////////////////////////////////////
void Visual_immagine(void)
{
int k;

clrscr();
printf("\n   Funzione esterna di visualizzazione delle immagini.\n");
printf("\n   Attendere il caricamento della funzione esterna (occorrono\n");
printf("   alcuni secondi).\n");
printf("\n   Dopo aver visto le immagini riapparirà questo schermo: allora\n");
printf("   premete return. ");
k=WinExec((LPSTR) "c:\\dos\\qbasic.exe /run c:\\thbas\\visuimg.bas",0);
if (k <= 32) {
   printf("\n\n   Ci sono problemi nel caricamento della funzione\n");
   printf("   esterna. Codice di ritorno %d. Premi return. ",k);
}
Aspetta_return();
}