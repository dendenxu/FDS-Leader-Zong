#include "Prog.h"
#include "Prog.c"
#include <time.h>

#define CLK_TCK CLOCKS_PER_SEC  //different name in macOS

static clock_t start, stop;

static int iterations[8];
static clock_t ticks[8];

FILE *fp;

void printResult(int mark);

int main() {
	int aryN[8] = {1000,
	               50000,
	               10000,
	               20000,
	               40000,
	               60000,
	               80000,
	               100000,
	              };
	fp = fopen("/Users/futuretech6/Documents/大二上/数结/HW/Project1/Prog/testResult.md", "w");
	fprintf(fp, "| | N |");
	for (int i = 0; i < 8; i++) fprintf(fp, " %d |", aryN[i]);
	fprintf(fp, "\n|");
	for (int i = 0; i < 10; i++) fprintf(fp, " :--: |");
	fprintf(fp, "\n");

	for (int i = 0; i < 8; i++) {
		start = clock();
		PowClassic(1.0001, aryN[i]);
		stop = clock();

		iterations[i] = aryN[i];
		ticks[i] = stop - start;
	}
	printResult(1);

	for (int i = 0; i < 8; i++) {
		start = clock();
		PowRecursive(1.0001, aryN[i]);
		stop = clock();

		iterations[i] = aryN[i];
		ticks[i] = stop - start;
	}
	printResult(2);

	for (int i = 0; i < 8; i++) {
		start = clock();
		PowIterative(1.0001, aryN[i]);
		stop = clock();

		iterations[i] = aryN[i];
		ticks[i] = stop - start;
	}
	printResult(3);

	return 0;
}

void printResult(int mark) {
	fprintf(fp, "| Algorithm%d | Iterations(K)", mark);
	for (int i = 0; i < 8; i++) {
		fprintf(fp, " | %d", iterations[i]);
	}

	fprintf(fp, " |\n| | Ticks");

	for (int i = 0; i < 8; i++) {
		fprintf(fp, " | %lu", ticks[i]);  //clock_t is actually unsigned long
	}
	fprintf(fp, " |\n| | Total Times(sec)");

	double totalTimes[8];  //Use array to save the total and save the times used in the division
	for (int i = 0; i < 8; i++) {
		totalTimes[i] = (double)ticks[i] / CLK_TCK;
		fprintf(fp, " | %g", totalTimes[i]);
	}
	fprintf(fp, " |\n| | Duration(sec)");

	for (int i = 0; i < 8; i++) {
		fprintf(fp, " | %g", (double)(totalTimes[i] / iterations[i]));
	}
	fprintf(fp, " |\n");

}
