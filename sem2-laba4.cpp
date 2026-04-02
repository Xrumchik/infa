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

struct stack{
    product *verh;
};

bool is_empty(stack *stk){
    if(stk->verh==NULL){
        return 1;
    }
    return 0;
}

void add_elem(stack *stk,FILE *f){
    product *korzina=new product;
    fscanf(f,"%s",korzina->title);
    fscanf(f,"%f",&(korzina->price));
    fscanf(f,"%s",korzina->department);
    fscanf(f,"%s",korzina->country);
    fscanf(f,"%d",&(korzina->weight));
    korzina->ptr=NULL;
    if (is_empty(stk)){
        stk->verh=korzina;
    }else{
        korzina->ptr=stk->verh;
        stk->verh=korzina;
    }
    

}

void init_stack(stack *stk,int n,FILE *f){
    stk->verh=NULL;
    for(int i=0;i<n;i++){
        add_elem(stk,f);
    }
}





bool zapoln(stack *stk){
    int i=0;
    product *temp=stk->verh;
    while (temp!=NULL){
        i+=1;
        temp=temp->ptr;
    }
    if (i==8){
        return 1;
    }
    return 0;
}

stack  *delete_head(stack *stk){
    if (is_empty(stk)){
        return stk;
    }
    delete(stk->verh);
    stk->verh=stk->verh->ptr;
    return (stk);
    

}

void print_all_elem(stack *stk){
    if (is_empty(stk)){
        puts("Стек пустой");
    }else{
        product *temp;
        for(temp=stk->verh;temp!=NULL;temp=temp->ptr){
            printf("Продукт называет: %s, его стоимость: %.2f, его отдел: %s, его страна производитель: %s, его масса: %d.\n", temp->title,temp->price,temp->department, temp->country,temp->weight);
        }
    }
    
}

void work_with_stk(stack *&stk1,stack *&stk2,int n){
    int x;
    product *temp;
    puts("Введите необходимый вес товара:");
    scanf("%d",&x);
    if (n==1){
        temp=stk1->verh;
        stk1->verh=stk1->verh->ptr;
        temp->ptr=NULL;
        if ((stk1->verh->weight)>x){
            if (is_empty(stk2)){
                stk2->verh=temp;
            }else{
                temp->ptr=stk2->verh;
                stk2->verh=temp;
            }
        }
    }else{
        temp=stk2->verh;
        stk2->verh=stk2->verh->ptr;
        temp->ptr=NULL;
        if ((stk2->verh->weight)>x){
            if (is_empty(stk1)){
                stk1->verh=temp;
            }else{
                temp->ptr=stk1->verh;
                stk1->verh=temp;
            }
        }
        
    }
}

int main(){
    FILE *ishod;
    int num,n;
    ishod=fopen("laba3-4.txt","r");
    stack *stk1=new stack;
    stack *stk2=new stack;
    init_stack(stk1,8,ishod);
    init_stack(stk2,0,ishod);
    while (1){
        printf("\nПанель управления:\n1.Вывести весь стек на экран\n2.Добавить продукт в стек\n3.Работа со стеком.\n4.Выход из программы\nВведите номер задачи: ");
        scanf("%d",&num);
        puts("Введите номер стека, c которым хотите работать:(1/2)");
        scanf("%d",&n);
        switch (num){
        case 1:
            if (n==1){
                print_all_elem(stk1);
            }else{
                print_all_elem(stk2);
            }
            break;
        case 2:
            if (n==1){
                if (zapoln(stk1)){
                    puts("Нельзя добавить, т.к. стек заполнен");
                }else{
                    add_elem(stk1,ishod);
                }
            }else{
                if (zapoln(stk2)){
                    puts("Нельзя добавить, т.к. стек заполнен");
                }else{
                    add_elem(stk2,ishod);
                }
            }
            break;
        case 3:
            if (n==1){
                if (is_empty(stk1)){
                    puts("Нельзя работать, т.к. стек пустой");
                }else{
                    work_with_stk(stk1,stk2,n);
                }
            }else{
                if (is_empty(stk2)){
                    puts("Нельзя работать, т.к. стек пустой");
                }else{
                    work_with_stk(stk1,stk2,n);
                }
            }
            break;
        case 4:
            puts("Всего хорошего! До свидания!");
            fclose(ishod);
            exit(1);
            break;
        default:
            puts("Команды с таким номером нет");
            break;
        }
    }
}

