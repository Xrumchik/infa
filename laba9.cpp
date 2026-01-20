 #include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstring>

int main()
{
    int c5=0,num1,num2,j=-1,k=0,kolvo_sl=0;
    char str[100],smb,arr[100][100];
    scanf("%s",str);//конец слова = "_"
    puts("Исходная строка");
    puts(str);
    //printf("%d\n",strlen(str));
    for(int i=0;i<strlen(str);i++){
        if (str[i]!='_' && str[i]!='\0' && k==0){
            j+=1;
        }
        if (str[i]!='_' && str[i]!='\0'){
            arr[j][k]=str[i];
            k+=1;
        }else{
            k=0;
        }
    }
    kolvo_sl=j+1;
    for(int i=0;i<kolvo_sl;i++){
        if (strlen(arr[i])%5==0)
            c5+=1;
    }
    printf("Кол-во слов, у которых длина кратна 5: %d\n",c5);
    //printf("%d",kolvo_sl);
    char b=getchar();
    printf("Введите символ:");
    scanf("%c",&smb);
    int mx_c=-1,mx_i=0,cur_c=0;
    for(int i=0;i<kolvo_sl;i++){
        cur_c=0;
        for(int j=0;j<strlen(arr[i]);j++){
            if (arr[i][j]==smb){
                cur_c+=1;
            }
        }
        if (cur_c>mx_c){
            mx_c=cur_c;
            mx_i=i;
        }
    }
    if (mx_c==-1){
        printf("В строке нет слова с буквой %c\n",smb);
    }else{
        printf("Слово в котором больше всего символа %c: %s\n",smb,arr[mx_i]);
    }

    puts("Введите номера слов для их замены");
    scanf("%d%d",&num1,&num2);
    if (num1>kolvo_sl || num2>kolvo_sl){
        puts("Ошибка: слов с такими номерами в строке нет");
        exit(1);
    }
    char temp[100];
    strcpy(temp,arr[num1-1]);
    strcpy(arr[num1-1],arr[num2-1]);
    strcpy(arr[num2-1],temp);
    printf("Строка с сменами слов:");
    for(int i=0;i<kolvo_sl;i++){
        printf("%s",arr[i]);
        if ((i+1)!=kolvo_sl){
            printf("_");
        }else{
            printf("\n");
        }
    }

    puts("Отсортитрованная строка");
    for(int i=0;i<kolvo_sl;i++){
        for(int j=0;j<kolvo_sl-1;j++){
            if (strcmp(arr[j],arr[j+1])>0){
                char temp[100];
                strcpy(temp,arr[j]);
                strcpy(arr[j],arr[j+1]);
                strcpy(arr[j+1],temp);
            }
        }
    }
    for(int i=0;i<kolvo_sl;i++){
        printf("%s",arr[i]);
        if ((i+1)!=kolvo_sl){
            printf("_"); // такой же вывод
        }else{
            printf("\n");
        }
    }


    puts("Строка с перевернутыми словами");
    for(int i=0;i<kolvo_sl;i++){
        for(int j=strlen(arr[i])-1;j>=0;j--){
            printf("%c",arr[i][j]);
        }
        if ((i+1)!=kolvo_sl){
            printf("_");
        }else{ // такой же вывод
            printf("\n");
        }
    }

    return 0;
}
