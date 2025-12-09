//在Linux终端用ANSI转义序列来改变文字的颜色
#define red "\033[31m"
#define green "\033[32m"
#define blue "\033[34m"
#define purple "\033[35m"
#define black "\033[30m"
#define yellow "\033[33m"
#define cyan "\033[36m"
#define white "\033[37m"
#define reset "\033[0m"//记得在printf的后面加上以重置颜色
#include<stdio.h>
int main(){
    char* colors[6]={red,yellow,cyan,green,blue,purple};
    for(int i=0;i<1225;i++){
        int num=i%6;
        printf("%scolors!!%s",colors[num],reset);
    }
    return 0;
}