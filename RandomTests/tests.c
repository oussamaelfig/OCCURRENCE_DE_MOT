#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

char input [1024];
char words[16];

int main(int argc, char const *argv[])
{
    printf("Enter text. Press enter on blank line to exit.\n");
    while(scanf("%15s", words) != EOF){
        printf("%s\n", words);
    }
    //while (1 == scanf("%[^\n]%*c", input)) { /* process input */ }

    return 0;
}
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
