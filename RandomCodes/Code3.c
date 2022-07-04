// /**
//  * C program to count occurrences of a word in a given string
//  */
// #include <stdio.h>
// #include <string.h>
// #define MAX_SIZE 100 // Maximum string size

// /* Function declaration */
// int countOccurrences(char * str, char * toSearch);

// int main()
// {
//     char str[MAX_SIZE];
//     char toSearch[MAX_SIZE];
//     int count;

//     /* Input string and word from user */
//     printf("Enter any string: ");
//     gets(str);
//     printf("Enter word to search occurrences: ");
//     gets(toSearch);

//     count = countOccurrences(str, toSearch);

//     printf("Total occurrences of '%s': %d", toSearch, count);

//     return 0;
// }

// /**
//  * Get, total number of occurrences of a word in a string
//  */
// int countOccurrences(char * str, char * toSearch)
// {
//     int i, j, found, count;
//     int stringLen, searchLen;

//     stringLen = strlen(str);      // length of string
//     searchLen = strlen(toSearch); // length of word to be searched

//     count = 0;

//     for(i=0; i <= stringLen-searchLen; i++)
//     {
//         /* Match word with string */
//         found = 1;
//         for(j=0; j<searchLen; j++)
//         {
//             if(str[i + j] != toSearch[j])
//             {
//                 found = 0;
//                 break;
//             }
//         }

//         if(found == 1)
//         {
//             count++;
//         }
//     }

//     return count;
// }

// Trouver le nombre d'occurence dans un text
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

int countWordOccurence(const char *textEntree, const char *mot_a_trouver)
{
    const char *p = textEntree;
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

int main()
{

    int count = 0;
    const char *textEntree = "  while()().while()\n while  while";
    const char *mot_a_trouver = "while";
    count = countWordOccurence(textEntree, mot_a_trouver);
    printf("nbr occurence %i", count);

    // const char *textEntree = "  while()().while()\n while";
    // const char *mot_a_trouver = "while";
    // const char *p = textEntree;
    // int trouve = 0;

    // //La raison pour laquelle on écrirait for(;;) au lieu de while(true)
    // //est que certains compilateurs émettent un avertissement pour l'expression booléenne constante dans while(true)
    // for (;p!=NULL;)
    // {
    //     p = strstr(p, mot_a_trouver);
    //   //  if (p == NULL)
    //     //    break;

    //     // Si le caractere n'est pas alphabetic
    //     if ((p == textEntree) || (!((unsigned char)p[-1] >= 65 && (unsigned char)p[-1] <= 90) && !((unsigned char)p[-1] >= 97 && (unsigned char)p[-1] <= 122)))
    //     {
    //         p += strlen(mot_a_trouver);

    //         // Si le caractere n'est pas alphapetic
    //         if ((!((unsigned char)*p >= 65 && (unsigned char)*p <= 90) && !((unsigned char)*p >= 97 && (unsigned char)*p <= 122)))
    //         {
    //             //printf("Match\n");
    //             trouve=trouve+1;

    //             // break; // Si, c'est trouvé on quitte
    //         } else{
    //             // substring was found, but no word match, move by 1 char and retry
    //             p += 1;
    //         }
    //     }

    // }

    // printf("\n%i", trouve);

    return 0;
}
