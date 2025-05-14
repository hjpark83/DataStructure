#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct Node{
    int data;
    struct Node* nextNode;
}Node;

typedef struct LinkedList{
    int curCount;
    Node headNode;
}LinkedList;

void initNode(LinkedList *plist);
int addNode(LinkedList *plist, int pos, int data);
int removeNode(LinkedList *plist, int pos);
void showNode(LinkedList *plist);
int isEmpty(LinkedList *plist);
int findPos(LinkedList *plist, int data);
void makeEmpty(LinkedList *plist);

#endif