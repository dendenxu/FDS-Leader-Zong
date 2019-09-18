#include "lab1algoimplementation.c"
#include <time.h>

#define CLK_TCK CLOCKS_PER_SEC

static clock_t start, stop;
static clock_t ticks[8];
static double result;
//the iteration times of a single alog func. Bigger the magnitude, higher the accuracy but also time consumption.
static int iternum[3] = {
    1000,
    100000,
    100000,
};

FILE *fp;

void printResult(int mark);

int main() {
    int aryN[8] = {
        1000,
        5000,
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
        for (int j = 0; j < iternum[0]; j++)
            result = PowClassic(1.0001, aryN[i]);
        stop = clock();
        printf("%g\n", result);
        ticks[i] = stop - start;
    }
    printResult(1);

    for (int i = 0; i < 8; i++) {
        start = clock();
        for (int j = 0; j < iternum[1]; j++)
            result = PowRecursive(1.0001, aryN[i]);
        stop = clock();
        printf("%g\n", result);
        ticks[i] = stop - start;
    }
    printResult(2);

    for (int i = 0; i < 8; i++) {
        start = clock();
        for (int j = 0; j < iternum[2]; j++)
            result = PowIterative(1.0001, aryN[i]);
        stop = clock();
        printf("%g\n", result);
        ticks[i] = stop - start;
    }
    printResult(3);

    fclose(fp);
    return 0;
}

void printResult(int mark) {
    fprintf(fp, "| Algorithm%d | Iterations(K)", mark);
    for (int i = 0; i < 8; i++) {
        fprintf(fp, " | %d", iternum[mark - 1]);
    }

    switch (mark) {
        case 1: fprintf(fp, " |\n| Classic | Ticks"); break;
        case 2: fprintf(fp, " |\n| Recursive | Ticks"); break;
        case 3: fprintf(fp, " |\n| Iterative | Ticks"); break;
    }

    for (int i = 0; i < 8; i++) {
        fprintf(fp, " | %lu", ticks[i]); //clock_t is actually unsigned long
    }
    fprintf(fp, " |\n| | Total Times(ms)");

    double totalTimes[8]; //Use array to save the total and save the times used in the division
    for (int i = 0; i < 8; i++) {
        totalTimes[i] = (double)ticks[i] / CLK_TCK * 1000.0;
        fprintf(fp, " | %g", totalTimes[i]);
    }
    fprintf(fp, " |\n| | Duration(ns)");

    for (int i = 0; i < 8; i++) {
        fprintf(fp, " | %g", (double)(totalTimes[i] * 1000000.0 / iternum[mark - 1]));
    }
    fprintf(fp, " |\n");
}