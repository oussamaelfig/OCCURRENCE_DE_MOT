#include "ListeChainee.h"


/**
 * Construit une liste chainée vide et la retourne.
 * @return ListeChaine newListe (liste vide)
 */
ListeChaine creerListe()
{
    ListeChaine nouvListe = malloc(sizeof(struct _listeChaine));
    nouvListe->initiale = NULL;
    return nouvListe;
}

Routine creerRoutine(int longeur){
    Routine r = malloc(sizeof(struct _routine));
    r->suivante = NULL;
    r->occurence = malloc(longeur * sizeof(int));
    return r;
}

/**
 * Détruit une liste chainée passée en argument
 * 
 * @param liste a détruire
 */
void detruireListe(ListeChaine *liste)
{
    Routine adresse = NULL;
    while ((**liste).initiale != NULL)
    {
        adresse = (**liste).initiale;
        free((**liste).initiale->suivante);
        (**liste).initiale->suivante = NULL;
        (**liste).initiale = (**liste).initiale->suivante;
        free(adresse);
    }
    free(*liste);
    *liste = NULL;
}

/**
 * Ajoute une routine a notre liste chainee en parcourant 
 * chaque routine jusqu'à "routine.suivante" == NULL
 * 
 * @param longueurTab pour créer une bonne longueur de tab d'occurence
 */
void ajouterRoutine(int longueurTab, ListeChaine liste)
{
    //adresse de la prochaine routine
    Routine c = liste->initiale;
    Routine bufferAd = NULL;
    if (c == NULL)
    {
        liste->initiale = creerRoutine(longueurTab);
    }else
    {
        while (c != NULL)
        {
            bufferAd = c;
            c = c->suivante;
        }
        bufferAd->suivante = liste->initiale = creerRoutine(longueurTab);
    }
}

/**
 * Additionne chaque case du tab d'occurence de chaque routine de la chaine.
 * Place les résultats de chaque addition dans la case correspondate dans un tab d'occurences totale
 * de chaque mot
 * 
 * @return int[] tabOcTotal 
 */
int * additionnerOccurence(ListeChaine liste)
{
    return NULL;
}
