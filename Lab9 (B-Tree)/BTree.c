#include <stdio.h>
#include <stdlib.h>

#define M_WAY 3

typedef struct BTNode{
    int n;                          // key의 개수로 pointer 개수보다 1 작음
    int isLeaf;                     // leaf node인 경우 1
    int isRoot;                     // root node인 경우 1
    int keys[M_WAY];                // 3-Way B-Tree이기 때문에 최대 2개의 키값을 갖지만
                                    // split을 용이하게 하기 위해 1개의 여유 키값을 갖도록 선언
    struct BTNode* childs[M_WAY+1]; // child node pointer의 개수도 같은 이유로 +1
} BTNode;

BTNode* initBTNode();
BTNode* BTInsert(BTNode* root, int key);
BTNode* splitChild(BTNode* root);
void inorderTraversal(BTNode* root);

BTNode* initBTNode(){
    BTNode* newBTNode = (BTNode*)malloc(sizeof(BTNode));
    
    newBTNode->n = 0;
    newBTNode->isLeaf = 1;    // 삽입할 때는 무조건 leaf 노드로 삽입되기 떄문
    newBTNode->isRoot = 0;

    for(int i=0; i<M_WAY+1; i++)
        newBTNode->childs[i] = NULL;    // Pointer 초기화

    return newBTNode;
}

BTNode* BTInsert(BTNode* root, int key){
    int pos, mid;
    BTNode* split;

    // 해당 노드가 leaf 노드일 때
    if(root->isLeaf){
        // 노드의 키 값들 중 key가 들어갈 위치 탐색 ex) 3,7 <- 5 삽입
        for(pos=0; pos<root->n; pos++)
            if(root->keys[pos] > key)
                break;

        // 정렬을 통해 위치를 맞춰주고 pos 위치에 key를 삽입
        for(int i=root->n; i>pos; i--)
            root->keys[i] = root->keys[i-1];
        root->keys[pos] = key;
        root->n++;

        // insertion 수행 후 노드의 키 값의 개수가 다 찼을 때
        // 해당 노드가 root 노드인 경우에만 split 수행
        if(root->n == M_WAY && root->isRoot)
            return splitChild(root);
        // 그냥 leaf 노드인 경우 상위 함수에서 split 수행
        return root;
    }else{ // leaf 노드가 아닌 경우
        // 노드의 키 값들 중 key가 들어갈 위치 탐색
        for(pos=0; pos<root->n; pos++)
            if(root->keys[pos]>key)
                break;
        // 해당 위치에 존재하는 child 노드로 들어가 leaf 노드까지 탐색
        root->childs[pos] = BTInsert(root->childs[pos], key);

        // insertion 수행 후 child 노드의 키의 개수가 다 찼을 때
        if(root->childs[pos]->n == M_WAY){
            // child 노드에 대해 split 수행
            split = splitChild(root->childs[pos]);
            // split 수행 후 적절하게 parent 노드에 추가
            for(int i = root->n; i > pos; i--){
                root->keys[i] = root->keys[i-1];
                root->childs[i+1] = root->childs[i];
            }

            // 새로운 key와 child 노드를 parent 노드에 삽입
            root->keys[pos] = split->keys[0];
            root->n++;
            root->childs[pos] = split->childs[0];
            root->childs[pos+1] = split->childs[1];
        }
        // 최종적으로 root 노드가 실제 b-tree의 root 노드인 경우 중에
        // 키의 개수가 다 찼을 때 split 수행
        if(root->n==M_WAY && root->isRoot)
            return splitChild(root);
        return root;
    }
}

BTNode* splitChild(BTNode* root){
    int i, mid;
    // root 노드를 split 하게 되면
    //          newParent
    // root                 newSibling
    // 형태로 split이 일어나게끔 수행
    BTNode* newParent;
    BTNode* newSibling;

    newParent = initBTNode();
    newParent->isLeaf = 0;
    // root 노드가 실제 root 노드였다면
    // newParent 노드가 실제 root 노드가 된다
    if(root->isRoot)
        newParent->isRoot = 1;
    root->isRoot = 0;

    // newSibling 노드는 root와 같은 level 상에 존재한다
    newSibling = initBTNode();
    newSibling->isLeaf = root->isLeaf;

    // root 노드의 중간 지점을 정하고
    // 오른쪽 key 값들은 newSibling 노드로 이동
    mid = (M_WAY-1)/2;
    for(i=mid+1; i<M_WAY; i++){ // 오른쪽 key 값 탐색
        // mid+1을 빼주는 이유 : newSibling의 index는 0부터 시작
        newSibling->childs[i-(mid+1)] = root->childs[i];
        newSibling->keys[i-(mid+1)] = root->keys[i];
        newSibling->n++;

        root->childs[i] = NULL;
        root->keys[i] = 0;
        root->n--;
    }
    // 이 때 child node pointer는 키 값보다 1개 많으므로
    // for문이 끝난 후 한번 더 수행
    newSibling->childs[i-(mid+1)] = root->childs[i];
    root->childs[i] = NULL;

    // root 노드에 중간에 위치했던 key 값을 newParent 노드로 이동
    newParent->keys[0] = root->keys[mid];
    newParent->n++;

    root->keys[mid] = 0;
    root->n--;

    // newParent 노드의 child 노드로 root, newSibling 노드를 연결
    newParent->childs[0] = root;
    newParent->childs[1] = newSibling;
    return newParent;
}

void inorderTraversal(BTNode* root){
    int i;
    printf("\n");
    for(i=0; i<root->n; i++){
        // leaf 노드가 아니라면 밑으로 탐색
        if(!(root->isLeaf)){
            inorderTraversal(root->childs[i]);
            printf("  ");
        }
        // 데이터를 출력
        printf("%d", root->keys[i]);
    }
    // key 값보다 child 노드가 한개 더 많으므로
    // 마지막 child 노드에 대해 밑으로 탐색
    if(!(root->isLeaf)){
        inorderTraversal(root->childs[i]);
    }
    printf("\n");
}

int main(){
    BTNode* root;
    int n, t;

    root = initBTNode();
    root->isRoot = 1;

    printf("Number of input data: ");
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        printf("Input data: ");
        scanf("%d", &t);
        root = BTInsert(root, t);
    }
    printf("Print tree. \n");
    inorderTraversal(root);

    return 0;
}