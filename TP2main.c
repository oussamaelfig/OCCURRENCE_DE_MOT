/*
 * TP2 INF3135 : OCCURRENCE DE MOT
 * Author: OUSSAMA EL-FIGHA
 * Author: NICOLAS PLANTE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "ListeChainee.h"
#define DEBUG

/**
 * Fonction qui verfie si le char est une lettre de l'alphabet anglais.
 * Le "& 0x00DF" permet de rendre une lettre maj et si elle l'etait deja, elle
 * restera inchangee.
 *
 * @param c
 * @return int 1 si c'est une lettre sinon 0
 */
int estLettre(char c)
{
    return (c & 0x00DF) >= 'A' && (c & 0x00DF) <= 'Z';
}

/**
 * Verifie si le char est un chiffre
 *
 * @param c
 * @return int 1 si c'est un chiffre sinon 0
 */
int estChiffre(char c)
{
    return c >= '0' && c <= '9';
}

/**
 * Verifie si le char est un "blanc"
 *
 * @param c
 * @return int 1 si oui sinon 0
 */
int estEspaceBlanc(char c)
{
    return c == ' ' || c == '\t' || c == '\n';
}

/**
 * Fonction qui verfie si le char est valide ou pas.
 * valide (lettre, '_', chiffres ou blanc )
 *
 * @param c
 * @return int estValide (1 si le char est valide sinon 0)
 */
int charEstValide(char c)
{
    char cMaj = c & 0x00DF;
    int estValide = 1;
    if (estLettre(cMaj) || estChiffre(c) || c == '_' || estEspaceBlanc(c))
    {
        estValide = 0;
    }
    else
    {
        // printf("%c\n", c);
        fprintf(stderr, "Le fichier contient autre chose que des mots valides séparés par des blancs\n");
        exit(-1);
    }
    return estValide;
}

/**
 * analyse so le fichier contient des mot valide et stock ces mots dans un tableau
 * de mot.
 * Si un char non valide est detecte, le programme se termine.
 *
 * @param buffer
 * @param tM
 * @param indice
 * @return int indice qui est le nombre de mot que le fichier contient
 */
int analyserMots(char *buffer, char *tM[], int indice)
{
    int i = 0;
    int j = 0;
    int longBuffer = strlen(buffer);
    if(longBuffer <= 0)
    {
        fprintf(stderr, "Erreur, le fichier de mots à trouver est vide.\n");
        exit(-1);
    }
    while (i < longBuffer - 1 || buffer[i] != 0)
    {
        if (estLettre(buffer[i]))
        {
            tM[indice] = malloc(longBuffer * sizeof(char));
            tM[indice][j] = buffer[i];
            while (i < longBuffer && !charEstValide(buffer[i]) && !estEspaceBlanc(buffer[i]))
            {
                ++i;
                ++j;
                tM[indice][j] = buffer[i];
            }
            tM[indice][j] = 0;
            ++indice;
        }
        else if (!estEspaceBlanc(buffer[i]) && buffer[i] != 0)
        {
            fprintf(stderr, "Le fichier contient autre chose que des mots valides séparés par des blancs\n");
            exit(-1);
        }
        j = 0;
        ++i;
    }
    if (indice == 0)
    {
        ++indice;
    }
    return indice;
}

/**
 * Procedure qui verifie si le bon nombre d'arguments est entre.
 * Si ce n'est pas le cas, le programme se termine.
 *
 * @param argc
 */
void verifierArgument(int argc)
{
    if (argc != 2)
    {
        fprintf(stderr, "Il n’y a pas le bon nombre d’arguments sur la ligne de commande.\n");
        exit(-1);
    }
}

/**
 * Fonction qui compte le nombre de char que contient le texte entre par
 * l'utilisateur
 *
 * @param nom
 * @return int cpt qui est le nombre de caracteres entres
 */
int compterChar(const char *nom)
{
    FILE *file = fopen(nom, "r");
    int cpt = 0;
    int estFini = 0;
    char c = 0;
    do
    {
        c = fgetc(file);
        if (feof(file))
        {
            estFini = 1;
        }
        ++cpt;
    } while (!estFini);
    fclose(file);
    return cpt;
}

/**
 * Cette procedure vient detruire toutes les sous chaines qui correspondent aux mots
 * a trouver dans le texte.
 *
 * @param tM
 * @param longueur
 */
void detruireChaine(char *tM[], int longueur)
{
    int i = 0;
    for (i = 0; i < longueur; i++)
    {
        free(tM[i]);
        tM[i] = NULL;
    }
}

/**
 * Fonction qui est responsable de prendre la saisie depuis le stdin sans prompt.
 * La fin de saisie est réaliser grace a ctrl+d (EOF) 
 * La chaine de char produite est mise dans un variable qui renvoyer
 * 
 * @param fp 
 * @param size 
 * @return char* la cahine entree par l'utilisateur (le programme C a analyser)
 */
char *insererChaine(FILE *fp, size_t size)
{
    // La taille est étendue par l'entrée avec la valeur du provisoire
    char *str;
    int ch;
    size_t len = 0;
    // size est la taille initiale
    str = realloc(NULL, sizeof(*str) * size);
    while (EOF != (ch = fgetc(fp)) && ch != EOF)
    {
        str[len++] = ch;
        if (len == size)
        {
            str = realloc(str, sizeof(*str) * (size += 16));
        }
    }
    str[len++] = '\0';
    return realloc(str, sizeof(*str) * len);
}

/* Methode qui sert à trouver le nombre d'occurence d'un mot dans une chaine
 *  const char *textEntree = "  while()().while()\n while  while";
 *  const char *mot_a_trouver = "while";
 *  le nombre d'occurence dans cet exemple sera 4
 */
int compterNbrOccur(char *textEntree, const char *mot_a_trouver)
{
    char *p = textEntree;
    int trouve = 0;

    for (; p != NULL;)
    {
        p = strstr(p, mot_a_trouver);

        // Si le caractere n'est pas null et n'est pas alphabetic
        if ((p != NULL) && ((p == textEntree) || (!((unsigned char)p[-1] >= 65 && (unsigned char)p[-1] <= 90) &&
                                                  !((unsigned char)p[-1] >= 97 && (unsigned char)p[-1] <= 122))))
        {
            // on skip le mot trouvé puis on passe au caractere venat juste après
            // while()().while()\n while  while ==> ()().while()\n while  while
            p += strlen(mot_a_trouver);

            // Si le caractere n'est pas alphapetic
            if ((!((unsigned char)*p >= 65 && (unsigned char)*p <= 90) &&
                 !((unsigned char)*p >= 97 && (unsigned char)*p <= 122)))
            {
                trouve = trouve + 1;
            }
            else
            {
                // une sous-chaîne a été trouvée, mais aucun mot ne correspond, déplacez-vous d'un caractère et réessayez
                p += 1;
            }
        }
    }
    return trouve;
}

// Fonction qui implémente un substring sur C
char *substring(char *destination, const char *source, int debut, int n)
{
    // copier `n` caractères de la chaîne source à partir de
    // `debut` index dans la destination
    strncpy(destination, (source + debut), n);

    // return tla chaine destination
    return destination;
}

// Fonction pour trouver les postion de l'accolade fermantes
//Étant donné la position d'une parenthèse ouverte
//  dans un tableau de caractères, l'algorithme
//  utilise un compteur pour trouver
//  l'accolade fermante correspondante.
int trouverAccoFerm(const char *textEntree, int accoOuvrante, int *cpt)
{
    unsigned long accoFermante = accoOuvrante;
    int compteur = 1;
    while (compteur > 0 && accoFermante <= strlen(textEntree))
    {
        // printf("compteur accolade: %i\n", Compteur);
        char c = textEntree[++accoFermante];
        if (c == '{')
        {
            compteur++;
        }
        else if (c == '}')
        {
            compteur--;
        }
        // Lorsque le compteur atteint zéro,
        //  vous avez trouvé la parenthèse fermante correspondante.
    }
    *cpt += accoFermante;
    return accoFermante;
}

// Fonction qui permet d'extraire la chaine entre l'accolade ouvrante et fermante
//  "  while{afk{}lgmsla{asg;as,gd;}dsvadv{}}{dlfmasg}.while()\n while  while"
//  "{afk{}lgmsla{asg;as,gd;}dsvadv{}" ça retourne la chaine entre accolade sauf que ça retounre pas la derniere accolade, ça ne cree aucun probleme
char *parentheseCorresp(char *textEntree, int *cpt)
{
    int premiereAccol;
    int derniereAccol;
    int len;
    const char *p = textEntree;
    //   printf("Le texte que finMatching recoit est: %s\n", p);
    // Le caractere qu'on veut trouver
    char key[] = "{";
    // Trouver la position de la premiere accolade avec la methode strcspn
    premiereAccol = strcspn(p, key);

    //*cpt += premiereAccol;
    // printf("The first number in str is at position %d.\n", premiereAccol); //DEBUG
    derniereAccol = trouverAccoFerm(p, premiereAccol, cpt);
    // La taille de la chaine à extraire est :
    len = derniereAccol - premiereAccol;
    ;
    char *destination = malloc(sizeof(char) * len + 2);
    substring(destination, p, premiereAccol, len + 1);
    destination[len + 1] = '\0';
    return destination;
}

/*
 * Methode qui permet d'enlever les commentaires
 * et entre '...' et "..."
 */
char *supprimerComments(char *code)
{
    char *output = malloc(sizeof(char) * strlen(code));
    int index = 0;
    int i = 0;
    // store removed comment code in output
    while (code[i] != '\0')
    {
        // Pour supprimer une ligne de commentaire
        if (code[i] == '/' && code[i + 1] == '/')
        {
            while (code[i] != '\n')
            {
                i++;
            }
            // Pour supprimer multiples lignes de comments
        }
        else if (code[i] == '/' && code[i + 1] == '*')
        {
            i = i + 2;
            while (code[i] != '*' && code[i + 1] != '/')
            {
                i++;
            }
            i = i + 3;
        }
        else if (code[i] == '"')
        {
            i++;
            while (code[i] != '"')
            {
                i++;
            }
            i = i + 1;
        }
        else if (code[i] == '\'')
        {
            i++;
            while (code[i] != '\'')
            {
                i++;
            }
            i = i + 1;
        }
        else
        {
            // stocker le reste dans un tableau
            output[index++] = code[i++];
        }
    }
    output[index] = '\0';

    return output;
}

/**
 * Cette fonction vient parcourir le texte que l'utilisateur a rentré et crée une nouvelle
 * routine dans la liste chainee qui contient un tableau d'occurence pour chaque mot.
 * La case a l'indice 0 correspond au premier mot du fichier de mot, l'indice 1 au 2e, etc..
 *
 * @param texteEntree
 * @param tabMots
 * @param longeurTabMot
 * @return ListeChaine liste qui contient toutes les routines du texte entre et dans chacune des routine un tab d'occurence
 */
ListeChaine trouverOccurenceRoutine(char *texteEntree, char *tabMots[], int longeurTabMot)
{
    int compteur = 0;
    ListeChaine liste = creerListe();
    char *chaineRoutine = parentheseCorresp(texteEntree, &compteur);
    int cpt;
    Routine routine = NULL;
    while (strlen(chaineRoutine) > 0)
    {
        cpt = 0;
        ajouterRoutine(longeurTabMot, liste);

        while (cpt < longeurTabMot)
        {
            routine = retournerDerniereRoutine(liste);
            routine->occurence[cpt] = compterNbrOccur(chaineRoutine, tabMots[cpt]);
            ++cpt;
        }
        free(chaineRoutine);
        chaineRoutine = NULL;
        chaineRoutine = parentheseCorresp(texteEntree + compteur, &compteur);
    }
    free(chaineRoutine);
    chaineRoutine = NULL;
    return liste;
}

/**
 * Cette fonction affiche le nombre d'occurence de chaque mot pour chaque routine
 *
 * @param liste ListeChaine a afficher
 */
void afficherSomme(ListeChaine liste, int tailleTabMots, char *tabMots[])
{
    Routine r = liste->initiale;
    Routine aLiberer;
    while (r != NULL)
    {
        aLiberer = r;
        printf("{\n");
        for (int i = 0; i < tailleTabMots; i++)
        {
            printf("  %s : %i\n", tabMots[i], r->occurence[i]);
        }
        printf("}\n");
        printf("\n");
        r = r->suivante;
        free(aLiberer->occurence);
        aLiberer->occurence = NULL;
        free(aLiberer);
        aLiberer = NULL;
    }
}

/**
 * Procedure qui est responsable d'affcher le tabelau des sommes des occurences.
 * La premiere case du tab correspond au premier mot du fichier, la 2e au 2e mot etc...
 *
 * @param tabMots
 * @param occTotal
 * @param taille
 */
void afficherOcTotales(char *tabMots[], int *occTotal, int taille)
{
    for (int i = 0; i < taille; i++)
    {
        printf("%s : %i\n", tabMots[i], occTotal[i]);
    }
    printf("\n");
}

/**
 * Fonction qui permet de calculer le nombre d'occurence des mots a trouver
 * dans tout le programme, qu'il soit dans une routine ou pas.
 * 
 * @param textEntree 
 * @param tabMots 
 * @param tailleTabMots 
 * @return int* r qui est un tab d'occurence (1ere case => 1er mot, ...)
 */
int *calculerTotal(char *textEntree, char *tabMots[], int tailleTabMots)
{
    int *r = malloc(tailleTabMots * sizeof(int));
    int i = 0;
    while (i < tailleTabMots)
    {
        r[i] = compterNbrOccur(textEntree, tabMots[i]);
        ++i;
    }
    return r;
}

// ****************************************************************************************************************************
// ****************************************************************************************************************************

int main(int argc, char const *argv[])
{
    int estEOF = 0;
    int longBuffer = 0;
    int i = 0;
    int tailleTabMots = 0;
    // var qui stock le texte entre au stdin
    char *textEntree;
    // tableau de int qui contient la somme des occurences
    int *occurencesTotales;

    // Verifier si on a juste le nom du fichier.
    verifierArgument(argc);

    // Ouverture du fichier en mode lecture
    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        fprintf(stderr, "Le fichier n’est pas accessible.\n");
    }

    // Cration de notre tampon pour avec sa longueur connue
    longBuffer = compterChar(argv[1]);
    char *buffer = malloc(longBuffer * sizeof(char));
    do
    {
        buffer[i] = fgetc(file);
        if (feof(file))
        {
            estEOF = 1;
        }
        ++i;
    } while (!estEOF && i < longBuffer - 1);
    buffer[i] = 0;
    char *tabMots[longBuffer];

    tailleTabMots = analyserMots(buffer, tabMots, 0);

    // detruireChaine(tabMots, longBuffer);
    free(buffer);
    buffer = NULL;
    fclose(file);

    textEntree = insererChaine(stdin, 10);

    textEntree = supprimerComments(textEntree);

    occurencesTotales = calculerTotal(textEntree, tabMots, tailleTabMots);

    ListeChaine listeChaine = trouverOccurenceRoutine(textEntree, tabMots, tailleTabMots);
    //occurencesTotales = additionnerOccurence(listeChaine, tailleTabMots);

    // Afficher les occurences pour chaque routine
    afficherSomme(listeChaine, tailleTabMots, tabMots);

    // afficher les occurences totales
    afficherOcTotales(tabMots, occurencesTotales, tailleTabMots);

    // char *v = parentheseCorresp(textEntree);
    // printf("la chaine retounrnée est : %s", v);
    // free(v);
    //*******************************************************************
    //*******************************************************************

    for (int i = 0; i < tailleTabMots; i++)
    {
        free(tabMots[i]);
        tabMots[i] = NULL;
    }

    free(listeChaine);
    free(textEntree);
    free(occurencesTotales);
    occurencesTotales = NULL;

    return 0;
}
