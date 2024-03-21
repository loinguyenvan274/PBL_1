#include<stdio.h>
#include<stdlib.h>

typedef struct sv {
    int a[9];
}sv;
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
int main(){
    char *a = "-434.54 66.6 -65";
    double b [10];
    StringToFloat(a,b);
    printf("%lf %lf %lf",b[0],b[1],b[2]);
}