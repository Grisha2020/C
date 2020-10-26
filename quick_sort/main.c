#include <stdio.h>

int print_arr(double arr[], int start, int end){
    int i = start;
    while (i < end){
        printf("%lf ", arr[i]);
        i++;
    }
    return 0;
}

int quick_sort_recurs(double arr[], int n, int smaller, int bigger){
    if (n > 1){
        int centre = (smaller + bigger) / 2;
        double element = arr[centre];
        double swap;
        int start = smaller;
        int end = bigger;
        print_arr(arr, 0, 7);
        printf(" all\n");
        print_arr(arr, start, end + 1);//--------------------------------------------------------
        printf(" 0\n");
        while (smaller != centre && bigger != centre){
            if (arr[smaller] >= element){
                while (bigger != centre){
                    if (arr[bigger] < element){
                        break;
                    }
                    bigger--;
                }
                if (bigger == centre){
                    break;
                }
                swap = arr[smaller];
                arr[smaller]= arr[bigger];
                arr[bigger] = swap;
                bigger--;
            }
            smaller++;
        }
        print_arr(arr, 0, 7);
        printf(" all\n");
        print_arr(arr, start, end + 1);//--------------------------------------------------------
        printf(" 1\n");
        if (smaller == centre && bigger == centre){
            quick_sort_recurs(arr, (centre - 1) - start, start, centre - 1);
            printf("1.1\n");
            quick_sort_recurs(arr, end - (centre - 1), centre + 1, end);
            printf("1.5,\n");
            return 0;
        }else if (smaller == centre && bigger != centre){
            int prosto = centre + 1;
            while (prosto != bigger){
                if (arr[prosto] >= element){
                    prosto++;
                }else{
                    int diff = prosto - centre;
                    swap = arr[prosto];
                    arr[prosto]= arr[centre];
                    arr[centre] = swap;
                    for (int i=0; i<diff; i++){
                        swap = arr[prosto - i];
                        arr[prosto - i]= arr[prosto - i - 1];
                        arr[prosto - i - 1] = swap;
                    }
                    centre++;
                    prosto = centre + 1;
                }
                print_arr(arr, 0, 7);
                printf(" all\n");
                print_arr(arr, start, end + 1);//----------------------------------------------------
                printf(" 2\n");
            }
            quick_sort_recurs(arr, (centre - 1) - start, start, centre - 1);
            printf("asdfgh\n");
            quick_sort_recurs(arr, end - (centre - 1), centre + 1, end);
            printf("okijl,\n");
            return 0;
        }else if (smaller != centre && bigger == centre){
            int prosto = centre - 1;
            while (prosto != smaller){
                if (arr[prosto] < element){
                    prosto--;
                }else{
                    int diff = centre - prosto;
                    swap = arr[prosto];
                    arr[prosto]= arr[centre];
                    arr[centre] = swap;
                    for (int i=0; i<diff; i++){
                        swap = arr[prosto + i];
                        arr[prosto + i]= arr[prosto + i + 1];
                        arr[prosto + i + 1] = swap;
                    }
                    centre--;
                    prosto = centre - 1;
                }
                print_arr(arr, 0, 7);
                printf(" all\n");
                print_arr(arr, start, end + 1);//------------------------------------------------
                printf(" 3\n");
            }
            quick_sort_recurs(arr, (centre - 1) - start, start, centre - 1);
            printf("asdfgh\n");
            quick_sort_recurs(arr, end - (centre - 1), centre + 1, end);
            printf("okijl,\n");
            return 0;
        }
    }
    printf("qwerty\n");
    return 0;
}

int quick_sort(double arr[], int n){
    int small = 0, big = n - 1;
    quick_sort_recurs(arr, n, small, big);
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
