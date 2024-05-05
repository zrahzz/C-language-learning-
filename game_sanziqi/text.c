#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define ROW 3
#define COL 3

int result;

int main (){

    int input;
    char board[ROW][COL];
    srand(time(NULL));  
//函数定义
void menu();
void initialize_board (char board[ROW][COL],int raw,int col);
void printf_board(char board[ROW][COL],int raw,int col);
void playermove(char board[ROW][COL],int raw,int col);
void robotmove(char board[ROW][COL],int raw,int col);
void run_time(char board[ROW][COL],int raw,int col);
void win_role_rowvoid(char board[ROW][COL],int raw,int col);
void win_role_colvoid(char board[ROW][COL],int raw,int col);
void win_role_slope1void(char board[ROW][COL],int raw,int col);
void win_role_slope2void(char board[ROW][COL],int raw,int col);
int win_role(int board [ROW][COL],int n[4]);
int  win(char board[ROW][COL],int raw,int col);

    do{
        menu();
        printf("请输入：");
        scanf("%1d",&input);
        switch (input){
            case 1:
                initialize_board(board,ROW,COL);
                //调试
                run_time(board,ROW,COL);
                
                //调试
                break;
            case 2:
                input = 0;
                break;
            default:
                printf("输入不合法!\n");
                break;
        }
    }while (input);

    return 0;
}

void menu(){//菜单
    printf("********************\n");
    printf("***    1.play    ***\n");
    printf("***    2.exit    ***\n");
    printf("********************\n");
}

void initialize_board (char board[ROW][COL],int raw,int col){//初始化棋盘
    int i, j;
    for(i = 0;i<ROW;i++){
        for(j=0;j<COL;j++){
            board[i][j] = ' ';
        }
    }
}

void printf_board(char board[ROW][COL],int raw,int col){//输出棋盘
    int i, j;
    for(i=0;i<ROW;i++){
        for(j=0;j<COL;j++){
            printf(" %c ",board[i][j]);
            if(j!=COL-1)
                printf("|");
            
        }
        printf("\n");
        for(j=0;j<COL;j++){
            if(i!=ROW-1)
                printf("----");
           
        } printf("\n");
    }
}

void playermove(char board[ROW][COL],int raw,int col){//玩家下棋
    int n,m;
    int true;
        do{
            true = 0;
            printf("请输入你要下的棋盘坐标：");
            scanf("%1d %1d",&n,&m);
            if(n>ROW||n<=0)
                true = 1;    
            if(m>COL||m<=0)
                true = 1;    
        } while (true);
        if(board[n-1][m-1]!=' '){
            printf("输入不合法!\n");
            playermove(board,ROW,COL);
        }else
            board[n-1][m-1] = '#';
}

void robotmove(char board[ROW][COL],int raw,int col){//人机下棋
    int n, m;
    int true;
  
   do{
        true = 0;
        n=rand()%3;
        m=rand()%3;
        if(n>ROW-1||n<0)
            true = 1;    
        if(m>COL-1||m<0)
            true = 1;    
    } while (true);
    if(board[n][m]!=' '){
        robotmove(board,ROW,COL);
    }else
            board[n][m] = '*';
}

void run_time(char board[ROW][COL],int raw,int col){//程序运行（次数计算）
    int times,x=1;
    int choose;
    printf("请选择谁先手\n");
    printf("输入1人机先手\n");
    printf("输入2玩家先手\n");
    scanf("%d",&choose);
    
    if(choose==1)
        robotmove(board,ROW,COL);
        printf_board(board,ROW,COL);
    for(times = 3;times>0;times--){
        playermove(board,ROW,COL);
        robotmove(board,ROW,COL);
        printf_board(board,ROW,COL);
    }
    for(times = ((ROW*COL)/2)-3;times>0;times--){
        x = win(board,ROW,COL);
        if(x==0)
            break;
        playermove(board,ROW,COL);
        x = win(board,ROW,COL);
        if(x==0){
            printf_board(board,ROW,COL);
            break;
        }
            
        robotmove(board,ROW,COL);
        printf_board(board,ROW,COL);
        
    }
    if (choose ==2&&x!=0){
        playermove(board,ROW,COL);
        printf_board(board,ROW,COL);
        x = win(board,ROW,COL);
       
    }  
    // x = win(board,ROW,COL);
    if(x!=0){
        x = win(board,ROW,COL);
        if (x!=0)
            printf("平局。\n");
    }
        
}

int win_role_row(char board[ROW][COL],int raw,int col){//水平胜者
    int i ,j;
    int result;
    int go_run=0;
    
    for(i = 0; i <ROW;i++){
        result = 0;
        for(j = 1; j <ROW;j++){
            if(board[i][0]==board[i][j]){
            result += 1;
            }
        }
    if(result == 2 &&board[i][0]=='#')
        return 1;
    else if(result == 2 &&board[i][0]=='*')
        return 0;
    }
    for(i=0;i<ROW;i++){//是否下完
        for(j=0;j<ROW;j++){
            if(board[i][j]==' '){
                go_run = -1;
                break;
            }   
        }
    }
    if(go_run!=-1)
        return -2;

    return -1;
}

int win_role_col(char board[ROW][COL],int raw,int col){//竖直胜者
    int i ,j;
    int result;
    int go_run=0;
    for(i = 0; i <ROW;i++){
        result = 0;
        for(j = 1; j <ROW;j++){
        if(board[0][i]==board[j][i]){
            result += 1;
        }
    }
    if(result == 2 &&board[0][i]=='#')
        return 1;
    else if(result == 2 &&board[0][i]=='*')
        return 0;
    }
    for(i=0;i<ROW;i++){//是否下完
        for(j=0;j<ROW;j++){
            if(board[i][j]==' '){
                go_run = -1;
                break;
            }
        }
    }
    if(go_run==-1)
        return -2;
    return -1;
}

int win_role_slope1(char board[ROW][COL],int raw,int col){
    int i ,j;
    int result= 0;
    int go_run=0;
    for(i = 1; i <ROW;i++){
        if(board[0][0]==board[i][i])
            result += 1;
    }
    if(result == 2 &&board[0][0]=='#')
        return 1;
    else if(result == 2 &&board[0][0]=='*')
        return 0;
    
    for(i=0;i<ROW;i++){//是否下完
        for(j=0;j<ROW;j++){
            if(board[i][j]==' '){
                go_run = -1;
                break;
            } 
        }
    }
    if(go_run==-1)
        return -2;
    return -1;
}

int win_role_slope2(char board[ROW][COL],int raw,int col){
    int i ,j;
    int result = 0;;
    int go_run=0;
    
    for(i = 1; i <ROW;i++){
        if(board[0][2]==board[ROW-i][i-1])
            result += 1;
    }
    if(result == 2 &&board[0][2]=='#')
        return 1;
    else if(result == 2 &&board[0][2]=='*')
        return 0;
    
    for(i=0;i<ROW;i++){//是否下完
        for(j=0;j<ROW;j++){
            if(board[i][j]==' '){
                go_run = -1;
                break;
            } 
        }
    }
    if(go_run==-1)
        return -2;
    return -1;
}

int win_role(int board[ROW][COL],int n[4]){
    int i,j;
    int go_run=0;
    for(i=0;i<4;i++){
        if(n[i]==1){
            printf("玩家获胜！\n");
            return 0;
        }else if(n[i]==0){
            printf("电脑获胜！\n");
            return 0;
        }
    }for(i=0;i<ROW;i++){//是否下完
        for(j=0;j<ROW;j++){
            if(board[i][j]==' ')
                go_run = -1;
        }
    }
    if(go_run!=-1)
        return -2;
        return -1;
}

int  win(char board[ROW][COL],int raw,int col){//判断胜者
    int n[4],x=-1;
    n[0] = win_role_row(board,ROW,COL);
    n[1]= win_role_col(board,ROW,COL);
    n[2] = win_role_slope1(board,ROW,COL);
    n[3] = win_role_slope2(board,ROW,COL);
    x = win_role(board,n);
    return x;
}