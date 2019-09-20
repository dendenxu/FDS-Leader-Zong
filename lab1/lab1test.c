#include "lab1algoimplementation.c"
#include <time.h>

#define CLK_TCK CLOCKS_PER_SEC

static clock_t start, stop;
static clock_t ticks[8];
static double result;
//the iteration times of a single alog func.
//Bigger the magnitude, higher the accuracy but also time consumption.
static int iternum[3] = {
    1000,
    1000000,
    1000000,
};
#define testBase 1.0001  //def the datum used in the test

FILE *fp;  //set a file pointer for the .md file
double (*pFunc[3])(double, int) = {PowClassic, PowRecursive, PowIterative};


void printResult(int mark);  //init the function to output the result to .md

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
    fp = fopen("./testResult.md", "w");  //set the relative path and the file mode in "w" so that the old data can be deleted
    fprintf(fp, "| | N |");  //print the title of the table
    for (int i = 0; i < 8; i++) fprintf(fp, " %d |", aryN[i]);  //print the magnitude of the exponent
    fprintf(fp, "\n|");  //print the title of the table
    for (int i = 0; i < 10; i++) fprintf(fp, " :--: |");  //set the table to align center
    fprintf(fp, "\n");

    for (int loopFunc = 0; loopFunc < 3; loopFunc++) {  //loop foe 3 times to test the 3 algorithms
        for (int i = 0; i < 8; i++) {
            start = clock();  //start keep the time
            for (int j = 0; j < iternum[0] - 1; j++)  //iterate iternum[0]-1 times to increase accuracy
                result = pFunc[loopFunc](testBase, aryN[i]);
            result = pFunc[loopFunc](testBase, aryN[i]);  //run 1 time to get the result so that the time used to keep the data can be saved.
            stop = clock();  //stop keep the time
            printf("%g\n", result);  //print the result to the command line
            ticks[i] = stop - start;  //keep the tick
        }
        printResult(loopFunc + 1); //give a index to func printResult(int) so that it can make the table more detailed
    }
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
