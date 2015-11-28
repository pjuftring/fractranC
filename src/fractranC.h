#ifndef FRACTRANC_FRACTRANC_H_
#define FRACTRANC_FRACTRANC_H_

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define ERR_MEMORY_ALLOC	"Memory cannot be allocated"

//	fractranC.c
void tragicFail(const char* error);

//	Token.c
#define MAX_WORD_LENGTH 255				// One less than 2^8, since we use null-terminated strings
extern char word[MAX_WORD_LENGTH + 1];
void initTokenizer(const char* path);
void killTokenizer();
int nextWord();

//	Output.c
#define MAX_INSTRUCTION_AMOUNT 4096
extern unsigned int instruction[MAX_INSTRUCTION_AMOUNT * 2];
extern unsigned int instructionSize;
void initWriter(const char* path);
void instructionWriter(unsigned int p, unsigned int q);
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


#endif
