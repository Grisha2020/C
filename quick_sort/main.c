#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

double double_cmp_asc(const void *elem1, const void *elem2) {
    return (*(double *) elem1 - *(double *) elem2);
}

double double_cmp_desc(const void *elem1, const void *elem2) {
    return (*(double *) elem2 - *(double *) elem1);
}

int int_cmp_asc(const void *elem1, const void *elem2) {
    return (*(int *) elem1 - *(int *) elem2);
}

void my_memcopy(void *elem_past, void *elem_copy, size_t size) {
    int i;
    if (&elem_copy > &elem_past && &elem_copy < &elem_past + size) {
        for (i = 0; i < size; i++) {
            ((unsigned char *) elem_past)[size - i] = ((unsigned char *) elem_copy)[size - i];
        }
    } else {
        for (i = 0; i < size; i++) {
            ((unsigned char *) elem_past)[i] = ((unsigned char *) elem_copy)[i];
        }
    }
}

int print_arr(int arr[], int start, int end) {
    int i = start;
    while (i < end) {
        printf("%d ", arr[i]);
        i++;
    }
    printf("\n");
    return 0;
}

int swap(void *elem1, void *elem2, size_t size) {
    void *swapp = malloc(size);
    my_memcopy(swapp, elem1, size);
    my_memcopy(elem1, elem2, size);
    my_memcopy(elem2, swapp, size);
    free(swapp);
    return 0;
}

int quick_sort_recurs(void *left, void *right, size_t size, int (*cmp)(void *, void *)) {//Перед (*cmp) надо ставить
    // тип такой же как у элементов по которым мы будем сортировать, и следовательно компаратор подбирать этого же типа
    if (right - left > size) {
        void *centre;
        if ((right - left) / size % 2 == 0) {
            centre = left + (right - left) / 2;
        } else {
            centre = left + (right - left + size) / 2;
        }
        void *start = left;
        void *end = right;
        while (left < right) {
            if (cmp(left, centre) >= 0 && cmp(right, centre) > 0) {
                while (cmp(right, centre) > 0) {
                    right -= size;
                    if (left >= right) {
                        break;
                    }
                }
            } else if (cmp(left, centre) < 0 && cmp(right, centre) < 0) {
                while (cmp(left, centre) < 0) {
                    left += size;
                    if (left >= right) {
                        break;
                    }
                }
            } else if (cmp(left, centre) < 0 && cmp(right, centre) >= 0) {
                left += size;
                right -= size;
                continue;
            }
            if (left >= right) {
                break;
            }
            swap(left, right, size);
            left += size;
            right -= size;
            if (left > right) {
                left -= size;
                right += size;
                break;
            }
        }
        quick_sort_recurs(start, left, size, cmp);
        quick_sort_recurs(right, end, size, cmp);
    } else if (right - left == size) {
        if (cmp(left, right) > 0) {
            swap(left, right, size);
        }
    }
    return 0;
}

int quick_sort(void *arr, int n, size_t size, void *cmp) {
    void *left = arr;
    void *right = arr + (n - 1) * size;
    quick_sort_recurs(left, right, size, cmp);
    return 0;
}

int test() {
    int n = 6;
    int arr1[6] = {5, 3, 4, 2, 1, 2};
    quick_sort(arr1, n, sizeof(int), &int_cmp_asc);
    int arr2[6] = {5, 3, 4, 2, 1, 2};
    qsort(arr2, 6, sizeof(int), int_cmp_asc);
    int i = 0;
    while (i < n) {
        if ((int) arr1[i] != arr2[i]) { assert(0); }
        i++;
    }
    return 0;
}

int main() {
    test();
    int n;
    printf("Enter the number of numbers in the array.\n");
    scanf("%d", &n);
    int *arr = malloc(n * sizeof(int));
    int i = 0;
    int number;
    while (i < n) {
        scanf("%d", &number);
        arr[i] = number;
        i++;
    }
    quick_sort(arr, n, sizeof(int), &int_cmp_asc);
    print_arr(arr, 0, n);
    return 0;
}

