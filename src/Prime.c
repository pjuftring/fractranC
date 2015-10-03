#include "fractranC.h"

unsigned int usedPrimeList[MAX_PRIME_AMOUNT] = { 0 };
unsigned int usedPrimeListLength = 0;

void determineUsedPrimes() {
	unsigned int i = 2;
	while (i < MAX_PRIME_SIZE) {
		unsigned int j;
		int discardThisNumber = 0;
		for (j = 0; j < usedPrimeListLength; j++) {
			if ((i % usedPrimeList[j]) == 0) {
				discardThisNumber = 1;
				break;
			}
		}
		if (discardThisNumber) {
			i++;
			continue;
		}
		for (j = 0; j < (instructionSize * 2); j++) {
			if ((instruction[j] % i) == 0) {
				usedPrimeList[usedPrimeListLength] = i;
				usedPrimeListLength++;
				if (usedPrimeListLength == MAX_PRIME_AMOUNT)
					return;
				break;
			}
		}
		i++;
	}
}

void factorize(unsigned int l, int factors[MAX_PRIME_AMOUNT], enum factorType type) {
	unsigned int i;
	for (i = 0; i < usedPrimeListLength; i++) {
		if (l == 1)
			return;
		while ((l%usedPrimeList[i]) == 0) {
			l /= usedPrimeList[i];
			if (type == FACTOR_ADD) {
				factors[i]++;
			} else {
				factors[i]--;
			}
		}
	}
	if (l != 1) {
		tragicFail("Couldn't remember all used primes. (Adjust MAX_PRIME_AMOUNT!)");
	}
}