#include <stdio.h>

int Factorial(int n){
    if(n==0)
        return 1;
    else
        return n*Factorial(n-1);
}

int main(){
    int val, result;

    printf("정수 입력: ");
    scanf("%d", &val);

    if(val<0){
        printf("0이상의 정수를 입력하시오\n");
        return -1;
    }
    result = Factorial(val);
    printf("%d!의 계산결과 = %d\n", val, result);
    return 0;
}