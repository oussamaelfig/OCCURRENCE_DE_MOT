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

int estLettre(char c)
{
    return (c & 0x00DF) >= 'A' && (c & 0x00DF) <= 'Z';
}

int estChiffre(char c)
{
    return c >= '0' && c <= '9';
}

int estEspaceBlanc(char c)
{
    return c == ' ' || c == '\t' || c == '\n';
}

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
        fprintf(stderr, "Le fichier contient autre chose que des mots valides séparés par des blancs123\n");
        exit(-1);
    }
    return estValide;
}

/*
    Fonction qui analyse une string composée d'un ou plusieurs mots valide.
*/
int analyserMots(char *buffer, char *tM[], int indice)
{
    int i = 0;
    int j = 0;
    int longBuffer = strlen(buffer);
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
    if(indice == 0)
    {
        ++indice;
    }
    return indice;
}

void verifierArgument(int argc)
{
    if (argc != 2)
    {
        fprintf(stderr, "Il n’y a pas le bon nombre d’arguments sur la ligne de commande.\n");
        exit(-1);
    }
}

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

void detruireChaine(char *tM[], int longueur)
{
    int i = 0;
    for (i = 0; i < longueur; i++)
    {
        free(tM[i]);
        tM[i] = NULL;
    }
}

// *************************************************************************************************************************
// *************************************************************************************************************************
// Methode qui sert à demander l'utilisateur d'entrer le texte puis elle store
// le nombre de caractere dans la variable globale TAILLETexte
char *inputString(FILE *fp, size_t size)
{
    // La taille est étendue par l'entrée avec la valeur du provisoire
    char *str;
    int ch;
    size_t len = 0;
    str = realloc(NULL, sizeof(*str) * size); // size is start size
    while (EOF != (ch = fgetc(fp)) && ch != EOF)
    {
        str[len++] = ch;
        if (len == size)
        {
            str = realloc(str, sizeof(*str) * (size += 16));

        }
    }
    str[len++] = '\0';
    // printf("\n\n\nLa taille du texte entré est : %i", TAILLETXT);
    return realloc(str, sizeof(*str) * len);
}

/* Methode qui sert à trouver le nombre d'occurence d'un mot dans une chaine
 *  const char *textEntree = "  while()().while()\n while  while";
 *  const char *mot_a_trouver = "while";
 *  le nombre d'occurence dans cet exemple sera 4
 */
int countWordOccurence(const char *textEntree, const char *mot_a_trouver)
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


//Fonction pour trouver les postion de l'accolade fermantes
//Étant donné la position d'une parenthèse ouverte
// dans un tableau de caractères, l'algorithme
// utilise un compteur pour trouver
// l'accolade fermante correspondante.
int trouverAccoFerm(const char *textEntree, int openPos, int *cpt)
{
    int closePos = openPos;
    int Compteur = 1;
    while (Compteur > 0 && closePos <= strlen(textEntree))
    {
        //printf("compteur accolade: %i\n", Compteur);
        char c = textEntree[++closePos];
        if (c == '{')
        {
            Compteur++;
        }
        else if (c == '}')
        {
            Compteur--;
        }
        // Lorsque le compteur atteint zéro,
        //  vous avez trouvé la parenthèse fermante correspondante.
    }
    *cpt += closePos;
    return closePos;
}



//Fonction qui permet d'extraire la chaine entre l'accolade ouvrante et fermante
// "  while{afk{}lgmsla{asg;as,gd;}dsvadv{}}{dlfmasg}.while()\n while  while"
// "{afk{}lgmsla{asg;as,gd;}dsvadv{}" ça retourne la chaine entre accolade sauf que ça retounre pas la derniere accolade, ça ne cree aucun probleme
char *findMatchingBraces(char *textEntree, int *cpt)
{
    int premiereAccol;
    int derniereAccol;
    int len;
    const char *p = textEntree;
 //   printf("Le texte que finMatching recoit est: %s\n", p);
    // Le caractere qu'on veut trouver
    char key[] = "{";
    //Trouver la position de la premiere accolade avec la methode strcspn
    premiereAccol = strcspn(p, key);
    
    //*cpt += premiereAccol;
    // printf("The first number in str is at position %d.\n", premiereAccol); //DEBUG
    derniereAccol = trouverAccoFerm(p, premiereAccol, cpt);
    // La taille de la chaine à extraire est :
    len = derniereAccol - premiereAccol;
    ;
    char *destination = malloc(sizeof(char) * len + 2 );
//    printf("Le cpt: %i, p : %s\n", *cpt, p);
    printf("test accolade 2\n");
    substring(destination, p, premiereAccol, len + 1);
    printf("test accolade 3\n");
    destination[len + 1] = '\0';
    printf("test acollade 4\n");
    return destination;
}



ListeChaine trouverOccurenceRoutine( char * texteEntree, char *tabMots[], int longeurTabMot)
{
    int compteur = 0;
    ListeChaine liste = creerListe();
    //printf("test1\n");

    char *chaineRoutine = findMatchingBraces(texteEntree, &compteur);
    //printf("test2\n");

    int cpt;
    int somme = 0;
    //int longueur = strcspn(texteEntree, "{");
    Routine routine = NULL;
    while (strlen(chaineRoutine) > 0)
    {
        printf("test3\n");
        printf("texteEntree + cpt :%i, texteentree max: %i\n",texteEntree + compteur,texteEntree + strlen(texteEntree));
	// printf("Chaine sortie: %s\n", chaineRoutine);
        cpt = 0;
        //longueur += strlen(chaineRoutine);
        ajouterRoutine(longeurTabMot, liste);

        while (cpt < longeurTabMot)
        {
            routine = retournerDerniereRoutine(liste);
            routine->occurence[cpt] = countWordOccurence(chaineRoutine, tabMots[cpt]);
            ++cpt;
        }
        //printf("Actuel : %i , Max :%i\n", longueur + texteEntree, texteEntree + strlen(texteEntree));
        free(chaineRoutine);
        chaineRoutine = NULL;
        chaineRoutine = findMatchingBraces(texteEntree + compteur, &compteur);
        //printf("succes\n");
	printf("texteEntree + cpt :%i, texteentree max: %i\n",texteEntree + compteur,texteEntree + strlen(texteEntree));
    }
    free(chaineRoutine);
    chaineRoutine = NULL;
    return liste;
}

// ****************************************************************************************************************************
// ****************************************************************************************************************************

int main(int argc, char const *argv[])
{

    // printf("test1\n");
    int estEOF = 0;
    int longBuffer = 0;
    int i = 0;
    int tailleTabMots = 0;

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

    // printf("Buffer: %s\n", buffer);
    // printf("%s\n", tabMots[1]);
    // detruireChaine(tabMots, longBuffer);
    free(buffer);
    buffer = NULL;
    fclose(file);



    // ******************************************************************
    // ******************************************************************
    // Cette partie dépend de la méthode (inputString)
    // Sert à tester la methode inputString
    char *m;
    int tailleText;

    //printf("input string : ");
    m = inputString(stdin, 10);
    //printf("%s\n", m);
    // Taille du texte entré par l'utilisateur : exemple:
    // Allo\nBonjour\0(CTRL D)       ==>     13     NB: je compte pas le (CTRL D)
    tailleText = strlen(m) - 1;
    //printf("\n\n\nla taille est : %i", tailleText);

    //free(m);

    // Cette partie dépend de la methode (countWordOccurence)
    // Sert à tester la methode countWordOccurence

    int count = 0;
    //const char *textEntree = "  while()().while()\n while  while";
    //const char *mot_a_trouver = "while";
    //count = countWordOccurence(textEntree, mot_a_trouver);
    //printf("nbr occurence %i", count);




    // Cette partie dépend de la methode (findMatchingBraces)
    // Sert à tester la methode findMatchingBraces

    char *textEntree = "  while{afk{}lgmsla{asg;as,gd;}dsvadv{}}{dlfmasg}.while()\n while  while";
    printf("test\n");
    //char *t;
    //strcpy(t, textEntree);
    // test de la fonction trouver occurence routine
    ListeChaine listeChaine = trouverOccurenceRoutine(m, tabMots, tailleTabMots);
    
    Routine r = listeChaine->initiale;
    Routine aLiberer;
    while (r != NULL)
    {
        aLiberer = r;
	printf("{\n");
        for (size_t i = 0; i < tailleTabMots; i++)
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

    //char *v = findMatchingBraces(textEntree);
   // printf("la chaine retounrnée est : %s", v);
   // free(v);
    //*******************************************************************
    //*******************************************************************
    

    for (size_t i = 0; i < tailleTabMots; i++)
    {
        free(tabMots[i]);
        tabMots[i] = NULL;
    }

    free(listeChaine);
    free(m);
    
    return 0;
}
