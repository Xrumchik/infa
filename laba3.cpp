#include <iostream>
#include <cmath>

int main(){
    int n,a,b;
    float A[21],s=0,sg=1;

    scanf("%d",&n);
    if (n>0 && n<=20){
        for (int i=0;i<n;i++){
            scanf("%f",&A[i]);
        }
        for (int i=0;i<n;i++){
            if (A[i]>0){
                printf("%.2f ", A[i]);
            }else{
                if (A[i]==0){
                    A[i]=10;
                }
            }
        }
        printf("\n");
        for (int i=0;i<n;i++){
            s+=A[i];
            if (A[i]<0){
                printf("%.2f ", A[i]);
            }
        }
        printf("\n%.2f\n",s/n);
        scanf("%d%d", &a,&b);
        if (a==b || b<a||b>(n-1)||b<0||a<0||a>(n-1)){
            puts("Необходимо вводить корректные индексы");
        }else{
            for (int i=a+1;i<b;i++){
                sg*=A[i];
            }
            if (sg<0){
                puts("Нет значения");
            }else{
                printf("%.2f", pow(sg,1.0/(float)(b-a-1)));
            }
        }
    }else{
        puts("Неверное число элементов");
    }



    return 0;
}