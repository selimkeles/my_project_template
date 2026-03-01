#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char* ltrim(char*);
char* rtrim(char*);

int parse_int(char*);


/*
 * Complete the 'findMaximumQuality' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY packets
 *  2. INTEGER channels
 */

int cmp (const void* a, const void* b){
    int l = *(const int*)a;
    int r = *(const int*)b;
    // Sort descending
    return r-l;
}

long sum(long len, int* arr){
    long total = 0;
    for (int i = 0; i < len-1 ; i++) {
        total += arr[i]; 
    }
    return total;
}

long findMaximumQuality(int packets_count, int* packets, int channels) {
    qsort(packets, packets_count, sizeof(packets[0]), cmp);
    
    long total_size = sum(channels, packets);
    // long median_sum = sum(packets_count-(channels-1), &packets[channels-1]);
    printf("total_size: %ld\n", total_size);
    long median = 0;
    long len = packets_count-channels-1;
    long avg = len/2;
    if (len % 2){
        median = packets[channels-1+avg];
    }
    else {
        median = (packets[channels-1+avg] + packets[channels-1+avg + 1]);
        median /= 2;
    }
    
    return median + total_size;
}
int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int packets_count = parse_int(ltrim(rtrim(readline())));

    int* packets = malloc(packets_count * sizeof(int));

    for (int i = 0; i < packets_count; i++) {
        int packets_item = parse_int(ltrim(rtrim(readline())));

        *(packets + i) = packets_item;
    }

    int channels = parse_int(ltrim(rtrim(readline())));

    long result = findMaximumQuality(packets_count, packets, channels);

    fprintf(fptr, "%ld\n", result);

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
