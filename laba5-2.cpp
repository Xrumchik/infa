#include <iostream>
#include <cmath>

int main(){
    int n,m,A[20][20];
    puts("Введите размеры матрицы(кол-во строк и стобцов):");
    scanf("%d%d", &n,&m);
    if (n<=20 && n>0 && m<=20 && m>0){
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                A[i][j]=m-j+i;
            }
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                printf("%d ", A[i][j]);
            }
            printf("\n");
        }
    }else{
        puts("Некорректные размеры матрицы");
    }

    
    return 0;
}