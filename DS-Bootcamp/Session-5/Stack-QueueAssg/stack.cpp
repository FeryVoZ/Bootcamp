#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct bookBox{
    char title[255];
    bookBox *up, *down;
}*top=NULL;

bookBox *createNode(const char *title){
    bookBox *newBook = (bookBox*)malloc(sizeof(bookBox));
    strcpy(newBook->title, title);
    newBook->up = NULL;
    newBook->down = NULL;
    return newBook;
}

void pushStack(const char *title){
    bookBox *newBook = createNode(title);
    if(!top){
        top=newBook;
    }
    else{
        top->up=newBook;
        newBook->down=top;
        top=newBook;
    }
}

void popStack(){
    if(!top){
        return;
    }
    else if(top->down == NULL){
        free(top);
        top=NULL;
    }
    else{
        bookBox *newTop =top->down;
        top->down = newTop -> up = NULL;
        free(top);
        top = newTop;
    }
}

bookBox *Top(){
    return top;
}

void printStack(){
    if(!top){
        printf("BookBox Kosong");
        return;
    }
    else{
        bookBox *curr = top;
        int i=0;
        while(curr!=NULL){
            if(curr->down!=NULL){
                printf("Judul buku ke %d: %s\n", i, curr->title);
                puts("|");
                puts("v");
                i++;
            }
            else{
                printf("Judul buku ke %d: %s\n", i, curr->title);
            }
            curr = curr->down;
        } 
    }
}

int main(){

    pushStack("Harry Potter");
    pushStack("Laskar Pelangi");
    pushStack("Kisah Tanah Jawa");
    pushStack("The Devil All the Time");

    printStack();

    puts("");
    puts("");
    puts("===============================");
    puts("");
    puts("");

    popStack();
    popStack();

    printStack();

    return 0;
}