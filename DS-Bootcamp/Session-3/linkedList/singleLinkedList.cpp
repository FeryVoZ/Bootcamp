#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// T069 - Fery Fernandi

// Linked list -> salah satu cara untuk menginput data secara dynamic
// Kalo biasa kan kita mau simpen sekumpulan data yang lebih dari satu kita bisa 
// makek struct array, nah tapi itu kan space nya udh kita tentuin ya dan statis,
// nah kalo link list itu dinamis, dia spacenya bisa nambah terus sesuai input user

// Single Linked List
// Double linked list
// multipled linked list
// multilevel linked list

// Selama bermain dengan linked list ini, maka kita akan terus menggunakan pola 
// -> C -> Create -> Create dan push
// -> R -> Read -> Search dan Print
// -> U -> Update -> Search dan push
// -> D -> Delete -> Pop

struct Node{
    int value;
    Node *next; //menunjuk alamat memory node lain
}*head=NULL, *tail=NULL; //global variabel yang menandakan alamat memory node awal dan akhir pada LL

//create Node
Node *createNode(int value){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->value=value; //mengisi value dengan parameter
    newNode->next=NULL; // pada awal, atur node next = null
    return newNode; // return node yang baru dibuat
}

void pushHead(int value){
    Node *newNode = createNode(value);
    if(head==NULL) head=tail=newNode;
    else{
        newNode->next=head;
        head=newNode;
    }
}

void pushTail(int value){
    Node *newNode = createNode(value);
    if(head==NULL) head=tail=newNode;
    else{
        tail->next=newNode;
        tail=newNode;
    }
}

void pushMid(int value){
    Node *newNode = createNode(value);
    if(head==NULL) head=tail=newNode;
    else if(head->value>newNode->value) pushHead(value);
    else if(tail->value<newNode->value) pushTail(value);
    else{
        Node *temp = head;
        while(temp->next->value<newNode->value){
            temp=temp->next;
        }
        newNode->next=temp->next;
        temp->next=newNode;
    }
}

void popHead(){
    if(head==NULL) return;
    else if(head==tail){
        free(head);
        head=tail=NULL;
    }
    else {
        Node *temp = head;
        head = head->next;
        temp->next=NULL;
        free(temp);
    }
}

void popTail(){
    if(head==NULL) return;
    else if(head==tail){
        free(head);
        head=tail=NULL;
    }
    else{
        Node *temp=head;
        while(temp->next!=tail){
            temp=temp->next;
        }
        // temp->next=NULL;
        // free(tail);
        tail=temp;
        free(tail->next);
        tail->next=NULL;
    }
}

void popMid(int value){
    if(head==NULL) return;
    else if(head->value==value){
    	popHead();
    }
    else if(tail->value==value){
    	popTail();
	}
    else{
        Node *temp=head, *curr=head;
        while(curr->next->value!=value){
            curr=curr->next;
        }
        while(temp){
            if(temp->value==value){
                curr->next=temp->next;
                free(temp);
                temp->next=NULL;
                printf("%d udah diapusss\n", value);
                return;
            }
            else if(temp==tail && temp->value!=value){
                printf("%d nya nggak adaa\n", value);
                return;
            }
            else {
                temp=temp->next;
            }
        }
    }
}

void search(int value){
    Node *temp=head;
    if(head==NULL) return;
    else{	
	    while(temp){
	        if(temp->value==value) printf("%d nya ketemuuu\n", temp->value);
    	    else if(temp==tail && temp->value!=value) printf("%d nya nggak adaa\n", value);
   	    else temp=temp->next;
    	}
	}
}

void readNode(Node *currNode){
    printf("Value : %d\n", currNode->value);
    printf("Alamat node sekarang : %p\n", currNode);
    printf("Alamat node setelahnya: %p\n", currNode->next);
}

void printLL(){
    Node *curr = head;
    while(curr!=NULL){
        readNode(curr);
        puts("|");
        puts("|");
        puts("V");
        curr=curr->next;
    }
}

int main(){
    
    pushMid(50);
    pushMid(10);
    pushMid(25);
    pushMid(15);
    pushMid(60);
    printLL();
    popMid(25);
    popMid(60);
    popMid(10);
    printLL();
    
    return 0;
}