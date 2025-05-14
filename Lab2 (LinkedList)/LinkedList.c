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
        printf("addNode() error2: �߰� ���� �ʰ�\n");
        return FALSE;
    }

    pNewNode = (Node*)malloc(sizeof(Node));
    if(!pNewNode){
        printf("addNode() error3\n");
        return FALSE;
    }

    pNewNode->data = data;
    pNewNode->nextNode = NULL;

    // �߰��� ��ġ ���� ���� �̵�
    pTapNode = &(plist->headNode);
    for(int i=0; i<pos; i++){
        pTapNode = pTapNode->nextNode;
    }

    // �߰� ����� nextNode = ���� ����� nextNode
    // ���� ����� nextNode = �߰� ����� �ּ�
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
    // ������ ��� ���� ��ġ�� �̵�
    for(int i=0; i<pos; i++){
        pTapNode = pTapNode->nextNode;
    }

    // ������ ��� = ���� ����� nextNode
    // ���� ����� nextNode = ������ ����� nextNode
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
    printf("���� Node�� ���� : %d\n", plist->curCount);
    pNode = plist->headNode.nextNode;
    // pNode�� LinkedList�� ������ ������ �̵��ϸ鼭 ���
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
    // head ��尡 ����Ű�� next ��尡 �����ϴ��� Ȯ��
    // plist�� headNode�� ������ TRUE
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
    // ������ ������ Ž��
    while(pNode != NULL){
        // Node�� data�� ��ġ�ϸ� pos return
        if(pNode->data == data){
            return pos;
        }
        // ã�� ���� ��� pos ��ġ�� �̵��ϸ鼭 pNode�� ���� ���� �̵�
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