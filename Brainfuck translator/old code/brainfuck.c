// Buran
// String to Brainfuck translator
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void writeto_file(const char* ostr, FILE *fp)
{
    fprintf(fp, "%s", ostr);
    fputs("[-]<", fp);
}

void translation(int cell0, int cell1, int extra, FILE *fp)
{   char* ostr = NULL;
    ostr = (char*)malloc(255); /* Just enough to create Brainfuck code within limits */
    char* beginloop = "[>"; // len 2
    char* endloop = "<-]>"; // len 4
    int pos = 0; /* track current position, used as an index */
    
    for (int i = 0; i < cell0; i++) {
        ostr[pos] = '+';
        pos++;
    }

    for (int i = 0; i < 2; i++) { // beginloop
        ostr[pos] = beginloop[i];
        pos++;
    }

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
    ostr[pos] = '\0';
        
    writeto_file((const char*) ostr, fp);
    free(ostr);
}

void calculation(char c, FILE *fp)
{
    int dividend = (int) c;
    int result, extra, check;
    extra = 0;
    check = 1;

    for (int i = 10; i > 1; i--) {
        if (dividend%i == 0) {
            check = 0;
            result = dividend/i;
            translation(i, result, extra, fp); 
            break;
        }
    }   

    /* Second try if modulo result for range 10 to 2 does not equal 0 */
    /* It might be that the received dividend is a prime number, e.g. 97 for 'a' */

    if (check == 1) {
        for (int i = 10; i > 1; i--) {
            if (dividend%i == 1) {
                //printf("A prime number: %d\n", dividend);
                extra = 1;
                result = (dividend-1)/i;
                translation(i, result, extra, fp);
                break;
            }
        }
    }
}   

void char_parser(const char* istr, const size_t strlen, FILE *fp) 
{
    for (int i = 0; (size_t) i < strlen; i++)
        calculation(istr[i], fp);
    /* Call function every iteration */
}

int main(void)
{
    FILE *fp;
    fp = fopen("output.bf", "w");
    char* istr = NULL;
    istr = (char*)malloc(255); /* 254 characters with one NUL termination maximum */
    puts("Enter a word or a sentence to translate into Brainfuck code!");
    
    scanf("%[^\n]", istr);
    printf("Input string: %s\n", istr);

    char_parser(istr, strlen(istr), fp);
    puts("The string has been translated into Brainfuck code in output.bf\nThe file should be where you ran the executable.");
    free(istr);
    fclose(fp);
    return 0;
}


