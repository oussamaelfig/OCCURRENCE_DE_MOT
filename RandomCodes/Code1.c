#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

int countAllBraces(const char *h, const char *n) {
    int count = 0;
    const char *tmp = h;
    while (tmp = strstr(tmp, n)) {
        //printf( "Position: %d\n", (int)(tmp-h)); //debugging
        ++count;
    }
    return count;
}

void KeyboardToScreen(const char *textEntree) {

    const char *p = textEntree;
    //char st[80];
    int br1 = 0, br2 = 0, j = 0, k = 0, t;
    //puts("Enter the code:");
    for (; p != NULL;) {
        j = 0;
        while (p[j] != '\0') {
            if (p[j] == '*') br1++;
            j++;
        }
        k += t = countAllBraces(p, "{");
        br2 += t;
        br2 -= countAllBraces(p, "}");

        p += 1;
    }
    if (br2 > 0)
        printf("ERROR: Block is not closed \n");
    printf("%d %d \n", br1, k);
    exit(0);
};

int main() {
    const char *textEntree = "  while(){{}}().while()\n{} while  while";
    KeyboardToScreen(textEntree);
    return 0;
}
