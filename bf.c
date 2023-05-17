/*
 * Buran
 * String to Brainfuck translator, improved 2
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int translation (const char *istr)
{
    FILE *fp;
    // change omemsize if you want to
    const unsigned int omemsize = 10256;
    // they never go above 255, we can keep it that way
    unsigned int ipos = 0;
    unsigned char prevchar = 0;
    unsigned char cell0, cell1, extra;
    char *ostr = NULL;

    if ((fp = fopen("output.bf", "w")) == NULL) {
        fputs("Cannot open/write to file. Make sure the executable has the perm"
        "issions to do so.\n", stderr);
        exit(EXIT_FAILURE);
    }

    if ((ostr = (char *)calloc(omemsize, sizeof(char))) == NULL) {
        // 10255 characters with one NUL termination maximum
        fputs("Failed to allocate memory for output string.\n", stderr);
        exit(EXIT_FAILURE);
    }


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
        if (prevchar == istr[ipos] && ostr[(const int)strlen(ostr)-1] == '.') {
            // print again
            strcat(ostr, ".");
            ipos++;
            continue;
        } else if (prevchar == istr[ipos] && ostr[(const int)strlen(ostr)-1] == '<') {
            strcat(ostr, ">.");
            ipos++;
            continue;
        }
        // check distance between previous char and incoming char
        if (prevchar - istr[ipos] < 13 && prevchar - istr[ipos] > 0) {
            for (char i = 0; i < prevchar - istr[ipos]; i++) {
                strcat(ostr, "-");
            }
            strcat(ostr, ".");
            prevchar = istr[ipos];
            ipos++;
            continue;
        } else if (istr[ipos] - prevchar < 13 && istr[ipos] - prevchar > 0) {
            for (char i = 0; i < istr[ipos] - prevchar; i++) {
                strcat(ostr, "+");
            }
            strcat(ostr, ".");
            prevchar = istr[ipos];
            ipos++;
            continue;
        }
        /* 
         * fall through if none works above
         * calculation 
         */
        for (char i = 10; i > 1; i--) { // composite numbers
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
            for (char j = 10; j > 1; j--) {
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
        if (ostr[(const int)strlen(ostr)-1] != '<' && (int)ostr[0] != 0) {
            // return to cell 0
            strcat(ostr, "<");
        }
        for (char i = 0; i < cell0; i++) {
            if (strlen(ostr) == 0) {
                strcat(ostr, "+");
                i++;
            }
            strcat(ostr, "+");
        }
        
        strcat(ostr, "[");
        
        strcat(ostr, ">");
        
        if (prevchar > istr[ipos]) { 
            for (int i = 0; i < cell1; i++) {
                
                strcat(ostr, "-");
            }
        } else if (prevchar < istr[ipos]) {
            for (int i = 0; i < cell1; i++) {
                
                strcat(ostr, "+");
            }
        }
        
        strcat(ostr, "<");
        strcat(ostr, "-");
        strcat(ostr, "]");
        strcat(ostr, ">");
        if (extra == 1) { // for prime numbers
            if (prevchar > istr[ipos]) {
                
                strcat(ostr, "-");
            } else if (prevchar < istr[ipos]) {
                
                strcat(ostr, "+");
            }
        }
        
        strcat(ostr, ".");
        prevchar = istr[ipos];
        ipos++;
    }
    
    fprintf(fp, "%s", ostr);
    fclose(fp);
    return EXIT_SUCCESS;
}


int main(void)
{
    // change imemsize if you want to
    const unsigned int imemsize = 1024; 
    char *istr = NULL;
    if ((istr = (char *)calloc(imemsize, sizeof(char))) == NULL) { /* 1023 characters with one NUL termination maximum */
        fputs("Failed to allocate memory for input string.\n", stderr);
        exit(EXIT_FAILURE);
    }
    fputs("Enter a word or a sentence to translate into Brainfuck code!\n", stdout);
    scanf("%[^\n]", istr);
    fprintf(stdout, "Input string: %s\n", istr);

    translation(istr);

    fputs("The string has been translated into Brainfuck code in output.bf\nThe file should be where you ran the executable.", stdout);
    return EXIT_SUCCESS;
}