#include <iostream>

int main(){
    int n,max_i=0,min_i=0;
    float A[21],max_el=0,min_el=0,temp=0;
    
    scanf("%d",&n);
    if (n>0 && n<=20){
        for(int i=0;i<n;i++){
            scanf("%f",&A[i]);
        }
        max_el=A[0];
        min_el=A[0];
        for (int i=0;i<n;i++){
            if (A[i]>=max_el){
                max_el=A[i];
                max_i=i;
            }
            if (A[i]<min_el){
                min_el=A[i];
                min_i=i;
            }
        }
        printf("Максимальный эл: %.2f, его индекс: %d\n",max_el,max_i);
        printf("Минимальный эл: %.2f, его индекс: %d\n",min_el,min_i);

        for (int i=0;i<n;i++){
            for (int j=0;j<n-1;j++){
                if (A[j+1]==0 && A[j]<0){
                    temp = A[j];
                    A[j] = A[j+1];
                    A[j+1] = temp;
                }else{
                    if (A[j]==0 && A[j+1]>0){
                        temp = A[j];
                        A[j] = A[j+1];
                        A[j+1] = temp;
                    }else{
                        if ((A[j]>A[j+1] || (A[j]<0 && A[j+1]>0)) && A[j]!=0 && A[j+1]!=0){
                            temp = A[j];
                            A[j] = A[j+1];
                            A[j+1] = temp;
                        }
                    }
                }
                
            }
        }

    for(int i=0;i<n;i++){
        printf("%.2f; ",A[i]);
    }

    }else{
        puts("Неверное число элементов");
    }
    
    return 0;
}