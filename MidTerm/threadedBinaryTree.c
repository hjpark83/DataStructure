#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct Node{
    int data;
    struct Node* left;
    struct Node* right;
    int rightThread;
    int leftThread;
} Node;

typedef Node* threadedPointer;

threadedPointer createNode(int data) {
    threadedPointer newNode = (threadedPointer)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->rightThread = FALSE;
    newNode->leftThread = FALSE;
    return newNode;
}

void createThreadedBinaryTreeUtil(threadedPointer current, threadedPointer* prev) {
    if (current == NULL) return;

    createThreadedBinaryTreeUtil(current->left, prev);

    if (current->left == NULL) {
        current->left = *prev;
        current->leftThread = TRUE;
    }

    if (*prev && (*prev)->right == NULL) {
        (*prev)->right = current;
        (*prev)->rightThread = TRUE;
    }

    *prev = current;

    createThreadedBinaryTreeUtil(current->right, prev);
}

void createThreadedBinaryTree(threadedPointer root) {
    threadedPointer prev = NULL;
    createThreadedBinaryTreeUtil(root, &prev);
}

threadedPointer buildTree(int* arr, int idx, int size){
    if (idx >= size || idx < 0) 
        return NULL;

    threadedPointer node = createNode(arr[idx]);
    node->left = buildTree(arr, 2*idx + 1, size);
    node->right = buildTree(arr, 2*idx + 2, size);
    return node;
}

threadedPointer insucc(threadedPointer node){
    if (node == NULL) return NULL;

    if (node->rightThread) {
        return node->right;
    }

    node = node->right;
    while (node && !node->leftThread) {
        node = node->left;
    }
    return node;
}

void tinorder(threadedPointer root) {
    threadedPointer current = root;

    while (current && !current->leftThread) {
        current = current->left;
    }

    while (current) {
        printf("%3d ", current->data);
        current = insucc(current);
    }
}

void insertRight(threadedPointer node, threadedPointer newNode) {
    if (node == NULL || newNode == NULL) 
        return;

    newNode->right = node->right;
    newNode->rightThread = TRUE;
    newNode->left = node;
    newNode->leftThread = TRUE;

    node->right = newNode;
    node->rightThread = FALSE;

    if (newNode->right && newNode->right->leftThread && newNode->right->left == node) {
        newNode->right->left = newNode;
    }
}

threadedPointer findNode(threadedPointer root, int value) {
    threadedPointer current = root;
    while (current && !current->leftThread) {
        current = current->left;
    }

    while (current) {
        if (current->data == value) return current;
        current = insucc(current);
    }

    return NULL;
}

void process(threadedPointer root, int* arr){
    printf("Inorder Traversal of the Threaded Binary Tree:\n");
    tinorder(root);
    printf("\n");

    int num, targetValue;
    printf("Enter a number to insert: ");
    scanf("%d", &num);

    while(1){
        printf("Enter the value of the node to insert to its right: ");
        scanf("%d", &targetValue);
        threadedPointer targetNode = findNode(root, targetValue);
        if(targetNode->rightThread == FALSE){
            printf("Cannot insert: right child already exists.\n");
            printf("Please enter a valid node value\n");
            continue;
        }
        if (!targetNode) {
            printf("Node %d not found in the tree.\n", targetValue);
            printf("Please enter a valid node value: ");
        } else {
            threadedPointer newNode = createNode(num);
            printf("Inserting %d as the right child of node %d...\n", num, targetValue);
            insertRight(targetNode, newNode);
            printf("Inorder Traversal after insertion:\n");
            tinorder(root);
            printf("\n");
            break;
        }   
    }
}

int main(void){
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int size = sizeof(arr) / sizeof(arr[0]);
    threadedPointer root = buildTree(arr, 0, size);

    createThreadedBinaryTree(root);

    process(root, arr);
    return 0;
}
