#include <iostream>
#include <cmath>

int main(){
    int n,m,f=0;
    float A[10][10], A1[100][2],eps=1e-6;
    for (int i = 0; i < 100; ++i) {
        A1[i][0] = 1000000;
        A1[i][1]=0;
    }
    puts("Введите размеры матрицы(кол-во строк и стобцов):");
    scanf("%d%d", &n,&m);
    if (n<=10 && n>0 && m<=10 && m>0){
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                scanf("%f",&A[i][j]);
                f=0;
                for (int k=0;k<100;k++){
                    if (abs(A1[k][0]-A[i][j])<eps){
                        f=1;
                        A1[k][1]+=1;
                        break;
                    }
                }
                if (f==0){
                    for (int k=0;k<100;k++){
                        if (abs(A1[k][0]-1000000)<eps){
                            A1[k][0]=A[i][j];
                            A1[k][1]++;
                            break;
                        }
                        
                    }
                }
            }
        }
        int c=0;
        for(int i=0;i<100;i++){
            if (A1[i][1]>1){
                c++;
            }
        }
        printf("Найдено пар: %d",c);
    }else{
        puts("Некорректные размеры матрицы");
    }

    
    return 0;
}