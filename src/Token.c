#include "fractranC.h"

char word[MAX_WORD_LENGTH + 1] = { 0 };
char* inputBuffer = NULL;
unsigned long fileSize = 0;
unsigned long filePosition = 0;

int isSpace(char c);

void initTokenizer(const char* path) {
	/*FILE* inputFile = fopen(path, "rb");
	if (inputFile == NULL) {
		tragicFail("Input file cannot be read.");
	}*/

	FILE* inputFile = stdin;

	fseek(inputFile, 0, SEEK_END);
	fileSize = ftell(inputFile);
	fseek(inputFile, 0, SEEK_SET);

	inputBuffer = malloc(fileSize);
	if (inputBuffer == NULL) {
		tragicFail("Memeory can not be allocated.");
	}

	fread(inputBuffer, 1, fileSize, inputFile);

	fclose(inputFile);
}

int nextWord() {
	int wordPosition = 0;

	while (isSpace(inputBuffer[filePosition]) && (filePosition < fileSize)) {
		filePosition++;
	}

	if (filePosition >= fileSize)
		return 0;

	if ((inputBuffer[filePosition] == '/') && ((filePosition + 1) < fileSize)) {
		if (inputBuffer[filePosition + 1] == '/') {
			while (inputBuffer[filePosition] != '\n' && (filePosition < fileSize)) {
				filePosition++;
			}
			return nextWord();
		}
	}

	if ((inputBuffer[filePosition] == '#') || (inputBuffer[filePosition] == ',')) {
		word[0] = inputBuffer[filePosition];
		word[1] = 0;
		filePosition++;
		return 1;
	}

	while ((!isSpace(inputBuffer[filePosition])) && (filePosition < fileSize) && (wordPosition <= MAX_WORD_LENGTH)) {
		word[wordPosition] = inputBuffer[filePosition];
		filePosition++;
		wordPosition++;
	}

	word[wordPosition] = 0;
	return 1;
}

void killTokenizer() {
	free(inputBuffer);
}

// Tokenizer's Little Helper Functions

int isSpace(char c) {
	return ((c == ' ') || (c == '\t') || (c == '\n') || (c == '\r'));
}
