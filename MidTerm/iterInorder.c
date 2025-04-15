#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 10
#define EMPTY_STACK -1

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

typedef Node *treePointer;

typedef struct Stack {
    treePointer nodes[MAX_STACK_SIZE];
    int top;
} Stack;

treePointer createNode(int data) {
    treePointer newNode = (treePointer)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

treePointer buildTree(int* arr, int idx, int size){
    if (idx >= size || idx < 0) 
        return NULL;

    treePointer node = createNode(arr[idx]);
    node->left = buildTree(arr, 2*idx + 1, size);
    node->right = buildTree(arr, 2*idx + 2, size);
    return node;
}

int isEmpty(Stack* stack) {
    return stack->top == EMPTY_STACK;
}

int isFull(Stack* stack) {
    return stack->top == MAX_STACK_SIZE - 1;
}

void push(Stack* stack, treePointer node) {
    if (isFull(stack)) {
        return;
    }
    stack->nodes[++stack->top] = node;
}


treePointer pop(Stack* stack) {
    if (isEmpty(stack)) {
        return NULL;
    }
    return stack->nodes[stack->top--];
}


void iterInorder(treePointer node){
    Stack stack;
    stack.top = EMPTY_STACK;

    for(;;){
        for(;node; node=node->left){
            push(&stack, node);
        }
        node = pop(&stack);
        if(!node) 
            break;
        printf("%d ", node->data);
        node = node->right;
    }
}

int main(void){
    int treeData[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int size = sizeof(treeData) / sizeof(treeData[0]);

    treePointer root = buildTree(treeData, 0, size);

    printf("Inorder Traversal: ");
    iterInorder(root);
    printf("\n");

    return 0;
}

/*
         1
       /   \
      2     3
     / \   / \
    4   5 6   7
   /
  8
Inorder Traversal: 8 4 2 5 1 6 3 7
*/