/*
NOME_FILE:THVARIE.H
PROGETTO:Thesis
AUTORE:Emanuele Maria Santanché
DATA_INIZ:Ago 26'92
FILES DOCUMENTAZIONE:THMODULI.DOC, THGRUPPI.DOC
*/

/////////////////////////////////////////////////////////////////////////
//   INCLUDE LIBRERIE
/////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <conio.h>
#include <mem.h>
#include <stdlib.h>
#include <alloc.h>
#include <dos.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <math.h>
#pragma argsused

//////////////////////////////////////////////////////////////////////////
//   MACRO
//////////////////////////////////////////////////////////////////////////

//// Generali
// TRUE & FALSE & INDEF
#define TRUE 1
#define FALSE 0
#define INDEF -1
// Il ritorno a capo é il codice 13
#define CR 13
// conversione gradi-radianti e viceversa
#define RAD_GRA 57.2957795131
#define GRA_RAD 1.74532925199E-2
// macro per il massimo e il minimo
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

//// MODPOL
#define DEV_ANG_MAX_LASER 0.00015
#define DEV_ANG_MAX_PSD   0.0002
// errori di puntamento del laser e di misura del PSD. Si tratta
// di deviazioni angolari in radianti. Sono la metà di quelle
// complessive
#define MAX_ALLONTANAMENTO_PER_RUMORE 100
// si dichiara indefinito un punto se dopo l' aggiunta dell' errore di
// misura esso viene a trovarsi ad una distanza dal punto ideale superiore
// a 10 mm. MAX_ALLONTANAMENTO_PER_RUMORE è il quadrato di tale numero.

//// IMMAGI
#define ESTENSIONE_IMMAGINI ".img"
#define DIRECTORY_IMMAGINI "c:\\thdata\\"
#define RAD2_DIV_2  0.707106781185
#define ALL_X 1
#define ALL_Z 2

//// GRABAS
#define INVIA_A_CLIPBOARD TRUE
#define NON_INV_A_CLIPBOARD FALSE

//// TAGLIO
#define PATH_FILE_TAGLIO "c:\\thdata\\taglio"
#define TEMPO_PER_TAGLIO 5.0
#define NUM_MAX_PUNTI_INT  1820
#define NUM_MAX_PUNTI_FILE 200
#define ALL_RETTA 25

//// RICDIS
#define NUM_MAX_PART NUM_MAX_PUNTI_INT/3+1
#define GAUSS_VERSO_UNIF 1.73205080757
#define MARG_SICUR_RUMORE 1.2
#define MINIMO_PER_CORR 8
#define SUPP_CORR_A 5
#define RAPP_RUMORE_A 2.0
#define SUPP_CORR_B 9
#define RAPP_RUMORE_B 2.0
#define SOGLIA_CANC_DISC 1
#define SOGLIA_MIN_RUMORE 0.1
#define RUMORE_DI_DEFAULT 0.1

//// FITTIN
#define NUM_FILTRI_GROSS 8
#define NUM_FILTRI_FINE  14

//// LOCDIS
#define SOGLIA_FILTRI_GRANDI 3
#define PRIMO_FILTRO_GRANDI 0
#define PRIMO_FILTRO_PICCOLI 2
#define ULTIMO_FILTRO_GRANDI 10
#define ULTIMO_FILTRO_PICCOLI 13
#define SICUR_SALTO 3.0
#define SICUR_ANGOLO 3.0
#define SALTO 1
#define ANGOLO 2
#define NON_TROVATA 3

//// ANADIS
#define PASSO_GROSS 0.4
#define PASSO_FINE 0.2
#define NUM_MAX_DISC 100
#define SOGLIA_CURVATURA -0.01
#define SOGLIA_DERIVATA 6.0
#define NUM_TENTATIVI_FITT_BORDO 2
#define NUM_FILTRI_BORDO 4
#define INCREM_SUPP 6

//// ERICPO
#define PATH_REPORT_ERICPO "c:\\thdata\\"
// path parziale dei files di report degli esperimenti di riconoscimento
// dei poliedri
#define PERC_DEFINITI 0.5
// percentuale minima di punti che devono risultare definiti in un taglio
