/***********************************************************************
 * buecher  (IN2, �bungsaufgabe 1)
 * Liest Buecherliste, erzeugt (statische) arrays
 * von B�chern, Autoren, Verlagen.
 * Gibt B�cherliste in Einlese-Reihenfolge und Top-20
 * (nach Anzahl der B�cher) der Autoren- und Verlageliste aus.
 *
 * Autor: H. Radners (Rumpfprogramm)
 ***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "buecher_func.h"

int main() {

   enum {
      MAXBUCH   = 1000, /* Maximalzahl B�cher */
      MAXAUTOR  =  300, /* Maximalzahl Autoren */
      MAXVERLAG =  100, /* Maximalzahl Verlage */
      NUMTOP    =   20, /* Gr��e Bestenliste */
   };

   Buch   buecher[MAXBUCH];   /* array der B�cher */
   Autor  autoren[MAXAUTOR];  /* array der unterschiedlichen Autoren */
   Verlag verlage[MAXVERLAG];/* array der unterschiedlichen Verlage */
   int num_buch   = 0;        /* Anzahl eingelesener B�cher */
   int num_autor  = 0;        /* Anzahl eingelesener, unterschiedl. Autoren */
   int num_verlag = 0;        /* Anzahl eingelesener, unterschiedl. Verlage */
   FILE *infile;              /* filepointer Eingabedatei */
   char infilename[] = "buecherliste.csv";


   /*************************************************************
    * B�cher-Datens�tze einlesen und speichern
    *************************************************************/

   printf("\nBuecher-Liste\n");
   printf("=============\n\n");

   /* Eingabedatei oeffnen und pruefen */
   if ((infile = fopen(infilename, "r")) == NULL) {
      fprintf(stderr, " *** Fehler: Kann '%s' nicht zum Lesen oeffnen!\n",
              infilename);
      return 1;
   }

   /* alle B�cher-Datens�tze einlesen */
   buecher_read(infile, buecher, &num_buch, MAXBUCH,
                autoren, &num_autor, MAXAUTOR,
                verlage, &num_verlag, MAXVERLAG);

   /* Eingabedatei schliessen und Kontrollmeldung */
   fclose(infile);
   printf("Es wurden %d Buecher-Datensaetze\n", num_buch);
   printf("aus %d unterschiedlichen Verlagen\n", num_verlag);
   printf("von %d unterschiedlichen Autoren eingelesen.\n\n", num_autor);


   /*************************************************************
    * Ergebnis-Ausgabe
    *************************************************************/

   printf("=== Eingelesene Buecher ===\n");
   buecher_print(buecher, num_buch);
   printf("=== Top%d Verlage sortiert nach Anzahl Buecher ===\n", NUMTOP);

   qsort(verlage,num_verlag,sizeof(Verlag),compare1) ;

   print_top_Verlage(verlage ,NUMTOP) ;

   printf("\n") ;


   printf("=== Top%d Autoren sortiert nach Anzahl Buecher ===\n", NUMTOP);
   qsort(autoren,num_autor,sizeof(Autor),compare2) ;


   print_top_Autoren(autoren ,NUMTOP ) ;
   printf("\n\n");

   return 0;
}
