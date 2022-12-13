#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student{
    char name[255];
    int age;
    double gpa;
};

// Data Structure -> Create, Read, Update, Delete (CRUD)

//createStudent
//return pointer that points to the newly created Student
Student *createStudent(const char *name, int age, double gpa){
    //allocate memorry
    Student *newStudent = (Student*)malloc(sizeof(Student));
    // *newStudent->gpa=gpa;
    newStudent->gpa=gpa;
    newStudent->age=age;
    strcpy(newStudent->name,name);
    return newStudent;
}

void readStudent(Student *s){
    printf("Name = %s\n", s->name); //printf("%s", (*s).name)
    printf("GPA = %lf\n", s->gpa);
    printf("Age = %d\n", s->age);
    printf("This student is located ad  %p\n", s);
}

void updateStudent(Student *s, int newAge){
    s->age=newAge;
}

void deleteStudent(Student *s){
    free(s);
    s=NULL;
}

void swap(int *a, int *b){
    int temp = *a;
    *a=*b;
    *b=temp;
}

int main(){

    // int a=5 -> reserve alamat 350
    // malloc(400) -> reserve memory(400)

    Student *s = createStudent("Budi", 20, 3.97);
    readStudent(s);
    puts("");
    updateStudent(s,22);
    readStudent(s);
    puts("");
    deleteStudent(s);

    readStudent(s);

    // int a=30; int b=20;
    // swap(&a,&b);
    // printf("%d\n", a);

    return 0;
}