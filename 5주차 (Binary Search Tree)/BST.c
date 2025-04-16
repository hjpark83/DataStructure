#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* leftChild;
    struct Node* rightChild;
} Node;

void initTreeNode(Node** pNode, int value);
void insertTreeNode(Node** p, int value);
void printTreePreorder(Node* pNode);
void printTreeInorder(Node* pNode);
void printTreePostorder(Node* pNode);

int main(){
    Node* pParentNode = NULL;

    insertTreeNode(&pParentNode, 4);
    insertTreeNode(&pParentNode, 2);
    insertTreeNode(&pParentNode, 6);
    insertTreeNode(&pParentNode, 1);
    insertTreeNode(&pParentNode, 3);
    insertTreeNode(&pParentNode, 5);
    insertTreeNode(&pParentNode, 7);

    printf("Preorder : \n");
    printTreePreorder(pParentNode);
    printf("\nInorder : \n");
    printTreeInorder(pParentNode);
    printf("\nPostorder : \n");
    printTreePostorder(pParentNode);
    
    printf("\n");
    return 0;
}

void initTreeNode(Node **pNode, int value){
    (*pNode) = (Node*)malloc(sizeof(Node));
    (*pNode)->data = value;
    (*pNode)->leftChild = NULL;
    (*pNode)->rightChild = NULL;
}

void insertTreeNode(Node** p, int value){
    if((*p) == NULL){
        initTreeNode(&(*p), value);
    }else if((*p)->data > value){
        insertTreeNode(&((*p)->leftChild), value);
    }else{
        insertTreeNode(&((*p)->rightChild), value);
    }
}

void printTreePreorder(Node* pNode){
    if(pNode==NULL)
        return;

    printf("%3d", pNode->data);
    printTreePreorder(pNode->leftChild);
    printTreePreorder(pNode->rightChild);
}

void printTreeInorder(Node* pNode){
    if(pNode == NULL)
        return;

    printTreeInorder(pNode->leftChild);
    printf("%3d", pNode->data);
    printTreeInorder(pNode->rightChild);
}

void printTreePostorder(Node* pNode){
    if(pNode == NULL)
        return;

    printTreePostorder(pNode->leftChild);
    printTreePostorder(pNode->rightChild);
    printf("%3d", pNode->data);
}