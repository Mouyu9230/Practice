//2.25更新：
//模块化数值计算相关代码，简化设置角色行动函数的流程
//更新格挡相关逻辑使其在多次攻击场景下正确生效，增加多层护甲判定
//添加六火,巨口和一个更强的测试怪boss_tester
//下一步实现一下设定怪物数量，但是fight限制了p1p2，难道只能通过把数值乘数量实现？


#include<stdio.h>
#include<string.h>
#include<unistd.h>

typedef struct 
{
    char name[20];
    int hp;
    int strength;
    int vulnerable;
    int weak;
    int ghost;
    int block;
    int multiblock;

}character;

int bosstesterflag=0;//act没法传递更多参数导致无法灵活的设置意图，只能整个全局变量了

//战斗流程函数
void cal_damage(character* self,character* enemy,int* damage){
    *damage+=self->strength;//力量判定
    if(self->weak>0){//虚弱判定
        *damage*=0.75;
    }
    if(enemy->vulnerable>0){//易伤判定
        *damage*=1.5;
    }
    if(enemy->ghost>0){//无实体判定
        *damage=1;
    }
}

void deal_damage(character* self,character* enemy,int damage){
        if(enemy->block<=damage){//格挡判定
        enemy->hp-=(damage-enemy->block);
        printf("%s dealt %d damage to %s\n",self->name,damage-enemy->block,enemy->name);  
        if(enemy->multiblock!=0){//造成伤害减少多层护甲层数
            enemy->multiblock--;
            printf("%s multiblock decreased\n",enemy->name);
        } 
        enemy->block=0;    
    }else{
        printf("%s attacked but failed to break %s block\n",self->name,enemy->name);
        enemy->block-=damage;
    }
        if(enemy->hp<=0){//死亡判定
        return;
    }
}

void buff_fading_end(character* self){

    self->block+=self->multiblock;//多层护甲生效
    if(self->multiblock!=0){
        printf("%ss multiblock make itself gain %d block, %d block in total\n",self->name,self->multiblock,self->block);
    }
    if(self->weak!=0){
    self->weak--;//虚弱层数减少
    }
    if(self->vulnerable!=0){
    self->vulnerable--;//易伤层数减少
    }

}

void buff_fading_start(character* self){
    self->block=0;//护甲置零
    if(self->ghost!=0){//无实体减少
        self->ghost--;
    }
}
//---------------------------------------------------------------------------------




//行动逻辑
void kakaa_act(character* self,character* enemy,int turns){
    buff_fading_start(self);
    if(turns==1){
        printf("kakaa gain 5 Ritual\n");
    }else{

    int damage=(6+(turns-1)*5);

    cal_damage(self,enemy,&damage);
    deal_damage(self,enemy,damage);

    }

    buff_fading_end(self);
}

void tester_act(character* self,character* enemy,int turns){
    buff_fading_start(self);
    int damage=9;

    cal_damage(self,enemy,&damage);
    deal_damage(self,enemy,damage);   
    buff_fading_end(self);
}

void boss_tester_act(character* self,character* enemy,int turns){
    buff_fading_start(self);
    if(self->hp<=30&&bosstesterflag==0){//低血量特殊意图 无实体强化
        self->ghost+=2;
        self->strength+=5;
        bosstesterflag=1;
        printf("boss_tester gain 2 ghost and 5 strengths!\n");
    }else if(turns%4==1){//格挡易伤
        self->block+=10;
        enemy->vulnerable+=2;
        printf("boss_tester gain 10 block and cause 2 vulnerable to %s\n",enemy->name);
    }else if(turns%4==2){//重击
        int damage=15;
        cal_damage(self,enemy,&damage);
        deal_damage(self,enemy,damage);  
    }else if(turns%4==3){//强化
        self->hp+=20;
        self->multiblock+=4;
        self->strength+=3;
        printf("boss_tester gain 20 hp,4 multiblock and 3 strength\n");
    }else if(turns%4==0){//连击
        int damage=6;
        cal_damage(self,enemy,&damage);
        for(int i=0;i<3;i++){
        deal_damage(self,enemy,damage);   
        }
    }
    buff_fading_end(self);
}

void jaw_worm_act(character* self,character* enemy,int turns){
    buff_fading_start(self);
    if(turns%3==1){//重击

    int damage=12;
    cal_damage(self,enemy,&damage);
    deal_damage(self,enemy,damage);  

    }else if(turns%3==2){//盾击

        self->block+=5;
        printf("jaw worm gain 5 block\n");
        int damage=7;
        cal_damage(self,enemy,&damage);
        deal_damage(self,enemy,damage);  

    }else{//咆哮
        self->block+=9;
        printf("jaw worm gain 9 block\n"); 
        self->strength+=5;
        printf("jaw worm gain 5 strength\n");       
    }

    buff_fading_end(self);
}

void six_fire_act(character* self,character* enemy,int turns){
    buff_fading_start(self);
    if(turns==1){
        printf("six fire is preparing a hug attack\n");
    }else if(turns==2){//百分比地狱火
        int damage=(enemy->hp/12)+1;
        cal_damage(self,enemy,&damage);
        for(int i=0;i<6;i++){
        deal_damage(self,enemy,damage);  
        }
    }else if(turns%7==1||turns%7==3||turns%7==6){//灼烧
        int damage=6;
        cal_damage(self,enemy,&damage);
        deal_damage(self,enemy,damage);         
    }else if(turns%7==2||turns%7==5){//双击
        int damage=6;
        cal_damage(self,enemy,&damage);
        for(int i=0;i<2;i++){
        deal_damage(self,enemy,damage);  
        }     
    }else if(turns%7==4){//高热
        self->strength+=3;
        self->block+=12;
        printf("six_fire gain 3 strength and 12 block\n");
    }else if(turns%7==0){//地狱火
        int damage=3;
        cal_damage(self,enemy,&damage);
        for(int i=0;i<6;i++){
        deal_damage(self,enemy,damage);  
        }
    }
    buff_fading_end(self);
}
void big_mouth_act(character* self,character* enemy,int turns){
    buff_fading_start(self);
    if(turns%4==1){
        enemy->weak+=5;
        printf("big mouth deal 5 weak to %s\n",enemy->name);
    }else if(turns%4==3){
        self->strength+=5;
        printf("big mouth gain 5 strength\n");
    }else if(turns%4==2){
        int damage=30;
        cal_damage(self,enemy,&damage);
        deal_damage(self,enemy,damage); 
    }else if(turns%4==0){
        int damage=turns/2;
        cal_damage(self,enemy,&damage);
        for(int i=0;i<5;i++){
        deal_damage(self,enemy,damage); 
        }
    }
    buff_fading_end(self);
}
//-------------------------------------------------------------------

//战斗
int fight(character* p1,character* p2,void (*act_1)(character* self,character* enemy,int turns),void (*act_2)(character* self,character* enemy,int turns)){
    int turns=1;
    int winflag=0;
    while(1){
        printf("turn %d\n",turns);
        act_1(p1,p2,turns);
        if(p2->hp<=0){
            winflag=1;
            break;
        }
        if(p1->hp<=0){
            break;
        }
        act_2(p2,p1,turns);   
        if(p2->hp<=0){
            winflag=1;
            break;
        }
        if(p1->hp<=0){
            break;
        }
        printf("%s %d hp left\n",p1->name,p1->hp);
        printf("%s %d hp left\n\n",p2->name,p2->hp);
        turns++;                
    }
    return winflag;
}
//--------------------------------------------------------------------------------------

//怪物数据保存
character kakaa={"kakaa",56,0,0,0,0,0,0};
character tester={"tester",70,0,0,0,0,0,0};
character boss_tester={"boss_tester",70,0,0,0,0,0,0};
character jaw_worm={"jaw_worm",46,0,0,0,0,0,0};
character six_fire={"six_fire",264,0,0,0,0,0,0};
character big_mouth={"big_mouth",300,0,0,0,0,0,0};
character monsters[20] = {
    {"kakaa",56,0,0,0,0,0,0},
    {"tester",70,0,0,0,0,0,0},
    {"boss_tester",200,0,0,0,0,0,0},
    {"jaw_worm",46,0,0,0,0,0,0},
    {"six_fire",264,0,0,0,0,0,0},
    {"big_mouth",300,0,0,0,0,0,0}
};

void (*monster_acts[20])(character* self,character* enemy,int turns)={kakaa_act,tester_act,boss_tester_act,jaw_worm_act,six_fire_act,big_mouth_act};
int monsternum=6;


int namefind(char* str,int* find){
    for(int i=0;i<monsternum;i++){
        if(!strcmp(str,monsters[i].name)){
            *find=i;
            return *find;
        }
    }
    return -1;
}


int main(int argc,char* argv[]){
    if(argc!=3){
        printf("try to ./ with correct monsters name!\n");
        printf("there it is\n");
        for(int i=0;i<monsternum;i++){
            printf("%s ",monsters[i].name);
        }
        printf("\n");
        return 0;
    }
    char p1_name[20];
    char p2_name[20];
    int find_p1,find_p2;
    strcpy(p1_name,argv[1]);
    strcpy(p2_name,argv[2]);
    if(namefind(p1_name,&find_p1)<0||namefind(p2_name,&find_p2)<0){
        printf("wrong input!\n");
        printf("now kakaa,tester and jaw_worm are avilable,try input ./slaythespire kakaa jaw_worm  to let them fight against each other!\n");
        return 0;
    }
    if(fight(&monsters[find_p1],&monsters[find_p2],monster_acts[find_p1],monster_acts[find_p2])){
        printf("%s wins",monsters[find_p1].name);
    }else{
        printf("%s wins",monsters[find_p2].name);
    }
    
}


