#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 5
#define TRUE 1
#define FALSE 0

typedef struct circularQueue{
    int data[CAPACITY];
    int front;
    int rear;
} CQueue;

CQueue* createCircularQueue();
void Enqueue(CQueue *CQ, int data);
int isFull(CQueue *CQ);
void ShowQueue(CQueue *CQ);
int isEmpty(CQueue *CQ);
void Dequeue(CQueue *CQ);

int main(){
    CQueue *CQ;
    CQ = createCircularQueue();
    printf("Front : %d, rear : %d\n", CQ->front, CQ->rear);

    printf("Enqueue data 10\n");
    printf("Enqueue data 20\n");
    printf("Enqueue data 30\n");
    Enqueue(CQ, 10);
    Enqueue(CQ, 20);
    Enqueue(CQ, 30);
    ShowQueue(CQ);
    printf("Front : %d, rear : %d\n", CQ->front, CQ->rear);

    printf("Dequeue\n");
    printf("Dequeue\n");
    Dequeue(CQ);
    Dequeue(CQ);
    ShowQueue(CQ);
    printf("Front : %d, rear : %d\n", CQ->front, CQ->rear);

    printf("Enqueue data 40\n");
    Enqueue(CQ, 40);
    printf("Front : %d, rear : %d\n", CQ->front, CQ->rear);
    printf("Enqueue data 50\n");
    Enqueue(CQ, 50);
    printf("Front : %d, rear : %d\n", CQ->front, CQ->rear);
    printf("Enqueue data 60\n");
    Enqueue(CQ, 60);
    printf("Front : %d, rear : %d\n", CQ->front, CQ->rear);
    printf("Enqueue data 70\n");
    Enqueue(CQ, 70);
    printf("Front : %d, rear : %d\n", CQ->front, CQ->rear);
    ShowQueue(CQ);
    return 0;
}

CQueue* createCircularQueue(){
    CQueue *CQ = NULL;

    CQ = (CQueue*)malloc(sizeof(CQueue));
    CQ->front = 0;
    CQ->rear = 0;
    return CQ;
}

void Enqueue(CQueue *CQ, int data){
    if(isFull(CQ)){
        printf("Circular Queue is Full!\n");
        return;
    }
    CQ->rear = (CQ->rear+1)%CAPACITY;
    CQ->data[CQ->rear] = data;
}

int isFull(CQueue *CQ){
    if((CQ->rear+1)%CAPACITY==CQ->front)
        return TRUE;
    else
        return FALSE;
}

void ShowQueue(CQueue *CQ){
    if(isEmpty(CQ)){
        printf("Circular Queue is Empty!\n");
        return;
    }
    printf("**********show queue**********\n");
    for(int i=(CQ->front+1)%CAPACITY; i!=(CQ->rear+1)%CAPACITY; i=(i+1)%CAPACITY){
        printf("[%d]\n", CQ->data[i]);
    }
    printf("******************************\n");
}

int isEmpty(CQueue *CQ){
    if(CQ->front == CQ->rear)
        return TRUE;
    else
        return FALSE;
}

void Dequeue(CQueue *CQ){
    if(isEmpty(CQ)){
        printf("Circular Queue is Empty!\n");
        return;
    }
    CQ->front = (CQ->front+1)%CAPACITY;
}