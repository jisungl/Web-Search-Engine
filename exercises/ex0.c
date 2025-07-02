/*
Jisung Lee
jisung@uw.edu
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

double estimate(int n);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Input exactly one argument\n");
        return 1;
    }

    char *end;
    long n = strtol(argv[1], &end, 10);

    if (*end != '\0') {
        fprintf(stderr, "Invalid input\n");
        return 2;
    }

    if (n < 0 || n > INT_MAX) {
        fprintf(stderr, "Input should be a valid non-negative integer between 0 and %d\n", INT_MAX);
        return 3;
    }

    double pi = estimate((int)n);
    printf("Our estimate of Pi is %.20f\n", pi);

    return 0;
}

double estimate(int n) {
    double pi = 3.0;
    if (n == 0) {
        return pi;
    }

    for (int i = 1; i <= n; i++) {
        double denom = 2.0 * i * (2.0 * i + 1) * (2.0 * i + 2);
        double add = 4.0 / denom;

        if (i % 2 == 1) {
            pi += add;
        } else {
            pi -= add;
        }
    }
    return pi;
}