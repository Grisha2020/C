#include <stdio.h>

int print_arr(double arr[], int start, int end){
    int i = start;
    while (i < end){
        printf("%lf ", arr[i]);
        i++;
    }
    printf("\n");
    return 0;
}

int quick_sort_recurs(double arr[], int smaller, int bigger) {
    if (bigger - smaller > 1) {
        double swap;
        double centre = arr[(smaller + bigger + 1) / 2];
        int start = smaller;
        int end = bigger;
        while (smaller < bigger) {
            int stop = 0;// if (stop = 1) { break the cycle while (smaller < bigger)}
            if (arr[smaller] >= centre && arr[bigger] > centre) {//-------------------------------------
                while (arr[bigger] > centre) {
                    bigger--;
                    if (smaller >= bigger) {
                        stop = 1;
                        break;
                    }
                }
            } else if (arr[smaller] < centre && arr[bigger] < centre) {
                while (arr[smaller] < centre) {
                    smaller++;
                    if (smaller >= bigger) {
                        stop = 1;
                        break;
                    }
                }
            } else if (arr[smaller] < centre && arr[bigger] >= centre){
                smaller++;
                bigger--;
                continue;
            }
            if (stop == 1){
                break;
            }
            swap = arr[smaller];
            arr[smaller] = arr[bigger];
            arr[bigger] = swap;
            smaller++;
            bigger--;
            if (smaller > bigger){
                smaller--;
                bigger++;
                break;
            }
        }
        quick_sort_recurs(arr, start, smaller);
        quick_sort_recurs(arr, bigger, end);
    } else if (bigger - smaller == 1){
        if (arr[smaller] > arr[bigger]){
            double swap;
            swap = arr[smaller];
            arr[smaller] = arr[bigger];
            arr[bigger] = swap;
        }
    }
    return 0;
}

int quick_sort(double arr[], int n){
    int small = 0, big = n - 1;
    quick_sort_recurs(arr, small, big);
    return 0;
}

int main() {
    int n;
    printf("Enter the number of numbers in the array.\n");
    scanf("%d", &n);
    double arr[n];
    int i = 0;
    double number;
    while (i < n){
        scanf("%lf", &number);
        arr[i] = number;
        i++;
    }
    quick_sort(arr, n);
    printf("finaly!\n");
    print_arr(arr, 0, n);
    return 0;
}
