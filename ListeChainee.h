#ifndef LISTE
#define LISTE
#include <stdio.h>
#include <stdlib.h>

typedef struct _listeChaine *ListeChaine;

typedef struct _routine *Routine;

struct _routine
{
    Routine suivante;
    int *occurence;
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
int *additionnerOccurence(ListeChaine liste, int longueur);


/**
 * Methode qui retourne la dernière Routine ajoutee a la liste chainee.
 * 
 * @param liste ListeChainee a analyser
 * @return Routine L'adresse de la derniere Routine de la liste
 */
Routine retournerDerniereRoutine(ListeChaine liste);

/**
 * Fonction qui retourne la taille d'une liste chainee (le nombre de routine qu'elle contient)
 * 
 * @param liste ListeChainee a analiser
 * @return int taille de la liste
 */
int trouverTailleListe(ListeChaine liste);

#endif