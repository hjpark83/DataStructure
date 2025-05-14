#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int key;
    int value;
    struct Node* leftChild;
    struct Node* rightChild;
}Node;

void insertTreeNode(Node** p, int key, int value);
void printTreeInorder(Node* p);
void deleteTreeNode(Node** p, int key);

void threeWayJoin(Node* mid, Node* small, Node* big);
void splitTree(Node* root, int key, Node** small, Node** mid, Node** big);

int main(void){
    Node* pParentNode = NULL;
    Node* left = NULL, *mid = NULL, *right = NULL;
    Node* joined = NULL;

    insertTreeNode(&pParentNode, 15, 100);
    insertTreeNode(&pParentNode, 10, 200);
    insertTreeNode(&pParentNode, 20, 300);
    insertTreeNode(&pParentNode, 17, 400);
    insertTreeNode(&pParentNode, 22, 500);

    printTreeInorder(pParentNode);
    printf("--------------------------\n");

    // Degree가 1인 노드를 삭제하는 경우
    deleteTreeNode(&pParentNode, 10);
    printTreeInorder(pParentNode);
    printf("--------------------------\n");

    // root 노드를 삭제하는 경우
    deleteTreeNode(&pParentNode, 15);
    printTreeInorder(pParentNode);
    printf("--------------------------\n");

    // Tree를 split하고 Join
    splitTree(pParentNode, 20, &left, &mid, &right);
    joined = mid;
    threeWayJoin(joined, left, right);
    printTreeInorder(joined);

    return 0;
}

void insertTreeNode(Node** p, int key, int value){
    if((*p) == NULL){
        (*p) = (Node*)malloc(sizeof(Node));
        (*p)->key = key;
        (*p)->value = value;
        (*p)->leftChild = NULL;
        (*p)->rightChild = NULL;
    }else if((*p)->key > key){
        insertTreeNode(&((*p)->leftChild), key, value);
    }else{
        insertTreeNode(&((*p)->rightChild), key, value);
    }
}

void printTreeInorder(Node* p){
    if(p == NULL)
        return;
    printTreeInorder(p->leftChild);
    printf("Key: %d, Value: %d\n", p->key, p->value);
    printTreeInorder(p->rightChild);
}

void deleteTreeNode(Node** p, int key){
    Node* pNode = *p;
    Node* pParent = NULL;
    Node* child = NULL;
    Node* successor = NULL;
    Node* successorParent = NULL;

    // key를 찾을 떄 까지 반복
    while(pNode != NULL && pNode->key != key){
        pParent = pNode;
        if(key < pNode->key)
            pNode = pNode->leftChild;
        else
            pNode = pNode->rightChild;
    }

    // key를 찾지 못한 경우    
    if(pNode == NULL)
        return;

    /* Degree가 0인 경우 (leaf node)
       해당 위치의 노드만 해제하고
       pParent의 left/right child를 NULL로 선언 */
    if(pNode->leftChild == NULL && pNode->rightChild == NULL){
        if(pParent == NULL){
            free(*p);
            *p = NULL;
        }else if(pParent->leftChild == pNode){
            free(pParent->leftChild);
            pParent->leftChild = NULL;
        }else{
            free(pParent->rightChild);
            pParent->rightChild = NULL;
        }
    }
    /* Degree가 1인 경우 (Child node가 1개만 있는 경우)
       pParent - pNode - child 노드 순으로 지정한 뒤
       pNode를 해제하고 pParent의 left/right child를 child로 지정 */
    else if(pNode->leftChild == NULL || pNode->rightChild == NULL){
        if(pNode->leftChild != NULL)
            child = pNode->leftChild;
        else
            child = pNode->rightChild;

        if(pParent == NULL){
            free(*p);
            *p = child;
        }else if(pParent->leftChild == pNode){
            free(pParent->leftChild);
            pParent->leftChild = child;
        }else{
            free(pParent->rightChild);
            pParent->rightChild = child;
        }
    }
    /* Degree가 2인 경우 (양쪽 child가 둘 다 있는 경우)
                    pNode                              successor
                        \                                   \
                        rightChild                      rightChild
                        /                                   /
                      ...              ==>                ...
                      /                                   /
                successorParent                     successorParent 
                    /
            successor

       pNode의 rightChild 중에서 가장 작은 값 (leftmost node)을 찾은 뒤
       해당 위치의 key, value를 pNode에 복사 
       그 뒤 원래 successor 위치의 노드를 제거 (leaf node) */
    else{
        successor = pNode->rightChild;
        successorParent = pNode;

        while(successor->leftChild != NULL){
            successorParent = successor;
            successor = successor->leftChild;
        }

        // successor의 데이터를 복사
        pNode->key = successor->key;
        pNode->value = successor->value;

        // successor를 제거 (successor는 leaf 또는 child 하나로 가정)
        if(successorParent->leftChild == successor){
            successorParent->leftChild = successor->rightChild;
        }else{
            successorParent->rightChild = successor->rightChild;
        }
        free(successor);
    }

}

void threeWayJoin(Node* mid, Node* small, Node* big){
    if(mid == NULL)
        return;
    mid->leftChild = small;
    mid->rightChild = big;
}

void splitTree(Node* root, int key, Node** small, Node** mid, Node** big){
    if(root == NULL){
        *small = *mid = *big = NULL;
    }

    if(key < root->key){
        splitTree(root->leftChild, key, small, mid, &(root->leftChild));
        *big = root;
    }else if(key > root->key){
        splitTree(root->rightChild, key, &(root->rightChild), mid, big);
        *small = root;
    }else{
        *mid = root;
        *small = root->leftChild;
        *big = root->rightChild;
    }
}