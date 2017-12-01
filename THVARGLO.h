/*
NOME_FILE:THVARGLO.H
PROGETTO:Thesis
AUTORE:Emanuele Maria Santanché
DATA_INIZ:Ago 26'92
FILES DOCUMENTAZIONE:THMODULI.DOC, THGRUPPI.DOC
*/

////////////////////////////////////////////////////////////////////////////
//   DICHIARAZIONE VARIABILI GLOBALI
////////////////////////////////////////////////////////////////////////////

//// Generali
// Assegnazione della grandezza dello stack
extern unsigned _stklen = 45000;
// handler del programma, reso globale perché richiesto in molte funzioni,
// per es. quelle di GRABAS
HANDLE h_programma;

//// MODPOL
// descrizione dei due poliedri (vedi funzione Imposta_poliedro() di MODPOL)
struct poliedro POL[2];
// parametri intrinseci dei due doppi diedri rappresentati dai due poliedri
// (vedi funzione Imposta_poliedro() di MODPOL)
struct diedro DIE[2];
// identificatore del poliedro (o doppio diedro che dir si voglia) in uso.
// POLI vale 0 o 1 (vedi funzione Imposta_poliedro() di MODPOL)
int POLI;

//// GRABAS
// device context relativo alla finestra grafica
HDC DC_fin_graf;
// device context relativo alla finestra nascosta e in cui si disegna per
// poi copiare la bitmap risultante nella finestra grafica visibile
HDC DC_hide;
// questo è l' handler della finestra grafica
HWND fin_graf;
// questo è il nome della classe della finestra, richiesto dalla funzione
// RegisterClass (Inizializza_grafica) e da CreateWindow (Apri_fin_graf)
LPSTR nome_classe_fin_graf = "Classe_finestra_grafica";
// handler della bitmap nascosta su cui si disegna per poi copiarla sulla
// finestra grafica
HBITMAP bitmap_nascosta;
// struttura dati contenente informazioni sullo stato del disegno.
// E' usata da BeginPaint e EndPaint in Apri_fin_graf e Chiudi_fin_graf
struct tagPAINTSTRUCT struttura_paint;
// riferimento utente usato nelle funzioni di disegno grafico (Croce,
// Linea_a, Vai_a ecc.) (vedi la struttura riferimento_2d). Viene
// inizializzato di default per evitare catastrofi se si dimenticasse
// di impostarlo con Usa_rif_2d() (GRABAS)
struct riferimento_2d rif_2d={ -320, 320, -230, 230};

//// FITTIN
// array delle descrizioni dei filtri per il fitting
struct str_descr_filtri descr_filtri[NUM_FILTRI_FINE];