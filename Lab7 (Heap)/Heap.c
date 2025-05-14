#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_NODES 50
typedef struct Heap{
    int nodes[MAX_NODES];
    int lastIndex;
} Heap;

void initHeap(Heap* heap);
void insertData(Heap* heap, int data);
void printHeap(Heap* heap);
void deleteData(Heap* heap);

int main(){
    Heap heap;

    initHeap(&heap);

    insertData(&heap, 1);
    insertData(&heap, 3);
    insertData(&heap, 8);
    insertData(&heap, 13);
    insertData(&heap, 4);
    insertData(&heap, 10);
    insertData(&heap, 6);

    printHeap(&heap);

    deleteData(&heap);
    printHeap(&heap);

    deleteData(&heap);
    printHeap(&heap);

    return 0;
}

void initHeap(Heap* heap){
    for(int i=0; i<MAX_NODES; i++){
        heap->nodes[i] = 0;
    }
    heap->lastIndex = 0;
}

void printHeap(Heap* heap){
    int cnt, newLineIndex;
    cnt = 1;
    newLineIndex = 0;

    for(int i=1; i<=heap->lastIndex; i++){
        printf("%d\t", heap->nodes[i]);

        if(pow(2, newLineIndex) == cnt){
            printf("\n");
            newLineIndex++;
            cnt = 0;
        }
        cnt++;
    }
    printf("\n\n");
}

void insertData(Heap* heap, int data){
    int idx, parentIdx;
    // heap이 가득 차 있는지 검사
    if(heap->lastIndex == MAX_NODES-1){
        printf("Heap is full\n");
        return;
    }

    // heap에 node를 확장시켜 데이터를 추가
    heap->lastIndex++;
    idx = heap->lastIndex;

    // 부모 노드의 데이터를 확인해가면서 update
    while((idx != 1) && (data > heap->nodes[idx/2])){
        heap->nodes[idx] = heap->nodes[idx/2]; // 부모 노드를 자식 노드에 복사
        idx /= 2;
    }
    heap->nodes[idx] = data;
}

void deleteData(Heap *heap){
    int tmp, parentIdx, childIdx;
    // heap이 비어있는지 검사
    if(heap->lastIndex == 0){
        printf("Heap is empty\n");
        return;
    }

    // root node에만 데이터가 존재하는 경우
    if(heap->lastIndex == 1){
        heap->nodes[heap->lastIndex] = 0;
        heap->lastIndex = 0;
        return;
    }

    // heap의 마지막 node의 데이터를 임시 변수에 저장
    tmp = heap->nodes[heap->lastIndex];
    heap->nodes[heap->lastIndex] = 0;
    heap->lastIndex--;
    
    parentIdx = 1;
    childIdx = 2;

    // root node부터 시작해서 자식 노드들의 데이터 값과 비교하며 update
    while(childIdx <= heap->lastIndex){
        // sibling node 중 값이 큰 node를 선택
        if(heap->nodes[childIdx] < heap->nodes[childIdx+1]){
            childIdx++;
        }

        // 부모 노드와 자식 노드의 값을 비교
        if(tmp > heap->nodes[childIdx]){
            break;
        }

        // 자식 node의 값이 더 클 경우 부모 node와 교체
        heap->nodes[parentIdx] = heap->nodes[childIdx];
        parentIdx = childIdx;
        childIdx *= 2;
    }
    heap->nodes[parentIdx] = tmp;
}