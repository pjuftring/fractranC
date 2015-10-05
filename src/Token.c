#include "fractranC.h"

char word[MAX_WORD_LENGTH + 1] = { 0 };
FILE* inputFile;
char c = 0;

int isSpace(char c);
void nextChar();

int lastWasSlash = 0;


void initTokenizer(const char* path) {
	/*FILE* inputFile = fopen(path, "rb");
	if (inputFile == NULL) {
		tragicFail("Input file cannot be read.");
	}*/
	
	inputFile = stdin;
	nextChar();
}

int nextWord() {
	int wordPosition = 0;

	while (isSpace(c) && (c != EOF)) {
		nextChar();
	}

	if (c == EOF)
		return 0;

	if (c == '/') {
		if (lastWasSlash) {
			while ((c != '\n') && (c != EOF)) {
				nextChar();
			}
		} else {
			lastWasSlash = 1;
			nextChar();
		}
		return nextWord();
	} else {
		lastWasSlash = 0;
	}

	if ((c == '#') || (c == ',')) {
		word[0] = c;
		word[1] = 0;
		nextChar();
		return 1;
	}

	while ((!isSpace(c)) && (c != EOF) && (wordPosition <= MAX_WORD_LENGTH)) {
		word[wordPosition] = c;
		nextChar();
		wordPosition++;
	}

	word[wordPosition] = 0;
	return 1;
}

void killTokenizer() {
	fclose(inputFile);
}

// Tokenizer's Little Helper Functions

int isSpace(char c) {
	return ((c == ' ') || (c == '\t') || (c == '\n') || (c == '\r'));
}

void nextChar() {
	c = getc(inputFile);
}