/*
NOME_FILE:UTILIT
PROGETTO:Thesis
AUTORE:Emanuele Maria Santanché
DATA_INIZ:Lug 26'92
FILES DOCUMENTAZIONE:THMODULI.DOC, THGRUPPI.DOC, UTILIT.DOC
NOMI FUNZIONI:
   Gruppo DOMENU
      Menu()
   Gruppo ERRORI
      Error()
   Gruppo VARIEF
      Aspetta_return()
      Crea_str_da_campo()
      Crea_campo()
      Zero_string()
      Lz()
      Screen_saver()
   Gruppo DEBUGF
      Debug()
*/

#include "thvarie.h"
#include "thstruct.h"
#include "thprotot.h"
#include "thextern.h"

/////////////////////////////////////////////////////////////////////////
//   Menu
/////////////////////////////////////////////////////////////////////////
int Menu(char test[60], char *opz[20])
{
int i,scelta,j,num_opz_valide;
int corrispondenza[20];
struct date data;
struct time ora;
char s[3];
char ok;

clrscr();
gotoxy(6,1);
printf("EMS Thesis System - ");
puts(test);
gotoxy(1,3);
j=1;
for (i=4;i<24;i++) {
   if ((opz[i-4][0] != 0) && (opz[i-4][0] != ' ')) {
      corrispondenza[j-1]=i-3;
      printf("%7d",j);
      printf(" - %s\n",opz[i-4]);
      j++;
   }
   else
      if (opz[i-4][0] == ' ')
         printf("          %s\n",opz[i-4]);
      else
         printf("\n");
}
num_opz_valide=j-1;
do {
   getdate(&data);
   gettime(&ora);
   gotoxy(6,24);
   printf("%02d/%02d/%02d %02d:%02d:%02d",
     data.da_day,data.da_mon,data.da_year%100,
     ora.ti_hour,ora.ti_min,ora.ti_sec);
   printf(" Scelta : ");
   clreol();
   strcpy(s,"0");
   gets(s);
   scelta=atoi(s);
   /* notare la condizione opz[scelta-1] ecc. che non accetta la scelta se
   la relativa stringa di opzione é nulla */
   if ((scelta>0) && (scelta<num_opz_valide+1))
      ok=TRUE;
   else
      ok=FALSE;
} while (!ok);
return (corrispondenza[scelta-1]);
}

/////////////////////////////////////////////////////////////////////////
//   Error
/////////////////////////////////////////////////////////////////////////
void Error(char *errmsg,char *nomerout,char *nomefile)
{
BOOL on;
long i,tempo;

on=TRUE;
do {
   if (on) tempo=100000L; else tempo=50000L;
   gotoxy(60,1);
   if (on) {
      printf("Errore! Premi.");
      on=FALSE;
   }
   else {
      printf("              ");
      on=TRUE;
   }
   for (i=0;i<tempo;i++);
} while (!kbhit());

clrscr();
printf("Errore non recuperabile: appuntati tutto ciò che é scritto qui\n");
printf("sotto poi premi Return\n");
printf("Messaggio di errore :\n");
printf("%s\n",errmsg);
printf("Nome routine : %s\n",nomerout);
printf("Nome file : %s\n",nomefile);
perror("Perror ");
fcloseall();
CloseClipboard();
Aspetta_return();
exit(0);
}

/////////////////////////////////////////////////////////////////////////
//   Aspetta_return
/////////////////////////////////////////////////////////////////////////
void Aspetta_return(void)
{
int c;

do {
  c=getch();
} while (c != CR);
}

/////////////////////////////////////////////////////////////////////////
//   Crea_str_da_campo
/////////////////////////////////////////////////////////////////////////
void Crea_str_da_campo(char *campo,char *str,int lungh)
{

memcpy(str,campo,(unsigned) lungh);
str[lungh]='\0';
} // Crea_str_da_campo

/////////////////////////////////////////////////////////////////////////
//   Crea_campo
/////////////////////////////////////////////////////////////////////////
void Crea_campo(char *campo,char *stringa,int lungh)
{

setmem(campo,lungh,' ');
if (strlen(stringa) == 0) return;
if (strlen(stringa)<=lungh)
   memcpy(campo,stringa,strlen(stringa));
else
   memcpy(campo,stringa,lungh);
} // Crea_campo

/////////////////////////////////////////////////////////////////////////
//   Zero_string
/////////////////////////////////////////////////////////////////////////
void Zero_string(char res[3],int num)
{
char ress[4];

if ((num<1) || (num>999))
   Error("Richiesta conversione numero <1 o >999","zero_string","pdlutil");
sprintf(ress,"%03d",num);
memcpy(res,ress,3);
} // Zero_string

/////////////////////////////////////////////////////////////////////////
//   Ranf
/////////////////////////////////////////////////////////////////////////
float Ranf(float da, float a)
{

return((((float)rand())/RAND_MAX)*(a-da)+da);
}

/////////////////////////////////////////////////////////////////////////
//   Lz
/////////////////////////////////////////////////////////////////////////
BOOL Lz(double l)
{

return (fabs(l) < 1E-6);
}

/////////////////////////////////////////////////////////////////////////
//   Screen_saver
/////////////////////////////////////////////////////////////////////////
void Screen_saver(float lavoro)
{
char riga[80];
int x,y,i;

clrscr();
riga[79]='\0';
for (i=0;i<79;i++) riga[i]=33+random(90);
for (i=1;i<25;i++) printf("%s\n",riga);
printf("%s",riga);
x=4+random(39);
y=3+random(21);
gotoxy(x,y);
printf("   Lavoro completato al %5.1f %%   ",(float) lavoro*100.0);
gotoxy(x,y+1);
printf("                                  ");
gotoxy(x,y-1);
printf("                                  ");
}

/////////////////////////////////////////////////////////////////////////
//   Debug
/////////////////////////////////////////////////////////////////////////
void Debug(int line,char file[40])
{
int x,y,pos;

x=wherex();
y=wherey();
pos=4;
if (strncmp(file,"ETRIEF",6) == 0) pos=0;
if (strncmp(file,"ANADIS",6) == 0) pos=1;
if (strncmp(file,"LOCDIS",6) == 0) pos=2;
if (strncmp(file,"MATEMA",6) == 0) pos=3;
gotoxy(1+14*pos,6);
printf("%4d%s",line,file);
gotoxy(x,y);
}

