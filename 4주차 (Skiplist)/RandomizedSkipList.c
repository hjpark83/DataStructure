#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LEVEL 3
#define MIN_DATA -9999

typedef struct SkipNode{
    int data;
    int level;
    struct SkipNode* next[MAX_LEVEL];
}SkipNode;

void InsertSkipNode(SkipNode** pHeadNode, int data);
void ShowSkipNode(SkipNode* pHeadNode);
void SearchSkipNode(SkipNode* pHeadNode, int data);

int main(){
    srand(time(NULL));

    SkipNode* SkipList = (SkipNode*)malloc(sizeof(SkipNode));
    SkipList->level = MAX_LEVEL;
    SkipList->data = MIN_DATA;

    for(int i=0; i<SkipList->level; i++){
        SkipList->next[i] = NULL;
    }

    InsertSkipNode(&SkipList, 3);
    InsertSkipNode(&SkipList, 9);
    ShowSkipNode(SkipList);

    InsertSkipNode(&SkipList, 1);
    InsertSkipNode(&SkipList, 4);
    ShowSkipNode(SkipList);
    
    SearchSkipNode(SkipList, 4);

    InsertSkipNode(&SkipList, 5);
    InsertSkipNode(&SkipList, 7);
    ShowSkipNode(SkipList);

    
    InsertSkipNode(&SkipList, 6);
    InsertSkipNode(&SkipList, 8);
    ShowSkipNode(SkipList);

    InsertSkipNode(&SkipList, 2);
    InsertSkipNode(&SkipList, 10);
    ShowSkipNode(SkipList);

    SearchSkipNode(SkipList, 7);
    return 0;
}

void InsertSkipNode(SkipNode** pHeadNode, int data){
    int level = 1, pos = MAX_LEVEL;
    SkipNode *pTmpNode[MAX_LEVEL];
    SkipNode *pNewNode;

    // MAX LEVEL에서 내려가면서 찾을 temp node의 변수 초기화
    for(int i=0; i<MAX_LEVEL; i++){
        pTmpNode[i] = *pHeadNode;
    }

    for(int i=MAX_LEVEL-1; i>=0; i--){
        // 현재 level에서 집어 넣을 직전 노드의 data가 찾고자 하는 data보다 크면 level 감소
        while(pTmpNode[i]->next[i] != NULL){
            if(pTmpNode[i]->next[i]->data > data)
                break;
            pTmpNode[i] = pTmpNode[i]->next[i];
        }
    }

    // 추가할 노드의 최대 레벨을 계산 (coin flip)
    while(rand()%2){
        level++;
        if(level>=MAX_LEVEL)
            break;
    }

    pNewNode = (SkipNode*)malloc(sizeof(SkipNode));
    pNewNode->level = level;
    pNewNode->data = data;

    for(int i=0; i<MAX_LEVEL; i++){
        pNewNode->next[i] = NULL;
    }

    // 추가할 노드의 level만큼 앞 뒤 연결된 노드들을 연결
    for(int i=pNewNode->level-1; i>=0; i--){
        pNewNode->next[i] = pTmpNode[i]->next[i];
        pTmpNode[i]->next[i] = pNewNode;
    }
    printf("Insert [%d] with level [%d]\n", pNewNode->data, pNewNode->level);
}

void ShowSkipNode(SkipNode* pHeadNode){
    SkipNode* pTmpNode = NULL;

    // Level 별로 끝에 도달할 때까지 데이터 출력
    printf("----------------------------------------------\n");
    for(int i=MAX_LEVEL; i>0; i--){
        pTmpNode = pHeadNode->next[0];
        printf("Level %d:\t", i);
        while(pTmpNode != NULL){
            if(pTmpNode->level >= i){
                printf("%d-----", pTmpNode->data);
            }else{
                printf("------");
            }
            pTmpNode = pTmpNode->next[0];
        }
        printf("NULL\n");
    }
    printf("----------------------------------------------\n");
}

void SearchSkipNode(SkipNode* pHeadNode, int data){
    int pos = MAX_LEVEL-1;
    SkipNode *pTmpNode = pHeadNode->next[pos];

    // 현재 level에 속한 노드가 없거나 data가 찾고자 하는 data보다 큰 경우 level 감소
    while(pTmpNode == NULL || pTmpNode->data > data){
        pTmpNode = pHeadNode->next[--pos];
    }

    printf("Search [%d] : ", data);
    while(pTmpNode->data != data){
        // 탐색을 하다가 Node가 끝나거나 찾고자 하는 data가 없을 경우 level 감소
        if(pTmpNode->next[pos]==NULL || pTmpNode->next[pos]->data > data){
            pos -= 1;
        }else{
            printf("%d, ", pTmpNode->data);
            pTmpNode = pTmpNode->next[pos];
            if(pTmpNode->data == data){
                printf("%d\n", pTmpNode->data);
                return;
            }
        }
    }
    printf("... there is no %d\n", data);
    printf("----------------------------------------------\n");
}