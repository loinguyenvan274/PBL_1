#include<stdio.h>
#include<stdlib.h>


typedef struct lineLinkedList {
    struct lineLinkedList* NSNext;
    struct numbersSeries* numbersList;
}lineLinkedList;
typedef struct numbersSeries {
    unsigned int count;
    unsigned int* max_sizeList;
    double number;
    struct numbersSeries* NNext;
}numbersSeries;

void StringToDoubleInStruct(char StringInFile[], lineLinkedList* lineList){
    //チェックをします
    printf("\nstart\n");
    int  j = 0;
    while(StringInFile[j]!='\0'){
        printf("%d ",StringInFile[j]);
        j++;
    }
    printf("\n");


    //最前の所
    lineList->numbersList = (numbersSeries*)malloc(sizeof(numbersSeries));
    numbersSeries* tempNumberList = lineList->numbersList;
    tempNumberList->max_sizeList = (int*)malloc(sizeof(int));

    int countC = 0;
    int check = 0;

    while(StringInFile[countC]!='\0' && StringInFile[countC] != 10){
        int sign = 1;
        int th_10 = 1;
        double temp = 0.0;
        int countNumberForNumberList = -1;
        while(StringInFile[countC]!=' ' && StringInFile[countC] !='\0' && StringInFile[countC] != 10){
            temp = (StringInFile[countC] != '-' && StringInFile[countC]!='.') ? temp*10 + ((double)(StringInFile[countC]-'0')) : temp; 
            check = 1;
            if(StringInFile[countC] == '-'){
                sign = -1;
            }
            if(StringInFile[countC] == '.' || th_10 != 1){
                th_10  *= 10;
            }
            countC++;
        }
        if(check == 1){

            temp = temp*sign;
            if(th_10 != 1){
                temp /=(th_10/10);
            }

            ++countNumberForNumberList;
            tempNumberList->count = countNumberForNumberList;
            tempNumberList->number = temp;

            //チェック
            printf("%lf  ",temp);


            tempNumberList->NNext = (numbersSeries*)malloc(sizeof(numbersSeries));
            tempNumberList->NNext->max_sizeList = tempNumberList->max_sizeList; 
            tempNumberList = tempNumberList->NNext;

            sign = 1;
            th_10 = 1;
            temp = 0.0;
        }
        countC++;
    }
     tempNumberList->NNext =  NULL;
     tempNumberList = lineList->numbersList;
    while(tempNumberList->NNext->NNext != NULL){
        tempNumberList = tempNumberList->NNext;
    }
    free(tempNumberList->NNext);
    tempNumberList->NNext =  NULL;
    tempNumberList->max_sizeList = tempNumberList->count;
    printf("\nEnd\n");
}
void readToFile(lineLinkedList** A){
    
    *A = (lineLinkedList*)malloc(sizeof(lineLinkedList));
    lineLinkedList* tempS ;
    tempS = *A;
    FILE *f;
    f = fopen("DAYSO.IN", "r");
    char temp[20];
    if(f == NULL){
        printf("Cannot open file !\n");
    }
    else{
        while(fgets(temp,sizeof(temp),f)){
            tempS->NSNext = (lineLinkedList*)malloc(sizeof(lineLinkedList));
           StringToDoubleInStruct(temp, tempS); 
            tempS = tempS->NSNext;         
        }
        tempS->NSNext = NULL;
        
    }
    fclose(f);
}
void printOneStruct(lineLinkedList* A){
    while(A != NULL){
        while(A->numbersList != NULL){
            printf("%lf  ",A->numbersList->number);
            A->numbersList = A->numbersList->NNext;
        }
        printf("\n");
        A = A->NSNext;
    }
}
void InsertInListNumber(lineLinkedList** A ){
    lineLinkedList* B = *A;
    numbersSeries* tempS;
    tempS =(*A)->numbersList;
    int count = 1;
    while(tempS != NULL){
        count++;
        tempS =tempS->NNext;
    }
    tempS =(*A)->numbersList;
    int tempCount = count;
    while(B != NULL){

        B = B->NSNext;
    }

}
int main(){

    lineLinkedList* A = NULL ;
    readToFile(&A);
    printOneStruct(A);
    printf("%u",A->numbersList->max_sizeList);
    
}