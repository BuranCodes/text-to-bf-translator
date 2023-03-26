// Buran
// String to Brainfuck translator, improved
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int translation (const char* istr)
{
    FILE *fp;
    if ((fp = fopen("test.bf", "w")) == NULL)
        goto ERROR;

    char *ostr = NULL;
    if ((ostr = (char*) malloc (10256)) == NULL)
        goto ERROR;

    ostr[0] = '<';
    unsigned int ipos = 0, opos = 0;
    char prevchar = istr[0];
    // int cell0, cell1, extra;

    while(istr[ipos] != '\0') {
        // check for same char and input char

        if (prevchar == istr[ipos] && ostr[opos] == '.') { // print again
            opos++;
            ostr[opos] = '.';
            ipos++;
            continue;
        } else if (prevchar == istr[ipos] && ostr[opos] == '<') {
            opos++;
            ostr[opos] = '>';
            opos++;
            ostr[opos]= '.';
            ipos++;
            continue;
        }

        // check distance between previous char and incoming char

        if (prevchar-istr[ipos] < 13 && prevchar-istr[ipos] > 0) {
            if (ostr[opos] == '<') {
                opos++;
                ostr[opos] = '>';
            }
            for (char i = 0; i < prevchar-istr[ipos]; i++) {
                opos++;
                ostr[opos] = '-';
            }
            opos++;
            ostr[opos] = '.';
            prevchar = istr[ipos];
            ipos++;
            continue;
        } else if (istr[ipos]-prevchar < 13 && istr[ipos]-prevchar > 0) {
            if (ostr[opos] == '<') {
                opos++;
                ostr[opos] = '>';
            }
            for (char i = 0; i < istr[ipos]-prevchar; i++) {
                opos++;
                ostr[opos] = '+';
            }
            opos++;
            ostr[opos] = '.';
            prevchar = istr[ipos];
            ipos++;
            continue;
        }
        /* 
        // calculation
        int check;
        for (int i = 10; i > 1; i--) { // first run
            if (prevchar > (int) istr[ipos] && (prevchar-(int) istr[ipos])%i == 0) {
                cell0 = (prevchar-(int) istr[ipos])/i;
                cell1 = i;
                extra = 0;
                break;
            } else if (prevchar < (int) istr[ipos] && (prevchar-(int) istr[ipos])%i == 0) {
                cell0 = ((int) istr[ipos]-prevchar)/i;
                cell1 = i;
                extra = 0;
                break;
            }
            else if (i == 2) {
                check = 1;
            }
        }
        if (check == 1) { // second run if true
            for (int j = 10; j > 1; j--) {
                if (prevchar > (int) istr[ipos] && (prevchar-(int) istr[ipos])%j == 1) {
                    cell0 = (prevchar-(int) istr[ipos])/j;
                    cell1 = j;
                    extra = 1;
                    break;
                } else if (prevchar < (int) istr[ipos] && (prevchar-(int) istr[ipos])%j == 0) {
                    cell0 = ((int) istr[ipos]-prevchar)/j;
                    cell1 = j;
                    extra = 0;
                    break;
                }
            }
        }
        // writing to output string
        // TODO: fix 
        
        opos++;
        ostr[opos] = '<';
        for (int i = 0; i < cell0; i++) {
            opos++;
            ostr[opos] = '+';
        }
        opos++;
        ostr[opos] = '[';
        opos++;
        ostr[opos] = '>';
        
        if (prevchar > (int) istr[ipos]) {
            for (int i = 0  ; i < cell1; i++) {
                opos++;
                ostr[opos] = '-';
            }
        } */
        

    ipos++;
    }
    opos++;
    ostr[opos] = '\0';

    fprintf(fp, "%s", ostr);
    fclose(fp);
    free(ostr);
    return 0;

    // will never fall through unless called by error checking routine

    ERROR:
    fprintf(stderr, "Memory error! Not enough memory...\n");
    exit(1); 
}


int main(void)
{
    char* istr = NULL;
    istr = (char*)malloc(1024); /* 1023 characters with one NUL termination maximum */

    puts("Enter a word or a sentence to translate into Brainfuck code!");
    
    scanf("%[^\n]", istr);
    printf("Input string: %s\n", istr);

    translation(istr);

    puts("The string has been translated into Brainfuck code in output.bf\nThe file should be where you ran the executable.");

    free(istr);
    return 0;
}