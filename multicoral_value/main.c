#include <stdio.h>

int func(double x, double arr[], int n){
    int i = 0, res = 0;
    int degree = 1;
    while (i < n){
        res += arr[i] * degree;
        degree *= x;
        i++;
    }
    printf("%d", res);
    return 0;
}

int main() {
    double x;
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
    printf("Enter the number from which the polynomials want to count.\n");
    scanf("%lf", &x);
    func(x, arr, n);
    return 0;
}
