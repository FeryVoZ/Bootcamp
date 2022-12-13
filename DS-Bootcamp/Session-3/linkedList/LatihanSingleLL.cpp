#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// T069-Fery Fernandi

// Nah saat kita membahas data struct pasti akan bermain dengan struct kan, tapi aku yakin kalian udah pernah belajar struct jadi disini aku
// bakal bahas sedikit aja tentang struct

// Jadi Struct adalah sebuah tipe data yang kita buat untuk menyimpan beberapa data menjadi suatu kesatuan, nah data yang disimpan dalam struct
// itu bisa berbagai macam gk 1 tipe data aja

// Linked List -> suatu cara untuk menyimpan data secara dynamic
// Maksudnya, kan biasa kita mau simpen banyak data makeknya array of struct, nah kalo pakek itu kan udh kita batasin memorynya misal arr[100]
// berarti kita udh mesen 100 tempat buat datanya gitu, nah kalo linked list ini dinamis, jadi nggak terbatas, bisa nambah sesuai kebutuhan user

// Single Linked list
// Double Linked List
// Multipled Linked List
// Multilevel Linked List

// Selama kita bermain dengan data Struct, kita bakal terus menggunakan sebuah pola, yaitu 
// C -> Create 
// R -> Read
// U -> Update
// D -> Delete

struct mhs{
    char name[255];
    int age;
    mhs *next;
}*head=NULL, *tail=NULL;

//Pabrik Node
mhs *createNode(char name[], int age){
    mhs *newMhs = (mhs*)malloc(sizeof(mhs));
    // *<nama struct>.<data yang mau diakses>
    newMhs->age = age;
    strcpy(newMhs->name, name);
    newMhs->next=NULL;
    return newMhs;
}

// push head -> kita memasukkan data dari depan linked
// push tail -> kita memasukkan data dari belakang linked list
// push mid -> kita memasukkan data ditengah lingked listnya berdasarkan urutas sebuah value

//pushTail
void pushTail(char name[], int age){
    mhs *newMhs = createNode(name, age);
    // ketika data kosong
    if(head==NULL) head=tail=newMhs;
    // ketika udah ada data
    else {
        tail->next=newMhs;
        tail=newMhs;
    }
}

//popHead
//popTail
//popMid

//popTail
void popTail(){
    //kalo gk ada datanya, nodenya kosong
    if(head==NULL) return;
    //kalo datanya cuma ada 1
    else if(head==tail) {
        free(head);
        head=tail=NULL;
    }
    //  data lebih dari 1
    else{
        mhs *temp = head;
        while(temp!=tail){
            temp=temp->next;
        }
        temp->next=NULL; 
        free(tail);
        tail=temp;
    }
}

// search
void searchMhs(int age){
    int counter=0;
    mhs *temp=head;
    if(head==NULL) return;
    else {
        while(temp!=NULL){
            if(temp->age==age){
                counter++;
                printf("Nama Mhs: %s\n", temp->name);
                printf("Umur Mhs: %d\n", temp->age);
                puts("");
            }
            else if(temp==tail&&temp->age!=age&&counter==0){
                printf("mhs umur %d tahun gk adaa\n", age);
                return;
            }
            temp=temp->next;
        }
    }
    
}

//print
void printAll(){
    if(head==NULL){
        printf("Data nya kosong");
    }
    else {
        mhs *temp =head;
        while(temp!=NULL){
            printf("Nama Mhs: %s\n", temp->name);
            printf("Umur Mhs: %d\n", temp->age);
            puts("");
            temp=temp->next;
        }
    }
}

int main(){

    pushTail("Budi", 20);
    pushTail("Tono", 21);
    pushTail("Angga", 18);

    printAll();
    
    popTail();
    printAll();

    searchMhs(20);

    return 0;
}