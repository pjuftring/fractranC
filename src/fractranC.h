#ifndef FRACTRANC_FRACTRANC_H_
#define FRACTRANC_FRACTRANC_H_

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

//	fractranC.c
void tragicFail(const char* error);

//	Token.c
#define MAX_WORD_LENGTH 255				// One less than 2^8, since we use null-terminated strings
extern char word[MAX_WORD_LENGTH + 1];
void initTokenizer(const char* path);
void killTokenizer();
int nextWord();
void verifyWord(char* txt1, char* txt2);
unsigned int circumflexToNumber();
unsigned int wordIsNumber();

//	Output.c
#define MAX_INSTRUCTION_AMOUNT 4096
#define MAX_INPUT_OUTPUT_AMOUNT 5
extern unsigned int instruction[MAX_INSTRUCTION_AMOUNT * 2];
extern unsigned int instructionSize;
void initWriter(const char* path);
void instructionWriter(unsigned int p, unsigned int q);
void optionWriter();
void killWriter();

// Prime.c
#define MAX_PRIME_AMOUNT 1000
#define MAX_PRIME_SIZE 8000
enum factorType{
	FACTOR_ADD,
	FACTOR_REMOVE
};
extern unsigned int usedPrimeList[MAX_PRIME_AMOUNT];
extern unsigned int usedPrimeListLength;
void determineUsedPrimes();
void factorize(unsigned int l, int factors[MAX_PRIME_AMOUNT], enum factorType type);
unsigned int getPositionOfPrime(unsigned int p);


#endif