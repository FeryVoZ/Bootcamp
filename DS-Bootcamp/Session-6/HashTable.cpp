#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define maxSize 5

const int MAX_BUCKETS = 5;
char hashTable[MAX_BUCKETS][255];

void linearProbing(int idx, const char *str[]){
    for(int i=(idx+1)%MAX_BUCKETS; i!=idx; i= (i+1)%MAX_BUCKETS){
        if(!hashTable[i][0]){
            strcpy(hashTable[i], str);
            return;
        }
    }
}

void insert(const char *str[]){
    int idx = hash(str);
    (!hashTable[idx][0]){
        strcpy(hashTable[idx], str)
    }else{
        linearProbing(idx, str);
    } 
}

void read(){
    for(int i=0; i<=MAX_BUCKETS; i++){
        printf("%d -> %s\n", i, hashTable[i]);
    }
}

int hash(const char *name[]){ //ascii sum
    int asciiSum=0;
    for(int i=0; name[i]!='\0'; i++){
        asciiSum+= name[i]-'a';
    }
    return asciiSum % MAX_BUCKETS;
}

int main(){

    char name[] = "budi";
    insert("rico");
    insert("budi");
    insert("cecep");
    insert("tono");
    read();
    // printf("%d\n", hash(name));

    return 0;
}