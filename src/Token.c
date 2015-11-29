#include "fractranC.h"
#include <ctype.h>

char word[MAX_WORD_LENGTH + 1] = { 0 };
char* inputBuffer = NULL;
unsigned long fileSize = 0;
unsigned long filePosition = 0;

void initTokenizer(const char* path) {
	/*FILE* inputFile = fopen(path, "rb");
	if (inputFile == NULL) {
		tragicFail("Input file cannot be read.");
	}*/

	FILE* inputFile = stdin;
	
	int length = 0, capacity = 100;

	inputBuffer = malloc(capacity);
	if (inputBuffer == NULL) {
		tragicFail(ERR_MEMORY_ALLOC);
		assert(0);
	}
	inputBuffer[0] = '\0';

	do{
		length = strlen(inputBuffer);
		if(capacity - length <= 1){
			void *n = realloc(inputBuffer, capacity += 100);
			if(n == NULL){
				free(inputBuffer);
				tragicFail(ERR_MEMORY_ALLOC);
				assert(0);
			}
		}
	}while(fgets(inputBuffer, capacity - length, inputFile) != NULL);

	fileSize = strlen(inputBuffer);

	fclose(inputFile);
}

int nextWord() {
	int wordPosition = 0;

	while (isspace(inputBuffer[filePosition]) && (filePosition < fileSize)) {
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

	while ((!isspace(inputBuffer[filePosition])) && (filePosition < fileSize) && (wordPosition <= MAX_WORD_LENGTH)) {
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

