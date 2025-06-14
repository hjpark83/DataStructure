#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY_SIZE 10
#define TABLE_SIZE 5
#define equal(e1, e2) (!strcmp(e1.key, e2.key))

typedef struct Element{
    char key[KEY_SIZE];
}Element;

typedef struct ListNode{
    Element item;
    struct ListNode *link;
}ListNode;

ListNode* hashTable[TABLE_SIZE];

void initTable(ListNode* ht[]){
    for(int i=0; i<TABLE_SIZE; i++)
        ht[i] = NULL;
}

int transform(char *key){
    int number = 0;
    int size = strlen(key);

    for(int i=0; i<size; i++)
        number += key[i];
    return number;
}

int hashFunction(char *key){
    return transform(key) % TABLE_SIZE;
}

void addHashTable(Element item, ListNode* ht[]){
    int hashValue = hashFunction(item.key);
    ListNode *ptr;
    ListNode* node = ht[hashValue];

    for(; node; node=node->link){
        if(equal(node->item, item)){
            printf("Error: Duplicated value\n");
            return;
        }
    }
    ptr = (ListNode*)malloc(sizeof(ListNode));

    ptr->item = item;
    ptr->link = ht[hashValue];
    ht[hashValue] = ptr;
}

void hashSearch(Element item, ListNode* ht[]){
    ListNode* node;

    int hashValue = hashFunction(item.key);
    for(node = ht[hashValue]; node; node=node->link){
        if(equal(node->item, item)){
            printf("Success: Item exists\n");
            return;
        }
    }
    printf("Failure: Item not exists\n");
}

void printHashTable(ListNode* ht[]){
    ListNode* tmp;

    for(int i=0; i<TABLE_SIZE; i++){
        tmp = ht[i];
        for(; tmp; tmp=tmp->link)
            printf("%s\t", tmp->item.key);
        printf("\n");
    }
}

int main(){
    Element tmp;
    int op;

    while(1){
        printf("Input operation (0: Insert, 1: Search, 2: Print, 3: End) = ");
        scanf("%d", &op);

        if(op==3)
            break;
        
        if(op==2)
            printHashTable(hashTable);
        else{
            printf("Input key: ");
            scanf("%s", tmp.key);
            if(op==0)
                addHashTable(tmp, hashTable);
            else if(op==1)
                hashSearch(tmp, hashTable);
        }
    }
    return 0;
}