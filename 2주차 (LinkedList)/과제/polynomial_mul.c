#define _CRT_SECURE_NO_WARNINGS
//#pragma warning(disable:4996)

#define BUFFSIZE 1024

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct polyTerm {
    int order;
    int coeff;
    struct polyTerm* nextNode;
}polyTerm;


typedef struct poly {
    polyTerm headNode;
} poly;

void initPoly(poly *A){
    A->headNode.coeff = 0;
    A->headNode.order = 0;
    A->headNode.nextNode = NULL;
}

void clearPoly(poly* A) {
    polyTerm* pTapNode = &(A->headNode);
    polyTerm* pDelNode = NULL;
    
    while(pTapNode->nextNode != NULL){
        pDelNode = pTapNode->nextNode;
        pTapNode->nextNode = pDelNode->nextNode;
        free(pDelNode);
    }
}

void printPoly_impl(poly A, char* buffer) {
    int isFirst = 1; // 첫 번째 항인지 여부 -> 첫번째 항이면 앞에 +를 붙일 필요 X
    polyTerm* pTapNode = A.headNode.nextNode;
    
    while(pTapNode != NULL){
        char tmp[BUFFSIZE] = "";
        if(pTapNode->coeff > 0){
            if(isFirst){
                sprintf(tmp, "%dx^%d", pTapNode->coeff, pTapNode->order);
                isFirst = 0;
            }else{
                sprintf(tmp, "+%dx^%d", pTapNode->coeff, pTapNode->order);
            }
            strcat(buffer, tmp);
        }else if(pTapNode->coeff < 0){
            sprintf(tmp, "%dx^%d", pTapNode->coeff, pTapNode->order);
            strcat(buffer, tmp);
        }
        pTapNode = pTapNode->nextNode;
    }

    if(isFirst){
        sprintf(buffer, "0");
    }
}

void printPoly(poly A) {
	char buffer[BUFFSIZE] = "";
	printPoly_impl(A, buffer);
	printf(buffer);
}

void addTerm(poly* A, int exp, int coeff) {
    if(coeff == 0)
        return;
    
    polyTerm *pTapNode = &(A->headNode);

    // 새로 추가하는 노드의 차수에 맞게 위치시키기 위함
    while(pTapNode->nextNode != NULL && pTapNode->nextNode->order > exp){
        pTapNode = pTapNode->nextNode;
    }

    // 계수가 같은 노드가 없는 경우 새 노드 추가
    if(pTapNode->nextNode == NULL || pTapNode->nextNode->order != exp){
        polyTerm *newNode = (polyTerm*)malloc(sizeof(polyTerm));
        newNode->coeff = coeff;
        newNode->order = exp;
        newNode->nextNode = pTapNode->nextNode;
        pTapNode->nextNode = newNode;
    }else{
        pTapNode->nextNode->coeff += coeff;     // 계수가 같으면 더해주기만 하면 됨
        
        if(pTapNode->nextNode->coeff == 0){     // 계수를 더한 결과가 0인 경우 해당 노드를 제거
            polyTerm *tmp = pTapNode->nextNode;
            pTapNode->nextNode = tmp->nextNode;
            free(tmp);
        }
    }
}

poly multiPoly(poly A, poly B) {
    poly res;
    
    initPoly(&res);
    polyTerm* pTapNodeA = A.headNode.nextNode;
    
    while(pTapNodeA != NULL){
        polyTerm* pTapNodeB = B.headNode.nextNode;
        while(pTapNodeB != NULL){
            addTerm(&res, pTapNodeA->order + pTapNodeB->order, pTapNodeA->coeff * pTapNodeB->coeff);
            pTapNodeB = pTapNodeB->nextNode;
        }
        pTapNodeA = pTapNodeA->nextNode;
    }
    return res;
}

int main() {
	poly A, B;
    initPoly(&A);
    initPoly(&B);

    addTerm(&A, 1, 1);
    addTerm(&A, 0, 1);
    printf("poly A: ");
    printPoly(A);
    printf("\n");

    addTerm(&B, 1, 1);
    addTerm(&B, 0, -1);
    printf("poly B: ");
    printPoly(B);
    printf("\n");

    printf("A*B: ");
    printPoly(multiPoly(A, B));

	return 0;
}
