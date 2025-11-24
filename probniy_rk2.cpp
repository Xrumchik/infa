#include <iostream>
#include <stdlib.h>
#include <stdio.h>

int ma_kr(int **arr,int n,int m,int &i_m,int &j_m){
    int ma=-1;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if (arr[i][j]>=ma){
                ma=arr[i][j];
                i_m=i;
                j_m=j;
            }
        }
    }
    return ma;
}

int main(){
    int n,m,**arr;
    float summa=0;
    FILE *f;
    f=fopen("test_rk2.txt","r");
    if (f==NULL){
        printf("Ошибка с открытием файла");
        exit(1);
    }
    fscanf(f,"%d%d",&n,&m);
    arr=new int*[n];
    for(int i=0;i<n;i++){
        arr[i]=new int[m];
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            fscanf(f,"%d",&arr[i][j]);
            if (arr[i][j]%2==0)
                summa+=arr[i][j];
        }
    }
    fclose(f);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            printf("%d ",arr[i][j]);
        }
        printf("\n");
    }
    printf("Среднее арифметическое = %f\n",summa/(n*m));

    int ma_kr5=0,i_m=-1,j_m=-1;
    ma_kr5=ma_kr(arr,n,m,i_m,j_m);
    printf("число = %d, i = %d, j = %d\n",ma_kr5,i_m,j_m);

    if (n==m){
        for(int i=0;i<n;i++){
            arr[i][n-i-1]*=3;
        }
    }else{
        printf("Матрица не квадратная");
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            printf("%d ",arr[i][j]);
        }
        printf("\n");
    }
    puts("Напишите номер строки существующий, если ее надо отсортировать");
    int num=-1;
    scanf("%d",&num);
    if (num>0 && num<=n){
        num--;
        for(int i=0;i<m;i++){
            for(int j=0;j<m-1;j++){
                if (arr[num][j+1]>arr[num][j]){
                    int temp=arr[num][j+1];
                    arr[num][j+1]=arr[num][j];
                    arr[num][j]=temp;
                }
            }
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                printf("%d ",arr[i][j]);
            }
            printf("\n");
        }
    }
    int c_otr=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
           if (arr[i][j]<0){
            c_otr++;
           }
        }
    }
    printf("Колво отрицательных чисел: %d",c_otr);
}
