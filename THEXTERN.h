/*
NOME_FILE:THEXTER.H
PROGETTO:Thesis
AUTORE:Emanuele Maria Santanché
DATA_INIZ:Ott 11'92
FILES DOCUMENTAZIONE:THMODULI.DOC, THGRUPPI.DOC
*/

//////////////////////////////////////////////////////////////////////////
//   DICHIARAZIONE EXTERN DELLE VARIABILI GLOBALI
//////////////////////////////////////////////////////////////////////////
// Generali
extern unsigned _stklen;
extern HANDLE h_programma;
// GRABAS
extern HDC DC_fin_graf;
extern HDC DC_hide;
extern HWND fin_graf;
extern LPSTR nome_classe_fin_graf;
extern HBITMAP bitmap_nascosta;
extern struct tagPAINTSTRUCT struttura_paint;
extern struct riferimento_2d rif_2d;
// FITTIN
extern struct str_descr_filtri descr_filtri[NUM_FILTRI_FINE];

extern struct poliedro POL[2];
extern struct diedro DIE[2];
extern int POLI;
