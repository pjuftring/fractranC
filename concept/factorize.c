#include <math.h>

const unsigned int usedPrimes[7] = {2, 3, 11, 13, 19, 23, 29};

void factorize(unsigned int input, unsigned int varList[7]){
	unsigned int i;
	for (i = 0; i < 7; i++){
		while((input % usedPrimes[i]) == 0){
			varList[i]++;
			input /= usedPrimes[i];
		}
	}
}

unsigned int unFactorize(unsigned int varList[7]){
	unsigned int i, returnValue = 1;
	for (i = 0; i < 7; i++){
		returnValue *= pow(usedPrimes[i], varList[i]);
	}
	return returnValue;
}