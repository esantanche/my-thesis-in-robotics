/*
NOME_FILE:THPROTOT.H
PROGETTO:Thesis
AUTORE:Emanuele Maria Santanché
DATA_INIZ:Ago 26'92
FILES DOCUMENTAZIONE:THMODULI.DOC, THGRUPPI.DOC
*/

//////////////////////////////////////////////////////////////////////////
//   THMAIN
//////////////////////////////////////////////////////////////////////////
// PRESEN
void Presentazione(void);
// PROVEF
void Prove_1(void);
void Prove_2(void);

//////////////////////////////////////////////////////////////////////////
//   MODPOL
//////////////////////////////////////////////////////////////////////////
// IMPOST
void Imposta_poliedro(void);
// INTERS
void Triangola_modpol(struct retta r,struct punto pv,
                      struct punto *pi,float *distanza,float *param_retta,
                      struct punto *pir,float *dist_rum);
// RUMORE
void Aggiungi_rumore_misura(struct retta rp,struct vettore n,
                            struct punto pi,struct punto pv,
                            struct punto *pr);

//////////////////////////////////////////////////////////////////////////
//   GRABAS
//////////////////////////////////////////////////////////////////////////
// INIZIA
void Inizializza_grafica(void);
long FAR PASCAL _export Messaggi_finestra(HWND w,WORD msg,WORD q,long l);
// GESFIN
void Apri_fin_graf(LPSTR titolo_fin_graf);
void Chiudi_fin_graf(BOOL invia_a_clipboard);
// CLPBRD
void Invia_a_clipboard(void);
// DISEGN
void Mostra_disegno(void);
void Usa_rif_2d(struct riferimento_2d rif_da_usare);
BOOL Croce(float x,float y,int dim);
BOOL Vai_a(float x,float y);
BOOL Linea_a(float x,float y);
BOOL Cerchio_pieno(float x,float y,int raggio);
BOOL Cerchio_vuoto(float x,float y,int raggio);

//////////////////////////////////////////////////////////////////////////
//   GEOMET
//////////////////////////////////////////////////////////////////////////
// INTRET
void Interseca_cono_retta(float x0,float z0,float x1,float z1,
                          struct retta r,
                          struct punto *p,
                          struct vettore *n,
                          float *distanza,float *param_retta);
void Calcola_normale_cono(float x0,float z0,float x1,float z1,
                          struct punto *p,struct vettore *n);
void Interseca_cilindro_retta(float xc,float z0,float z1,
                              struct retta r,
                              struct punto *p,
                              struct vettore *n,
                              float *distanza,float *param_retta);
void Calcola_normale_cilindro(float xc,float z0,float z1,
                              struct punto *p,struct vettore *n);
void Interseca_piano_retta(float x0,float x1,float zr,
                           struct retta r,
                           struct punto *p,
                           struct vettore *n,
                           float *distanza,float *param_retta);
// VISIBI
BOOL Visibilita_cono_retta(float x0,float z0,float x1,float z1,
                           struct retta r,BOOL stesso);
BOOL Visibilita_cilindro_retta(float xc,float z0,float z1,
                               struct retta r,BOOL stesso);
BOOL Visibilita_piano_retta(float x0,float x1,float zr,
                            struct retta r,BOOL stesso);
// INTSEG
BOOL Interseca_segmenti(float x1,float z1, float x2,float z2,
                        float x3,float z3, float x4,float z4);
BOOL Distanza_segmenti(float x1,float z1, float x2,float z2,
                       float x3,float z3, float x4,float z4);
// INTPIA
void Interseca_piano_cerchio(struct piano piano,
                             float z_cerchio,
                             float raggio,
                             struct punto *p1,
                             struct punto *p2);
// CRERET
struct retta Crea_retta(float xp,float yp,float zp,
                        float xa,float ya,float za);
struct punto Punto_da_retta(struct retta r,float t);
// PIANO3
struct piano Piano_per_tre_punti(struct punto p1,
                                 struct punto p2,
                                 struct punto p3);
// VETTOR
struct vettore Versore_da_retta(struct retta r);
float Coseno_tra_versori(struct vettore v1,struct vettore v2);
struct vettore Vett_tra_punti(struct punto p1,struct punto p2);
float Prod_scal(struct vettore v1,struct vettore v2);
struct vettore Prod_vett(struct vettore v1,struct vettore v2);
struct vettore Vett_per_scal(float s,struct vettore v);
struct vettore Sott_vett(struct vettore v1,struct vettore v2);
struct vettore Somma_vett(struct vettore v1,struct vettore v2);
struct punto Punto_piu_vett(struct punto p,struct vettore v);
float Modulo(struct vettore v);

//////////////////////////////////////////////////////////////////////////
//   TAGLIO
//////////////////////////////////////////////////////////////////////////
// CREAZI
void Crea_taglio_rett_int(struct punto *pp,
                          struct punto pv,
                          struct retta rt,
                          int n_punti,
                          struct taglio_rett_int huge *t);
void Crea_taglio_rett_file(int n_modello,
                           struct modello_rotondo *m,
                           struct punto *pp,
                           struct punto pv,
                           struct retta rt,
                           int n_punti,
                           struct taglio_rett_file *t,
                           BOOL no_rum_mod);
struct taglio_rett_int huge *Alloca_taglio(void);
void Dealloca_taglio(struct taglio_rett_int huge *t);
// GESFIL
void Creaz_e_salvat_taglio_rett_inter(void);
void Creaz_e_salvat_taglio_rett_cas(void);
struct retta Genera_cas_rette_taglio(int n_base_line,
                                     struct modello_rotondo *m);
BOOL Scegli_file_taglio_rett(char lettere[3]);
int Scegli_e_carica_taglio_rett(char lettere[3],struct taglio_rett_file *t);
BOOL Carica_taglio_rett(char lettere[3],int num_taglio,
                        struct taglio_rett_file *t);
BOOL Esiste_file_tagli(char lettere[3]);
// VISUAL
void Carica_e_visual_taglio_rett(void);
void Visual_dati_taglio_rett(char lettere[3],int num_taglio,
                             struct taglio_rett_file *t);
void Visual_graf_taglio_rett(char lettere[3],int num_taglio,
                             struct taglio_rett_file *t);
//////////////////////////////////////////////////////////////////////////
//   IMMAGI
//////////////////////////////////////////////////////////////////////////
// CREAZI
void Crea_immagine(void);
// VISUAL
void Visual_immagine(void);

//////////////////////////////////////////////////////////////////////////
//   UTILIT
//////////////////////////////////////////////////////////////////////////
// DOMENU
int Menu(char test[60],char *opz[20]);
// ERRORI
void Error(char *errmsg,char *nomerout,char *nomefile);
// VARIEF
void Aspetta_return(void);
void Crea_str_da_campo(char *campo,char *str,int lungh);
void Crea_campo(char *campo,char *stringa,int lungh);
void Zero_string(char res[3],int num);
float Ranf(float da, float a);
BOOL Lz(double l);
// DEBUGF
void Debug(int line,char file[40]);
void Screen_saver(float lavoro);

//////////////////////////////////////////////////////////////////////////
//   NUMREC
//////////////////////////////////////////////////////////////////////////
//   SISLIN
BOOL ludcmp(double huge **a,int n,int huge *indx,double *d);
void lubksb(double huge **a,int n,int huge *indx,double huge *b);
//   UTILIT
double huge *vector(int nl,int nh);
int huge *ivector(int nl,int nh);
void nrerror(char error_text[]);
void free_vector(double huge *v,int nl);
void free_ivector(int huge *v,int nl);
double huge **matrix(int nrl,int nrh,int ncl,int nch);
void free_matrix(double huge **m,int nrl,int nrh,int ncl);
int huge **imatrix(int nrl,int nrh,int ncl,int nch);
void free_imatrix(int huge **m,int nrl,int nrh,int ncl);

//////////////////////////////////////////////////////////////////////////
//   MATEMA
//////////////////////////////////////////////////////////////////////////
// OPEMAT
void Prod_matr(double huge **m1,int r1,int c1,
               double huge **m2,int r2,int c2,
               double huge **mr);
void Trasposta(double huge **m,int r,int c,
               double huge **mr);
void Inversa(double huge **m,int n,double huge **mr);
// POLINO
double Valuta_polinomio(int ord,double x,double huge *coeff);
// SUPCOM
void Rotazione_quaternionica(double huge *q,
                             double huge **alpha,
                             double huge *bet,
                             struct vettore *s1,
                             struct vettore *s2,
                             struct vettore *s3, int die);
void Mnewt(int ntrial, double huge *x, int n, float tolx, float tolf,
           struct vettore *s1,struct vettore *s2,struct vettore *s3,
           int die);

//////////////////////////////////////////////////////////////////////////
//   RICDIS
//////////////////////////////////////////////////////////////////////////
// PARTAG
void Partiziona_taglio(struct taglio_rett_int huge *t,
                       struct elenco_part *e);
// TAPBUC
void Tappa_buchi_dist(struct taglio_rett_int huge *t,
                      struct elenco_part *e);
// VALRUM
void Valuta_rumore(struct taglio_rett_int huge *t,   // buchi già attappati
                   struct elenco_part *e,       // già calcolato
                   double huge *rumore);
// TRODIS
void Trova_discontinuita(
                  struct taglio_rett_int huge *t,   // buchi già attappati
                  struct elenco_part *e,            // già calcolato
                  double huge *rumore,                   // già valutato
                  int huge *discontinuita);

//////////////////////////////////////////////////////////////////////////
//   FITTIN
//////////////////////////////////////////////////////////////////////////
// INIZIA
void Inizializza_filtri(void);
void Dealloca_filtri(void);
// ESTRAI
void Estrai_segmento(struct taglio_rett_int huge *t,
                     BOOL rum_indef,
                     double huge *rumore,
                     int punto_inizio,
                     int lungh,
                     BOOL avanti,
                     double huge *seg_distanze,
                     double huge *seg_rumore);
// DOFITT
void Esegui_fitting(struct taglio_rett_int huge *t,
                    BOOL rum_indef,
                    double huge *rumore,
                    int punto_inizio,
                    int num_filtro,
                    BOOL avanti,
                    double huge *coeff,
                    double *sqme,
                    double *prob,
                    BOOL *accettato);

//////////////////////////////////////////////////////////////////////////
//   LOCDIS
//////////////////////////////////////////////////////////////////////////
// LOCDIS
void Localizza_una_discontinuita(struct taglio_rett_int huge *t,
                                 struct elenco_part *e,
                                 double huge *rumore,
                                 int pos_disc,
                                 int fil_disc,
                                 int *tipo_disc,
                                 int *pos_fin_disc,
                                 int *filtro_fin,
                                 double *valore_disc,
                                 double huge *coeff3_dx,
                                 double huge *coeff3_sx);

//////////////////////////////////////////////////////////////////////////
//   ANADIS
//////////////////////////////////////////////////////////////////////////
// ANADIS
void Analizza_discontinuita(struct punto *pp,
                            struct punto pv,
                            struct retta rt,
                            struct taglio_rett_int huge *t,
                            struct elenco_part *e,
                            double huge *rumore,
                            int huge *discontinuita,
                            struct elenco_disc huge *ed);
void Calcola_retta_fine(struct taglio_rett_int huge *t,
                        struct retta rt,
                        int indice_disc,
                        int fil_disc,
                        struct retta *rtf,
                        int *n_punti);
// ALLELD
struct elenco_disc huge *Alloca_elenco_disc(void);
void Dealloca_elenco_disc(struct elenco_disc huge *ed);

//////////////////////////////////////////////////////////////////////////
//   ERICPO
//////////////////////////////////////////////////////////////////////////
// ERICPO
void Esperimento_di_ric_poliedri(void);
void Presentazione_e_parametri(FILE *r,char path[40],
                               int iterazioni);
void Esegui_un_riconoscimento(double *errore,
                              int *pol_ric,
                              BOOL *riuscito);

