#include "fractranC.h"

const char* outputPath;
unsigned int instruction[MAX_INSTRUCTION_AMOUNT * 2];
unsigned int instructionSize = 0;

struct {
	unsigned int runsForever;
	unsigned int staticInput;
	unsigned int staticInputData;
	unsigned int directInput;
	unsigned int directOutput;
	unsigned int input[MAX_INPUT_OUTPUT_AMOUNT];
	unsigned int output[MAX_INPUT_OUTPUT_AMOUNT];
	unsigned int inputAmount;
	unsigned int outputAmount;
}option = { 0, 0, 0, 0, 0, {0}, {0}, 0, 0};

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
		} else if (word[0] == 'n') {
			option.directInput = 1;
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
		if (word[0] == 'n') {
			option.directOutput = 1;
		} else {
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

	fputs("//Generated with fractranC https://github.com/pjuftring/fractranC \n", outputFile);
	if (option.directOutput) {
		fputs("#include <math.h>\n", outputFile);
	}
	fputs("#include <stdio.h>\n#include <stdlib.h>\n\n", outputFile);

	if (option.directInput || option.directOutput) {
		fprintf(outputFile, "const unsigned int usedPrimes[%d] = {", usedPrimeListLength);
		for (i = 0; i < usedPrimeListLength; i++) {
			if (i > 0) {
				fprintf(outputFile, ", %d", usedPrimeList[i]);
			} else {
				fprintf(outputFile, "%d", usedPrimeList[i]);
			}
		}
		fputs("};\n\n", outputFile);
	}
	if (option.directInput) {
		fprintf(outputFile, "unsigned int factorize(unsigned int input, unsigned int varList[%d]){\n"
								"\tunsigned int i;\n"
								"\tfor (i = 0; i < %d; i++){\n"
									"\t\twhile((input %% usedPrimes[i]) == 0){\n"
										"\t\t\tvarList[i]++;\n"
									"\t\t\tinput /= usedPrimes[i];\n"
									"\t\t}\n"
								"\t}\n"
								"\treturn input;"
							"}\n\n", usedPrimeListLength, usedPrimeListLength);
	}
	if (option.directOutput) {
		fprintf(outputFile, "unsigned int unFactorize(unsigned int varList[%d]){\n"
								"\tunsigned int i, returnValue = 1;\n"
								"\tfor (i = 0; i < %d; i++) {\n"
									"\t\treturnValue *= pow(usedPrimes[i], varList[i]);\n"
								"\t}\n"
								"\treturn returnValue;\n"
							"}\n\n", usedPrimeListLength, usedPrimeListLength);
	}
	fprintf(outputFile, "int main(int argc, char* argv[]){\n\tlong varList[%i]={0};\n", usedPrimeListLength);
	if (option.staticInput) {
		fprintf(outputFile, "\factorize(%d, varList);\n\n", option.staticInputData);
	} else if (option.directInput){
		fputs(	"\tif (argc < 2){\n"	// Has to be changed
					"\t\tfputs(\"Input value expected!\", stderr);\n"
					"\t\treturn EXIT_FAILURE;\n"
				"\t} else {\n"
					"\t\tfactorize(atoi(argv[1]), varList);\n"
				"\t}\n\n", outputFile);
	} else {
		fprintf(outputFile,	"\tif (argc < %d){\n"
								"\t\tfputs(\"At least %d input value(s) expected!\", stderr);\n"
								"\t\treturn EXIT_FAILURE;\n"
							"\t} else {\n", option.inputAmount, option.inputAmount);
		for (i = 0; i < option.inputAmount; i++) {
			fprintf(outputFile, "\t\tvarList[%d] = atoi(argv[%d]);\n", getPositionOfPrime(usedPrimeList[i]), i + 1);
		}
		fputs(				"\t}\n\n", outputFile);
	}
	fputs("\tdo {\n", outputFile);
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
	if (option.directOutput) {
		fputs("\t\tprintf(\"%d\\n\", unFactorize(varList));\n", outputFile);
	} else {
		fputs("\t\tprintf(\"%d", outputFile);
		for (i = 1; i < option.outputAmount; i++) {
			fputs(", %d", outputFile);
		}
		fputs("\\n\", ", outputFile);
		for (i = 0; i < option.outputAmount; i++) {
			if (i == 0) {
				fprintf(outputFile, "varList[%d]", getPositionOfPrime(option.output[i]));
			} else {
				fprintf(outputFile, ", varList[%d]", getPositionOfPrime(option.output[i]));
			}
		}
		fputs(");\n", outputFile);
	}
	if (!option.runsForever) {
		fputs("\t\treturn EXIT_SUCCESS;\n", outputFile);
	}
	fputs("\t}while(1);\n}", outputFile);

	fclose(outputFile);
}