#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>

struct meal
{
    char title[30];
    int price;
    char ingredient1[30];
    char ingredient2[30];
    char ingredient3[30];
    int weight;
};

void filling_menu(FILE *f, meal *arr,int n){
    for(int i=0;i<n;i++){
        fscanf(f,"%s",arr[i].title);
        fscanf(f,"%d",&(arr[i].price));
        fscanf(f,"%s",arr[i].ingredient1);
        fscanf(f,"%s",arr[i].ingredient2);
        fscanf(f,"%s",arr[i].ingredient3);
        fscanf(f,"%d",&(arr[i].weight));
    }
}

void print_menu(meal *arr,int n){
    printf("У нас в меню есть %d блюд:\n", n);
    for (int i=0;i<n;i++){
        printf("%d. %s.\n", i+1,arr[i].title);
    }
}

void print_meal(meal *arr,int n){
    int i=n-1;
    printf("Блюдо называет: %s, его стоимость: %d, его первый ингредиент: %s, его второй ингредиент: %s, его третий ингредиент: %s, его масса: %d.\n", arr[i].title,arr[i].price,arr[i].ingredient1, arr[i].ingredient2,arr[i].ingredient3, arr[i].weight);
}

void search_meal(meal *arr, int n){
    char s[30]={0};
    puts("Введите название блюда, которое будем искать в меню:");
    scanf("%s",&s);
    int flag=-1;
    for(int i=0;i<n;i++){
        if (strcmp(arr[i].title,s)==0){
            flag=1;
            printf("По вашему запросу найдено блюдо %s, вот его описание:\n",s);
            print_meal(arr,i+1);
            break;
        }
    }
    if (flag==-1){
        puts("К сожалению в нашем меню нет блюда с таким названием");
    }
}

void create_new_menu(meal *arr, meal *cur_arr, int n){
    int pricce;
    char ingred[30];
    printf("Введите минимальную стоимость блюда для нового меню и необходимый ингредиент у всех блюд:");
    scanf("%d%s",&pricce,&ingred);
    int cnt=0;
    for(int i=0;i<n;i++){
        if (arr[i].price>pricce && (strcmp(arr[i].ingredient1,ingred)==0 || strcmp(arr[i].ingredient2,ingred)==0 || strcmp(arr[i].ingredient3,ingred)==0)){
            cur_arr[cnt]=arr[i];
            cnt+=1;
        }
    }
    if (cnt==0){
        puts("Меню оказалось пустым");
    }{
        puts("Наше новое меню и описанию блюд из него:");
        print_menu(cur_arr,cnt);
        for(int i=0;i<cnt;i++){
            print_meal(arr,i+1);  
        }
    }
    
}

void sort_menu(meal *arr, int n, bool vozr){
    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            if (arr[j].price>arr[j+1].price && vozr==1){
                meal temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
            if (arr[j].price<arr[j+1].price && vozr==0){
                meal temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
    if (vozr){
        puts("Отсортировванное по возрастанию меню:");
    }else{
        puts("Отсортировванное по убыванию меню:");
    }
    print_menu(arr,n);
}


int main(){
    int n;
    FILE *ishod;
    ishod=fopen("laba0.txt","r");
    printf("Введите кол-во блюд от 5 до 10 включительно: ");
    scanf("%d",&n);
    //n=5;
    printf("\n");
    if (n>10 || n<5){
        puts("Вам отказано в обслуживании без объяснения причины");
        exit(1);
    }
    meal arr[10],temp_arr[10];
    filling_menu(ishod,arr,n);
    print_menu(arr,n);
    for(int i=0;i<n;i++){
        print_meal(arr,i+1);  
    }
    int gg=0;
    printf("Введите 1, если хотите отсортировать меню по возрастанию цены и 0, если по убыванию");
    scanf("%d",&gg);
    sort_menu(arr,n,gg);
    search_meal(arr,n);
    create_new_menu(arr,temp_arr,n);
    fclose(ishod);
}