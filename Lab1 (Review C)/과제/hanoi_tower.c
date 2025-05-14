#include <stdio.h>
#include <math.h>

void hanoi(int n, char from, char middle, char to){
    if(n==1){        
        printf("%d�� ������ %c���� %c�� �̵�\n", n, from, to);
    }else{
        hanoi(n-1, from, to, middle);
        printf("%d�� ������ %c���� %c�� �̵�\n", n, from, to);
        hanoi(n-1, middle, from, to);
    }
}

int main(){
    int n;
    printf("������ ������ �Է��Ͻÿ�:");
    scanf("%d", &n);

    hanoi(n, 'A', 'B', 'C');
    
    int total = (int)pow(2,n)-1;
    printf("�� �̵� Ƚ��: %d\n", total);
    return 0;
}