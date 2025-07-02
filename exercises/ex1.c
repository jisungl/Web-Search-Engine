/*
Jisung Lee
jisung@uw.edu
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

void CopyAndSort(const int64_t *source, int64_t *dest, int length);

int main() {
    int64_t source[] = {3, 2, -5, 7, 17, 42, 6, 333, 7, 8, -8, 6};
    int length = sizeof(source) / sizeof(source[0]);
    int64_t sorted[length];

    CopyAndSort(source, sorted, length);

    for (int i = 0; i < length; i++) {
        printf("%" PRId64 " ", sorted[i]);
    }
    printf("\n");

    return 0;
}

void CopyAndSort(const int64_t *source, int64_t *dest, int length) {
    for (int i = 0; i < length; i++) {
        int64_t current = source[i];
        int j = i - 1;

        while (j >= 0 && dest[j] > current) {
            dest[j + 1] = dest[j];
            j--;
        }

        dest[j + 1] = current;
    }
}