#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
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
    while (i < longBuffer - 1 || buffer[i] == 0)
    {
        if (estLettre(buffer[i]))
        {
            tM[indice] = malloc(longBuffer * sizeof(char));
            tM[indice][j] = buffer[i];
            // printf("succes!\n");
            // printf("%i\n", indice);
            while (i < longBuffer - 1 && !charEstValide(buffer[i]) && !estEspaceBlanc(buffer[i]))
            {
                // printf("%c\n", tM[indice][j]);
                ++i;
                ++j;
                tM[indice][j] = buffer[i];
            }
            tM[indice][j] = 0;
        }
        else if (!estEspaceBlanc(buffer[i]) && buffer[i] != 0)
        {
            fprintf(stderr, "Le fichier contient autre chose que des mots valides séparés par des blancs\n");
            exit(-1);
        }
        j = 0;
        ++i;
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

// Methode qui sert à demander l'utilisateur d'entrer le texte puis elle store
// le nombre de caractere dans la variable globale TAILLETexte
char *inputString(FILE *fp, size_t size)
{
    // The size is extended by the input with the value of the provisional
    char *str;
    int ch;
    size_t len = 0;
    str = realloc(NULL, sizeof(*str) * size); // size is start size
    if (!str)
        return str;
    while (EOF != (ch = fgetc(fp)) && ch != EOF)
    {
        str[len++] = ch;
        if (len == size)
        {
            str = realloc(str, sizeof(*str) * (size += 16));
            if (!str)
                return str;
        }
    }
    str[len++] = '\0';
    // printf("\n\n\nLa taille du texte entré est : %i", TAILLETXT);
    return realloc(str, sizeof(*str) * len);
}

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

    char *tabMots[longBuffer];

    tailleTabMots = analyserMots(buffer, tabMots, 0);

    // printf("Buffer: %s\n", buffer);
    // printf("%s\n", tabMots[1]);
    // detruireChaine(tabMots, longBuffer);
    free(buffer);
    buffer = NULL;

    fclose(file);

    // ******************************************************************
    // Cette partie dépend de la méthode (inputString)
    char *m;

    printf("input string : ");
    m = inputString(stdin, 10);
    // printf("%s\n", m);
    // Taille du texte entré par l'utilisateur : exemple:
    // Allo\nBonjour\0       ==>     13
    printf("\n\n\nla taille est : %i", strlen(m));

    free(m);

    //*******************************************************************

    return 0;
}
