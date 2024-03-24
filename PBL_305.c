#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct lineLinkedList {
    struct lineLinkedList* NSNext;
    struct numbersSeries* numbersList;
}lineLinkedList;

typedef struct numbersSeries {
    unsigned int* max_sizeList;
    double number;
    struct numbersSeries* NNext;
}numbersSeries;

int d_fArray(double** array, double number);
void d_cArray(char** array, char* character);
void readFAW(double** array);
void StringToDoubleInStruct(char StringInFile[], lineLinkedList* lineList);
void readToFile(lineLinkedList** A);
void printOneStruct(lineLinkedList** B);
void insertToList(numbersSeries** A, numbersSeries** B);
void insertPartNumberList(numbersSeries** A, double Fnumber);
void insertToAllLine(lineLinkedList** A, double* d_fArray);
double stringtoNumber(char str[]);
void writeToFileS(lineLinkedList** B);

int main(){
    double* tempFile ;
    readFAW(&tempFile);
    lineLinkedList* A;
    readToFile(&A); 

    printOneStruct(&A);
    insertToAllLine(&A,tempFile);

    free(tempFile);
    

    printf("\n\n# ---- after changed ----\n\n");
    writeToFileS(&A);
    printOneStruct(&A);


    
}
int d_fArray(double** array, double number) {
    static int count_dArray = 0;
    if (count_dArray == 0) {
        *array = (double*)malloc(sizeof(double));
    } else {
        *array = realloc(*array, (count_dArray + 1) * sizeof(double));
    }
    (*array)[count_dArray] = number;
    count_dArray++;
    return count_dArray - 1;
}
void d_cArray(char** array, char* character) {
    static int count_dArray = 0;
    int characterLength = strlen(character);
    if (count_dArray == 0) {
        count_dArray = characterLength + 1;
        *array = (char*)malloc(count_dArray * sizeof(char));
        strcpy(*array, character);
    } else {
        int arrayLength = strlen(*array);
        count_dArray += characterLength;
        *array = realloc(*array, count_dArray * sizeof(char));
        memcpy(*array + arrayLength, character, characterLength + 1); 
    }
}

void readFAW(double** array){
    int count_number_to_file = 0;
    char temp_c[20];
    FILE *f;
    f = fopen("InNumberEnter.IN","r");
    if(f == NULL){
        printf("open file InNumberEnter.IN is fail\n");
    }else{
        while(fgets(temp_c, sizeof(temp_c),f) != NULL){
            double temp_f = stringtoNumber(temp_c);
             d_fArray(array,temp_f); 
             count_number_to_file++;
        } 
        fclose(f);
    }
    
}
void StringToDoubleInStruct(char StringInFile[], lineLinkedList* lineList){

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
            tempNumberList->number = temp;

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
}
void readToFile(lineLinkedList** A){
    
    *A = (lineLinkedList*)malloc(sizeof(lineLinkedList));
    lineLinkedList* tempS = *A;
    FILE *f;
    f = fopen("DAYSO.IN", "r");
    char temp[100];
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
     printf("\n\n#-----successfully wrote the \"DAYSO.IN\" file to the linked list-----\n\n");
}
void printOneStruct(lineLinkedList** B){
    lineLinkedList* A = *B;
    static int line = 0;
    while(A->NSNext != NULL){
        numbersSeries* tempNumbersList = A->numbersList;
        line++;
        printf("#line_%d  ",line);
        while(tempNumbersList != NULL){
            printf("%lf     ",tempNumbersList->number );
            tempNumbersList = tempNumbersList->NNext;
        }
        printf("\n");
        A = A->NSNext;
    }
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
    
   while(--i){
        tempNumberStruct = tempNumberStruct->NNext;
   }


   insertToList(&tempNumberStruct,&B);
   B->number = Fnumber;

}
void insertToAllLine(lineLinkedList** A, double* d_fArray){
    lineLinkedList* tempLineStruct = *A;
    int count = 0;
    while(tempLineStruct->NSNext != NULL){
        insertPartNumberList(&(tempLineStruct->numbersList),d_fArray[count]);
        tempLineStruct = tempLineStruct->NSNext;
        count += 1;
    }
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
void writeToFileS(lineLinkedList** B){
    lineLinkedList* A = *B;
    char* tempCharater;
    FILE* f = fopen("RESULT1.OUT","w");
    if(f == NULL){
        printf("#----writing to file RESULT1.OUT failed---");
        return;
    }
    char* charac;
    while(A->NSNext != NULL){
        numbersSeries* tempNumbersList = A->numbersList;
        while(tempNumbersList != NULL){
            char tempCharac[20];
            sprintf(tempCharac, "%.6f", tempNumbersList->number);
            strcat(tempCharac," ");
            d_cArray(&charac,tempCharac);
            tempNumbersList = tempNumbersList->NNext;
        }
        d_cArray(&charac,"\n");
        A = A->NSNext;
    }
    fprintf(f,charac);
    fclose(f);
}