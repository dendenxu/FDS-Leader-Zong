#include "lab1algoimplementation.c" //get the func of 3 algorithms
#include <time.h>

#define CLK_TCK CLOCKS_PER_SEC      //redef the macro

static clock_t start, stop;         //save the time used for ticks counting
static clock_t ticks[8];            //use an array to save the ticks data for printing
static double result;
//the iteration times of a single alog func.
//Bigger the magnitude, higher the accuracy but also time consumption.

#define testBase 1.0001             //def the datum used in the test

FILE *fp;                           //set a file pointer for the .md file
double (*pFunc[])(double, int) = {PowClassic, PowRecursive, PowIterative, PowIterativeBetter};
static int iternum[sizeof(pFunc) / sizeof(pFunc[0])] = {
    1000,
    1000000,
    1000000,
    1000000,
};
void printResult(int mark); //init the function to output the result to .md

int main()
{
    int aryN[8] = {
        //set the array of exponent
        1000,
        5000,
        10000,
        20000,
        40000,
        60000,
        80000,
        100000,
    };
    fp = fopen("testResult.md", "w");  //set the relative path and the file mode in "w" so that the old data can be deleted
    fprintf(fp, "| | N |");            //print the title of the table
    for (int i = 0; i < 8; i++)
        fprintf(fp, " %d |", aryN[i]); //print the magnitude of the exponent
    fprintf(fp, "\n|");                //print the title of the table
    for (int i = 0; i < 10; i++)
        fprintf(fp, " :--: |");        //set the table to align center
    fprintf(fp, "\n");

    for (int loopFunc = 0; loopFunc < sizeof(pFunc) / sizeof(pFunc[0]); loopFunc++) { //loop for 3 times to test the 3 algorithms
        for (int i = 0; i < 8; i++) {
            start = clock();                                //start keep the time
            for (int j = 0; j < iternum[loopFunc] - 1; j++) //increase accuracy by eliminating the time used in result assignment
                pFunc[loopFunc](testBase, aryN[i]);         //pFunc[] is an array of function pointer
            result = pFunc[loopFunc](testBase, aryN[i]);    //run 1 time to get the result so that the time used to keep the data can be saved.
            stop = clock();                                 //stop keep the time
            printf("%g\n", result);                         //print the result to the command line
            ticks[i] = stop - start;                        //keep the tick
        }
        printResult(loopFunc + 1); //give a index to func printResult(int) so that it can make the table more detailed
    }
    fclose(fp);
    return 0;
}

void printResult(int mark)
{
    fprintf(fp, "| Algorithm%d | Iterations(K)", mark); //print the mark of the algorithms
    for (int i = 0; i < 8; i++) {
        fprintf(fp, " | %d", iternum[mark - 1]);        //print the iterations time
    }

    switch (mark) {                                     //print the algorithm name
        case 1:
            fprintf(fp, " |\n| Classic | Ticks");
            break;
        case 2:
            fprintf(fp, " |\n| Recursive | Ticks");
            break;
        case 3:
            fprintf(fp, " |\n| Iterative | Ticks");
            break;
        case 4:
            fprintf(fp, " |\n| IterativeBetter | Ticks");
            break;
    }

    for (int i = 0; i < 8; i++) {
        fprintf(fp, " | %lu", ticks[i]);            //clock_t is actually unsigned long
    }
    fprintf(fp, " |\n| | Total Times(ms)");

    double totalTimes[8];                           //Use array to save the Total Times and save the time used in the division operations
    for (int i = 0; i < 8; i++) {
        totalTimes[i] = (double)ticks[i] / CLK_TCK * 1000.0;
        fprintf(fp, " | %g", totalTimes[i]);        //print Total Times
    }
    fprintf(fp, " |\n| | Duration(ns)");

    for (int i = 0; i < 8; i++) {
        fprintf(fp, " | %g", (double)(totalTimes[i] * 1000000.0 / iternum[mark - 1])); //print Duration of a single call
    }
    fprintf(fp, " |\n");
}
