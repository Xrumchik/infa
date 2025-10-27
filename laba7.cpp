#include <iostream>

void arr1_in(int *A,int n){
    for(int i=0;i<n;i++){
        scanf("%d",&A[i]);
    }
    return;
}

void arr1_out(int *A,int n){
    printf("Адрес массива: %p\n",A);
    for(int i=0;i<n;i++){
        printf("Адрес элемента: %p и значение: %d\n", &A[i],A[i]);
    }
    return;
}

void arr2_in(int **A,int n,int m){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%d",&A[i][j]);
        }
        
    }
    return;
}

void arr2_out(int **A,int n,int m){
    printf("Адрес массива: %p\n",A);
    for(int i=0;i<n;i++){
        printf("Адрес массива указателей на строки: %p\n", &A[i]);
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            printf("Адрес элемента массива: %p и значение: %d\n", &A[i][j],A[i][j]);
        }
    }
    return;
}

void arr3_in(int (&A)[2][3]){
    for(int i=0;i<2;i++){
        for(int j=0;j<3;j++){
            scanf("%d",&A[i][j]);
        }
        
    }
    return;
}

void arr3_out(int (&A)[2][3]){
    printf("Адрес массива: %p\n",&A);
    for(int i=0;i<2;i++){
        for(int j=0;j<3;j++){
            printf("Адрес элемента массива: %p и значение: %d\n", &A[i][j],A[i][j]);
        }
    }
    return;
}


int main(){
    int *A,a,*c,C,*d1,**d2,n1,n2,m2, d3[2][3];
    puts("Введите переменную:");
    scanf("%d",&a);
    A=&a;
    printf("Адрес переменой а: %p и ее значение: %d\n",A,*A);

    // printf("Пробуем вывести значение пустого указателя c: %d",*c); -> ошибка Segmentation fault

    puts("Введите переменную:");
    scanf("%d",&C);
    c=&C;
    printf("Адрес переменой C: %p и ее значение: %d\n",c,*c);

    printf("Введите положительное кол-во элементов для массива d1(одномерного динамического):");
    scanf("%d",&n1);
    if (n1<1){
        printf("Некорректное колво элементов");
        return 0;
    }
    d1=new int[n1];
    printf("Введите массив одномерный длиной: %d\n",n1);
    arr1_in(d1,n1);
    arr1_out(d1,n1);

    printf("Введите размеры массива d2(двумерного динамического):");
    scanf("%d%d",&n2,&m2);
    if (n2<1 || m2<1){
        printf("Некорректное колво элементов");
        return 0;
    }
    d2=new int*[n2];
    for(int i=0;i<n2;i++){
        d2[i]=new int[m2];
    }
    printf("Введите двумерный массив одномерный длиной: %d*%d\n",n2,m2);
    arr2_in(d2,n2,m2);
    arr2_out(d2,n2,m2);

    puts("Введите двумерный массив 2*3");
    arr3_in(d3);
    arr3_out(d3);


    delete []d1;
    for(int i=0;i<n2;i++){
        delete[] d2[i];
    }
    delete []d2;
    return 0;
}
