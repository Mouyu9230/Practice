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
    char password[]={"qwerty"};
    char inputpassword[100];

void Load_books_from_file();
void Save_books_to_file();
void Show_all_books();
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
    printf("password?\n");
    scanf("%s",inputpassword);
    if(strcmp(inputpassword,password)!=0){
        printf("wrong password!\n");
        return 0;
    }
    printf("welcome\n");

    while(1){
            ui();
     if(scanf("%d",&bookchoice)!=1) {
        printf("输入格式错误！请重新输入\n");
        int sweeper;
        while((sweeper=getchar())!='\n'&&sweeper!=EOF);
        continue;
    }
        switch(bookchoice){
            case 1: Change_information();Save_books_to_file();break;
            case 2: Check_information();break;
            case 3: Add_book();Save_books_to_file();break;
            case 4: Delete_book();Save_books_to_file();break;
            case 5: Show_all_books();break;
            case 6: Count_target_books();break;
            case 7: Mysort();break;
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
        -
        printf("作者:%s\n", books[i].author);
        printf("ID:%lld\n", books[i].ID);
        printf("数量:%d\n", books[i].all);
        printf("价格:%lf\n", books[i].price);
        printf("-----------------------------------\n");
    }
    printf("=========== 展示结束 ===========\n");
}


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
    if(bookcount>=2048){
        printf("书库已满！\n");
    }
    book newbook;

    printf("请输入书名:\n");
    scanf("%s",newbook.name);

    printf("请输入作者:\n");
    scanf("%s",newbook.author);

    printf("请输入ID:\n");
    if(scanf("%lld",&newbook.ID)!=1){
        printf("输入错误！\n");
        return;
    }

    for(int i=0;i<bookcount;i++){
        if(books[i].ID==newbook.ID){
            printf("ID已存在！\n");
            return;
        }
    }

    printf("请输入数量:\n");
    if(scanf("%d",&newbook.all)!=1){
        printf("输入错误！\n");
        return;
    }

    printf("请输入价格:\n");
    if(scanf("%lf",&newbook.price)!=1){
        printf("输入错误！\n");
        return;
    }

    books[bookcount]=newbook;
    bookcount++;
    printf("添加成功！\n");
}
void Delete_book(){
    long long targetID;
    int flag=0;

    printf("请输入ID:\n");
    if(scanf("%lld",&targetID)!=1){
        printf("输入错误！\n");
        return;
    }

    for(int i=0;i<bookcount;i++){
        if(books[i].ID==targetID){
            flag=1;
            for(int j=i;j<bookcount-1;j++){
                books[j]=books[j+1];
            }
            bookcount--;
            printf("删除成功！\n");
            break;
        }
    }

    if(flag==0){
        printf("未找到该书籍！\n");
    }
}

void Count_target_books(){
    if(bookcount==0){
        printf("当前没有任何书籍！\n");
        return;
    }

    int use_name=0,use_author=0,use_price=0,use_all=0;
    char tname[100],tauthor[100];
    double minp,maxp;
    int mina,maxa;

    printf("按书名筛选?1是0否\n");
    scanf("%d",&use_name);
    if(use_name){
        printf("输入书名:\n");
        scanf("%s",tname);
    }

    printf("按作者筛选?1是0否\n");
    scanf("%d",&use_author);
    if(use_author){
        printf("输入作者:\n");
        scanf("%s",tauthor);
    }

    printf("按价格区间筛选?1是0否\n");
    scanf("%d",&use_price);
    if(use_price){
        printf("输入最低价格和最高价格:\n");
        scanf("%lf%lf",&minp,&maxp);
    }

    printf("按数量区间筛选?1是0否\n");
    scanf("%d",&use_all);
    if(use_all){
        printf("输入最小数量和最大数量:\n");
        scanf("%d%d",&mina,&maxa);
    }

    int cnt=0;
    for(int i=0;i<bookcount;i++){
        int ok=1;

        if(use_name&&strcmp(books[i].name,tname)!=0) ok=0;
        if(use_author&&strcmp(books[i].author,tauthor)!=0) ok=0;
        if(use_price&&(books[i].price<minp||books[i].price>maxp)) ok=0;
        if(use_all&&(books[i].all<mina||books[i].all>maxa)) ok=0;

        if(ok) cnt++;
    }

    printf("符合条件的书籍数量:%d\n",cnt);
}
void Mysort(){
    if(bookcount==0){
        printf("当前没有任何书籍！\n");
        return;
    }

    int type,order;
    printf("按什么排序?\n1:ID\n2:价格\n3:数量\n");
    if(scanf("%d",&type)!=1){
        printf("输入错误\n");
        return;
    }

    printf("1:升序 0:降序\n");
    if(scanf("%d",&order)!=1){
        printf("输入错误\n");
        return;
    }

    for(int i=0;i<bookcount-1;i++){
        for(int j=0;j<bookcount-1-i;j++){
            int flag=0;

            if(type==1){
                if(order&&books[j].ID>books[j+1].ID)flag=1;
                if(!order&&books[j].ID<books[j+1].ID)flag=1;
            }
            else if(type==2){
                if(order&&books[j].price>books[j+1].price)flag=1;
                if(!order&&books[j].price<books[j+1].price)flag=1;
            }
            else if(type==3){
                if(order&&books[j].all>books[j+1].all)flag=1;
                if(!order&&books[j].all<books[j+1].all)flag=1;
            }

            if(flag){
                book temp=books[j];
                books[j]=books[j+1];
                books[j+1]=temp;
            }
        }
    }

    printf("排序完成\n");
}


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
    printf("1:修改书籍信息\n2:查看书籍信息\n3:创建书目\n4:注销书目\n5:展示所有书目\n6:依需求统计书目\n7:排序\n0:退出\n");
    printf("========================================================\n");      
}
