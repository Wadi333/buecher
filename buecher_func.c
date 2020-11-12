/***********************************************************************
 * buecher_func.c
 * Sammlung von Funktionen zur B�cherlisten-Verwaltung
 *
 * Autor: H. Radners (Rumpfprogramm)
 ***********************************************************************/

#include "buecher_func.h"
static int i = 0;
static int j = 0 ;
static int cmp = 0 ;
static int k = 0 ;

/***********************************************************************/
int counter(char *str, Buch m_buecher[], int N)
{ int i;
   for (i = 0; i < N; i++)
   {
      if (strcmp(str, m_buecher[i].autor->name) == 0)
      {
         return i;
      }
     
   }
}
int counter2(char *str, Buch m_buecher[], int N)
{ int i;
   for (i = 0; i < N; i++)
   {
      if (strcmp(str, m_buecher[i].verlag->name) == 0)
      {
         return i;
      }
      
   }
}

static unsigned short anz_cmp = 0;
void buecher_read(FILE *infile,
                  Buch buecher[], int *num_buch, const int MAXBUCH,
                  Autor autoren[], int *num_autor, const int MAXAUTOR,
                  Verlag verlage[], int *num_verlag, const int MAXVERLAG)
{
   /* Liest das komplette Eingabe-file zeilenweise von (bereits
    * ge�ffnetem) infile ein */

   enum
   {
      MAXLL = 240

   };                      /* max. input line length */
   char c, linebuf[MAXLL]; /* Einlesepuffer f�r eine Zeile */

   fgets(linebuf, sizeof(linebuf), infile); /* 1x Kopfzeile ueberlesen */

   /* Schleife ueber alle B�cher-Datens�tze, speichern */
   while (fgets(linebuf, sizeof(linebuf), infile))
   {

      if (*num_buch >= MAXBUCH)
      { /* Feldgroesse absichern */
         fprintf(stderr,
                 " *** Hinweis: Mehr als %d B�cher auf der Datei!\n", MAXBUCH);
         break;
      }

      /* Zeilenl�nge absichern */
      if (linebuf[strlen(linebuf) - 1] != '\n')
      { /* Zeile zu lang! */
         fprintf(stderr,
                 " *** Hinweis: Zeile auf der Datei zu lang (>%d)! ", MAXLL);
         fprintf(stderr, "Diese Zeile ignoriert:\n *** >%s...<\n", linebuf);
         while ((c = fgetc(infile)) != EOF)
         { /* Rest der �berlangen Zeile ... */
            if (c == '\n')
               break; /* ... �berlesen bis NL od. EOF  */
         }
         continue; /* diesen (unvollst�ndigen) Buch-Datensatz ignorieren */
      }

      /* dieses Buch mit Verweisen auf Autor und Verlag speichern */
      buch_add(linebuf, buecher, num_buch,
               autoren, num_autor, MAXAUTOR,
               verlage, num_verlag, MAXVERLAG);
   }
   for (k = 0 ; k < *num_buch ; k++ ){
       if (buecher[k].autor->anz_buecher != 0)
   {
       autoren[cmp].anz_buecher = buecher[k].autor->anz_buecher ;
       cmp ++ ;
   }
   }
   
for (k = 0 ; k < *num_buch ; k++ ){

       if (buecher[k].verlag->anz_buecher != 0){
          verlage[anz_cmp].anz_buecher = buecher[k].verlag->anz_buecher ;
           anz_cmp ++ ; 
           }   
           }
}

/***********************************************************************/

void buch_add(char linebuf[],
              Buch buecher[], int *num_buch,
              Autor autoren[], int *num_autor, const int MAXAUTOR,
              Verlag verlage[], int *num_verlag, const int MAXVERLAG)
{
   /* Erh�lt die eingelesene Eingabezeile eines Buch-Datensatzes,
    * zerlegt diese am Trennzeichen in die Attribute und speichert diese.
    * In der Buch-Struktur werden Zeiger auf dessen Autor- und Verlag-
    * Element gespeichert.
    */

   const char *delim = ";\n"; /* CSV-Trennzeichen + NL! */
   char *cp_autor;
   char *cp_verlag;
   char *cp_isbn;
   unsigned short cp_erscheinungsjahr;


   /* Zeile zerlegen und Teile speichern */
   /* Titel;Autor;Verlag;Erscheinungsjahr;ISBN */
   buecher[*num_buch].titel = strdup(strtok(linebuf, delim));
   buecher[*num_buch].autor = malloc(sizeof(Autor));
   cp_autor = strdup(strtok(NULL, delim));
   buecher[*num_buch].autor->name = cp_autor;
   buecher[*num_buch].autor->anz_buecher = 0;
   buecher[*num_buch].verlag = malloc(sizeof(Verlag));
   cp_verlag = strdup(strtok(NULL, delim));
   buecher[*num_buch].verlag->name = cp_verlag;
   buecher[*num_buch].verlag->anz_buecher = 0;
   cp_erscheinungsjahr = atoi(strdup(strtok(NULL, delim)));
   buecher[*num_buch].erscheinungsjahr = cp_erscheinungsjahr;
   buecher[*num_buch].isbn = malloc(sizeof(Buch));
   cp_isbn = strdup(strtok(NULL, delim));
   buecher[*num_buch].isbn = cp_isbn;

   /* Autor im bisherigen Autoren-Feld suchen, ggfs. neu anlegen,
    * pointer darauf im akt. Buch speichern */

   buecher[counter(buecher[*num_buch].autor->name, buecher, *num_buch)].autor->anz_buecher++ ;
   if (buecher[*num_buch].autor->anz_buecher != 0)
   {
       autoren[i].name = buecher[*num_buch].autor->name ;
       i++;
   }

   /* Verlag im bisherigen Verlage-Feld suchen, ggfs. neu anlegen,
    * pointer darauf im akt. Buch speichern */
buecher[counter2(buecher[*num_buch].verlag->name, buecher, *num_buch)].verlag->anz_buecher++ ;
    if (buecher[*num_buch].verlag->anz_buecher != 0)
   {
       verlage[j].name = buecher[*num_buch].verlag->name ;
       j++;
   }

    *num_autor = i;
    *num_verlag = j ;
   (*num_buch)++;
}

/***********************************************************************/

void buecher_print(Buch buecher[], const int num_buch)
{
   /* Iteriert �ber B�cherliste zur Ausgabe */

   unsigned int i;

   for (i = 0; i < num_buch; i++)
   {
      printf("%3d: ", i + 1);
      buch_print(&(buecher[i]));
   }
   
   printf("\n");
}

/***********************************************************************/

void buch_print(const Buch *b)
{
   /* Gibt ausgew�hlte Attribute eines Buches formatiert aus */

   printf("%s (%d): %s\n",
          (b->autor != NULL ? b->autor->name : "*unbekannt*"),
          b->erscheinungsjahr, b->titel);
}
/***********************************************************************/
int compare1 (const void * a, const void * b)
{
  Verlag *A = (Verlag *)a;
  Verlag *B = (Verlag *)b;
  return ( B->anz_buecher - A->anz_buecher);
}
int compare2 (const void * a, const void * b)
{
  Autor *A = (Autor *)a;
  Autor *B = (Autor *)b;
  return ( B->anz_buecher - A->anz_buecher);
}

void print_top_Verlage (Verlag* verlage , int NUMTOP )
{   int i ;
    for(i = 0 ; i < NUMTOP ; i++)
   {
     printf("%2d: (%d) %s\n",i+1,verlage[i].anz_buecher,verlage[i].name) ;
   }
}
void print_top_Autoren(Autor* autoren , int NUMTOP )
{
    int i ;
    for(i = 0 ; i < NUMTOP ; i++)
   {
     printf("%2d: (%d) %s\n",i+1,autoren[i].anz_buecher,autoren[i].name) ;
   }
}



