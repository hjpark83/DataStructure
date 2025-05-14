#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct person{
    char *name;
    int age;
} Person;

int main(void){
    int size = 10;
    Person *pPerson = (Person*)malloc(sizeof(Person)*size);
    char temp[256];

    for(int i=0; i<size; i++){
        printf("[%d]name: ", i);
        scanf("%s", temp);

        pPerson[i].name = (char*)malloc(sizeof(temp));
        strcpy(pPerson[i].name, temp);

        pPerson[i].age = rand()%25;
    }
    printf("\n");

    for(int i=0; i<size; i++){
        printf("[%d]name: %s, age: %d\n", i, pPerson[i].name, pPerson[i].age);
    }

    for(int i=0; i<size; i++){
        free(pPerson[i].name);
    }
    free(pPerson);
    return 0;
}