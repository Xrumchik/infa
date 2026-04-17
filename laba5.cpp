#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <cctype>

struct product
{
    char title[30];
    float price;
    char department[30];
    char country[30];
    int weight;
    product *prev;
    product *nxt;
};


void init_product(product *korzina,FILE *f){
    fscanf(f,"%s",korzina->title);
    fscanf(f,"%f",&(korzina->price));
    fscanf(f,"%s",korzina->department);
    fscanf(f,"%s",korzina->country);
    fscanf(f,"%d",&(korzina->weight));
    korzina->nxt=korzina;
    korzina->prev=korzina;
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
    product *cur=korzina;
    if (korzina->nxt==NULL){
        korzina->nxt=temp;
        korzina->prev=temp;
    }else{
        if (n<=0){
            while (korzina->nxt!=cur){
                korzina=korzina->nxt;
            }
            temp->nxt=cur;
            temp->prev=korzina;
            korzina->nxt=temp;
        }else{
            int i=1;
            while (i < n) {
                korzina = korzina->nxt;
                i++;
            }
            product *temp2 = korzina->nxt;
            temp->nxt=temp2;
            temp->prev=korzina;
            korzina->nxt=temp;
            
        }
    }
    
}

void print_all_elem(product *korzina){
    product *temp=korzina;
    if (korzina->nxt==NULL){
        puts("Корзина пустая");
    }else{
        while(1){
            printf("Продукт называет: %s, его стоимость: %.2f, его отдел: %s, его страна производитель: %s, его масса: %d.\n", korzina->title,korzina->price,korzina->department, korzina->country,korzina->weight);
            korzina=korzina->nxt;
            if (korzina==temp){
                break;
            }
        }
    }
}

void cnt_uzl(product *korzina){
    char s[3]={0};
    char ccc[30]={0};
    puts("Введите букву, по которой мы будем считать кол-во продуктов, название которых начинается с нее:");
    scanf("%s",s);
    s[0]=tolower(s[0]);
    int cnt=0;
    product *temp = korzina;
    while(1){
        strcpy(ccc,korzina->title);
        ccc[0]=tolower(ccc[0]);
        if (strncmp(ccc,s,1)==0){
            cnt+=1; 
        }
        korzina=korzina->nxt;
        if (korzina==temp){
            break;
        }
    }
    printf("Сейчас в корзине есть %d продуктов, название которых начинается на букву %s\n",cnt,s);
}

void clear_products(product* &korzina) {
    if (korzina == NULL) {
        return;
    }
    
    product* cur = korzina;
    while (cur != NULL) {
        product* next = cur->nxt;
        delete cur;
        cur = next;
    }
    
    delete korzina;
}

product* delete_chet_el(product* head) {
    if (head->nxt == head) {
        puts("В списке 1 элемент, удалять нечего");
        return head; 
    }
    int len = 0;
    product* p = head;
    do { 
        len++; 
        p = p->nxt; 
    } while (p != head);
    int i = 0;
    product* cur = head;         
    int del = 0;
    int need_del = (len + 1) / 2; 
    while (del < need_del) {      
        if (i % 2 == 0) {
            product* temp = cur->nxt;
            cur->nxt = temp->nxt;
            cur->nxt->prev = cur;
            if (temp == head) {   
                head = cur->nxt;
            }
            delete temp;          
            del++;               
        }
        i++;
        cur = cur->nxt;
    }
    return head;
}

int main(){
    int n=0,num;
    FILE *ishod;
    ishod=fopen("laba1.txt","r");
    product *korzina;
    korzina = new product;
    init_product(korzina,ishod);
    while (1){
        printf("Панель управления:\n1.Вывести все продукты на экран\n2.Добавить продукт(работает зацикленность)\n3.Подсчитать кол-во элементов, название которых начинается на введенную букву\n4.Удалить элементы, стоящие на четных позициях\n5.Выход из программы\nВведите номер задачи: ");
        scanf("%d",&num);
        switch (num){
        case 1:
            print_all_elem(korzina);
            break;
        case 2:
            add_elem(korzina,ishod);
            break;
        case 3:
            cnt_uzl(korzina);
            break;
        case 4:
            korzina=delete_chet_el(korzina);
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
