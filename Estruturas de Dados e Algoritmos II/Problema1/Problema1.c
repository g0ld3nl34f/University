#include <stdio.h>

int result = 0;

int count_digits(int N){
    if (N < 10 && N > -10){                     //if the input given by the user has only one
        result += 1;                            //digit or has only one digit left,
    }                                           //result is incremented and returned

    else{
        result += 1;
        count_digits(N/10);                     //recursive call to fuction count_digits
    }                                           //with one less significant digit

    return result;                                           
}

int main() {
    int number;

    scanf("%d", &number);
    printf("%d\n", count_digits(number));

    return 0;
}