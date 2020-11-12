#ifndef BUECHER_FUNC_H
#define BUECHER_FUNC_H
/***********************************************************************
 * buecher_func.h
 * Headerfile der Sammlung von Funktionen zur B�cherlisten-Verwaltung
 *
 * Autor: H. Radners (Rumpfprogramm)
 ***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Struktur einer Autor-Definition */
typedef struct {
   char *name;                   /* Zeiger auf vollstdg. Namen dieses Autors */
   unsigned short anz_buecher;   /* Anzahl der B�cher dieses Autors */
} Autor;

/* Struktur einer Verlag-Definition */
typedef struct {
   char *name;                   /* Zeiger auf vollstdg. Namen dieses Verlags */
   unsigned short anz_buecher;   /* Anzahl der B�cher dieses Verlags */
} Verlag;

/* Struktur einer Buch-Definition */
typedef struct {
   char *titel;                     /* Zeiger auf Titelstring */
   Autor *autor;                    /* Zeiger auf Element des Autoren-arrays */
   Verlag *verlag;                  /* Zeiger auf Element des Verlage-arrays */
   unsigned short erscheinungsjahr; /* Jahreszahl 4-stellig, z. B.: 2009 */
   char *isbn;                      /* Zeiger auf ISBN-string */
} Buch;


void buecher_read(FILE *infile,
                  Buch buecher[], int *num_buch, const int MAXBUCH,
                  Autor autoren[], int *num_autor, const int MAXAUTOR,
                  Verlag verlage[], int *num_verlag, const int MAXVERLAG);
/* Liest das komplette Eingabe-file zeilenweise von (bereits
 * ge�ffnetem) infile ein */


void buch_add(char linebuf[],
              Buch buecher[], int *num_buch,
              Autor autoren[], int *num_autor, const int MAXAUTOR,
              Verlag verlage[], int *num_verlag, const int MAXVERLAG);
/* Erh�lt die eingelesene Eingabezeile eines Buch-Datensatzes,
 * zerlegt diese am Trennzeichen in die Attribute und speichert diese.
 * In der Buch-Struktur werden Zeiger auf dessen Autor- und Verlag-
 * Element gespeichert.
 */


void buecher_print(Buch buecher[], const int num_buch);
/* Iteriert �ber B�cherliste zur Ausgabe */


void buch_print(const Buch *b);
/* Gibt ausgew�hlte Attribute eines Buches formatiert aus */

Autor *autor_link(Autor autoren[], int *num_autor, char *autorname);
Verlag *verlag_link(Verlag verlage[], int *num_verlage, char *verlagname);
int cmp_autor_anzbuch(const void *p1, const void *p2) ;
void perm_autoren(int *num_autor, Autor autoren[]) ;

#endif
