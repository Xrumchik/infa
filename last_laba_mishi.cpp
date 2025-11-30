#include <iostream>
#include <random>
using namespace std;

void error_game(){
    puts("Ошибка: некорректно введенные данные");
    exit(1);
}

void zero_arr(int **arr,int n,int m){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            arr[i][j]=0;
        }
    }
}

void create_mouse(int **arr,int n,int m){
    for(int i=1;i<n;i++){
        arr[i][0]=2;
        arr[i][m-1]=3;
    }
}

void create_cheese(int **arr,int n,int m,mt19937 &gen){
    uniform_int_distribution<int> dis_n(0, n-1);
    int cur_cheese=0;
    for(int j=1;j<m-1;j++){
        cur_cheese=0;
        while ((float(cur_cheese+1)/float(n))<0.5){
            for(int i=0;i<n;i++){
                int t=dis_n(gen);
                if (arr[t][j]==0 && (float(cur_cheese+1)/float(n))<=0.8){
                    cur_cheese+=1;
                    arr[t][j]=1;
                }
            }   
        }  
    }
}

void initializing_field(int **arr,int n,int m, mt19937 &gen){
    uniform_int_distribution<int> dis_n(0, n-1);
    uniform_int_distribution<int> dis_m(1, m-1);
    zero_arr(arr,n,m);
    create_mouse(arr,n,m);
    create_cheese(arr,n,m,gen);
}

void print_field(int **arr,int n,int m,int num_motion){
    printf("Текущее положение на поле после хода номер %d:\n",num_motion);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            printf("%d ",arr[i][j]);
        }
        printf("\n");
    }
}

void move_left_mouse(int **arr, int n, int m, int &mouse_count) {
    for(int k=0;k<n*m;k++){
        for (int i=0; i<n; i++) {
            for (int j=m-1; j>=0; j--) {
                if (arr[i][j]==2) {
                    int cur_j=j,cur_i=i;
                    while ((cur_j+1)<m && arr[cur_i][cur_j+1]==0) {
                        arr[cur_i][cur_j]=0;
                        cur_j++;
                        arr[cur_i][cur_j]=2;
                        if (cur_j==(m-1)) {
                            arr[cur_i][cur_j]=0;
                            mouse_count--;
                            break;
                        }
                        for (int i=n-1; i>=0; i--){
                            for (int j=0; j<m; j++) {
                                if (arr[i][j]==2) {
                                    int cur_j=j,cur_i=i;
                                    while ((cur_i+1)<n && arr[cur_i+1][cur_j]==0) {
                                        arr[cur_i][cur_j]=0;
                                        cur_i++;
                                        arr[cur_i][cur_j]=2;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        for (int i=n-1; i>=0; i--){
            for (int j=0; j<m; j++) {
                if (arr[i][j]==2) {
                    int cur_j=j,cur_i=i;
                    while ((cur_i+1)<n && arr[cur_i+1][cur_j]==0) {
                        arr[cur_i][cur_j]=0;
                        cur_i++;
                        arr[cur_i][cur_j]=2;
                    }
                }
            }
        }
    }
}


void move_right_mouse(int **arr, int n, int m, int &mouse_count) {
    for(int k=0;k<n*m;k++){
        for (int i=0; i<n; i++) {
            for (int j=m-1; j>=0; j--) {
                if (arr[i][j]==3) {
                    int cur_j=j,cur_i=i;
                    while ((cur_j-1)>=0 && arr[cur_i][cur_j-1]==0) {
                        arr[cur_i][cur_j]=0;
                        cur_j--;
                        arr[cur_i][cur_j]=3;
                        if (cur_j==0) {
                            arr[cur_i][cur_j]=0;
                            mouse_count--;
                            break;
                        }
                        for (int i=n-1; i>=0; i--){
                            for (int j=0; j<m; j++) {
                                if (arr[i][j]==3) {
                                    int cur_j=j,cur_i=i;
                                    while ((cur_i+1)<n && arr[cur_i+1][cur_j]==0) {
                                        arr[cur_i][cur_j]=0;
                                        cur_i++;
                                        arr[cur_i][cur_j]=3;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        for (int i=n-1; i>=0; i--){
            for (int j=0; j<m; j++) {
                if (arr[i][j]==3) {
                    int cur_j=j,cur_i=i;
                    while ((cur_i+1)<n && arr[cur_i+1][cur_j]==0) {
                        arr[cur_i][cur_j]=0;
                        cur_i++;
                        arr[cur_i][cur_j]=3;
                    }
                }
            }
        }
    }
}

void array_shift(int **arr,int n,int m,int num_column,char shift_direction){
    int *temp_arr=new int[n];
    if (shift_direction=='U'){
        for(int i=1;i<n;i++){
            temp_arr[i-1]=arr[i][num_column-1];
        }
        temp_arr[n-1]=arr[0][num_column-1];
    }else{
        for(int i=0;i<n-1;i++){
            temp_arr[i+1]=arr[i][num_column-1];
        }
        temp_arr[0]=arr[n-1][num_column-1];
    }
    for(int i=0;i<n;i++){
        arr[i][num_column-1]=temp_arr[i];
    }

    delete []temp_arr;
}

void check_pat(int **arr,int n,int m, int **pat_arr,int &cnt_motion_field_same){
    int flag=1,cur_left=0,cur_right=0;
    for(int j=0;j<m;j++){
        cur_left=0;
        cur_right=0;
        for(int i=0;i<n;i++){
            if (arr[i][j]==2){
                cur_left++;
            }
            if (arr[i][j]==3){
                cur_right++;
            }
        }
        if (cur_left!=pat_arr[0][j] || cur_right!=pat_arr[1][j]){
            flag=0;
        }
        pat_arr[0][j]=cur_left;
        pat_arr[1][j]=cur_right;
    }
    if (flag==1){
        cnt_motion_field_same++;
    }
    if (cnt_motion_field_same==5){
        puts("Ходов больше нет. Игра закончена.");
        exit(1);
    }
}



//Для справки 0 - пустой блок, 1 - сырный блок, 2 - мышь левого игрока, 3 - мышь правого игрока или компьютера.
//Компьютер всегда играет за правую сторону.

int main(){
    std::random_device rd;
    mt19937 gen(rd());
    char shift_direction;
    int game_mode,n,m,**game_field,num_motion=0,num_column,cnt_mouse_left=0,cnt_mouse_right=0;
    printf("Добро пожаловать в игру мыши.\nЯ уверен, что вы уже знаете правила игры, так что выберите режим игры и размеры поля(длину и ширину).\nВведите 1, если хотите играть против человека и 2, если хотите играть против компьютера:");
    scanf("%d",&game_mode);
    printf("Введите размеры поля:");
    scanf("%d%d",&n,&m);

    int cnt_motion_field_same=0;
    int **pat_arr=new int *[2];
    for(int i=0;i<2;i++){
        pat_arr[i]=new int[m];
    }

    uniform_int_distribution<int> comp_column(2, m-1);
    uniform_int_distribution<int> comp_shift_direction(0,1);
    if (n<3 || m<3 || game_mode<1 || game_mode>2){
        error_game();
    }
    cnt_mouse_left=n-1;
    cnt_mouse_right=n-1;
    game_field=new int *[n];
    for(int i=0;i<n;i++){
        game_field[i]=new int[m];
    }
    initializing_field(game_field,n,m,gen);
    print_field(game_field,n,m,num_motion);
    if (game_mode==1){
        printf("Первым ходит человек, мыши которого расположены слева.\nВведите номер столбца, который вы хотите подвинуть(от второй до предпоследнего) и букву закглавную U(подвинуть вверх) или D(подвинуть вниз):");
        while(cnt_mouse_left!=0 && cnt_mouse_right!=0){
            num_motion+=1;
            printf("Первый игрок, напишите номер столбца и направление для его сдвига: ");
            scanf("%d%c",&num_column,&shift_direction);
            if (num_column>=m || num_column<=1 || !(shift_direction=='U' || shift_direction=='D')){
                error_game();
            }
            
            array_shift(game_field,n,m,num_column,shift_direction);
            //print_field(game_field,n,m,num_motion);
            move_left_mouse(game_field,n,m,cnt_mouse_left);
            print_field(game_field,n,m,num_motion);

            printf("Второй игрок, напишите номер столбца и направление для его сдвига: ");
            scanf("%d%c",&num_column,&shift_direction);
            if (num_column>=m || num_column<=1 || !(shift_direction=='U' || shift_direction=='D')){
                error_game();
            }
            array_shift(game_field,n,m,num_column,shift_direction);
            //print_field(game_field,n,m,num_motion);
            move_right_mouse(game_field,n,m,cnt_mouse_right);
            print_field(game_field,n,m,num_motion);
            check_pat(game_field,n,m,pat_arr,cnt_motion_field_same);
        }
        if (cnt_mouse_left==0 && cnt_mouse_right==0){
            puts("Победила дружба");
        }else{
            if (cnt_mouse_left==0){
                puts("Победил первый игрок");
            }else{
                puts("Победил второй игрок");
            }
            
        }
    }else{
        puts("Первым ходит человек( его мыши расположены слева)");
        while(cnt_mouse_left!=0 && cnt_mouse_right!=0){
            num_motion+=1;
            printf("Первый игрок, напишите номер столбца и направление для его сдвига: ");
            scanf("%d%c",&num_column,&shift_direction);
            if (num_column>=m || num_column<=1 || !(shift_direction=='U' || shift_direction=='D')){
                error_game();
            }
            
            array_shift(game_field,n,m,num_column,shift_direction);
            //print_field(game_field,n,m,num_motion);
            move_left_mouse(game_field,n,m,cnt_mouse_left);
            print_field(game_field,n,m,num_motion);

            num_column=comp_column(gen);
            if (comp_shift_direction(gen)==1){
                shift_direction='U';
            }else{
                shift_direction='D';
            }
            array_shift(game_field,n,m,num_column,shift_direction);
            //print_field(game_field,n,m,num_motion);
            move_right_mouse(game_field,n,m,cnt_mouse_right);
            print_field(game_field,n,m,num_motion);
            check_pat(game_field,n,m,pat_arr,cnt_motion_field_same);
        }
        if (cnt_mouse_left==0 && cnt_mouse_right==0){
            puts("Победила дружба");
        }else{
            if (cnt_mouse_left==0){
                puts("Победил первый игрок");
            }else{
                puts("Победил компьютер");
            }
            
        }
    }
    for(int i=0;i<n;i++){
        delete []game_field[i]; 
    }
    delete []game_field;

    for(int i=0;i<2;i++){
        delete []pat_arr[i]; 
    }
    delete []pat_arr;
    return 0;
}
