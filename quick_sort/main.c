#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int double_cmp_asc(const void *elem1, const void *elem2) {
    if (*(double *) elem1 - *(double *) elem2 > 0) {
        return 1;
    } else if (*(double *) elem1 - *(double *) elem2 == 0) {
        return 0;
    } else {
        return -1;
    }
}

int double_cmp_desc(const void *elem1, const void *elem2) {
    if (*(double *) elem2 - *(double *) elem1 > 0) {
        return 1;
    } else if (*(double *) elem2 - *(double *) elem1 == 0) {
        return 0;
    } else {
        return -1;
    }
}

int int_cmp_asc(const void *elem1, const void *elem2) {
    return (*(int *) elem1 - *(int *) elem2);
}

int int_cmp_desc(const void *elem1, const void *elem2) {
    return (*(int *) elem2 - *(int *) elem1);
}

typedef struct Student {
    char *name;
    int age;
} student;

student create_stud(int age, char *name) {
    student stud;
    stud.age = age;
    stud.name = name;
    return stud;
}

int student_cmp_age_asc(const void *student1, const void *student2) {
    student stud1 = *(student *) student1;
    student stud2 = *(student *) student2;
    return (stud1.age - stud2.age);
}

int student_cmp_age_desc(const void *student1, const void *student2) {
    student stud1 = *(student *) student1;
    student stud2 = *(student *) student2;
    return (stud2.age - stud1.age);
}

int student_cmp_name_asc(const void *student1, const void *student2) {
    student stud1 = *(student *) student1;
    student stud2 = *(student *) student2;
    int i = 0;
    while (stud1.name[i] != '\0' || stud2.name[i] != '\0') {
        if (stud1.name[i] > stud2.name[i]) {
            return 1;
        } else if (stud1.name[i] < stud2.name[i]) {
            return -1;
        }
        i++;
    }
    if (stud1.name[i] == '\0' && stud2.name[i] == '\0') {
        return (stud1.age - stud2.age);//Если имя одинаковое, то сортирует по возрасту(по возрастанию)
    } else {
        return (stud1.name[i]-stud2.name[i]);
    }
}

int student_cmp_name_desc(const void *student1, const void *student2) {
    return student_cmp_name_asc(student2, student1);
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

int print_int_arr(int arr[], int start, int end) {
    int i = start;
    while (i < end) {
        printf("%d ", arr[i]);
        i++;
    }
    printf("\n");
    return 0;
}

int print_double_arr(double arr[], int start, int end) {
    int i = start;
    while (i < end) {
        printf("%lf ", arr[i]);
        i++;
    }
    printf("\n");
    return 0;
}

int print_student_arr(student arr[], int start, int end) {
    int i = start;
    while (i < end) {
        printf("%s %d, ", arr[i].name, arr[i].age);//Не красивый вывод(в самом конце вывода будет стоя ть запятая)
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

int quick_sort_recurs(void *left, void *right, size_t size, int (*cmp)(void *, void *)) {
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
    double *arr = malloc(n * sizeof(double));
    int i = 0;
    double number;
    while (i < n) {
        scanf("%lf", &number);
        arr[i] = number;
        i++;
    }
    quick_sort(arr, n, sizeof(double), &double_cmp_asc);
    print_double_arr(arr, 0, n);
    char arr_name1[50] = "Kostya";
    int age1 = 19;
    char arr_name2[50] = "Artem";
    int age2 = 19;
    char arr_name3[50] = "Grisha";
    int age3 = 19;
    student *array = malloc(3 * sizeof(student));
    array[0] = create_stud(age1, arr_name1);
    array[1] = create_stud(age2, arr_name2);
    array[2] = create_stud(age3, arr_name3);
    print_student_arr(array, 0, 3);
    quick_sort(array, 3, sizeof(student), &student_cmp_name_asc);
    print_student_arr(array, 0, 3);
    return 0;
}

