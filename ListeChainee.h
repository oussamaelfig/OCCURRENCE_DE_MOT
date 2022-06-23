#ifndef LISTE
#define LISTE
#include <stdio.h>
#include <stdlib.h>

typedef struct _listeChaine *ListeChaine;

typedef struct _routine *Routine;

struct _routine
{
    int[] occurence;
    Routine suivante;
};

struct _listeChaine
{
    Routine initiale;
};

/**
 * Construit une liste chainée vide et la retourne.
 * @return ListeChaine newListe (liste vide)
 */
ListeChaine creerListe();


/**
 * Détruit une liste chainée passée en argument
 * 
 * @param liste a détruire
 */
void detruireListe(ListeChaine *liste);

/**
 * Ajoute une routine a notre liste chainee en parcourant 
 * chaque routine jusqu'à "routine.suivante" == NULL
 * 
 * @param longueurTab pour créer une bonne longueur de tab d'occurence
 */
void ajouterRoutine(int longueurTab, ListeChaine liste);

/**
 * Additionne chaque case du tab d'occurence de chaque routine de la chaine.
 * Place les résultats de chaque addition dans la case correspondate dans un tab d'occurences totale
 * de chaque mot
 * 
 * @return int[] tabOcTotal 
 */
int[] additionnerOccurence();



#endif