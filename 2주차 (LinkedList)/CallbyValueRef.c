#include <stdio.h>

void changeVal(int x, int y){
    int tmp;
    tmp = x;
    x = y;
    y = tmp;
    printf("��ȯ �� : %d, %d\n", x, y);
}

void changeRef(int *x, int *y){
    int tmp;
    tmp = *x;
    *x = *y;
    *y = tmp;
    printf("��ȯ �� : %d, %d\n", *x, *y);
}

int main(){
    int option = 0;
    int x = 100, y = 200;
    printf("��ȯ �� : %d, %d\n", x, y);
    
    printf("Option: ");
    scanf("%d", &option);

    if(option == 1){
        changeVal(x, y);    
        printf("��ȯ �� : %d, %d\n", x, y);
    }else if(option == 2){
        changeRef(&x, &y);
        printf("��ȯ �� : %d, %d\n", x, y);
    }
    return 0;
}