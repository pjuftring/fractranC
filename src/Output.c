#include "fractranC.h"

const char* outputPath;
unsigned int instruction[MAX_INSTRUCTION_AMOUNT * 2];
unsigned int instructionSize = 0;

struct {
	unsigned int runsForever;
	unsigned int staticInput;
	unsigned int staticInputData;
	unsigned int input[MAX_INPUT_OUTPUT_AMOUNT];
	unsigned int output[MAX_INPUT_OUTPUT_AMOUNT];
	unsigned int inputAmount;
	unsigned int outputAmount;
}option = { 0, 0, 0, {0}, {0}, 0, 0};

void initWriter(const char* path) {
	outputPath = path;
}

void instructionWriter(unsigned int p, unsigned int q) {
	if (instructionSize == MAX_INSTRUCTION_AMOUNT)
		tragicFail("Too many instructions. (Adjust MAX_INSTRUCTION_AMOUNT!)");
	instruction[instructionSize * 2]		= p;
	instruction[instructionSize * 2 + 1]	= q;
	instructionSize++;
}

void optionWriter() {
	nextWord();
	switch (word[0]) {
	case 'i':
		verifyWord(word, "input");
		nextWord();
		if (wordIsNumber()) {
			option.staticInput = 1;
			option.staticInputData = atoi(word);
		} else {
			option.staticInput = 0;
			if (option.inputAmount == MAX_INPUT_OUTPUT_AMOUNT){
				tragicFail("Too many input options. (Adjust MAX_INPUT_OUTPUT_AMOUNT)");
			}
			option.input[option.inputAmount] = circumflexToNumber();
			option.inputAmount++;
		}
		break;
	case 'o':
		verifyWord(word, "output");
		nextWord();
		if (option.outputAmount == MAX_INPUT_OUTPUT_AMOUNT) {
			if (option.outputAmount == MAX_INPUT_OUTPUT_AMOUNT) {
				tragicFail("Too many output options. (Adjust MAX_INPUT_OUTPUT_AMOUNT)");
			}
			option.output[option.outputAmount] = circumflexToNumber();
			option.outputAmount++;
		}
		break;
	case 'r':
		verifyWord(word, "runs");
		nextWord();
		switch (word[0]) {
		case 'f':
			verifyWord(word, "forever");
			option.runsForever = 1;
			break;
		case 'o':
			verifyWord(word, "once");
			option.runsForever = 0;
			break;
		default:
			tragicFail("Can't recognize parameter for 'runs'");
		}
		break;
	default:
		tragicFail("Can't recognize option.");
	}
}

void killWriter() {
	int primeAmount[MAX_PRIME_AMOUNT];
	unsigned int i, j;

	/*FILE* outputFile = fopen(outputPath, "w");
	if (outputFile == NULL) {
		tragicFail("Output file cannot be written.");
	}*/

	FILE* outputFile = stdout;

	fprintf(outputFile, "#include <stdio.h>\n#include <stdlib.h>\n\nint main(){\n\tlong varList[%i]={0};\n\tvarList[0]=27;\n\tvarList[1]=15;\n\n\tdo {\n", usedPrimeListLength);
	for (i = 0; i < instructionSize; i++) {
		unsigned int p, q;
		int isFirstComparison = 1;
		memset(primeAmount, 0, sizeof(usedPrimeList));
		p = instruction[i * 2];
		q = instruction[i * 2 + 1];
		factorize(p, primeAmount, FACTOR_ADD);
		factorize(q, primeAmount, FACTOR_REMOVE);
		fputs("\t\tif ((", outputFile);
		for (j = 0; j < usedPrimeListLength; j++) {
			if (primeAmount[j] < 0) {
				if (!isFirstComparison) {
					fputs(") && (", outputFile);
				} else {
					isFirstComparison = 0;
				}
				fprintf(outputFile, "varList[%i] >= %i", j, -primeAmount[j]);
			}
		}
		fputs(")) {\n", outputFile);
		for (j = 0; j < usedPrimeListLength; j++) {
			if (primeAmount[j] != 0) {
				fprintf(outputFile, "\t\t\tvarList[%i]+=%i;\n", j, primeAmount[j]);
			}
		}
		fputs("\t\t\tcontinue;\n\t\t}\n", outputFile);
	}
	if (option.runsForever) {
		fputs("\t\tprintf(\"%d, \", varList[0]);", outputFile);
	} else {
		fputs("\t\tprintf(\"%d\n\", varList[0]);\n\t\treturn EXIT_SUCCESS;", outputFile);
	}
	fputs("\n\t}while(1);\n}", outputFile);

	fclose(outputFile);
}