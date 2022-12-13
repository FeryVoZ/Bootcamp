#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node{
    int value;
    Node *next;
    Node *prev;
}*top=NULL;

Node *createNode(int value){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->value=value;
    newNode->next=NULL;
    newNode->prev=NULL;
    return newNode;
}

void pushStack(int value){
    Node *newNode = createNode(value);
    if(!top){
        top=newNode;
    }
    else{
        top->next=newNode;
        newNode->prev=top;
        top=newNode;
    }
}

void removeStack(){
    if(!top){
        return;
    }
    else if(top->prev == NULL){
        free(top);
        top=NULL;
    }
    else{
        Node *newTop=top->prev;
        top->prev = newTop -> next = NULL;
        free(top);
        top = newTop;
    }
}

Node *Top(){
    return top;
}

int main(){


    return 0;
}