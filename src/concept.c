#include <stdio.h>

int main() {
	const long primeList[] = { 2, 3, 5, 7, 11, 13};	// Wird nicht wirklick gebraucht, war eher für mich
	long varList[sizeof(primeList) / sizeof(long)] = { 0 };

	varList[0] = 45467;
	varList[1] = 10674;

	do {
		if ((varList[1] >= 1) && (varList[4] >= 1)) {
			varList[1]--;
			varList[2]++;
			varList[4]--;
			varList[3]++;
			varList[5]++;
		}
		else if (varList[5] >= 1) {
			varList[4]++;
			varList[5]--;
		}
		else if (varList[4] >= 1) {
			varList[4]--;
		}
		else if (varList[3] >= 1) {
			varList[1]++;
			varList[3]--;
		}
		else if (varList[0] >= 1) {
			varList[0]--;
			varList[4]++;
		}
		else if (varList[1] >= 1) {
			varList[1]--;
		}
		else {
			return varList[2];
		}
	} while (1);
}