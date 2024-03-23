#include<stdio.h>
#include<stdlib.h>


typedef struct lineLinkedList {
    struct lineLinkedList* NSNext;
    struct numbersSeries* numbersList;
}lineLinkedList;
typedef struct numbersSeries {
    unsigned int* max_sizeList;
    double number;
    struct numbersSeries* NNext;
}numbersSeries;
typedef struct fileNumber{
    double number;
    struct fileNumber* LNext;
}fileNumber;

void StringToDoubleInStruct(char StringInFile[], lineLinkedList* lineList){
    //チェックをします
    // printf("\nstart\n");
    // int  j = 0;
    // while(StringInFile[j]!='\0'){
    //     printf("%d ",StringInFile[j]);
    //     j++;
    // }
    // printf("\n");


    //最前の所
    lineList->numbersList = (numbersSeries*)malloc(sizeof(numbersSeries));
    numbersSeries* tempNumberList = lineList->numbersList;


    



    tempNumberList->max_sizeList = (unsigned int*)malloc(sizeof(unsigned int));

    int countC = 0;
    int check = 0;
    int countNumberForNumberList = 0;
    while(StringInFile[countC]!='\0' && StringInFile[countC] != 10){
        int sign = 1;
        int th_10 = 1;
        double temp = 0.0;
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

            countNumberForNumberList++;
            // printf(" value : %d ",countNumberForNumberList);
            tempNumberList->number = temp;

            //チェック
            // printf("%lf  \n",temp);


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
    *(tempNumberList->max_sizeList) = countNumberForNumberList ;
    // printf(" value Maxsize main : %u",*(tempNumberList->max_sizeList));
    // printf("\nEnd\n");
}
void readToFile(lineLinkedList** A){
    //check it't has same
    // printf(" address of lineList = %d ", ((*A)->numbersList));
    
    *A = (lineLinkedList*)malloc(sizeof(lineLinkedList));
    lineLinkedList* tempS = *A;
    FILE *f;
    f = fopen("DAYSO.IN", "r");
    char temp[50];
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
void printOneStruct(lineLinkedList** B){
    lineLinkedList* A = *B;
    while(A->NSNext != NULL){
        numbersSeries* tempNumbersList = A->numbersList;
        while(tempNumbersList != NULL){
            printf("%lf  max: %u |",tempNumbersList->number ,*(tempNumbersList->max_sizeList));
            tempNumbersList = tempNumbersList->NNext;
        }
        printf("\n");
        A = A->NSNext;
    }
    printf("printed to finish");
}
void insertToList(numbersSeries** A, numbersSeries** B){
// 使用前にメモリを割り当てる必要がある
    (*B)->max_sizeList = (*A)->max_sizeList;
    (*B)->NNext = (*A)->NNext;
    (*A)->NNext = (*B);
    *((*A)->max_sizeList) += 1; 
}
void insertPartNumberList(numbersSeries** A, double Fnumber){
    int i =(int) (*((*A)->max_sizeList)/2);
    numbersSeries* B = (numbersSeries*)malloc(sizeof(numbersSeries));
    numbersSeries* tempNumberStruct = *A;
//    printf("here");
//    printf("\n%d ",*(tempNumberStruct->max_sizeList));
   while(--i){
        tempNumberStruct = tempNumberStruct->NNext;
   }


   insertToList(&tempNumberStruct,&B);
   B->number = Fnumber;
   printf(" number->%lf\n",B->NNext->number);
   printf(" max when chagned %u\n ",*(tempNumberStruct->max_sizeList));

}
void insertToAllLine(lineLinkedList** A, fileNumber** J){
    lineLinkedList* tempLineStruct = *A;
    fileNumber* tempFNumber = *J;
    while(tempLineStruct->NSNext != NULL){
        insertPartNumberList(&(tempLineStruct->numbersList),tempFNumber->number);
        tempLineStruct = tempLineStruct->NSNext;
        tempFNumber = tempFNumber->LNext;
    }
    printf("end to here");
}
double stringtoNumber(char str[]){
    int i = 0;
    int sign = 1;
    int th_10 = 1;
    double number = 0;
    while(str[i]!='\0' && str[i] != 10 &&  str[i] != '.'){
        number = (str[i] != ' ') ? number*10 + (double) (str[i]-'0') : number;
        ++i;
    }
    if(str[i] == '.'){
        ++i;
        while(str[i]!='\0' && str[i] != 10){
            number = (str[i] != ' ') ? number*10 + (double) (str[i]-'0') : number;
            th_10 *= 10;
        }
    }
    return number*sign/th_10;

}
void readFAW(fileNumber** j){
    FILE *f;
    f = fopen("InNumberEnter.IN","r");
    if(f == NULL){
        printf("can not open file InNumberEnter.IN");
    }
    else{
        fileNumber* tempLFileNumber = *j;
         tempLFileNumber = (fileNumber*)malloc(sizeof(fileNumber));
        char tempC[50];
        while(fgets(tempC,sizeof(tempC),f)){
           
            tempLFileNumber->LNext = (fileNumber*)malloc(sizeof(fileNumber));
            tempLFileNumber->number = stringtoNumber(tempC);
            tempLFileNumber = tempLFileNumber->LNext;
        }
        tempLFileNumber->LNext = NULL;
    }
    
    
}
int main(){

    lineLinkedList* A;
    fileNumber* j;
    readFAW(&j); 
    readToFile(&A);
    insertToAllLine(&A,&j);
    printf("when changed \n");
    printOneStruct(&A);


    
}