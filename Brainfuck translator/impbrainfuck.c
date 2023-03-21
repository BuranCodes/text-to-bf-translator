// Buran
// String to Brainfuck translator, improved
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void translation(const char *istr, const size_t strlen, FILE *fp)
{   
    char* ostr = NULL;
    ostr = (char*)malloc(2048); /* Just enough to create Brainfuck code within limits */

    char* beginloop = "[>"; // len 2
    char* endloop = "<-]>"; // len 4

    static int pos = 0; /* track current position, used as an index */
    static int prevchar = 0; /* keep track of previous vals for char */
    int dividend = 0, extra = 0, cell0 = 0, cell1 = 0;

    for (int i = 0; (size_t) i < strlen; i++) {

        if (prevchar == 0)
            dividend = (int) istr[i];
        else if (prevchar > (int) istr[i])
            dividend = prevchar - (int) istr[i];
        else if (prevchar < (int) istr[i])
            dividend = (int) istr[i] - prevchar;
        else
            dividend = prevchar;

        for (int j = 10; j > 1; j--) {
            
            if (dividend%j == 0) {
                cell0 = dividend/j;
                cell1 = j;
                extra = 0;
                break;
            } else if (dividend%j == 1) {
                cell0 = dividend/j;
                cell1 = j;
                extra = 1;
                break;
            }
        }

        if (prevchar == (int) istr[i]) {
            ostr[pos] = '>';
            pos++;
            ostr[pos] = '.';
            pos++;
            ostr[pos] = '<';
            pos++;
            ostr[pos] = '\0';
            continue;
        }

        for (int i = 0; i < cell0; i++) {
            ostr[pos] = '+';
            pos++;
        }

        for (int i = 0; i < 2; i++) { // beginloop
            ostr[pos] = beginloop[i];
            pos++;
        }

        if (prevchar < (int) istr[i]) {

        for (int i = 0; i < cell1; i++) {
            ostr[pos] = '+';
            pos++;
        }

        for (int i = 0; i < 4; i++) { // endloop
            ostr[pos] = endloop[i];
            pos++;
        }

        if (extra == 1) {
            ostr[pos] = '+';
            pos++;
        }
            ostr[pos] = '.';
            pos++;
            ostr[pos] = '<';
            pos++;
            ostr[pos] = '\0';
        }

        else if (prevchar > (int) istr[i]) {

            for (int i = 0; i < cell1; i++) {
                ostr[pos] = '-';
                pos++;
            }

            for (int i = 0; i < 4; i++) { // endloop
                ostr[pos] = endloop[i];
                pos++;
            }

            if (extra == 1) {
                ostr[pos] = '-';
                pos++;
            }

            ostr[pos] = '.';
            pos++;
            ostr[pos] = '<';
            pos++;
            ostr[pos] = '\0';
        }
        

        prevchar = (int) istr[i];

    }
    fprintf(fp, "%s", ostr);
    free(ostr);
}

int main(void)
{
    FILE *fp;
    fp = fopen("output.bf", "w");

    char* istr = NULL;
    istr = (char*)malloc(1024); /* 1023 characters with one NUL termination maximum */

    puts("Enter a word or a sentence to translate into Brainfuck code!");
    
    scanf("%[^\n]", istr);
    printf("Input string: %s\n", istr);

    translation(istr, strlen(istr), fp);

    puts("The string has been translated into Brainfuck code in output.bf\nThe file should be where you ran the executable.");

    free(istr);
    fclose(fp);
    return 0;
}