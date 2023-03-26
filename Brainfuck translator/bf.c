// Buran
// String to Brainfuck translator, improved
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    FILE_ERR = 1,
    MEMERR
};

int translation (const char* istr)
{
    FILE *fp;
    if ((fp = fopen("output.bf", "w")) == NULL) {
        fputs("Cannot open/write to file\n", stderr);
        exit(FILE_ERR);
    }

    char *ostr = NULL;
    if ((ostr = (char*) malloc (10256)) == NULL) {
        fputs("Failed to allocate memory for output string\n", stderr);
        exit(MEMERR);
    }

    unsigned int ipos = 0, opos = 0;
    char prevchar = 0;
    unsigned char cell0, cell1, extra;

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
        // fall through if none works above
        // calculation
        int check = 0;
        for (char i = 10; i > 1; i--) { // first run
            if (prevchar > istr[ipos] && (prevchar-istr[ipos])%i == 0) {
                cell0 = (prevchar-istr[ipos])/i;
                cell1 = i;
                extra = 0;
                break;
            } else if (prevchar < istr[ipos] && (istr[ipos]-prevchar)%i == 0) {
                cell0 = (istr[ipos]-prevchar)/i;
                cell1 = i;
                extra = 0;
                break;
            } else if (i == 2) 
                check = 1;
        }
        if (check == 1) { // second run if true
            for (char j = 10; j > 1; j--) {
                if (prevchar > istr[ipos] && (prevchar-istr[ipos])%j == 1) {
                    cell0 = (prevchar-istr[ipos])/j;
                    cell1 = j;
                    extra = 1;
                    break;
                } else if (prevchar < istr[ipos] && (istr[ipos]-prevchar)%j == 1) {
                    cell0 = (istr[ipos]-prevchar)/j;
                    cell1 = j;
                    extra = 1;
                    break;
                }
            }
        }
        // writing to output string
        
        if (ostr[opos] != '<' && opos != 0) { // return to cell 0
            opos++;
            ostr[opos] = '<';
        }
        for (int i = 0; i < cell0; i++) {
            if (opos == 0) {
                ostr[opos] = '+';
                i++;
                goto SKIP;
            }
            SKIP:
            opos++;
            ostr[opos] = '+';
        }
        opos++;
        ostr[opos] = '[';
        opos++;
        ostr[opos] = '>';
        
        if (prevchar > istr[ipos]) { 
            for (int i = 0; i < cell1; i++) {
                opos++;
                ostr[opos] = '-';
            }
        } else if (prevchar < istr[ipos]) {
            for (int i = 0; i < cell1; i++) {
                opos++;
                ostr[opos] = '+';
            }
        }
        opos++;
        ostr[opos] = '<';
        opos++;
        ostr[opos] = '-';
        opos++;
        ostr[opos] = ']';
        opos++;
        ostr[opos] = '>';
        if (extra == 1) { // for prime numbers
            if (prevchar > istr[ipos]) {
                opos++;
                ostr[opos] = '-';
            } else if (prevchar < istr[ipos]) {
                opos++;
                ostr[opos] = '+';
            }
        }
        opos++;
        ostr[opos] = '.';
        prevchar = istr[ipos];
        ipos++;
    }
    opos++;
    ostr[opos] = '\0';

    fprintf(fp, "%s", ostr);
    fclose(fp);
    free(ostr);
    return 0;
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