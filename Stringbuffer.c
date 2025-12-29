#include"strbuf.h"


 // 初始化 sb 结构体，容量为 alloc
 void strbuf_init(struct strbuf *sb, size_t alloc){
    sb->len=0;
    sb->alloc=alloc;
    sb->buf=(char*)malloc(alloc*sizeof(char));
    if(sb->buf==NULL){
        sb->alloc = 0;
        printf("malloc failed");
        exit(EXIT_FAILURE);
    }
 }

// 将字符串填充到 sb 中，长度为 len，容量为 alloc
//不是添加
void strbuf_attach(struct strbuf *sb, void *str, size_t len, size_t alloc){
    free(sb->buf);
    sb->buf=(char*)str;
    sb->len=len;
    sb->alloc=alloc;

}
// 释放 sb 结构体的内存
void strbuf_release(struct strbuf *sb){
    free(sb->buf);
    sb->buf=NULL;
    sb->len=0;
    sb->alloc=0;

}// 交换两个 strbuf
void strbuf_swap(struct strbuf *a, struct strbuf *b) {
    struct strbuf tmp=*a;
    *a=*b;
    *b=tmp;
}
// 将 sb 中的原始内存取出，并将 sz 设置为其 alloc 大小
char *strbuf_detach(struct strbuf *sb, size_t *sz){
    char* string=sb->buf;
    sb->buf=NULL;
    *sz=sb->alloc;
    sb->alloc=0;
    sb->len=0;
    return string;
}
// 比较两个 strbuf 的内存是否相同
int strbuf_cmp(const struct strbuf *first, const struct strbuf *second){
    if(first->len!=second->len){
        return 1;
    }
    int ans=memcmp(first->buf,second->buf,first->len);
    if(ans!=0){
        return 1;
    }else{
        return 0;
    }

}
// 清空 sb
void strbuf_reset(struct strbuf *sb){
    for(int i=0;i<sb->alloc;i++) {
            sb->buf[i]='\0';
        }
    sb->len=0;    
}

// 确保在 len 之后 strbuf 中至少有 extra 个字节的空闲空间可用
void strbuf_grow(struct strbuf *sb, size_t extra){
    if(sb->alloc-sb->len>=extra){
        return;
    }
    sb->buf=(char*)realloc(sb->buf,sizeof(char)*(sb->len+extra));
    if(sb->buf==NULL){
        sb->alloc=0;
        sb->len=0;
        printf("realloc failed");
        exit(EXIT_FAILURE);
    }
    sb->alloc=sb->len+extra;

}
// 向 sb 追加长度为 len 的数据 data
void strbuf_add(struct strbuf *sb, const void *data, size_t len){
    sb->len+=len;
    while(sb->len+1>=sb->alloc){
        sb->alloc++;
        sb->alloc*=2;
        sb->buf=(char*)realloc(sb->buf,sb->alloc*sizeof(char));   
        if(sb->buf==NULL){
        sb->alloc=0;
        sb->len=0;
        printf("realloc failed");
        exit(EXIT_FAILURE);
    }

    }
    memcpy(sb->buf+sb->len-len,data,len);   
    if(sb->buf[sb->len]!='\0'){
        sb->buf[sb->len]='\0';
    }
}
// 向 sb 追加一个字符 c
//?
void strbuf_addch(struct strbuf *sb, int c){
    sb->len++;
    while(sb->len+1>=sb->alloc){
        sb->alloc++;
        sb->alloc*=2;
        sb->buf=(char*)realloc(sb->buf,sb->alloc*sizeof(char));
        if(sb->buf==NULL){
        sb->alloc=0;
        sb->len=0;
        printf("realloc failed");
        exit(EXIT_FAILURE);
    }

    }
    memcpy(sb->buf+(sb->len-1),&c,1);  
    if(sb->buf[sb->len]!='\0'){
    sb->buf[sb->len]='\0';
    }  
}
// 向 sb 追加一个字符串 s
void strbuf_addstr(struct strbuf *sb, const char *s){
    int len=strlen(s);
    sb->len+=len;
    while(sb->len+1>=sb->alloc){
        sb->alloc++;
        sb->alloc*=2;
        sb->buf=(char*)realloc(sb->buf,sb->alloc*sizeof(char));

    }
    memcpy(sb->buf+(sb->len-len),s,len);
    if(sb->buf[sb->len]!='\0'){
        sb->buf[sb->len]='\0';
    }        
}
// 向一个 sb 追加另一个 strbuf 的数据
void strbuf_addbuf(struct strbuf *sb, const struct strbuf *sb2){
    sb->len+=sb2->len;
    while(sb->len>sb->alloc){
        sb->alloc*=2;
        sb->buf=(char*)realloc(sb->buf,sb->alloc*sizeof(char));

    }
    memcpy(sb->buf+(sb->len-sb2->len),sb2->buf,sb2->len);    
    if(sb->buf[sb->len]!='\0'){
    sb->buf[sb->len]='\0';
    }   
}

// 设置 sb 的长度 len
void strbuf_setlen(struct strbuf *sb, size_t len){
    sb->len=len;
    while(sb->len+1>=sb->alloc){
        sb->alloc++;
        sb->alloc*=2;
        sb->buf=(char*)realloc(sb->buf,sb->alloc*sizeof(char));

    }
        if(sb->buf[sb->len]!='\0'){
    sb->buf[sb->len]='\0';
    }
}


// 计算 sb 目前仍可以向后追加的字符串长度
size_t strbuf_avail(const struct strbuf *sb){
    size_t leftlength=sb->alloc-sb->len-1;//预留\0
    return leftlength;
}

// 向 sb 内存坐标为 pos 位置插入长度为 len 的数据 data
void strbuf_insert(struct strbuf *sb, size_t pos, const void *data, size_t len) {
    if(pos>sb->len){
       pos=sb->len;
    }    
    int newlen=sb->len+len;
    while(newlen+1>=sb->alloc){
        sb->alloc++;
        sb->alloc*=2;
        sb->buf=(char*)realloc(sb->buf,sb->alloc*sizeof(char));   
        if(sb->buf==NULL){
        sb->alloc=0;
        sb->len=0;
        printf("realloc failed");
        exit(EXIT_FAILURE);
    }

    }
    for(int i=sb->len;i>pos;i--){
        sb->buf[i+len-1]=sb->buf[i-1];
    }
    memcpy(sb->buf+pos,data,len);  
    sb->len=newlen; 
    if(sb->buf[sb->len]!='\0'){
        sb->buf[sb->len]='\0';
    }
}
// 去除 sb 缓冲区右端的所有空格、制表符和'\t'字符
void strbuf_rtrim(struct strbuf *sb) {
    int count=0;
    for(int i=sb->len-1;i>=0;i--){
        if(sb->buf[i]==' '||sb->buf[i]=='\t'||sb->buf[i]==9||sb->buf[i]==11){
            sb->buf[i]='\0';
            count++;
        }else{
            break;
        }
    }
    sb->len-=count;
    if(sb->buf[sb->len]!='\0'){
        sb->buf[sb->len]='\0';
    }
}
// 去除 sb 缓冲区左端的所有空格、制表符和'\t'字符
void strbuf_ltrim(struct strbuf *sb){
    int count=0;
    for(int i=0;i<sb->len;i++){
        if(sb->buf[i]==' '||sb->buf[i]=='\t'||sb->buf[i]==9||sb->buf[i]==11){
            for(int j=i;j<sb->len-1;j++){
                sb->buf[j]=sb->buf[j+1];
            }
            i--;
            count++;
        }else{
            break;
        }
    }
    sb->len-=count;
    if(sb->buf[sb->len]!='\0'){
        sb->buf[sb->len]='\0';
    }
}
// 删除 sb 缓冲区从 pos 坐标开始长度为 len 的内容
void strbuf_remove(struct strbuf *sb, size_t pos, size_t len) {
    for(int i=pos;i<pos+len;i++){
        sb->buf[i]=sb->buf[i+len];
    }
    sb->len-=len;
    if(sb->buf[sb->len]!='\0'){
        sb->buf[sb->len]='\0';
    }
}
// 将文件描述符为 fd 的所有文件内容追加到 sb 中，sb 增长 hint ? hint : 8192 大小
ssize_t strbuf_read(struct strbuf *sb, int fd, size_t hint){
    int len=hint ? hint : 8192;
    int all=0;
    while(1){
        while(sb->len+len+1>=sb->alloc){
        sb->alloc++;
        sb->alloc*=2;
        sb->buf=(char*)realloc(sb->buf,sb->alloc*sizeof(char));   
        if(sb->buf==NULL){
        sb->alloc=0;
        sb->len=0;
        printf("realloc failed");
        exit(EXIT_FAILURE);
    }    
    }
    ssize_t reader=read(fd,sb->buf+sb->len,len);
    if(reader<0){
        return -1;
    }
    if(reader==0){
        break;
    }
    sb->len+=reader;
    all+=reader;
    }
    sb->buf[sb->len] = '\0';
    return all;
 

}
// 将文件句柄为 fp 的一行内容（抛弃换行符）读取到 sb
int strbuf_getline(struct strbuf *sb, FILE *fp){
    int ch;
    while((ch=fgetc(fp))!=EOF){
        if(ch=='\n'){
            break;
        }
        strbuf_addch(sb,ch);
    }
        if(sb->buf[sb->len]!='\0'){
        sb->buf[sb->len]='\0';
    }
    return sb->len;
}

struct strbuf **strbuf_split_buf(const char *str, size_t len, int terminator, int max){
    struct strbuf **cutted=NULL;
    int arraymembercount=0;
    int start=0;
    for(int i=0; (i<len)&&(arraymembercount<max);i++){
        if(str[i]==terminator){
            int cutlen=i-start;
            if (cutlen>0){
                cutted=(struct strbuf**)realloc(cutted, sizeof(struct strbuf*)*(arraymembercount+2));
                if(cutted==NULL){
                     return NULL;
                }
                cutted[arraymembercount]=(struct strbuf*)malloc(sizeof(struct strbuf));
                cutted[arraymembercount]->buf=(char*)malloc(cutlen+1);
                memcpy(cutted[arraymembercount]->buf,str+start,cutlen);
                cutted[arraymembercount]->buf[cutlen]='\0';
                cutted[arraymembercount]->len=cutlen;
                cutted[arraymembercount]->alloc=cutlen+1;
                arraymembercount++;
            }
            start=i+1;
        }
    }
    if(start<len&&arraymembercount<max){
        int cutlen=len-start;
        if(cutlen>0){
            cutted=(struct strbuf**)realloc(cutted,sizeof(struct strbuf*)*(arraymembercount+2));
            if(cutted==NULL){
                    return NULL;
            } 
            cutted[arraymembercount]=(struct strbuf*)malloc(sizeof(struct strbuf));
            cutted[arraymembercount]->buf=(char*)malloc(cutlen+1);
            memcpy(cutted[arraymembercount]->buf,str+start,cutlen);
            cutted[arraymembercount]->buf[cutlen]='\0';
            cutted[arraymembercount]->len=cutlen;
            cutted[arraymembercount]->alloc=cutlen+1;
            arraymembercount++;
        }
    }
    cutted=(struct strbuf**)realloc(cutted,sizeof(struct strbuf*)*(arraymembercount+1));
    cutted[arraymembercount]=NULL;
    return cutted;
}


bool strbuf_begin_judge(char *target_str, const char *str, int strnlen) {
    if(str==NULL){
        return true;
    }
    int flag=0;
    int len=strlen(str);
    if (strnlen<len) {
        return false;
    }
    for(int i=0;i<len;i++){
        if(target_str[i]!=str[i]){
            flag=1;
            break;
        }
    }
    if(flag==1){
        return false;
    }else{
        return true;
    }
}
//拷贝
char *strbuf_get_mid_buf(char *target_buf, int begin, int end, int len) {
    if(target_buf==NULL){
        return NULL;
    }
    int anslen=end-begin;
    char* ans;
    ans=(char*)malloc(sizeof(char)*(anslen+1));
    for(int i=0;i<anslen;i++){
        ans[i]=target_buf[begin+i];
    }
    ans[anslen]='\0';
    return ans;
}