#include <stdio.h>

int func(){
    printf("Make a guess from 1 to 100.\n");
    int hight = 101, low = 0;
    int middle = (hight + low) / 2;
    char answer;
    while(low != hight - 1){
        printf("Your number is greater than or equal %d?\n", middle);
        scanf("%c", &answer);
        getchar();
        if (answer == 'y'){
            low = middle;
        } else if (answer == 'n'){
            hight = middle;
        } else {
            printf("Please only use the characters 'y' or 'n'!");
            return 0;
        }
        middle = (hight + low) / 2;
    }
    if (middle == 0){
        printf("Make a guess from 1 to 100.");
        return 0;
    }
    printf("Your number is %d!", middle);
    return 0;
}

int main() {
    func();
    return 0;
}
