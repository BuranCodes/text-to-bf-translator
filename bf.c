/*
 * Buran
 * String to Brainfuck translator, improved 2
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define EXPANSION_FACTOR 1.5

typedef unsigned char __uint8;

int translation (const char *istr)
{
    int ipos = 0;
    /* they never go above 255, we can keep it that way */
    __uint8 prevchar = 0;
    __uint8 cell0, cell1, extra;
    __uint8 start = 1;
    /* 
     * This algorithm checks for same characters, different characters where
     * the distance between is < 13 and dividing the character number in
     * order to get cell0 and cell1 values as well extra if it's a prime
     * number. Noteworthy: decrementation included, thus reducing output size!
     * For example: the prompt "Hello, world!" for this algorithm produces 191
     * characters. When it comes to my first and second algorithm:
     * it would take for them the same prompt 434 and 245 characters,
     * respectively.
     */
    while(istr[ipos] != '\0') {
        int check = 0;
        // check for same char and input char
        if (prevchar == istr[ipos]) {
            // print again
            putchar('.');
            ipos++;
            continue;
        }
        // check distance between previous char and incoming char
        if (prevchar - istr[ipos] < 13 && prevchar - istr[ipos] > 0) {
            for (__uint8 i = 0; i < prevchar - istr[ipos]; i++) {
                putchar('-');
            }
            putchar('.');
            prevchar = istr[ipos];
            ipos++;
            continue;
        } else if (istr[ipos] - prevchar < 13 && istr[ipos] - prevchar > 0) {
            for (__uint8 i = 0; i < istr[ipos] - prevchar; i++) {
                putchar('+');
            }
            putchar('.');
            prevchar = istr[ipos];
            ipos++;
            continue;
        }
        /* 
        * fall through if none works above
        * calculation 
        */
        for (__uint8 i = 10; i > 1; i--) { // composite numbers
            if (prevchar > istr[ipos] && (prevchar - istr[ipos]) % i == 0) {
                cell0 = (prevchar - istr[ipos]) / i;
                cell1 = i;
                extra = 0;
                break;
            } else if (prevchar < istr[ipos] && (istr[ipos]-prevchar) % i == 0) {
                cell0 = (istr[ipos] - prevchar) / i;
                cell1 = i;
                extra = 0;
                break;
            } else if (i == 2) 
                check = 1;
        }
        if (check == 1) { // prime numbers
            for (__uint8 j = 10; j > 1; j--) {
                if (prevchar > istr[ipos] && (prevchar - istr[ipos]) % j == 1) {
                    cell0 = (prevchar - istr[ipos]) / j;
                    cell1 = j;
                    extra = 1;
                    break;
                } else if (prevchar < istr[ipos] && (istr[ipos] - prevchar) % j == 1) {
                    cell0 = (istr[ipos] - prevchar) / j;
                    cell1 = j;
                    extra = 1;
                    break;
                }
            }
        }
        // writing to output string
        if (start != 1) {
            // return to cell 0
            putchar('<');
        }
        for (__uint8 i = 0; i < cell0; i++) {
            putchar('+');
        }
        fputs("[>", stdout);
        if (prevchar > istr[ipos]) { 
            for (int i = 0; i < cell1; i++) {
                putchar('-');
            }
        } else if (prevchar < istr[ipos]) {
            for (int i = 0; i < cell1; i++) {
                putchar('+');
            }
        }
        fputs("<-]>", stdout);
        if (extra == 1) { // for prime numbers
            if (prevchar > istr[ipos]) {
                putchar('-');
            } else if (prevchar < istr[ipos]) {                
                putchar('+');
            }
        }
        putchar('.');
        start = 0;
        prevchar = istr[ipos];
        ipos++;
    }
    return EXIT_SUCCESS;
}


int main(void)
{
    fputs("Enter any text:\n", stdout);
    char tmpc[2] = "0\0";
    char *input = NULL;
    int strsize = 8; /* starting size */
    int tmp = EOF;

    if ((input =(char *)calloc(strsize, sizeof(char))) == NULL) {
        fputs("Cannot create input string.", stderr);
        exit(EXIT_FAILURE);
    }
    while (tmp) {
        tmp = fgetc(stdin);

        if (tmp == EOF || tmp == '\n')
            tmp = 0;

        if (strlen(input) == strsize-1) {
            strsize *= EXPANSION_FACTOR;
            if ((input = (char *)realloc(input, strsize)) == NULL) {
                fputs("Reallocation failed.", stderr);
                exit(EXIT_FAILURE);
            }
        }
        tmpc[0] = (char)tmp;
        strcat(input, tmpc);
    }
    translation(input);
    free(input);
    fputs("\nThe text has been translated into Brainfuck code.\n", stdout);
    return EXIT_SUCCESS;
}