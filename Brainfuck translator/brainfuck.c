// Buran
// String to Brainfuck translator
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void writeto_file(const char* ostr)
{
        /* TODO */
        /* Write to text file after receiving output string */
}

char* translation(int cell0, int cell1, int extra)
{       char* ostr = NULL;
        ostr = (char*)malloc(255); /* Just enough to create Brainfuck code within limits */
        if (extra == 1) {
                printf("WIP\n");
        } else {
                printf("WIP\n");
        }
        /* TODO */
        /* Build a new string with for loops, return to writeto_file when done */
        free(ostr);
}

int calculation(char c)
{
	int dividend = (int) c;
	int result, extra;
	for (int i = 10; i > 1; i--) {
		if (dividend%i == 0) {
			printf("Not a prime number: %d\n", dividend);
			result = dividend/i;
			translation(i, result, extra);
			return 0;	
		}
	}	



	/* Second try if modulo result for range 10 to 2 does not equal 0 */
	/* It might be that the received dividend is a prime number, e.g. 97 for 'a' */
	
	/* TODO Checks missing! If first for loop passes with no problem,
	 * the loop below needs to be not ran unless a criteria is met. */
	
		
	for (int i = 10; i > 1; i--) {
		if (dividend%i == 1) {
			printf("A prime number: %d\n", dividend);
			extra = 1;
			result = (dividend-1)/i;
			translation(i, result, extra);
			return 0;

		}
	}
}	

void char_parser(const char* istr, const size_t strlen) 
{
	for (int i = 0; i < strlen; i++)
		calculation(istr[i]);
	/* Here, we should be able to call function for each iterator...
	   to work on character argument that has been converted into int. */
}

int main(void)
{
	char* istr = NULL;
	istr = (char*)malloc(255); /* 254 characters with one NUL termination maximum */
	puts("Enter a word or a sentence to translate into Brainfuck code!");
	
	scanf("%[^\n]", istr);
	printf("Input string: %s\n", istr);
	

	char_parser(istr, strlen(istr));
	
	free(istr);
	return 0;
}
