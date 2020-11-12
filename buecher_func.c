/***********************************************************************
 * buecher_func.c
 * Sammlung von Funktionen zur B�cherlisten-Verwaltung
 *
 * Autor: H. Radners (Rumpfprogramm)
 ***********************************************************************/

#include "buecher_func.h"
#define MAX_AUTOR 300
/***********************************************************************/
static int i = 0;
Autor *autor_link(Autor autoren[], int *num_autor, char *autorname)
{
   for (i = 0; i < *num_autor; i++)
   {
      if (strcmp(autoren[i].name, autorname) == 0)
      {

         autoren[i].anz_buecher += 1;
         return &autoren[i];
      }
   }

   autoren[*num_autor].name = strdup(autorname);
   autoren[*num_autor].anz_buecher = 1;
   if (*num_autor < MAX_AUTOR-1)
   return &(autoren[(*num_autor)++]);
}

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

   /* Zeile zerlegen und Teile speichern */
   /* Titel;Autor;Verlag;Erscheinungsjahr;ISBN */
   buecher[*num_buch].titel = strdup(strtok(linebuf, delim));
   char *autorname = strtok(NULL, delim);
   buecher[*num_buch].autor = autor_link(autoren, num_autor, autorname);
   buecher[*num_buch].verlag = NULL;
   buecher[*num_buch].erscheinungsjahr = 0;
   buecher[*num_buch].isbn = NULL;
   /* Autor im bisherigen Autoren-Feld suchen, ggfs. neu anlegen,
    * pointer darauf im akt. Buch speichern */
   /* TODO */

   /* Verlag im bisherigen Verlage-Feld suchen, ggfs. neu anlegen,
    * pointer darauf im akt. Buch speichern */
   /* TODO */

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
