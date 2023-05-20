# Text To Brainf**k Code Translator

Short summary: A CLI one-way translator that translates your text you write in console into Brainfuck code that when ran, will output same text you've wrote.

## Intended use

Clone repo to your directory of any choice, then run `cmake .` inside repo directory and `cmake --build .`
Or, since it's just one source file... might as well compile it yourself with C compilers :D

Depending on the system, you can run in terminal with the following command:

- Windows: `.\bf`
- Linux/Mac: `./bf`

The program takes input text and then passes it to the one big function that creates brainfuck file and output string (default max string size can be changed as well). The input string gets processed by an algorithm in a while loop until the input string's null terminating character is reached. During the loop, Brainfuck code is generated and outputted to standard output immediately. Once looping is finished, you will be notified that the text has been translated and ready to be copied.

Key features of the algorithm include:

- checking for same characters, thus skipping the unnecessary calculations
- incrementation/decrementation of a cell without loop if the distance between previous and incoming character is less than 13.
- division of composite / prime numbers with `extra`, using looping incrementation/decrementation to get to the desired character to print.

Included in the code is error checking; if memory allocation fails, the program will notify you about it and then do `exit()`.

**Any contribution here is highly appreciated!**
