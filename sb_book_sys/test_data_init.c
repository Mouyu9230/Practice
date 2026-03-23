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
    int bookcount=10;
    char name[100];
    char author[100];
    double price;
    long long int ID;
    int all;

void Save_books_to_file() {
    FILE *fp = fopen("book.dat", "wb");
    if (!fp) { printf("文件写入失败！\n"); return; }
    for (int i = 0; i < bookcount; i++)
        fwrite(&books[i], sizeof(book), 1, fp);
    fclose(fp);
}

int main(){
books[0] = (book){"C Programming", "Dennis Ritchie", 59.9, 100001, 50};
books[1] = (book){"C++ Primer", "Stanley Lippman", 88.5, 100002, 30};
books[2] = (book){"Data Structures", "Mark Allen Weiss", 72.0, 100003, 40};
books[3] = (book){"Operating System", "Andrew Tanenbaum", 95.0, 100004, 25};
books[4] = (book){"Computer Networks", "James Kurose", 85.0, 100005, 35};
books[5] = (book){"Database System", "Abraham Silberschatz", 90.0, 100006, 20};
books[6] = (book){"Algorithm Design", "Jon Kleinberg", 78.5, 100007, 45};
books[7] = (book){"Artificial Intelligence", "Stuart Russell", 110.0, 100008, 15};
books[8] = (book){"Machine Learning", "Tom Mitchell", 99.9, 100009, 18};
books[9] = (book){"Deep Learning", "Ian Goodfellow", 120.0, 100010, 12};

    for (int i = 10; i < 500; i++) {
        sprintf(books[i].name, "Book_%d", i);
        sprintf(books[i].author, "Author_%d", i);
        books[i].price = 50.0 + i * 0.5;
        books[i].ID = 100000 + i; 
        books[i].all = (i % 50) + 1; 
        bookcount++;
    }
    Save_books_to_file();
    printf("succeed");
    return 0;
}

