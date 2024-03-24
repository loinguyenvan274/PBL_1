#include <stdio.h>
#include <stdlib.h>


int d_dArray(double** array, double number){
    static int count_dArray = 0;
    if(count_dArray == 0){
        *array = (double*)malloc(sizeof(double));
        count_dArray += 1;
       ( *array)[count_dArray] = number;
    }else{
        count_dArray += 1;
        *array = realloc(*array,count_dArray*sizeof(double));
        (*array)[count_dArray] = number;
    }
    return count_dArray;
}


int main() {
    double* tempFile;
    int i = d_dArray(&tempFile,5);
    printf("%lf",tempFile[i]);
    i = d_dArray(&tempFile,9);
    printf("\n%lf",tempFile[i]);
    printf("\n%lf",tempFile[i-1]);
}
