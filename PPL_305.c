#include<stdio.h>
#include<stdlib.h>

int n = 7;
typedef struct numberSeries {
    double a[10];
    struct numberSeries* NSNext;
}numberSeries;

void StringToFloat(char B[], double a[]){
    int countC = 0;
    int countN = 0;
    int check = 0;
    while(B[countC]!='\0'){
        int sign = 1;
        int th_10 = 1;
        double temp = 0.0;
        while(B[countC]!=' ' && B[countC] !='\0'){
            temp = (B[countC] != '-' && B[countC]!='.') ? temp*10 + ((double)(B[countC]-'0')) : temp; 
            check = 1;
            if(B[countC] == '-'){
                sign = -1;
            }
            if(B[countC] == '.' || th_10 != 1){
                th_10  *= 10;
            }
            countC++;
        }
        if(check == 1){

            temp = temp*sign;
            if(th_10 != 1){
                temp /=(th_10/10);
            }
            a[countN] = temp;
            countN++;
            sign = 1;
            th_10 = 1;
            temp = 0.0;
        }
        countC++;
    }
}
void readToFile(numberSeries* A){
    numberSeries** B = (numberSeries**)malloc(7 * sizeof(numberSeries*)); 
    B[0] = (numberSeries*)malloc(sizeof(numberSeries)); 
    int i = 1; 
    while (i < 7) {
        B[i] = (numberSeries*)malloc(sizeof(numberSeries));
        B[i - 1]->NSNext = B[i];
        ++i;
    }
    B[6]->NSNext = NULL; 
    A = B[0];
    numberSeries* tempS ;
    tempS = A;
    FILE *f;
    f = fopen("DAYSO.IN", "r");
    char temp[20];
    if(f == NULL){
        printf("Cannot open file !\n");
    }
    else{
        while(fgets(temp,sizeof(temp),f) && A != NULL){
            StringToFloat(temp,A->a);
            A = A->NSNext;     
        }
        A = tempS;
    }
    fclose(f);
}
int main(){

    numberSeries* A;
    readToFile(A);
    printf("result\n");
    while(A != NULL){
        for(int i = 0 ; i < 6 ; i++){
            printf("%lf  " ,A->a[i]);
        }
        printf("\n");
        A = A->NSNext;
    }
}