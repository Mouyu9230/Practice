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

books[10] = (book){"Compiler Design", "Aho Ullman", 89.0, 100011, 22};
books[11] = (book){"Modern OS", "Andrew Tanenbaum", 102.0, 100012, 18};
books[12] = (book){"Unix Programming", "W. Richard Stevens", 75.5, 100013, 28};
books[13] = (book){"Clean Code", "Robert Martin", 66.0, 100014, 40};
books[14] = (book){"Design Patterns", "Erich Gamma", 92.0, 100015, 26};
books[15] = (book){"Effective C++", "Scott Meyers", 70.0, 100016, 32};
books[16] = (book){"STL Source", "Hou Jie", 80.0, 100017, 20};
books[17] = (book){"Linux Kernel", "Robert Love", 98.0, 100018, 15};
books[18] = (book){"TCP/IP Guide", "Charles Kozierok", 88.0, 100019, 24};
books[19] = (book){"Python Crash", "Eric Matthes", 60.0, 100020, 38};

books[20] = (book){"Java Core", "Cay Horstmann", 85.0, 100021, 27};
books[21] = (book){"Go Programming", "Alan Donovan", 78.0, 100022, 33};
books[22] = (book){"Rust Book", "Steve Klabnik", 82.0, 100023, 21};
books[23] = (book){"C# in Depth", "Jon Skeet", 90.0, 100024, 19};
books[24] = (book){"Web Dev", "Jon Duckett", 65.0, 100025, 44};
books[25] = (book){"HTML CSS", "Jon Duckett", 58.0, 100026, 50};
books[26] = (book){"JavaScript Guide", "David Flanagan", 95.0, 100027, 30};
books[27] = (book){"React Basics", "Max Schwarzmüller", 72.0, 100028, 28};
books[28] = (book){"Node.js Design", "Mario Casciaro", 88.0, 100029, 23};
books[29] = (book){"System Design", "Alex Xu", 105.0, 100030, 17};

books[30] = (book){"Cloud Computing", "Rajkumar Buyya", 110.0, 100031, 14};
books[31] = (book){"Distributed Sys", "Maarten van Steen", 99.0, 100032, 20};
books[32] = (book){"Big Data", "Tom White", 93.0, 100033, 18};
books[33] = (book){"Hadoop Guide", "Tom White", 87.0, 100034, 26};
books[34] = (book){"Spark Intro", "Holden Karau", 91.0, 100035, 22};
books[35] = (book){"Kubernetes", "Kelsey Hightower", 115.0, 100036, 13};
books[36] = (book){"Docker Deep", "Nigel Poulton", 77.0, 100037, 29};
books[37] = (book){"DevOps", "Gene Kim", 83.0, 100038, 31};
books[38] = (book){"Microservices", "Sam Newman", 97.0, 100039, 19};
books[39] = (book){"Software Eng", "Ian Sommerville", 101.0, 100040, 16};

books[40] = (book){"Discrete Math", "Kenneth Rosen", 76.0, 100041, 35};
books[41] = (book){"Linear Algebra", "Gilbert Strang", 85.0, 100042, 30};
books[42] = (book){"Probability", "Sheldon Ross", 92.0, 100043, 24};
books[43] = (book){"Statistics", "Freedman", 80.0, 100044, 28};
books[44] = (book){"Calculus", "James Stewart", 110.0, 100045, 20};
books[45] = (book){"Numerical Methods", "Burden Faires", 88.0, 100046, 21};
books[46] = (book){"Graph Theory", "Bondy Murty", 78.0, 100047, 26};
books[47] = (book){"Cryptography", "William Stallings", 95.0, 100048, 17};
books[48] = (book){"AI Modern", "Russell Norvig", 120.0, 100049, 12};
books[49] = (book){"ML Intro", "Ethem Alpaydin", 99.0, 100050, 15};

books[50] = (book){"DL Practice", "Francois Chollet", 108.0, 100051, 13};
books[51] = (book){"NLP Intro", "Jacob Eisenstein", 90.0, 100052, 18};
books[52] = (book){"CV Basics", "Richard Szeliski", 102.0, 100053, 14};
books[53] = (book){"Reinforcement", "Sutton Barto", 111.0, 100054, 11};
books[54] = (book){"Game Dev", "Jason Gregory", 95.0, 100055, 16};
books[55] = (book){"Unity Guide", "Jeremy Gibson", 70.0, 100056, 30};
books[56] = (book){"Unreal Engine", "Epic Games", 88.0, 100057, 25};
books[57] = (book){"OpenGL", "Joey de Vries", 85.0, 100058, 22};
books[58] = (book){"Vulkan", "Graham Sellers", 98.0, 100059, 18};
books[59] = (book){"Embedded C", "Michael Barr", 82.0, 100060, 27};

books[60] = (book){"ARM Systems", "Joseph Yiu", 94.0, 100061, 19};
books[61] = (book){"RTOS", "Jean Labrosse", 87.0, 100062, 23};
books[62] = (book){"IoT Design", "Arshdeep Bahga", 89.0, 100063, 21};
books[63] = (book){"Cybersecurity", "Charles Pfleeger", 105.0, 100064, 15};
books[64] = (book){"Ethical Hacking", "EC-Council", 92.0, 100065, 17};
books[65] = (book){"Network Sec", "William Stallings", 97.0, 100066, 16};
books[66] = (book){"Malware Analysis", "Michael Sikorski", 110.0, 100067, 12};
books[67] = (book){"Reverse Eng", "Dennis Yurichev", 78.0, 100068, 28};
books[68] = (book){"Assembly Lang", "Kip Irvine", 85.0, 100069, 26};
books[69] = (book){"Computer Arch", "David Patterson", 120.0, 100070, 10};

books[70] = (book){"Digital Logic", "Morris Mano", 88.0, 100071, 20};
books[71] = (book){"FPGA Design", "Stephen Brown", 91.0, 100072, 18};
books[72] = (book){"EDA Tools", "Sanjay Sapatnekar", 95.0, 100073, 14};
books[73] = (book){"Parallel Comp", "Ananth Grama", 100.0, 100074, 13};
books[74] = (book){"GPU Prog", "David Kirk", 105.0, 100075, 12};
books[75] = (book){"CUDA Guide", "NVIDIA", 98.0, 100076, 15};
books[76] = (book){"Quantum Comp", "Michael Nielsen", 115.0, 100077, 9};
books[77] = (book){"Bioinformatics", "Pevsner", 92.0, 100078, 17};
books[78] = (book){"Data Mining", "Jiawei Han", 102.0, 100079, 14};
books[79] = (book){"Info Retrieval", "Christopher Manning", 99.0, 100080, 16};

books[80] = (book){"Search Engines", "Ricardo Baeza-Yates", 95.0, 100081, 18};
books[81] = (book){"Recommendation", "Charu Aggarwal", 108.0, 100082, 11};
books[82] = (book){"Time Series", "Hyndman", 85.0, 100083, 20};
books[83] = (book){"Optimization", "Boyd Vandenberghe", 110.0, 100084, 10};
books[84] = (book){"Game Theory", "Drew Fudenberg", 93.0, 100085, 15};
books[85] = (book){"Economics", "Greg Mankiw", 78.0, 100086, 25};
books[86] = (book){"Finance Intro", "Zvi Bodie", 88.0, 100087, 19};
books[87] = (book){"Project Mgmt", "Harold Kerzner", 90.0, 100088, 18};
books[88] = (book){"Agile Dev", "Ken Schwaber", 75.0, 100089, 27};
books[89] = (book){"Scrum Guide", "Jeff Sutherland", 65.0, 100090, 35};

books[90] = (book){"UI Design", "Don Norman", 82.0, 100091, 22};
books[91] = (book){"UX Basics", "Steve Krug", 70.0, 100092, 30};
books[92] = (book){"Human Comp", "Stuart K. Card", 95.0, 100093, 16};
books[93] = (book){"Accessibility", "Sarah Horton", 88.0, 100094, 20};
books[94] = (book){"Testing", "Glenford Myers", 85.0, 100095, 21};
books[95] = (book){"QA Guide", "Rex Black", 80.0, 100096, 23};
books[96] = (book){"Refactoring", "Martin Fowler", 92.0, 100097, 18};
books[97] = (book){"Code Complete", "Steve McConnell", 105.0, 100098, 12};
books[98] = (book){"Pragmatic Prog", "Andrew Hunt", 88.0, 100099, 19};
books[99] = (book){"Debugging", "David Agans", 76.0, 100100, 26};



    for (int i = 100; i < 500; i++) {
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

