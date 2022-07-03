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

Routine creerRoutine(int longeur)
{
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
    // adresse de la prochaine routine
    Routine c = liste->initiale;
    Routine bufferAd = NULL;
    if (c == NULL)
    {
        liste->initiale = creerRoutine(longueurTab);
    }
    else
    {
        while (c != NULL)
        {
            bufferAd = c;
            c = c->suivante;
        }
        bufferAd->suivante  = creerRoutine(longueurTab);
    }
}

/**
 * Additionne chaque case du tab d'occurence de chaque routine de la chaine.
 * Place les résultats de chaque addition dans la case correspondate dans un tab d'occurences totale
 * de chaque mot
 * Si la liste est vide -> retourne NULL
 * @return int[] somme
 */
int *additionnerOccurence(ListeChaine liste, int longueur)
{
    Routine buffer = liste->initiale;
    int *somme;
    if (buffer != NULL)
    {
        somme = malloc(longueur * sizeof(int));
        for (int i = 0; i < longueur; i++)
        {
            somme[i] = 0;
        }

        int i = 0;
        do
        {
            for (i = 0; i < longueur; i++)
            {
                somme[i] += buffer->occurence[i];
            }
            buffer = buffer->suivante;
        } while (buffer != NULL);
    }
    else
    {
        somme = NULL;
    }
    return somme;
}

/**
 * Methode qui retourne la dernière Routine ajoutee a la liste chainee.
 * 
 * @param liste ListeChainee a analyser
 * @return Routine L'adresse de la derniere Routine de la liste
 */
Routine retournerDerniereRoutine(ListeChaine liste)
{
    Routine r = NULL;
    if(liste->initiale != NULL)
    {
        r = liste->initiale;
        while (r->suivante != NULL)
        {
            r = r->suivante;
        }
    }
    return r;
}


/**
 * Fonction qui retourne la taille d'une liste chainee (le nombre de routine qu'elle contient)
 * 
 * @param liste ListeChainee a analiser
 * @return int taille de la liste
 */
int trouverTailleListe(ListeChaine liste)
{
    Routine r = liste->initiale;
    int taille = 0;
    while (r != NULL)
    {
        ++taille;
        r = r->suivante;
    }
    return taille;
}
