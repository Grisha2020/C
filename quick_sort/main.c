#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int cmp(const void* elem1, const void* elem2){
    return (*(int*)elem1 - *(int*)elem2);
}

int print_arr(double arr[], int start, int end){
    int i = start;
    while (i < end){
        printf("%lf ", arr[i]);
        i++;
    }
    printf("\n");
    return 0;
}

int swap(double arr[], int elem1, int elem2){
    void* swapp = malloc(sizeof(arr[elem1]));
    memcpy(swapp, arr + elem1, sizeof(arr[elem1]));
    memcpy(arr + elem1, arr + elem2, sizeof(arr[elem1]));
    memcpy(arr + elem2, swapp, sizeof(arr[elem1]));
    free(swapp);
    return 0;


int quick_sort_recurs(double arr[], int smaller, int bigger, int comp) {
    if (bigger - smaller > 1) {
        double centre = arr[(smaller + bigger + 1) / 2];
        int start = smaller;
        int end = bigger;
        while (smaller < bigger) {
            if (arr[smaller] >= centre && arr[bigger] > centre) {
                while (arr[bigger] > centre) {
                    bigger--;
                    if (smaller >= bigger) {
                        break;
                    }
                }
            } else if (arr[smaller] < centre && arr[bigger] < centre) {
                while (arr[smaller] < centre) {
                    smaller++;
                    if (smaller >= bigger) {
                        break;
                    }
                }
            } else if (arr[smaller] < centre && arr[bigger] >= centre){
                smaller++;
                bigger--;
                continue;
            }
            if (smaller >= bigger){
                break;
            }
            swap(arr, smaller, bigger);
            smaller++;
            bigger--;
            if (smaller > bigger){
                smaller--;
                bigger++;
                break;
            }
        }
        quick_sort_recurs(arr, start, smaller, comp);
        quick_sort_recurs(arr, bigger, end, comp);
    } else if (bigger - smaller == 1){
        if (arr[smaller] > arr[bigger]){
            swap(arr, smaller, bigger);
        }
    }
    return 0;
}

int quick_sort(double arr[], int n){
    int small = 0, big = n - 1;
    quick_sort_recurs(arr, small, big, cmp);
    return 0;
}

int test(){
    int n = 6;
    double arr1[6] = {5, 3, 4, 2, 1, 2};
    quick_sort(arr1, n);
    int arr2[6] = {5, 3, 4, 2, 1, 2};
    qsort(arr2, 6, sizeof(int), cmp);
    int i = 0;
    while (i<n){
        if (arr1[i] != arr2[i]){
            printf("%d, %d\n", (int)arr1[i], arr2[i]);
            //assert(0);
        }
        i++;
    }
    return 0;
}

int main() {
    test();
    int n;
    printf("Enter the number of numbers in the array.\n");
    scanf("%d", &n);
    double* arr = malloc(n * sizeof(double));
//    double arr[1000];
    int i = 0;
    double number;
    while (i < n){
        scanf("%lf", &number);
        arr[i] = number;
        i++;
    }
    quick_sort(arr, n);
    print_arr(arr, 0, n);
    return 0;
}

