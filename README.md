# Text To Brainf**k Code Translator

Short summary: A console based translator that translates your text you write in console into Brainf**k code that will output the said text inside a .bf file for you to run the code with appropriate brainfuck interpreter.

## Intended use

Clone repo to your directory of any choice, then use any C compiler and compile `bf.c`, to create an executable named `bf`.
Then depending on the system when you're in the same directory as the executable, you can run in terminal with the following command:

- Windows: `.\bf`
- Linux/Mac: `./bf`

The program takes string as an input (default max string size is 1024); to finish writing, you have to press Enter, which is an equivalent of '\n' that the program will detect and stop taking further characters.

It then passes said input string to the one big function that creates brainfuck file and output string. The input string gets processed by an algorithm in a while loop until the input string's null terminating character is reached. The finished output string gets written to the file, the memory gets freed and the program will tell you that the translation has been completed.

Key features of the algorithm include:

- checking for same characters, thus skipping the unnecessary calculations
- incrementation/decrementation of a cell without loop if the distance between previous and incoming character is less than 13.
- division of composite / prime numbers with `extra`, using looping incrementation/decrementation to get to the desired character to print.

There are older algorithms in the folder that lack such one of the key features and output considerably bigger brainfuck code.

Included in the code is error checking; if file or memory allocation fails, the program will notify you about it and then do `exit()`.
