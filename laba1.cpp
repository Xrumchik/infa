#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>

struct product
{
    char title[30];
    float price;
    char department[30];
    char country[30];
    int weight;
};

void filling_store(FILE *f, product *store,int n){
    for(int i=0;i<n;i++){
        fscanf(f,"%s",store[i].title);
        fscanf(f,"%f",&(store[i].price));
        fscanf(f,"%s",store[i].department);
        fscanf(f,"%s",store[i].country);
        fscanf(f,"%d",&(store[i].weight));
    }
}

void print_store(product *store,int n){
    printf("У нас в магазине есть %d различных продуктов:\n", n);
    for (int i=0;i<n;i++){
        printf("%d. %s.\n", i+1,store[i].title);
    }
}

void print_product(product *store,int n){
    int i=n-1;
    printf("Продукт называет: %s, его стоимость: %.2f, его отдел: %s, его страна производитель: %s, его масса: %d.\n", store[i].title,store[i].price,store[i].department, store[i].country,store[i].weight);
}

void search_product(product *store, int n){
    char s[30]={0};
    puts("Введите название продукта, которое будем искать:");
    scanf("%s",&s);
    int flag=-1;
    for(int i=0;i<n;i++){
        if (strcmp(store[i].title,s)==0){
            flag=1;
            printf("По вашему запросу найден продукт %s, вот его описание:\n",s);
            print_product(store,i+1);
            break;
        }
    }
    if (flag==-1){
        puts("К сожалению в нашем магазине нет продукта с таким названием");
    }
}

void sort_store(product *store, int n, bool vozr){
    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            if (store[j].price>store[j+1].price && vozr==1){
                product temp=store[j];
                store[j]=store[j+1];
                store[j+1]=temp;
            }
            if (store[j].price<store[j+1].price && vozr==0){
                product temp=store[j];
                store[j]=store[j+1];
                store[j+1]=temp;
            }
        }
    }
    if (vozr){
        puts("Отсортировванные по возрастанию продукты:");
    }else{
        puts("Отсортировванные по убыванию продукты:");
    }
    print_store(store,n);
}


int main(){
    int n,num,gg=0;
    FILE *ishod;
    ishod=fopen("laba1.txt","r");
    printf("Введите кол-во продуктов от 6 до 10 включительно: ");
    scanf("%d",&n);
    //n=6;
    printf("\n");
    if (n>10 || n<=5){
        puts("Вам отказано в обслуживании без объяснения причины");
        exit(1);
    }
    product *store;
    store=new product[n];
    filling_store(ishod,store,n);
    for(int i=0;i<n;i++){
        print_product(store,i+1);  
    }
    while (1){
        printf("Панель управления:\n1.Вывести все продукты на экран\n2.Найти продукт по названию\n3.Отсортировать продукты по цене\n4.Выйти из программы\nВведите номер задачи: ");
        scanf("%d",&num);
        switch (num){
        case 1:
            print_store(store,n);
            break;
        case 2:
            search_product(store,n);
            break;
        case 3:
            printf("Введите 1, если хотите отсортировать продукты по возрастанию цены и 0, если по убыванию: ");
            scanf("%d",&gg);
            if (gg!=0 && gg!=1){
                puts("Вы ввели не то");
                break;
            }else{
                sort_store(store,n,gg);
            }
            
            break;
        case 4:
            puts("Всего хорошего! До свидания!");
            exit(1);
            break;
        default:
            puts("Команды с таким номером нет");
            break;
        }
    }
    delete store;
    fclose(ishod);
}
