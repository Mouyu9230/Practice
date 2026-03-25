#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct book
{
    char name[100];
    char author[100];
    double price;
    long long int ID;
    int all;


}book;

    book books[2048];
    int bookcount=0;
    char name[100];
    char author[100];
    double price;
    long long int ID;
    int all;

void Load_books_from_file();
void Save_books_to_file();
void Show_all_books();
void Input();
void Output();
void Change_information();
void Check_information();
void Add_book();
void Delete_book();
void Count_target_books();
void Mysort();
int change_information_unit();
void ui();

int main(){

    Load_books_from_file(); 

    int bookchoice=0;

    while(1){
            ui();
     if(scanf("%d",&bookchoice)!=1) {
        printf("输入格式错误！请重新输入\n");
        int sweeper;
        while((sweeper=getchar())!='\n'&&sweeper!=EOF);
        continue;
    }
        switch(bookchoice){
            case 1: Input();Save_books_to_file();break;
            case 2: Output();Save_books_to_file();break;
            case 3: Change_information();Save_books_to_file();break;
            case 4: Check_information();break;
            case 5: Add_book();Save_books_to_file();break;
            case 6: Delete_book();Save_books_to_file();break;
            case 7: Show_all_books();break;
            case 8: Count_target_books();break;
            case 9: Mysort();break;
            case 0: printf("欢迎再次使用");return 0;
            default:printf("wrong input!");
        };
    }


    return 0;

}   


void Load_books_from_file() {
    FILE *fp=fopen("book.dat", "rb");
    if(!fp){bookcount=0;return;}
    bookcount=0;
    while(fread(&books[bookcount],sizeof(book),1,fp)){
        bookcount++;
        if(bookcount>=2000)break;
    }
    fclose(fp);
}

void Save_books_to_file() {
    FILE *fp=fopen("book.dat","wb");
    if(!fp){ printf("文件写入失败！\n");return;}
    for(int i=0;i<bookcount;i++)
        fwrite(&books[i],sizeof(book),1,fp);
    fclose(fp);
}

void Show_all_books(){//展示所有用户信息
    if(bookcount == 0){
        printf("当前没有任何用户！\n");
        return;
    }

    printf("=========== 所有书籍信息 ===========\n");
    for(int i = 0; i < bookcount; i++){
        printf("名字:%s\n", books[i].name);
        printf("作者:%s\n", books[i].author);
        printf("ID:%lld\n", books[i].ID);
        printf("数量:%d\n", books[i].all);
        printf("价格:%lf\n", books[i].price);
        printf("-----------------------------------\n");
    }
    printf("=========== 展示结束 ===========\n");
}


void Input(){

};
void Output(){

};
void Change_information(){
    int checkflag=0;
    printf("请输入ID\n");
    if(scanf("%lld",&ID)!=1){
         printf("输入格式错误！请重新输入\n");
         int sweeper;
         while((sweeper=getchar())!='\n'&&sweeper!=EOF);
         return;
}
    for(int i=0;i<bookcount;i++){
        if(books[i].ID==ID){
            printf("验证通过！以下是书籍信息\n");
            printf("名称:%s\nID:%lld\n作者:%s\n数量:%d\n价格:%lf\n",books[i].name,books[i].ID,books[i].author,books[i].all,books[i].price);
            checkflag=1;
            while(change_information_unit(&books[i])!=0);
        }

    }
    if(checkflag==0){
        printf("输入错误！\n");
    }
};
void Check_information(){
    int checkflag=0;
    printf("请输入ID\n");
    if(scanf("%lld",&ID)!=1){
         printf("输入格式错误！请重新输入\n");
         int sweeper;
         while((sweeper=getchar())!='\n'&&sweeper!=EOF);
         return;
}
    for(int i=0;i<bookcount;i++){
        if(books[i].ID==ID){
            printf("验证通过！以下是书籍信息\n");
            printf("名称:%s\nID:%lld\n作者:%s\n数量:%d\n价格:%lf\n",books[i].name,books[i].ID,books[i].author,books[i].all,books[i].price);
            checkflag=1;
        }
    }
    if(checkflag==0){
        printf("输入错误！\n");
    }
};
void Add_book(){

};
void Delete_book(){

};

void Count_target_books(){

};
void Mysort(){

};


int change_information_unit(book *x){
    printf("想要改哪个?\n");
    printf("1:名字\n2:ID\n3:作者\n4:价格\n5:数量\n0:退出\n");

    int bookchoice;

    while(1){
        if(scanf("%d",&bookchoice)!=1){
            printf("输入格式错误！请重新输入\n");
            int sweeper;
            while((sweeper=getchar())!='\n'&&sweeper!=EOF);
            continue;
        }

        switch(bookchoice){
            case 1: 
                printf("输入新名字:\n");
                scanf("%s", x->name);
                printf("修改成功！\n");
                break;

            case 2:
                printf("输入新ID:\n");
                if(scanf("%lld",&x->ID)!=1){
                    printf("输入错误！\n");
                    return -1;
                }
                printf("修改成功！\n");
                break;

            case 3:
                printf("输入新作者:\n");
                scanf("%s", x->author);
                printf("修改成功！\n");
                break;

            case 4:
                printf("输入新价格:\n");
                if(scanf("%lf",&x->price)!=1){
                    printf("输入错误！\n");
                    return -1;
                }
                printf("修改成功！\n");
                break;

            case 5:
                printf("输入新数量:\n");
                if(scanf("%d",&x->all)!=1){
                    printf("输入错误！\n");
                    return -1;
                }
                printf("修改成功！\n");
                break;

            case 0:
                return 0;

            default:
                printf("wrong input!\n");
        }
        return 1;
    }
}


void ui(){
    printf("==============图书馆信息管理系统==================\n");
    printf("图书馆信息管理系统\n");
    printf("输入数字选择对应服务\n");
    printf("1:存书\n2:取书\n3:修改书籍信息\n4:查看书籍信息\n5:创建书目\n6:注销书目\n7:展示所有书目\n8:依需求统计书目\n9:排序\n0:退出\n");
    printf("========================================================\n");      
}
