// Buran
// String to Brainfuck translator
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void calculation(char c)
{
	int dividend = (int) c;
	int result, extra;
	for (int i = 10; i > 1; i--) {
		if (dividend%i == 0) {
			puts("Not a prime number");
			result = dividend/i;
			translation(i, result, extra);
			break;	
		}
	}	



	/* Second try if modulo result for range 10 to 2 does not equal 0 */
	/* It might be that the received dividend is a prime number, e.g. 97 for 'a' */
	
	
	for (int i = 10; i > 1; i--) {
		if (dividend%i == 1) {
			puts("A prime number");
			extra = 1;
			result = (dividend-1)/i;
			translation(i, result, extra);
			break;

		}
	}
}

char* translation(int cell0, int cell1, int extra)
{	char* ostr = NULL;
	ostr = (char*)malloc(255); /* Just enough to create Brainfuck code within limits */
	if (extra == 1) {
		printf("WIP");
	} else {
		printf("WIP");
	}
 	/* TODO */
	/* Build a new string with for loops, return to writeto_file when done */
	free(ostr);
}	

void writeto_file(const char* ostr)
{
	/* TODO */
	/* Write to text file after receiving output string */
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