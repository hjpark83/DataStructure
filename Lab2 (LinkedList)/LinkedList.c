#include <stdio.h>
#include "LinkedList.h"

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

    // 추가될 위치 직전 노드로 이동
    pTapNode = &(plist->headNode);
    for(int i=0; i<pos; i++){
        pTapNode = pTapNode->nextNode;
    }

    // 추가 노드의 nextNode = 직전 노드의 nextNode
    // 직전 노드의 nextNode = 추가 노드의 주소
    pNewNode->nextNode = pTapNode->nextNode;
    pTapNode->nextNode = pNewNode;
    plist->curCount++;

    return TRUE;
}

int removeNode(LinkedList *plist, int pos){
    Node *pDelNode = NULL, *pTapNode = NULL;

    if(plist == NULL){
        printf("removeNode() error1\n");
        return FALSE;
    }

    if(pos<0 || pos>plist->curCount){
        printf("removeNOde() error2\n");
        return FALSE;
    }

    pTapNode = &(plist->headNode);
    // 삭제될 노드 직전 위치로 이동
    for(int i=0; i<pos; i++){
        pTapNode = pTapNode->nextNode;
    }

    // 삭제할 노드 = 직전 노드의 nextNode
    // 직전 노드의 nextNode = 삭제할 노드의 nextNode
    pDelNode = pTapNode->nextNode;
    pTapNode->nextNode = pDelNode->nextNode;
    plist->curCount--;

    free(pDelNode);
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
    // pNode가 LinkedList의 마지막 노드까지 이동하면서 출력
    while(pNode != NULL){
        printf("[%d]\n", pNode->data);
        pNode = pNode->nextNode;
    }
    printf("----------------------------\n");
}

int isEmpty(LinkedList *plist){
    if(plist == NULL){
        printf("isEmpty() error\n");
        return -1;
    }
    // head 노드가 가리키는 next 노드가 존재하는지 확인
    // plist에 headNode만 있으면 TRUE
    if(plist->headNode.nextNode == NULL)
        return TRUE;
    else
        return FALSE;
}

int findPos(LinkedList *plist, int data){
    int pos = 0;
    Node *pNode = NULL;

    if(plist == NULL){
        printf("findPos() error\n");
        return FALSE;
    }

    pNode = plist->headNode.nextNode;
    // 마지막 노드까지 탐색
    while(pNode != NULL){
        // Node의 data가 일치하면 pos return
        if(pNode->data == data){
            return pos;
        }
        // 찾지 못한 경우 pos 위치를 이동하면서 pNode를 다음 노드로 이동
        pos++;
        pNode = pNode->nextNode;
    }
    return FALSE;
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

int main(void){
    int pos;
    LinkedList *linkedlist = (LinkedList*)malloc(sizeof(LinkedList));
    initNode(linkedlist);

    showNode(linkedlist);
    addNode(linkedlist, 0, 10);
    addNode(linkedlist, 5, 100);
    addNode(linkedlist, 1, 20);
    addNode(linkedlist, 2, 30);
    addNode(linkedlist, 1, 50);

    showNode(linkedlist);

    removeNode(linkedlist, 1);
    showNode(linkedlist);

    pos = findPos(linkedlist, 30);
    printf("The location of node with data '30' : %d\n", pos);

    makeEmpty(linkedlist);
    showNode(linkedlist);
    return 0;
}