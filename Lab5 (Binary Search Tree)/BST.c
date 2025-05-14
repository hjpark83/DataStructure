#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* leftChild;
    struct Node* rightChild;
} Node;

void initTreeNode(Node** pNode, int value);
void insertTreeNode(Node** p, int value);
void deleteTreeNode(Node** p, int value);
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

    printf("After Inserting:");
    printf("\n  Preorder : ");
    printTreePreorder(pParentNode);
    printf("\n  Inorder : ");
    printTreeInorder(pParentNode);
    printf("\n  Postorder : ");
    printTreePostorder(pParentNode);
    
    printf("\n-----------------------------------");
    
    deleteTreeNode(&pParentNode, 4); // 루트 노드 삭제
    printf("\nAfter deleting 4:");
    
    printf("\n  Preorder : ");
    printTreePreorder(pParentNode);
    printf("\n  Inorder : ");
    printTreeInorder(pParentNode);
    printf("\n  Postorder : ");
    printTreePostorder(pParentNode);
    
    printf("\n");

    deleteTreeNode(&pParentNode, 1); // 자식 노드가 없는 경우
    printf("\nAfter deleting 1:");
    printf("\n  Preorder : ");
    printTreePreorder(pParentNode);
    printf("\n  Inorder : ");
    printTreeInorder(pParentNode);
    printf("\n  Postorder : ");
    printTreePostorder(pParentNode);
    printf("\n");

    deleteTreeNode(&pParentNode, 6); // 자식 노드가 하나인 경우
    
    printf("\nAfter deleting 6:");    
    printf("\n  Preorder : ");
    printTreePreorder(pParentNode);
    printf("\n  Inorder : ");
    printTreeInorder(pParentNode);
    printf("\n  Postorder : ");
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

void deleteTreeNode(Node** p, int value){
    if((*p) == NULL){
        return;
    }

    if((*p)->data > value){
        deleteTreeNode(&((*p)->leftChild), value);
    }else if((*p)->data < value){
        deleteTreeNode(&((*p)->rightChild), value);
    }else{
        Node *tmp = NULL;
    
        if((*p)->leftChild == NULL && (*p)->rightChild == NULL){
            free(*p);
            *p = NULL;
        }else if((*p)->leftChild == NULL){
            tmp = *p;
            *p = (*p)->rightChild;
            free(tmp);
        }else if((*p)->rightChild == NULL){
            tmp = *p;
            *p = (*p)->leftChild;
            free(tmp);
        }else{
            Node* minNode = (*p)->rightChild;
            while(minNode->leftChild != NULL){
                minNode = minNode->leftChild;
            }
            (*p)->data = minNode->data;
            deleteTreeNode(&((*p)->rightChild), minNode->data);
        }
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