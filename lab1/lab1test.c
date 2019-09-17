#include "lab1algoimplementation.c"
#include <time.h>

#define CLK_TCK CLOCKS_PER_SEC

static clock_t start, stop;
static clock_t ticks[8];
int iternum[3] = {10000, 1000000, 1000000};
double result;

FILE *fp;

void printResult(int mark);

int main()
{
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
    fp = fopen("./testResult.md", "w");
    fprintf(fp, "| | N |");
    for (int i = 0; i < 8; i++)
        fprintf(fp, " %d |", aryN[i]);
    fprintf(fp, "\n|");
    for (int i = 0; i < 10; i++)
        fprintf(fp, " :--: |");
    fprintf(fp, "\n");

    for (int i = 0; i < 8; i++) {
        start = clock();
        for (int j = 0; j < iternum[0]; j++)
            result = PowClassic(1.0001, aryN[i]);
        stop = clock();
        printf("%f\n", result);
        ticks[i] = stop - start;
    }
    printResult(1);

    for (int i = 0; i < 8; i++) {
        start = clock();
        for (int j = 0; j < iternum[1]; j++)
            result = PowRecursive(1.0001, aryN[i]);
        stop = clock();
        printf("%f\n", result);
        ticks[i] = stop - start;
    }
    printResult(2);

    for (int i = 0; i < 8; i++) {
        start = clock();
        for (int j = 0; j < iternum[2]; j++)
            result = PowIterative(1.0001, aryN[i]);
        stop = clock();
        printf("%f\n", result);
        ticks[i] = stop - start;
    }
    printResult(3);
    fclose(fp);
    return 0;
}

void printResult(int mark)
{
    fprintf(fp, "| Algorithm%d | Iterations(K)", mark);
    for (int i = 0; i < 8; i++) {
        fprintf(fp, " | %d", iternum[mark - 1]);
    }

    fprintf(fp, " |\n| | Ticks");

    for (int i = 0; i < 8; i++) {
        fprintf(fp, " | %lu", ticks[i]); //clock_t is actually unsigned long
    }
    fprintf(fp, " |\n| | Total Times(milisecond)");

    double totalTimes[8]; //Use array to save the total and save the times used in the division
    for (int i = 0; i < 8; i++) {
        totalTimes[i] = (double)ticks[i];
        fprintf(fp, " | %f", totalTimes[i]);
    }
    fprintf(fp, " |\n| | Duration(nanosecond)");

    for (int i = 0; i < 8; i++) {
        fprintf(fp, " | %f", (double)(totalTimes[i] * 1000000 / iternum[mark - 1]));
    }
    fprintf(fp, " |\n");
}