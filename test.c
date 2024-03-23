#include<stdio.h>
#include<stdlib.h>

typedef struct sv {
    int a;
    struct sv* Next;
}sv;
void p(sv* a){
    printf("%d",&(a->Next));
}
void m(sv* a){
    a->Next = (sv*)malloc(sizeof(sv));
}
int main(){
 sv* a;
 a = (sv*)malloc(sizeof(sv));
 m(a);
 printf("%d\n",&(a->Next));
 p(a);
}