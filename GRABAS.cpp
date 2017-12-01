/*
NOME_FILE:GRABAS
PROGETTO:Thesis
AUTORE:Emanuele Maria Santanché
DATA_INIZ:Ago 25'92
FILES DOCUMENTAZIONE:THMODULI.DOC, THGRUPPI.DOC, GRABASDF.DOC
NOMI FUNZIONI:
   Gruppo INIZIA
      Inizializza_grafica()
      messaggi_finestra()
   Gruppo GESFIN
      Apri_fin_graf()
      Chiudi_fin_graf()
   Gruppo CLPBRD
      Invia_a_clipboard()
   Gruppo DISEGN
      Mostra_disegno()
      Usa_rif_2d()
      Croce()
      Vai_a()
      Linea_a()
      Cerchio_pieno()
      Cerchio_vuoto()
*/


#include "thvarie.h"
#include "thstruct.h"
#include "thprotot.h"
#include "thextern.h"

/////////////////////////////////////////////////////////////////////////
//   Inizializza_grafica
/////////////////////////////////////////////////////////////////////////
void Inizializza_grafica(void)
{
WNDCLASS classe_finestra;

// inizializzazione del sistema Easy Window che permette di scrivere
// su di una finestra creata dal sistema con i normali printf e scanf
_InitEasyWin();

// Riempimento di tutti i campi della struttura che definisce la classe
// della finestra. Notare in particolare il nome della classe, il
// proprietario della stessa che è h_programma cioè questo stesso
// programma e la funzione di gestione dei messaggi Messaggi_finestra.
classe_finestra.lpszClassName = nome_classe_fin_graf;
classe_finestra.hInstance     = h_programma;
classe_finestra.lpfnWndProc   = Messaggi_finestra;
classe_finestra.hCursor       = NULL;
classe_finestra.hIcon         = NULL;
classe_finestra.lpszMenuName  = (LPSTR) NULL;
classe_finestra.hbrBackground = GetStockObject(WHITE_BRUSH);
classe_finestra.style         = 0;
classe_finestra.cbClsExtra    = 0;
classe_finestra.cbWndExtra    = 0;

// Registro la classe per il futuro uso in fase di creazione della
// finestra
RegisterClass(&classe_finestra);
}

/////////////////////////////////////////////////////////////////////////
//   Messaggi_finestra
/////////////////////////////////////////////////////////////////////////
long FAR PASCAL _export Messaggi_finestra(HWND wnd,WORD msg,
                                          WORD wpar,long lpar)
{
// se la finestra grafica viene mossa, provvedo a ridisegnarla copiando
// in essa la bitmap contenuta nella finestra nascosta (vedi gruppo
// funzioni GESFIN e funzione Inizializza_grafica)
if ((msg == WM_MOVE) || (msg == WM_ACTIVATE)) {
   BitBlt(DC_fin_graf,0,0,640,460,DC_hide,0,0,SRCCOPY);
   return(0L);
}
// comunque il messaggio viene consegnato a DefWindowProc per le elabora-
// zioni di default
return(DefWindowProc(wnd,msg,wpar,lpar));
}

/////////////////////////////////////////////////////////////////////////
//   Apri_fin_graf
/////////////////////////////////////////////////////////////////////////
void Apri_fin_graf(LPSTR titolo_fin_graf)
{

// creazione della finestra
fin_graf=CreateWindow(nome_classe_fin_graf,titolo_fin_graf,
                      WS_MINIMIZEBOX,
                      0,0,640,480,NULL,NULL,h_programma,NULL);
if (fin_graf == NULL)
   Error("Non riesco ad aprire la finestra grafica",
         "Apri_fin_graf","grabas");
// visualizzazione della finestra
ShowWindow(fin_graf,SW_SHOW);
// rintraccio il device context della finestra
DC_fin_graf=GetDC(fin_graf);
// creo un device context compatibile con la finestra visibile.
DC_hide=CreateCompatibleDC(DC_fin_graf);
// creo una bitmap associata al device context nascosto sulla
// quale scriverò per poi copiarla sulla finestra visibile
bitmap_nascosta=CreateCompatibleBitmap(DC_hide,640,460);
// associo la bitmap al device context nascosto
SelectObject(DC_hide,bitmap_nascosta);
// cancello la bitmap
BitBlt(DC_hide,0,0,640,460,NULL,0,0,WHITENESS);
// inizio il disegno sul device context nascosto
BeginPaint(DC_hide,&struttura_paint);
// dico al device context nascosto di scrivere nero su bianco
SetROP2(DC_hide,R2_BLACK);
}

/////////////////////////////////////////////////////////////////////////
//   Chiudi_fin_graf
/////////////////////////////////////////////////////////////////////////
void Chiudi_fin_graf(BOOL invia_a_clipboard)
{

// fine del disegno su finestra nascosta
EndPaint(DC_hide,&struttura_paint);
// cancellazione device context della finestra nascosta
DeleteDC(DC_hide);
if (invia_a_clipboard)
   Invia_a_clipboard();
else
   DeleteObject(bitmap_nascosta);
DestroyWindow(fin_graf);
}

/////////////////////////////////////////////////////////////////////////
//   Invia_a_clipboard
/////////////////////////////////////////////////////////////////////////
void Invia_a_clipboard(void)
{
BOOL ok;

ok=OpenClipboard(fin_graf);
if (!ok)
   Error("Non riesco ad aprire la clipboard",
         "Invia_a_clipboard","grabas");

ok=EmptyClipboard();
if (!ok)
   Error("Non riesco a svuotare la clipboard",
         "Invia_a_clipboard","grabas");

ok=SetClipboardData(CF_BITMAP,bitmap_nascosta);
if (!ok)
   Error("Non riesco a scrivere nella clipboard",
         "Invia_a_clipboard","grabas");

CloseClipboard();
}

/////////////////////////////////////////////////////////////////////////
//   Mostra_disegno
/////////////////////////////////////////////////////////////////////////
void Mostra_disegno(void)
{

// la finestra nascosta viene copiata in quella visibile
BitBlt(DC_fin_graf,0,0,640,460,DC_hide,0,0,SRCCOPY);
}

/////////////////////////////////////////////////////////////////////////
//   Usa_rif_2d
/////////////////////////////////////////////////////////////////////////
void Usa_rif_2d(struct riferimento_2d rif_da_usare)
{

rif_2d=rif_da_usare;
}

/////////////////////////////////////////////////////////////////////////
//   Croce
/////////////////////////////////////////////////////////////////////////
BOOL Croce(float x,float y,int dim)
{
int x_video,y_video;

// se il punto è fuori video esco
if ( ((x < rif_2d.xl) || (x > rif_2d.xh))  ||
     ((y < rif_2d.yl) || (y > rif_2d.yh)) )
   return(TRUE);
// calcolo il punto centrale della croce
x_video=(x-rif_2d.xl)/(rif_2d.xh-rif_2d.xl)*640;
y_video=(rif_2d.yh-y)/(rif_2d.yh-rif_2d.yl)*460;
// disegno la croce
MoveTo(DC_hide,x_video,y_video-dim);
LineTo(DC_hide,x_video,y_video+dim+1);
MoveTo(DC_hide,x_video-dim,y_video);
LineTo(DC_hide,x_video+dim+1,y_video);
return(FALSE);
}

/////////////////////////////////////////////////////////////////////////
//   Vai_a
/////////////////////////////////////////////////////////////////////////
BOOL Vai_a(float x,float y)
{
int x_video,y_video;

// calcolo il punto in cui andare
x_video=(x-rif_2d.xl)/(rif_2d.xh-rif_2d.xl)*640;
y_video=(rif_2d.yh-y)/(rif_2d.yh-rif_2d.yl)*460;
// vado nel punto calcolato
MoveTo(DC_hide,x_video,y_video);
// se il punto è fuori video esco con TRUE, altrimenti con FALSE
if ( ((x < rif_2d.xl) || (x > rif_2d.xh))  ||
     ((y < rif_2d.yl) || (y > rif_2d.yh)) )
   return(TRUE);
else
   return(FALSE);
}

/////////////////////////////////////////////////////////////////////////
//   Linea_a
/////////////////////////////////////////////////////////////////////////
BOOL Linea_a(float x,float y)
{
int x_video,y_video;

// calcolo il punto in cui andare
x_video=(x-rif_2d.xl)/(rif_2d.xh-rif_2d.xl)*640;
y_video=(rif_2d.yh-y)/(rif_2d.yh-rif_2d.yl)*460;
// traccio la linea fino al punto calcolato
LineTo(DC_hide,x_video,y_video);
// se il punto è fuori video esco con TRUE, altrimenti con FALSE
if ( ((x < rif_2d.xl) || (x > rif_2d.xh))  ||
     ((y < rif_2d.yl) || (y > rif_2d.yh)) )
   return(TRUE);
else
   return(FALSE);
}

/////////////////////////////////////////////////////////////////////////
//   Cerchio_pieno
/////////////////////////////////////////////////////////////////////////
BOOL Cerchio_pieno(float x,float y,int raggio)
{
int x_video,y_video;

// calcolo il punto in cui andare
x_video=(x-rif_2d.xl)/(rif_2d.xh-rif_2d.xl)*640;
y_video=(rif_2d.yh-y)/(rif_2d.yh-rif_2d.yl)*460;
// traccio la linea fino al punto calcolato
Ellipse(DC_hide,x_video-raggio,y_video-raggio,
                x_video+raggio+1,y_video+raggio+1);
// se il punto è fuori video esco con TRUE, altrimenti con FALSE
if ( ((x < rif_2d.xl) || (x > rif_2d.xh))  ||
     ((y < rif_2d.yl) || (y > rif_2d.yh)) )
   return(TRUE);
else
   return(FALSE);
}

/////////////////////////////////////////////////////////////////////////
//   Cerchio_vuoto
/////////////////////////////////////////////////////////////////////////
BOOL Cerchio_vuoto(float x,float y,int raggio)
{
int x_video,y_video;

// calcolo il punto in cui andare
x_video=(x-rif_2d.xl)/(rif_2d.xh-rif_2d.xl)*640;
y_video=(rif_2d.yh-y)/(rif_2d.yh-rif_2d.yl)*460;
// traccio la linea fino al punto calcolato
Arc(DC_hide,x_video-raggio,y_video-raggio,
            x_video+raggio+1,y_video+raggio+1,
            x_video,y_video-raggio,
            x_video,y_video-raggio);
// se il punto è fuori video esco con TRUE, altrimenti con FALSE
if ( ((x < rif_2d.xl) || (x > rif_2d.xh))  ||
     ((y < rif_2d.yl) || (y > rif_2d.yh)) )
   return(TRUE);
else
   return(FALSE);
} // Cerchio_vuoto
