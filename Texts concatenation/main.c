#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#define ROWS 4
#define COLS 1001

int concatenate(char *buffer, int buffer_size, int count, ...) {
    if (buffer == NULL || buffer_size <= 0 || count <= 0) return 1;
    va_list vaList;
            va_start(vaList, count);
    size_t size_left = buffer_size;
    for (int i = 0; i < count; ++i) {
        char * tmp_str = va_arg(vaList, char *);
        if (size_left < strlen(tmp_str) + 1) {
                    va_end(vaList);
            return 2;
        }
        if (i == 0) {
            strcpy(buffer, tmp_str);
            strcat(buffer, " ");
        } else {
            strcat(buffer, tmp_str);
            if (i != count - 1) {
                strcat(buffer, " ");
            }
        }
        size_left -= strlen(tmp_str) + 1;
    }
            va_end(vaList);
    return 0;
}


void free_str(char ** arr, int rows) {
    for (int i = 0; i < rows; ++i) {
        free(*(arr + i));
    }
    free(arr);
}

int main() {
    char **texts = (char **) malloc(ROWS * sizeof(char *));
    if (texts == NULL) return 8 + !printf("Failed to allocate memory");
    for (int i = 0; i < ROWS; ++i) {
        *(texts + i) = malloc(COLS * sizeof(char));
        if (*(texts + i) == NULL) {
            for (int j = i - 1; j >= 0; --j) {
                free(*(texts + j));
            }
            free(texts);
            return 8 + !printf("Failed to allocate memory");
        }
    }
    char *res = malloc(sizeof(char ) * ROWS * COLS);
    if (res == NULL) {
        free_str(texts, ROWS);
        printf("Failed to allocate memory");
        return 8;
    }
    int amount;
    printf("Podaj liczbe tekstow: ");
    if (scanf("%d", &amount) != 1) {
        free_str(texts, ROWS);
        free(res);
        printf("Incorrect input");
        return 1;
    }
    if (amount < 2 || amount > 4) {
        printf("Incorrect input data");
        free_str(texts, 4);
        free(res);
        return 2;
    }

    printf("Podaj teksty: ");
    for (int i = 0; i < amount; ++i) {
        int c;
        do {
            c = getchar();
        } while (c != '\n' && c != EOF);
        scanf("%1000[^\n]s", *(texts + i));
    }
    if (amount == 2) {
        concatenate(res, ROWS * COLS, amount, *(texts + 0), *(texts + 1));
    }
    if (amount == 3) {
        concatenate(res, ROWS * COLS, amount, *(texts + 0), *(texts + 1), *(texts + 2));
    }
    if (amount == 4) {
        concatenate(res, ROWS * COLS, amount, *(texts + 0), *(texts + 1), *(texts + 2), *(texts + 3));
    }
    printf("%s", res);
    free(res);
    free_str(texts, 4);
    return 0;
}