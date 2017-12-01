/*
NOME_FILE:THSTRUCT.H
PROGETTO:Thesis
AUTORE:Emanuele Maria Santanché
DATA_INIZ:Ago 26'92
FILES DOCUMENTAZIONE:THMODULI.DOC, THGRUPPI.DOC
*/

//////////////////////////////////////////////////////////////////////////
//   GRABAS
//////////////////////////////////////////////////////////////////////////

// la seguente struttura serve per disegnare punti o linee sulla finestra
// grafica: alla funzione di disegno si danno coordinate in riferimento
// utente e la funzione di disegno converte in coordinate video tramite
// questo riferimento per il quale l' ascissa sinistra dello schermo
// è xl, quella destra è xh, l' ordinata superiore è yh,
// quella inferiore yl. In altri termini c'è una corrispondenza utente -
// video che è: (xl,yl) -> (0,460), (xl,yh) -> (0,0), (xh,yl) -> (640,460),
// (xh,yh) -> (640,0). Ricordo che la finestra grafica ha uno spazio
// utile di 640 x 460 pixel.

struct riferimento_2d {
   float               xl;
   float               xh;
   float               yl;
   float             yh;
};

//////////////////////////////////////////////////////////////////////////
//   GEOMET
//////////////////////////////////////////////////////////////////////////

// la seguente è una struttura che descrive una retta passante per i
// punti (xp,yp,zp) e (xa,ya,za). Precisamente l' equazione della retta è:
// x=xp+(xa-xp)*t, y=yp+(ya-yp)*t, z=zp+(za-zp)*t
// Volendo sapere la distanza tra un punto sulla retta e il punto
// di origine (xp,yp,zp), se si conosce il parametro t corrispondente a
// tale punto, si ottiene la distanza (con segno) calcolando cd*t

struct retta {
   float               xp;
   float               yp;
   float               zp;
   float               xap;  // = xa-xp
   float               yap;  // = ya-yp
   float               zap;  // = za-zp
   float               cd;   // = sqrt(xap^2+yap^2+zap^2)
};

// la seguente struttura definisce un punto.

struct punto {
   BOOL               indefinito; // TRUE se il punto non è definito
   float              x;
   float              y;
   float              z;
};

// la seguente struttura definisce un vettore

struct vettore {
   BOOL               indefinito; // TRUE se il vettore non è definito
   float              a;
   float              b;
   float              c;
};

// la seguente struttura definisce un piano corrispondente all'
// equazione ax+by+cz+d=0

struct piano {
   BOOL               indefinito; // TRUE se il piano non è definito
   float              a;
   float              b;
   float              c;
   float              d;
};

//////////////////////////////////////////////////////////////////////////
//   TAGLIO
//////////////////////////////////////////////////////////////////////////

// la seguente struttura contiene un taglio destinato ad essere salvato su
// file

struct taglio_rett_file {
   char                 data[8]; // data di creazione del taglio
   char                 ora[8];  // ora di creazione del taglio
   int                  n_modello; // modello "tagliato"
   struct punto         pp; // punto di proiezione laser
   struct punto         pv; // punto di vista (PSD)
   struct retta         rt; // retta di taglio (il cui punto di partenza
                            // è il punto di inizio del taglio e il punto
                            // corrispondente al valore unitario del
                            // parametro della retta è il punto di fine
                            // del taglio
   int                  n_punti; // numero di punti del taglio
   struct {  // punti rilevati dal taglio
      struct punto         pi;  // punto misurato privo di rumore
      float                dist_i;  // distanza del punto dal punto di
                                    // proiezione laser
      struct punto         pr; // punto misurato comprensivo di rumore
      float                dist_r;  // distanza del punto dal punto di
                                    // proiezione laser
   } p[NUM_MAX_PUNTI_FILE];  // l' array dei punti è dimensionato per
                             // NUM_MAX_PUNTI_FILE punti
};

// la seguente struttura contiene un taglio destinato ad uso interno

struct taglio_rett_int {
   int                  n_punti; // numero di punti del taglio
   struct { // punti rilevati dal taglio
      struct punto         pi; // punto misurato privo di rumore
      float                dist_i; // distanza del punto dal punto di
                                   // proiezione laser
      struct punto         pr; // punto misurato comprensivo di rumore
      float                dist_r; // distanza del punto dal punto di
                                   // proiezione laser
   } p[NUM_MAX_PUNTI_INT]; // l' array dei punti è dimensionato per
                           // NUM_MAX_PUNTI_INT punti
};

//////////////////////////////////////////////////////////////////////////
//   RICDIS
//////////////////////////////////////////////////////////////////////////

// Il taglio viene partizionato in sequenze di punti definiti e sequenze
// di punti indefiniti. Vengono riportati i punti di inizio e di fine
// della partizione, la sua lunghezza ed anche il numero di punti
// definiti in essa presenti se si tratta di una sequenza di punti definiti,
// analogamente se si tratta di una sequenza di punti indefiniti.
// Il numero di punti definiti in una sequenza di punti definiti non
// coincide con la sua lunghezza perché ci possono essere singoli punti
// indefiniti (o coppie) che vengono inglobati nella sequenza

struct elenco_part {
   int                     n_part; // numero di partizioni
   struct {
      BOOL                    stato; // TRUE=sequenza di punti indefiniti
      int                     da; // punto di partenza, compreso nella
                                  // sequenza
      int                     a; // punto di arrivo, compreso nella
                                 // sequenza
      int                     lungh;  // lunghezza della partizione
      int                     n_stato; // numero di punti indefiniti in
                                       // in sequenze indefinite,
                                       // numero di punti definiti in
                                       // in sequenze definite
   } part[NUM_MAX_PART];  // l' array è dimensionato per NUM_MAX_PART
                          // partizioni
};

//////////////////////////////////////////////////////////////////////////
//   FITTIN
//////////////////////////////////////////////////////////////////////////

// la seguente struttura serve a contenere la descrizione dei filtri di
// fitting. Occorre una di queste strutture per ognuno dei NUM_FILTRI_FINE
// filtri. Occorre spiegare il campo fil_fine. Se filtro di numero
// progressivo n, usato come rilevatore di discontinuità grossolano, trova
// una discontinuità, il campo fil_fine dice quale filtro usare per
// localizzare in modo fine la discontinuità. Se il passo di spaziatura del
// taglio grossolano non è il doppio di quello del taglio fine, i numeri
// d' ordine dei filtri non coincidono. Se invece il passo di spaziatura del
// taglio grossolano è il doppio di quello del taglio fine, allora il numero
// d' ordine del filtro rimane lo stesso perché è giusto che il supporto
// dell'operatore fine sia la metà (in mm) di quello dell' operatore
// grossolano.

struct str_descr_filtri {
   int                     lungh_supp; // lunghezza in passi di spaziatura
                                       // del filtro (s)
   int                     ord_fitt; // ordine di fitting del filtro (o)
   int                     fil_fine; // filtro fine corrispondente
   double                  soglia;   // soglia minima di verosimiglianza
                                     // per l' accettazione del fitting
   double huge             **filtro; // matrice o+1 x s contenente
                                     // il filtro di fitting
};

//////////////////////////////////////////////////////////////////////////
//   ANADIS
//////////////////////////////////////////////////////////////////////////

// la struttura seguente è l' elenco delle discontinuità che vengono
// trovate nell' analisi grossolana di un taglio e nella successiva
// analisi fine. Le discontinuità interne sono quelle rilevate internamente
// ad una sequenza di punti definiti. Quelle esterne sono invece quelle
// tra sequenze di punti definiti e sequenze di punti indefiniti.
// Le discontinuità possono non corrispondere a spigoli se dovute ad
// autoocclusione: per es. un cilindro tagliato perpendicolarmente all' asse
// non presenta spigoli però produce due discontinuità nei dati di distanza.
// In tal caso da_inseguire sarà FALSE.

struct elenco_disc {
   int                     n_disc; // numero di discontinuità
   struct {
      BOOL                    interna;  // TRUE se si tratta di discont.
                                        // interna
      int                     tipo_disc;  // ha il valore della macro
                                          // SALTO oppure ANGOLO
      BOOL                    da_inseguire;
      struct vettore          vers_disc; // è un versore orientato come la
                                         // retta di taglio fine. Se la
                                         // discont. è a salto, il versore
                                         // punta verso il lato del salto
                                         // più vicino al punto di
                                         // proiezione laser
      double                  supporto;  // è il doppio del supporto
                                         // del filtro che ha rilevato la
                                         // discont. . Però in mm
      double                  curvatura; // è la curvatura della superficie
                                         // in corrispondenza di un salto,
                                         // dal lato più vicino al punto di
                                         // proiezione laser. In 1/mm
      double                  derivata_dx; // derivata del lato destro,
                                           // riportata ai mm e orientata
                                           // secondo vers_disc
      double                  derivata_sx; // derivata del lato sinistro,
                                           // riportata ai mm e orientata
                                           // secondo vers_disc
      double                  valore_disc; // valore della discontinuità
                                           // (salto nel valore o nella
                                           // derivata) riportato ai mm
      struct punto            punto_disc; // punto della discont.
   } d[NUM_MAX_DISC]; // l' array è dimensionato per NUM_MAX_DISC
                      // discontinuità
};

//////////////////////////////////////////////////////////////////////////
//   MODPOL
//////////////////////////////////////////////////////////////////////////

// la seguente struttura definisce una faccia del poliedro in base ai
// vertici di cui è composta, vertici chiaramente elencati in modo ordinato

struct faccia {
   int  n_vert; // numero di vertici di cui è composta la faccia
   int  nv[10]; // numeri d'ordine dei vertici nell' elenco dei vertici
                // contenuto nella definizione del poliedro
   struct vettore  n; // normale alla faccia uscente dal poliedro
   float  d;  // quarto parametro piano faccia: la normale alla faccia, con
              // le sue tre componenti, fornisce i primi tre coefficienti
              // dell' equazione del piano cui la faccia appartiene. Se
              // tale piano ha equazione ax+by+cz+d=0, a,b,c sono appunto le
              // tre componenti di n, mentre il coefficiente d è appunto il
              // dato che stiamo esaminando
};

// la seguente struttura definisce un poliedro dando le coordinate dei
// vertici e la definizione delle facce in funzione di tali vertici

struct poliedro {
   int               n_vertici; // numero di vertici presenti nel poliedro
   int               n_facce; // numero di facce del poliedro
   struct punto      v[10]; // coordinate dei vertici del poliedro
   struct faccia     f[10]; // descrizione delle facce del poliedro
};

// la seguente struttura contiene i parametri intrinseci che definiscono un
// doppio diedro e che vanno usati nella costruzione della sup. di
// compatibilità

struct diedro {
   struct vettore    n1; // normale alla prima faccia
   struct vettore    n2; // normale alla seconda faccia
   struct vettore    n3; // normale alla terza faccia
   float             fi; // angolo tra il secondo e il terzo spigolo
   float             d1; // lunghezza secondo spigolo (prolungato)
   float             d2; // lunghezza terzo spigolo (prolungato)
   float             fi1; // angolo primo-secondo spigolo
   float             fi2; // angolo terzo-quarto spigolo
};
