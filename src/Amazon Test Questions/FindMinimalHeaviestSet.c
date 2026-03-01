#include <stdio.h>
#include <stdlib.h>
// Helper function to calculate the sum of an array
int sum(int* arr, int size) {
int total = 0;
for (int i = 0; i < size; i++) {
total += arr[i];
}
return total;
}
// Comparator function for sorting in descending order
int compare(const void* a, const void* b) {
return (*(int*)b - *(int*)a);
}
int* minimalHeaviestSetA(int arr_count, int* arr, int* result_count) {
// Sort the array in descending order
qsort(arr, arr_count, sizeof(int), compare);
// Initialize variables
int* result = (int*)malloc(arr_count * sizeof(int));
int target = sum(arr, arr_count) / 2;
int sumA = 0;
int index = 0;
// Construct subset A
for (int i = 0; i < arr_count; i++) {
if (sumA > target) {
break;
}
result[index++] = arr[i];
sumA += arr[i];
}
// Set the result count and return the subset A
*result_count = index;
return result;
}
int main() {
int n = 5;
int arr[] = {3, 7, 5, 6, 2};
int result_count;
int* subsetA = minimalHeaviestSetA(n, arr, &result_count);
printf("Subset A: ");
for (int i = 0; i < result_count; i++) {
printf("%d ", subsetA[i]);
}
printf("\n");
free(subsetA); // Don't forget to free the allocated memory
return 0;
}