#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>

class A{
private:
    char title[30];
    float price;
    char department[30];
    char country[30];
    int weight;
public:
    void print_el();
    void init_el(FILE *f);
    void work();
    friend void fa();
};

void fa(){

}

void A::work(){

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


int main(){
    A arr[10];
    FILE *ishod=fopen("laba1.txt","r");
    for(int i=0;i<10;i++){
        arr[i].init_el(ishod);
        arr[i].print_el();
    }
}
