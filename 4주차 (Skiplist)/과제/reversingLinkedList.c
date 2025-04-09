#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

// Node 구조체
typedef struct Node{
    int data;
    struct Node *nextNode;
}Node;

// Reverse Linkedlist 저장용
typedef struct StackNode{
    int data;
    struct StackNode *nextNode;
}StackNode;

// LinkedList 구조체
typedef struct LinkedList{
    int curCount;
    Node headNode;
}LinkedList;

void initNode(LinkedList *plist);
int addNode(LinkedList *plist, int pos, int data);
void showNode(LinkedList *plist);
void makeEmpty(LinkedList *plist);
void reverseList(LinkedList *plist, StackNode **top);

int main(void){
    int pos;
    LinkedList *linkedlist = (LinkedList*)malloc(sizeof(LinkedList));
    initNode(linkedlist);

    StackNode *top = NULL;
    StackNode *pNode;

    showNode(linkedlist);
    addNode(linkedlist, 0, 10);
    addNode(linkedlist, 5, 100);
    addNode(linkedlist, 1, 20);
    addNode(linkedlist, 2, 30);
    addNode(linkedlist, 1, 50);
    addNode(linkedlist, 1, 70);
    addNode(linkedlist, 1, 40);

    showNode(linkedlist);

    reverseList(linkedlist, &top);

    showNode(linkedlist);
    
    makeEmpty(linkedlist);
    showNode(linkedlist);
    return 0;
}

void initNode(LinkedList *plist){
    plist->curCount = 0;
    plist->headNode.nextNode = NULL;
}

int addNode(LinkedList *plist, int pos, int data){
    Node *pNewNode = NULL, *pTapNode = NULL;
    if(plist == NULL){
        printf("addNode() error1\n");
        return FALSE;
    }
    if(pos<0 || pos>plist->curCount){
        printf("addNode() error2: 추가 범위 초과\n");
        return FALSE;
    }

    pNewNode = (Node*)malloc(sizeof(Node));
    if(!pNewNode){
        printf("addNode() error3\n");
        return FALSE;
    }

    pNewNode->data = data;
    pNewNode->nextNode = NULL;

    pTapNode = &(plist->headNode);
    for(int i=0; i<pos; i++){
        pTapNode = pTapNode->nextNode;
    }

    pNewNode->nextNode = pTapNode->nextNode;
    pTapNode->nextNode = pNewNode;
    plist->curCount++;

    return TRUE;
}

void showNode(LinkedList *plist){
    Node *pNode = NULL;

    if(plist == NULL){
        printf("showNode() error\n");
        return;
    }
    printf("현재 Node의 개수 : %d\n", plist->curCount);
    pNode = plist->headNode.nextNode;
    
    while(pNode != NULL){
        printf("[%d]\n", pNode->data);
        pNode = pNode->nextNode;
    }
    printf("----------------------------\n");
}

void makeEmpty(LinkedList *plist){
    Node *pDummyNode = NULL, *pTapNode = NULL;
    if(plist != NULL){
        pTapNode = plist->headNode.nextNode;
        while(pTapNode != NULL){
            pDummyNode = pTapNode;
            pTapNode = pTapNode->nextNode;
            free(pDummyNode);
        }
        plist->headNode.nextNode = NULL;
    }
}

void reverseList(LinkedList *plist, StackNode **top){
    Node *pNode = NULL;
    StackNode *sNode = NULL;

    printf("Reverse Linked List!\n");
    // Stack에 List 저장
    pNode = plist->headNode.nextNode;
    while(pNode != NULL){
        sNode = (StackNode*)malloc(sizeof(StackNode));
        sNode->data = pNode->data;
        sNode->nextNode = *top;
        *top = sNode;

        pNode = pNode->nextNode;
    }
    // List에 Stack 저장
    pNode = plist->headNode.nextNode;
    while(*top != NULL && pNode != NULL){
        pNode->data = (*top)->data;

        sNode = *top;
        *top = (*top)->nextNode;
        free(sNode);

        pNode = pNode->nextNode;
    }
}