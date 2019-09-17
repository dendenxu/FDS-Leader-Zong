#include <stdio.h>
// These three functions calculate the power of a real number to an integer
// The first one simply uses the definition of power
// The second one uses recursive mechanism to reduce to number of multiplications
// The third one uses stack to implement the second one's recursion by hand, reducing unneccessary machine code
// For example:
// push ebp
// mov ebp, esp
// ...
// mov esp, ebp
// pop ebp
// ret
// is what the computer needs to do even dealing with an empty function
// let alone the complicated recursive function
double PowClassic(double x, int n);
double PowRecursive(double x, int n);
double PowIterative(double x, int n);
// Before the test, it's the implementer's assumption that the Recursive and Iterative ones' complexity is O(log n)
// The classic algorithm's complexity is O(n)
// While the Iterative one's constant may be smaller

int main()
{
    printf("%f\n", PowClassic(1.0001, 1000000));
    printf("%f\n", PowRecursive(1.0001, 1000000));
    printf("%f\n", PowIterative(1.0001, 1000000));
    return 0;
}

double PowClassic(double x, int n)
{
    // Simplest implementation
    double result = 1;
    for (int i = 0; i < n; i++) {
        result = x * result;
    }
    return result;
}

double PowRecursive(double x, int n)
{
    // Recursive exit
    if (n == 0) {
        return 1;
    }
    if (n == 1) {
        return x;
    }

    // If n is even, x^n = x^(n/2) * x^(n/2).
    // If n is odd, x^n = x^((n-1)/2) * x^((n-1)/2) * x
    if (n % 2) {
        // Avoiding statement like:
        // return PowRecursive(x, n/2) * PowRecursive(x, n/2) * x
        // It recursives twice as much
        double re = PowRecursive(x, n / 2);
        return re * re * x;
    } else {
        double re = PowRecursive(x, n / 2);
        return re * re;
    }
}

double PowIterative(double x, int n)
{
    int stack[100];
    int *p = stack;
    // Simplest stack implementation
    // Using information stored in the stack to determine whether you use:
    // result = result * result * x
    // or
    // result = result * result
    double result = 1;
    while (n) {
        *p = n % 2;
        p++;
        n /= 2;
    }
    while (p > stack) {
        if (*(--p)) {
            result = result * result * x;
        } else {
            result *= result;
        }
    }
    return result;
    // No need to explicitly give n=0 or n=1 some code.
}