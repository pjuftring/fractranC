#include "fractranC.h"

void tragicFail(const char* error) {
	puts(error);
	exit(EXIT_FAILURE);
}

int main(int argc, const char* argv[]) {
	const char* in = "multiply.fractran";
	const char* out = "test.c";

	initTokenizer(in);
	initWriter(out);
	
	while (nextWord()) {
		unsigned int p, q;
		p = atoi(word);
		nextWord(); //	'/'
		nextWord();
		q = atoi(word);
		instructionWriter(p, q);
	}

	determineUsedPrimes();

	killWriter();
	killTokenizer();
}