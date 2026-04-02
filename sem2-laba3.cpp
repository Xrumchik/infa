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

struct ochered{
    product *bgn, *eend;
};

void init_ochered(ochered *och){
    och->eend=NULL;
    och->bgn=NULL;
}

bool is_empty(ochered *och){
    if(och->bgn==NULL){
        return 1;
    }
    return 0;
}

void add_elem(ochered *och,FILE *f){
    product *korzina=new product;
    fscanf(f,"%s",korzina->title);
    fscanf(f,"%f",&(korzina->price));
    fscanf(f,"%s",korzina->department);
    fscanf(f,"%s",korzina->country);
    fscanf(f,"%d",&(korzina->weight));
    korzina->ptr=NULL;
    if (is_empty(och)){
        och->eend=korzina;
        och->bgn=och->eend;
    }else{
        och->eend->ptr=korzina;
        och->eend=och->eend->ptr;
    }
    

}

bool zapoln(ochered *och){
    int i=0;
    product *temp=och->bgn;
    while (temp!=NULL){
        i+=1;
        temp=temp->ptr;
    }
    if (i==8){
        return 1;
    }
    return 0;
}

ochered  *delete_head(ochered *och){
    if (is_empty(och)){
        return och;
    }
    delete(och->bgn);
    och->bgn=och->bgn->ptr;
    return (och);
    

}

void print_all_elem(ochered *och){
    if (is_empty(och)){
        puts("Очередь пустая");
    }else{
        product *temp;
        for(temp=och->bgn;temp!=NULL;temp=temp->ptr){
            printf("Продукт называет: %s, его стоимость: %.2f, его отдел: %s, его страна производитель: %s, его масса: %d.\n", temp->title,temp->price,temp->department, temp->country,temp->weight);
        }
    }
    
}

ochered  *work_with_och(ochered *och){
    ochered *new_och=new ochered;
    init_ochered(new_och);
    char s[30]={0};
    puts("Введите название отдела, в котором меняем цену:");
    scanf("%s",s);
    product *temp = och->bgn;
    while (1) {
        if (strcmp(temp->department,s)==0){
            temp->price=temp->price*0.8;
            if (temp->price>=10){
                if (is_empty(new_och)){
                    new_och->eend=temp;
                    new_och->bgn=new_och->eend;
                }else{
                    new_och->eend->ptr=temp;
                    new_och->eend=new_och->eend->ptr;
                }
            }
        }else{
            if (is_empty(new_och)){
                new_och->eend=temp;
                new_och->bgn=new_och->eend;
            }else{
                new_och->eend->ptr=temp;
                new_och->eend=new_och->eend->ptr;
            }
        }
        if (temp->ptr==NULL){
            break;
        }
        temp=temp->ptr;
    }
    return (new_och);
}

int main(){
    FILE *ishod;
    int num;
    ishod=fopen("laba3-4.txt","r");
    ochered *och=new ochered;
    init_ochered(och);
    while (1){
        printf("Панель управления:\n1.Вывести всю очередь на экран\n2.Добавить продукт в очередь\n3.Работа с очередью.\n4.Выход из программы\nВведите номер задачи: ");
        scanf("%d",&num);
        switch (num){
        case 1:
            print_all_elem(och);
            break;
        case 2:
            if (zapoln(och)){
                puts("Нельзя добавить, т.к. очередь заполнена");
            }else{
                add_elem(och,ishod);
            }
            break;
        case 3:
            och=work_with_och(och);
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

