#include <stdio.h>

int Factorial(int n){
    if(n==0)
        return 1;
    else
        return n*Factorial(n-1);
}

int main(){
    int val, result;

    printf("���� �Է�: ");
    scanf("%d", &val);

    if(val<0){
        printf("0�̻��� ������ �Է��Ͻÿ�\n");
        return -1;
    }
    result = Factorial(val);
    printf("%d!�� ����� = %d\n", val, result);
    return 0;
}