#include <cmath>
#include <iostream>

int main(){
    float A,B,h;
    scanf("%f%f%f", &A,&B,&h);
    if (B<A || h<0){
        puts("Нет чисел");
    }else{
        for (float i=A;i<=B;i+=h){
            printf("%.2f ; ",i);
            if (i<0 || i>=20){
                printf("нет значений\n");
            }else{
                if (i>=0 && i<=5){
                    if (i==0 || i==5){
                        printf("нет значений\n");
                    }else{
                        printf("%.2f\n", 5+log10(i)/(i-5));
                    }
                }else{
                    printf("%.2f\n",sqrt(10*i-5));
                }
            }
        }
    }
    return 0;
}