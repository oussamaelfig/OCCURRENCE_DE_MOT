#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

// Taille du texte entré par l'utilisateur : exemple:
// Allo\nBonjour\0       ==>     13
int TAILLETXT;

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
    TAILLETXT = len;
    printf("\n\n\nLa taille du texte entré est : %i", TAILLETXT);
    return realloc(str, sizeof(*str) * len);
}

int main(void)
{
    char *m;

    printf("input string : ");
    m = inputString(stdin, 10);
    // printf("%s\n", m);
    printf("\n\n\nla taille est : %i", strlen(m)-1);

    free(m);
    return 0;
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <math.h>
// #include <stdbool.h>

// char input [1024];
// char words[16];

// int main(int argc, char const *argv[])
// {
//     printf("Enter text. Press enter on blank line to exit.\n");
//     while(scanf("%15s", words) != EOF){
//         printf("%s\n", words);
//     }
//     //while (1 == scanf("%[^\n]%*c", input)) { /* process input */ }

//     return 0;
// }
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <math.h>
// #include <stdbool.h>
// int main(int argc, char const *argv[])
// {
//     char octets_array[100][128];
//     for (int line_counter = 0; line_counter < 100; line_counter++)
//     {
//         printf("Please enter octet: ");
//         char ret_code = scanf("%s", octets_array[line_counter]);
//         //char end= 0x04;
//         if (ret_code == 4)
//             puts("Ctrl+D or other end of file");
//         else
//             puts("Thank you for the input");
//     }
//     return 0;
// }
