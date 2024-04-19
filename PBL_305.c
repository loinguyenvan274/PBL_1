#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define er 1e-8
int max_size;

typedef struct lineLinkedList {
    struct lineLinkedList* NSNext;
    struct numbersSeries* numbersList;
}lineLinkedList;

typedef struct numbersSeries {
    unsigned int* maxNumbersNodeSize;
    double number;
    struct numbersSeries* NNext;
}numbersSeries;

int d_fArray(double** array, double number);
void d_cArray(char** array, char* character);
void readFAW(double** array);
void StringToDoubleInStruct(char StringInFile[], lineLinkedList* lineList);
void readToFile(lineLinkedList** lineList);
void printOneStruct(lineLinkedList** lineList);
void insertToList(numbersSeries** numberNode, numbersSeries** numberNode_input );
void insertPartNumberList(numbersSeries** numberNode, double Fnumber);
void insertToAllLine(lineLinkedList** lineList, double* d_fArray);
double stringtoNumber(char str[]);
void writeToFileS(lineLinkedList** lineList);

void Swap(double* valueA, double* valueB);
void EnterMaxtrixValue(double maxTrix[max_size][max_size+1],lineLinkedList** lineList);
int findDifElement(double maxTrix [max_size][max_size+1],int* maxValueLocationI,int* maxValueLocationJ );
void swapIntoMainDiagonal(double maxTrix[max_size][max_size + 1],int* maxValueLocationI,int* maxValueLocationJ );
double* soloveMaxtrix(double maxTrix[max_size][max_size+1]);
int findMaxElementValue(double surplus[]);
void printMaxtrix(double maxTrix [max_size][max_size+1]);
void printExperienceToFile(double* experience);
void print(double a[]){
    static int count = 1;
    printf("#%d ",count++);
    for(int i = 0; i<max_size; i++){
        printf("%0.3lf ",a[i]);
    }
    printf("\n");
}

double* solveTheMaxtrix(lineLinkedList** lineList);

int main(){
    double* tempFile ;
    readFAW(&tempFile);
    lineLinkedList* lineList;
    readToFile(&lineList); 

    printOneStruct(&lineList);
    insertToAllLine(&lineList,tempFile);

    free(tempFile);
    

    writeToFileS(&lineList);
    printf("\n\n# ---- after changed ----\n\n");
    printOneStruct(&lineList);

    max_size = *(lineList->numbersList->maxNumbersNodeSize);

    double* allX = solveTheMaxtrix(&lineList);
    printExperienceToFile(allX);
    printf("write File is success");
}
void printExperienceToFile(double* experience){
    FILE* f;
    f = fopen("RESULT2.OUT","w");
    for(int i = 0; i < max_size ; i++){
        fprintf(f,"%lf ",experience[i]);
    }
    fclose(f);
}
//nhập và giải ma trận
double* solveTheMaxtrix(lineLinkedList** lineList){
    double maxTrix [max_size][max_size+1];
    EnterMaxtrixValue(maxTrix,lineList);
    printMaxtrix(maxTrix);
    double* experience = soloveMaxtrix(maxTrix);
    for(int i = 0; i < max_size; i++){
        printf("%lf ",experience[i]);
    }
    printf("\n");
    return experience;
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
    char temp_c[20];
    FILE *f;
    f = fopen("InNumberEnter.IN","r");
    if(f == NULL){
        printf("open file InNumberEnter.IN is fail\n");
    }else{
        while(fgets(temp_c, sizeof(temp_c),f) != NULL){
            double temp_f = stringtoNumber(temp_c);
             d_fArray(array,temp_f);
        } 
        fclose(f);
    }
    
}
void StringToDoubleInStruct(char StringInFile[], lineLinkedList* lineList){

    lineList->numbersList = (numbersSeries*)malloc(sizeof(numbersSeries));
    numbersSeries* tempNumberList = lineList->numbersList;

    tempNumberList->maxNumbersNodeSize = (unsigned int*)malloc(sizeof(unsigned int));

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
            tempNumberList->NNext->maxNumbersNodeSize = tempNumberList->maxNumbersNodeSize; 
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
    *(tempNumberList->maxNumbersNodeSize) = countNumberForNumberList ;
}
void readToFile(lineLinkedList** lineList){
    
    *lineList = (lineLinkedList*)malloc(sizeof(lineLinkedList));
    lineLinkedList* tempS = *lineList;
    FILE *f;
    f = fopen("DAYSO.IN", "r");
    char temp[1000];
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
void printOneStruct(lineLinkedList** lineList){
    lineLinkedList* A = *lineList;
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
void insertToList(numbersSeries** numberNode, numbersSeries** tempNumberNode){
    (*tempNumberNode)->maxNumbersNodeSize = (*numberNode)->maxNumbersNodeSize;
    (*tempNumberNode)->NNext = (*numberNode)->NNext;
    (*numberNode)->NNext = (*tempNumberNode);
    *((*numberNode)->maxNumbersNodeSize) += 1; 
}
void insertPartNumberList(numbersSeries** numberNode, double Fnumber){
    int i =(int) (*((*numberNode)->maxNumbersNodeSize)/2);
    numbersSeries* tempNumberNode = (numbersSeries*)malloc(sizeof(numbersSeries));
    numbersSeries* tempNumberStruct = *numberNode;
    
   while(--i){
        tempNumberStruct = tempNumberStruct->NNext;
   }


   insertToList(&tempNumberStruct,&tempNumberNode);
   tempNumberNode->number = Fnumber;

}
void insertToAllLine(lineLinkedList** lineList, double* d_fArray){
    lineLinkedList* tempLineStruct = *lineList;
    int count = 0;
    while(tempLineStruct->NSNext != NULL){
        insertPartNumberList(&(tempLineStruct->numbersList),d_fArray[count]);
        tempLineStruct = tempLineStruct->NSNext;
        count += 1;
    }
}
double stringtoNumber(char str[]){
    
    int i = 0 ; 
    int sign = 1;
    int th_10 = 1;
    int check_f = 0;
    double number = 0;

    while(str[i]!='\0'){
        sign = (str[i] =='-') ? -1 : 1;
        if((str[i]-'0') >= 0 && (str[i]-'0') <= 9){
            th_10 *= (check_f == 1) ? th_10 : 1;
            number = number*10 + (str[i]-'0');
        }
        if(str[i] == '.'){
            check_f = 1;
        }
        i += 1;
    }
    return number*sign/th_10;

}
void writeToFileS(lineLinkedList** lineList){
    lineLinkedList* tempLineList = *lineList;
    char* tempCharater;
    FILE* f = fopen("RESULT1.OUT","w");
    if(f == NULL){
        printf("#----writing to file RESULT1.OUT failed---");
        return;
    }
    char* charac;
    while(tempLineList->NSNext != NULL){
        numbersSeries* tempNumbersList = tempLineList->numbersList;
        while(tempNumbersList != NULL){
            char tempCharac[20];
            sprintf(tempCharac, "%.6f", tempNumbersList->number);
            strcat(tempCharac," ");
            d_cArray(&charac,tempCharac);
            tempNumbersList = tempNumbersList->NNext;
        }
        d_cArray(&charac,"\n");
        tempLineList = tempLineList->NSNext;
    }
    fprintf(f,charac);
    fclose(f);
}

// this method is edited as add element and changed alocation
void EnterMaxtrixValue(double maxTrix [max_size][max_size+1],lineLinkedList** lineList){ 
    lineLinkedList* tempLineList = *(lineList);
   for(int i = 0 ; i < max_size ; i++){
        for(int j = 1; j < max_size + 1; j++){
            double tempEnter;
            tempEnter = tempLineList->numbersList->number;
            tempLineList->numbersList = tempLineList->numbersList->NNext;
            maxTrix[i][j] = (-1)*tempEnter;
        }
        tempLineList = tempLineList->NSNext;
   }
   printf("#Enter values into the array\n");
   for(int i = 0; i< max_size ; i++){
        scanf("%lf",&maxTrix[i][0]);
        
   }  
}
//chuyên đổi ma trận để áp dụng phương pháp giảm dư
//chuyên đổi ma trận để áp dụng phương pháp giảm dư
int findDifElement(double maxTrix [max_size][max_size+1],int* maxValueLocationI,int* maxValueLocationJ ){
    for(int ij = 0 ; ij< max_size; ij++){
        if(maxTrix[ij][ij+1] == 0){
            int alocaMaxValue = 0;
            double tempFind = maxTrix[alocaMaxValue][ij+1];
            for(int i = 1 ; i< max_size; i++){
                if(tempFind < maxTrix[i][ij+1] && maxTrix[i][ij+1] != 0){
                    tempFind = maxTrix[i][ij+1];
                    alocaMaxValue = i;
                }
            }
//nếu phương trình có cột toàn bằng 0 thì phương trình vô nghiệm
            if(tempFind == 0){
                printf("the equation has no solution\n");
                return 0;
            }else{ // sử lý nếu đường chéo chính có phần tử bằng 0
                for(int j = 0 ; j < max_size +1 ; j++){
                    maxTrix[ij][j] += maxTrix[alocaMaxValue][j];
                }
            }

        }

    }
    swapIntoMainDiagonal(maxTrix,maxValueLocationI,maxValueLocationJ);
//chia các phần tử ở hàng cho phần tử hàng ở đường chéo chính
     for(int ij = 0 ; ij< max_size; ij++){
    double MaindiagonalElement = maxTrix[ij][ij+1];
        for(int j = 0 ; j < max_size + 1; j++){
            maxTrix[ij][j] /= MaindiagonalElement;
        }
     }
    return 1;
}
void printMaxtrix(double maxTrix [max_size][max_size+1]){
    for(int i = 0; i < max_size; i++){
        for(int j = 0; j < max_size + 1 ; j++){
            printf("%0.3lf ",maxTrix[i][j]);
        }
        printf("\n");
    }
}
double* soloveMaxtrix(double maxTrix[max_size][max_size+1]){
    int maxValueLocationJ = 1;
    int maxValueLocationI = 0;
    findDifElement(maxTrix,&maxValueLocationI,&maxValueLocationJ);
    double* allX = (double*)malloc(max_size*sizeof(double));
    //khởi tạo các giá trị bằng 0 hết và gán giá trị số dư vào mảng tạm thời
    double surplus[max_size];
    for(int i = 0; i < max_size ;i++){
        surplus[i] = maxTrix[i][0];
        allX[i] = 0;
    }
    int maxValueLocation = findMaxElementValue(surplus);
    int x = 0;
    while(fabs(surplus[maxValueLocation]) > er){
        allX[maxValueLocation] += surplus[maxValueLocation];
        for(int i = 0; i< max_size; i++){
            if(i != maxValueLocation){
                surplus[i] -= maxTrix[i][maxValueLocation+1]*surplus[maxValueLocation];
            }
        }
        surplus[maxValueLocation] = 0;
        maxValueLocation = findMaxElementValue(surplus);
        print(allX);
        printf("R: ");
        print(surplus);
        x++;
    }
    for(int i = 0; i < max_size; i++){
        allX[i] = allX[i]*(-1);
    }
    Swap(&allX[maxValueLocationI],&allX[maxValueLocationJ-1]);
    return allX;
}
void Swap(double* valueA, double* valueB){
    double temp = *valueA;
    *valueA = *valueB;
    *valueB = temp;
}
int findMaxElementValue(double surplus[]){
    int location = 0;
    double tempMaxValue = fabs(surplus[location]);
    for(int i = 1; i < max_size; i++){
        if(tempMaxValue<fabs(surplus[i])){
            tempMaxValue = fabs(surplus[i]);
            location = i;
        }
    }
    return location;
}
void swapIntoMainDiagonal(double maxTrix[max_size][max_size+1],int* maxValueLocationI,int* maxValueLocationJ){
    double tempAbsMaxValue = fabs(maxTrix[0][1]);
    for(int i = 0; i< max_size ; i++){
        for(int j = 1; j < max_size + 1; j++){
            if(fabs(maxTrix[i][j]) > tempAbsMaxValue){
                tempAbsMaxValue = fabs(maxTrix[i][j]);
                *maxValueLocationJ = j;
                *maxValueLocationI = i;
            }
        }
    }
    for(int i = 0; i < max_size; i++){
        Swap(&maxTrix[i][*maxValueLocationJ],&maxTrix[i][*maxValueLocationI+1]);
    }
}