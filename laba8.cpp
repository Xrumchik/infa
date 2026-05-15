#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

class A{
private:
    float price;
protected:
    char *title;
    int weight;
    char *department;
    char *country;
public:
    float get_price(){return price;}
    void set_price(float &p){price=p;}
    void print_el();
    void init_el(FILE *f);
    float obsh_price();
    friend void fa(A arr[10]);
    A(){
        title=new char [30];
        department=new char [30];
        country=new char [30];
    }
    A(char *t, float p, char *dep, char *c, int w){
        title=new char [strlen(t)+1];
        strcpy(title,t);
        price=p;
        department=new char [strlen(dep)+1];
        strcpy(department,dep);
        country=new char [strlen(c)+1];
        strcpy(country,c);
        weight=w;

    };
    A(char *t, char *dep, char *c){
        title=new char [strlen(t)+1];
        strcpy(title,t);
        price=500;
        department=new char [strlen(dep)+1];
        strcpy(department,dep);
        country=new char [strlen(c)+1];
        strcpy(country,c);
        weight=1000;

    };
    A(A &curr){
        title=new char [strlen(curr.title)+1];
        strcpy(title,curr.title);
        price=curr.price;
        department=new char [strlen(curr.department)+1];
        strcpy(department,curr.department);
        country=new char [strlen(curr.country)+1];
        strcpy(country,curr.country);
        weight=curr.weight;
    }
    ~A(){
        delete [] title,department,country;
    }
};

class Fa : public A{
private:
    int cnt_sugar;
    char *shop;
protected:
    int cnt_salt;
public:
    int cnt_tasty(){
        return 10-abs(cnt_salt-cnt_sugar);
    };
    Fa(){
        shop=new char [30];
    }
    Fa(char *t, float p, char *dep, char *c, int w, char *s, int sug,int slt):A(t,p,dep,c,w){
        shop=new char [strlen(s)+1];
        strcpy(shop,s);
        cnt_sugar=sug;
        cnt_salt=slt;

    };
    Fa(char *t, char *dep, char *c, char *s):A(t,dep,c){
        shop=new char [strlen(s)+1];
        strcpy(shop,s);
        cnt_sugar=5;
        cnt_salt=4;
    };
    Fa(Fa &curr):A(curr.title,curr.get_price(),curr.department,curr.country,curr.weight){
        shop=new char [strlen(curr.shop)+1];
        strcpy(shop,curr.shop);
        cnt_salt=curr.cnt_salt;
        cnt_sugar=curr.cnt_sugar;
    }
    ~Fa(){
        delete [] shop;
    }
    void print_el(){
        printf("Продукт называет: %s, его стоимость: %.2f, его отдел: %s, его страна производитель: %s, его масса: %d, кол-во соли: %d, кол-во сахара: %d, магазин: %s.\n", title,get_price(),department, country,weight,cnt_salt,cnt_sugar,shop);
    }
    void init_el(FILE *f);
};



void fa(A arr[10]){
    char s[30]={0};
    puts("Введите название страны, для товаров из которой будем считать общую стоимость закупки");
    scanf("%s",s);
    float cnt=0;
    for(int i=0;i<10;i++){
        if (strcmp(s,arr[i].country)==0){
            cnt+=arr[i].obsh_price();
        }
    }
    if (cnt==0){
        puts("Нет товаров из этой страны");
    }else{
        printf("Общая цена закупок для товаров из страны %s равна %.2f",s,cnt);
    }
    
}

float A::obsh_price(){
    float obsh;
    return (float(weight)/1000.0)*price;
}

void A::print_el(){
    printf("Продукт называет: %s, его стоимость: %.2f, его отдел: %s, его страна производитель: %s, его масса: %d.\n", title,price,department, country,weight);
}

void A::init_el(FILE *f){
    fscanf(f,"%s",title);
    fscanf(f,"%f",&(price));
    fscanf(f,"%s",department);
    fscanf(f,"%s",country);
    fscanf(f,"%d",&(weight));
}

void Fa::init_el(FILE *f){
    float p;
    fscanf(f,"%s",title);
    fscanf(f,"%f",&(p));
    fscanf(f,"%s",department);
    fscanf(f,"%s",country);
    fscanf(f,"%d",&(weight));
    fscanf(f,"%d",&(cnt_sugar));
    fscanf(f,"%d",&(cnt_salt));
    fscanf(f,"%s",shop);
    set_price(p);
}


int main(){
    SetConsoleOutputCP(65001);
    Fa arr[10];
    FILE *ishod=fopen("laba8.txt","r");
    for(int i=0;i<10;i++){
        arr[i].init_el(ishod);
        arr[i].print_el();
        printf("Уровень вкуса продукта №%d: %d\n", i,arr[i].cnt_tasty());
    }
    puts("Конструктор по умолчанию");
    Fa s1;
    s1.print_el();
    puts("Конструктор копирования");
    Fa s2=arr[9];
    s2.print_el();
    puts("Конструктор полностью");
    Fa s3("Yabkoko",123,"Frukti","Somali",321,"KupiShop",7,3);
    s3.print_el();
    puts("Конструктор только с символами");
    Fa s4("Yabkoko","Frukti","Somali", "U_Doma");
    s4.print_el();
    fclose(ishod);
    return 0;
}