#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 24
#define TRUE 1
#define FALSE 0

typedef struct node *nodePointer;
typedef struct node{
    int data;
    nodePointer link;
} node;

int main(){
    int out[MAX_SIZE]; // 방문 여부
    nodePointer seq[MAX_SIZE]; // 정점의 연결리스트
    nodePointer x, y, top; // 연결리스트 탐색을 위한 변수
    int i, j, n;
    
    printf("Enter the size (<= %d) ", MAX_SIZE);
    scanf("%d", &n);

    for(i=0; i<n; i++){
        out[i] = TRUE; // 모든 노드를 방문하지 않은 상태로 설정
        seq[i] = NULL; // 인접 리스트 초기화
    }

    printf("Enter a pair of numbers (-1 -1 to quit): ");
    scanf("%d%d", &i, &j);
    while(i>=0){
        /* 양방향 연결이기 때문에 i->j, j->i 둘 다 연결 */
        // 새 노드를 만들어 j를 넣고 i번 노드에 추가
        // ex) 3-7을 연결 (i=3, j=7)
        x = (nodePointer)malloc(sizeof(node));
        x->data = j;
        x->link = seq[i];
        seq[i] = x;

        // 새 노드를 만들어 i를 넣고 j번 노드에 추가
        // ex) 7-3을 연결 (i=3, j=7)
        x = (nodePointer)malloc(sizeof(node));
        x->data = i;
        x->link = seq[j];
        seq[j] = x;

        printf("Enter a pair of numbers (-1 -1 to quit): ");
        scanf("%d%d", &i, &j);
    }

    for(i=0; i<n; i++){
        if(out[i]){
            printf("\nNew Class: %5d", i);

            // 클래스 i를 탐색
            out[i] = FALSE; // 방문 처리
            x = seq[i]; // i의 인접리스트 시작
            top = NULL; // 탐색 stack 초기화
            for(;;){
                while(x){
                    j = x->data; // 다음으로 방문할 정점
                    // 아직 탐색되지 않았다면 위치를 저장하고 새로운 리스트로 이동
                    if(out[j]){
                        printf("%5d", j);
                        out[j] = FALSE; // 방문 처리
                        y = x->link; // y에 backup을 해놓는 이유 : x->link=top으로 바꾸면 잃어버리기 때문
                        x->link = top; // stack에 push
                        top = x; // top update
                        x = y; // 다음 노드로 이동
                    }else{
                        // 이미 탐색되었다면 통과
                        x = x->link;
                    }
                }
                // top이 FALSE이면 전부 탐색한 것 (stack empty)
                if(!top)
                    break;
                // 위치를 저장해두었던 top으로 이동
                x = seq[top->data]; // 다음 탐색 시작 노드로 이동
                top = top->link; // stack pop
            }
        }
    }
    printf("\n");
}

/*
입력 : (3, 7)
입력 : (3, 4)
입력 : (3, 2)

seq[3] -> [data=7 | link=NULL]
seq[3] -> [data=4 | link=0x1000] -> [data=7 | link=NULL]
seq[3] -> [data=2 | link=0x2000] -> [data=4 | link=0x1000] -> [data=7 | link=NULL]
*/