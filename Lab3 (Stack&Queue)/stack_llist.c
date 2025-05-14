#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct StackNode{
    int data;
    struct StackNode* next;
}StackNode;

void pushLinkedStack(StackNode** top, int data);
StackNode* popLinkedStack(StackNode** top);
void showLinkedStack(StackNode* top);
StackNode* topLinkedStack(StackNode* top);
void deleteLinkedStack(StackNode** top);
int isEmpty(StackNode* top);

int main(){
    StackNode *top = NULL;
    StackNode *pNode;

    printf("Push(10,20,30) called\n");
    pushLinkedStack(&top, 10);
    pushLinkedStack(&top, 20);
    pushLinkedStack(&top, 30);
    showLinkedStack(top);

    printf("Pop() called\n");
    pNode = popLinkedStack(&top);
    if(pNode){
        free(pNode);
        showLinkedStack(top);
    }

    printf("Top() called\n");
    pNode = topLinkedStack(top);
    if(pNode){
        printf("Top node's data = %d\n", pNode->data);
    }else{
        printf("The Stack is empty\n");
    }
    showLinkedStack(top);

    deleteLinkedStack(&top);
    return 0;
}

// double pointer : pointer의 pointer
void pushLinkedStack(StackNode** top, int data){
    StackNode *pNode = NULL;
    
    pNode = (StackNode*)malloc(sizeof(StackNode));
    
    pNode->data = data;
    pNode->next = NULL;

    if(isEmpty(*top)){
        *top = pNode;
    }else{
        pNode->next = *top;
        *top = pNode;
    }
}

StackNode* popLinkedStack(StackNode** top){
    StackNode *pNode = NULL;

    if(isEmpty(*top)){
        printf("The Stack is empty\n");
        return NULL;
    }
    pNode = *top;
    *top = pNode->next;
    return pNode;
}

void showLinkedStack(StackNode* top){
    StackNode *pNode = NULL;
    if(isEmpty(top)){
        printf("The Stack is Empty\n");
    }

    pNode = top;
    printf("**********Show Stack**********\n");
    while(pNode != NULL){
        printf("[%d]\n", pNode->data);
        pNode = pNode->next;
    }
    printf("******************************\n");
}

StackNode* topLinkedStack(StackNode* top){
    StackNode *pNode = NULL;

    if(!isEmpty(top))
        pNode = top;
    return pNode;
}

void deleteLinkedStack(StackNode** top){
    StackNode *pNode = NULL, *pDelNode = NULL;
    pNode = *top;

    while(pNode != NULL){
        pDelNode = pNode;
        pNode = pNode->next;
        free(pDelNode); // free를 지울떄마다 해줘야 메모리 공간이 비워짐
    }
    *top = NULL;
}

int isEmpty(StackNode* top){
    if(top == NULL)
        return TRUE;
    else
        return FALSE;
}
