#include <stdio.h>
#include <stdlib.h>
#define Max(x,y) ((x)>(y)?(x):(y))

typedef struct AvlNode{
    int data;
    struct AvlNode *left, *right;
    int Height;
} AvlNode;

int height(AvlNode *node){
    if(node == NULL)
        return -1;
    else
        return node->Height;
}

AvlNode *rotateLL(AvlNode* parent){
    AvlNode *child = parent->left;
    parent->left = child->right;
    child->right = parent;

    parent->Height = Max(height(parent->left), height(parent->right)) + 1;
    child->Height = Max(height(child->left), height(child->right)) + 1;
    
    return child;
}

AvlNode *rotateRR(AvlNode* parent){
    AvlNode *child = parent->right;
    parent->right = child->left;
    child->left = parent;
    
    parent->Height = Max(height(parent->left), height(parent->right)) + 1;
    child->Height = Max(height(child->left), height(child->right)) + 1;
    
    return child;
}

AvlNode* rotateLR(AvlNode *parent){
    AvlNode *child = parent->left;
    parent->left = rotateRR(child);
    return rotateLL(parent);
}

AvlNode* rotateRL(AvlNode *parent){
    AvlNode *child = parent->right;
    parent->right = rotateLL(child);
    return rotateRR(parent);
}

AvlNode *avlAdd(AvlNode *root, int data){
    if(root == NULL){
        root = (AvlNode*)malloc(sizeof(AvlNode));
        root->data = data;
        root->Height = 0;
        root->left = root->right = NULL;
    }else if(data < root->data){
        root->left = avlAdd(root->left, data);
        if(height(root->left) - height(root->right) == 2){
            if(data < root->left->data)
                root = rotateLL(root);
            else
                root = rotateLR(root);
        }
    }else if(data > root->data){
        root->right = avlAdd(root->right, data);
        if(height(root->right) - height(root->left) == 2){
            if(data > root->right->data)
                root = rotateRR(root);
            else
                root = rotateRL(root);
        }
    }else{
        printf("중복 키 삽입 오류\n");
        exit(1);
    }
    root->Height = Max(height(root->left), height(root->right)) + 1;
    return root;
}

AvlNode *avlDelete(AvlNode *root, int data){
    if(root == NULL) return NULL;

    if(data < root->data){
        root->left = avlDelete(root->left, data);
    }else if(data > root->data){
        root->right = avlDelete(root->right, data);
    }else{
        if(root->left == NULL && root->right == NULL){
            free(root);
            return NULL;
        }else if(root->left == NULL || root->right == NULL){
            AvlNode* child = (root->left) ? root->left : root->right;
            free(root);
            return child;
        }else{
            AvlNode* succ = root->right;
            while(succ->left != NULL)
                succ = succ->left;
            root->data = succ->data;
            root->right = avlDelete(root->right, succ->data);
        }
    }

    if(root == NULL) 
        return NULL;

    root->Height = Max(height(root->left), height(root->right)) + 1;

    if(height(root->left) - height(root->right) > 1){
        if(height(root->left->left) >= height(root->left->right))
            root = rotateLL(root);
        else
            root = rotateLR(root);
    }else if(height(root->right) - height(root->left) > 1){
        if(height(root->right->right) >= height(root->right->left))
            root = rotateRR(root);
        else
            root = rotateRL(root);
    }

    root->Height = Max(height(root->left), height(root->right)) + 1;
    return root;
}

void InorderTraveling(AvlNode* root){
    if(root != NULL){
        InorderTraveling(root->left);
        printf("%d ", root->data, root->Height);
        InorderTraveling(root->right);
    }
}

int main(){
    AvlNode *root = NULL;

    root = avlAdd(root, 7);
    root = avlAdd(root, 8);
    root = avlAdd(root, 9);
    root = avlAdd(root, 2);
    root = avlAdd(root, 1);
    root = avlAdd(root, 5);
    root = avlAdd(root, 3);
    root = avlAdd(root, 6);
    root = avlAdd(root, 4);
    
    InorderTraveling(root);
    printf("\nRoot node: %d(h=%d)\n", root->data, root->Height);

    root = avlDelete(root, 8);
    InorderTraveling(root);
    printf("\nRoot node: %d(h=%d)\n", root->data, root->Height);

    root = avlDelete(root, 2);
    InorderTraveling(root);
    printf("\nRoot node: %d(h=%d)\n", root->data, root->Height);

    return 0;
}
