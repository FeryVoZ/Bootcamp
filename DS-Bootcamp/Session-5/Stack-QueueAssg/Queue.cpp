#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct patient{
    char name[255];
    int age;
    patient *next;
}*first=NULL, *last=NULL;

patient *createNode(const char *name, int age){
    patient *newPatient = (patient*)malloc(sizeof(patient));
    newPatient->age=age;
    strcpy(newPatient->name,name);
    newPatient->next = NULL;
    return newPatient;
}

void pushFirst(const char *name, int age){
    patient *newPatient = createNode(name, age);
    if(first==NULL) first=last=newPatient;
    else{
        newPatient->next=first;
        first=newPatient;
    }
}

void pushLast(const char *name, int age){
    patient *newPatient = createNode(name, age);
    if(first==NULL) first=last=newPatient;
    else{
        last->next=newPatient;
        last=newPatient;
    }
}

void pushPriority(const char *name, int age){
    patient *newPatient = createNode(name, age);
    if(first==NULL) first=last=newPatient;
    else if(first->age<newPatient->age) pushFirst(name, age);
    else if(last->age>newPatient->age) pushLast(name, age);
    else{
        patient *temp = first;
        while(temp->next->age>newPatient->age){
            temp=temp->next;
        }
        newPatient->next=temp->next;
        temp->next=newPatient;
    }
}

void popQueue(){
    if(first==NULL) return;
    else if(first==last){
        free(first);
        first=last=NULL;
    }
    else {
        patient *temp = first;
        first = first->next;
        temp->next=NULL;
        free(temp);
    }
}

void printQueue(){
    patient *curr = first;
    int i=0;
    while(curr!=NULL){
        printf("Pasien ke %d:\n", i+1);
        printf("Nama : %s\n", curr->name);
        printf("Umur : %d\n", curr->age);
        puts("");
        i++;
        curr=curr->next;
    }
}

void queue(){
    pushLast("Budi", 16);
    pushLast("Angga", 20);
    pushLast("Tono", 50);
    pushLast("Roni", 70);
    printQueue();
    puts("");
    puts("=======================");
    puts("");
    popQueue();
    popQueue();
    printQueue();
    popQueue();
    popQueue();
}

void priorityQueue(){ //umur lebih tua lebih diprioritaskan
    pushPriority("Budi", 16);
    pushPriority("Angga", 20);
    pushPriority("Doni", 5);
    pushPriority("Kevin", 80);
    pushPriority("Tono", 50);
    pushPriority("Roni", 70);
    printQueue();
    puts("");
    puts("=======================");
    puts("");
    popQueue();
    popQueue();
    printQueue();
}

int main(){
    puts("Queue");
    puts("");
    queue();
    puts("");
    puts("========================");
    puts("");
    puts("Priority Queue");
    puts("");
    priorityQueue();

    return 0;
}