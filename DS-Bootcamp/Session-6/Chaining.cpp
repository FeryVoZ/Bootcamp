#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxBuckets = 3;

struct node{
    char name[255];
    node *next;
}*head[maxBuckets], *tail[maxBuckets];

node *createNode(const char *name){
    node *newNode = (node*)malloc(sizeof(node));
    strcpy(newNode->name,name);
    newNode->next = NULL;
    return newNode;
}

unsigned long djb2(const char *str){
    unsigned long key = 5381;
    for(int i=0; str[i]!='\n'; i++){
        int ascii = int(str[i]);
        key = (key << 5) + key + ascii;
    }

    return key%maxBuckets;
}

void insert(const char *str){
    node *newNode = createNode(str);
    int idx = djb2(str);
    if(!head[idx]){
        head[idx]=tail[idx]=newNode;
    }
    else{
        tail[idx]->next = newNode;
        tail[idx]=newNode;;
    }
}

void traverseLL(int i){
    node *curr = head[i];
    while(curr){
        printf("%s -> ", curr->name);
        curr=curr->next;
    }
    puts("NULL");
}

void read(){
    for(int i=0; i<maxBuckets; i++){
        printf("Index %d: ", i);
        if(head[i]){
            traverseLL(i);
        }
        else{
            puts("NULL");
        }
    }
}

int main(){

    insert("budi");
    insert("cecep");
    insert("asep");
    insert("tono");
    insert("anto");
    insert("siti");
    read();

    return 0;
}