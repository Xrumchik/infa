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
    struct product *ptr;
};


void init_product(product *korzina,FILE *f){
    fscanf(f,"%s",korzina->title);
    fscanf(f,"%f",&(korzina->price));
    fscanf(f,"%s",korzina->department);
    fscanf(f,"%s",korzina->country);
    fscanf(f,"%d",&(korzina->weight));
    korzina->ptr=NULL;
}

void add_elem(product *korzina, FILE *f){
    int n;
    printf("Введите 0(или меньше), если добавить в конец или номер, после которого ввести: ");
    scanf("%d",&n);
    product *temp = new product;
    fscanf(f,"%s",temp->title);
    fscanf(f,"%f",&(temp->price));
    fscanf(f,"%s",temp->department);
    fscanf(f,"%s",temp->country);
    fscanf(f,"%d",&(temp->weight));
    if (n<=0){
        while (korzina->ptr!=NULL){
            korzina=korzina->ptr;
        }
        temp->ptr=NULL;
        korzina->ptr=temp;
    }else{
        int i=1;
        while (i < n && korzina->ptr != NULL) {
            korzina = korzina->ptr;
            i++;
        }
        product *temp2 = korzina->ptr;
        temp->ptr=temp2;
        korzina->ptr=temp;
        
    }
}

struct product *delete_head(product *korzina){
    if (korzina == NULL) return NULL;
    product *temp = new product;
    temp=korzina;
    delete(korzina);
    return (temp->ptr);
    

}

void delete_elem(product *korzina, int n){
    if (n==1){
        korzina=delete_head(korzina);
    }if(n<1){
        puts("Некорректный номер");
    }else{
        int i=1;//по порядковому номеру, а не по индексу
        product *temp = korzina;
        while (i < n-1 && temp->ptr != NULL) {
            temp = temp->ptr;
            i++;
        }
        if (temp->ptr == NULL) {
            puts("Нет продукта с таким номером");
            return;
        }
        product *to_delete = temp->ptr;
        temp->ptr = to_delete->ptr;
        delete to_delete;
    }
}



void print_all_elem(product *korzina){
    while(1){
        printf("Продукт называет: %s, его стоимость: %.2f, его отдел: %s, его страна производитель: %s, его масса: %d.\n", korzina->title,korzina->price,korzina->department, korzina->country,korzina->weight);
        if (korzina->ptr==NULL){
            break;
        }
        korzina=korzina->ptr;
    }
}

void print_elem(product *korzina, int n){
    product *temp = korzina;
    if(n<1){
        puts("Некорректный номер");
    }else{
        int i=1;//по порядковому номеру, а не по индексу
        product *temp = korzina;
        while (i < n && temp->ptr != NULL) {
            temp = temp->ptr;
            i++;
        }
        if (temp->ptr == NULL && i!=n) {
            puts("Нет продукта с таким номером");
            return;
        }
        printf("Продукт называет: %s, его стоимость: %.2f, его отдел: %s, его страна производитель: %s, его масса: %d.\n", temp->title,temp->price,temp->department, temp->country,temp->weight);
    }
}

void search_elem(product *korzina){
    char s[30]={0};
    puts("Введите название продукта, которое искать:");
    scanf("%s",s);
    int flag=-1,i=1;
    product *temp = korzina;
    while (1) {
        if (strcmp(temp->title,s)==0){
            flag=1;
            printf("По вашему запросу найден продукт %s, вот его описание:\n",s);
            print_elem(korzina,i);
            break;
        }
        i++;
        if (temp->ptr==NULL){
            break;
        }
        temp=temp->ptr;
    }
    if (flag==-1){
        puts("К сожалению в нашем магазине нет продукта с таким названием");
    }
}

void sort_products(product* &korzina) {
    if (korzina == NULL || korzina->ptr == NULL) {
        return;
    }
    bool swapped;
    product* last = NULL;
    do {
        swapped = false;
        product* prev = NULL;
        product* curr = korzina;
        while (curr->ptr != last) {
            product* first = curr;
            product* second = curr->ptr;
            product* rest = second->ptr;
            if (strcmp(first->department, second->department) > 0) {
                if (prev == NULL) {
                    korzina = second;
                } else {
                    prev->ptr = second;
                }
                second->ptr = first;
                first->ptr = rest;
                swapped = true;
                prev = second;
            } else {
                prev = first;
                curr = curr->ptr;
            }
        }
        last = curr;
    } while (swapped);
}

void clear_products(product* &korzina) {
    if (korzina == NULL) {
        return;
    }
    
    product* cur = korzina;
    while (cur != NULL) {
        product* next = cur->ptr;
        delete cur;
        cur = next;
    }
    
    delete korzina;
}

int main(){
    int n=0,num;
    FILE *ishod;
    ishod=fopen("laba1.txt","r");
    product *korzina;
    korzina = new product; 
    init_product(korzina,ishod);
    print_all_elem(korzina);
    while (1){
        printf("Панель управления:\n1.Вывести все продукты на экран\n2.Добавить продукт\n3.Найти продукт по стране производства\n4.Отсортировать по отделу продукты(в алфавитном порядке)\n5.Выход из программы\nВведите номер задачи: ");
        scanf("%d",&num);
        switch (num){
        case 1:
            print_all_elem(korzina);
            break;
        case 2:
            add_elem(korzina,ishod);
            break;
        case 3:
            search_elem(korzina);
            break;
        case 4:
            sort_products(korzina);
            break;
        case 5:
            puts("Всего хорошего! До свидания!");
            clear_products(korzina);
            fclose(ishod);
            exit(1);
            break;
        default:
            puts("Команды с таким номером нет");
            break;
        }
    }
    
}

