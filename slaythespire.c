////杀戮尖塔赛博斗蛐蛐，看b站斗蛐蛐视频之后一时兴起
//差不多成了，但是加怪物不方便，很多地方也没仔细打磨
//查了wiki才知道意图的概率这么复杂？？
#include<stdio.h>
#include<string.h>
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




void kakaa_act(character* self,character* enemy,int turns){
    if(turns==1){
        printf("kakaa gain 5 Ritual\n");
    }else{
    int damage=(6+(turns-1)*5);
    damage+=self->strength;//力量判定
    if(self->weak>0){//虚弱判定
        damage*=0.75;
    }
    if(enemy->vulnerable>0){//易伤判定
        damage*=1.5;
    }
    if(enemy->ghost>0){//无实体判定
        damage=1;
    }
    if(enemy->block<=damage){//格挡判定
        enemy->hp-=(damage-enemy->block);
        printf("%s dealt %d damage to %s\n",self->name,damage-enemy->block,enemy->name);       
    }enemy->block=0;
        if(enemy->hp<=0){//死亡判定
        return;
    }
    self->weak--;//虚弱层数减少
    self->vulnerable--;//易伤层数减少
}

}
void tester_act(character* self,character* enemy,int turns){
    int damage=9;
    damage+=self->strength;
    if(self->weak>0){
        damage*=0.75;
    }
    if(enemy->vulnerable>0){
        damage*=1.5;
    }
    if(enemy->ghost>0){
        damage=1;
    }
    if(enemy->block<=damage){
        enemy->hp-=(damage-enemy->block);
        printf("%s dealt %d damage to %s\n",self->name,damage-enemy->block,enemy->name);       
    }enemy->block=0;
        if(enemy->hp<=0){
        return;
    }
    self->weak--;
    self->vulnerable--;
}
void jaw_worm_act(character* self,character* enemy,int turns){
    if(turns%3==1){//重击
    int damage=12;
    damage+=self->strength;
    if(self->weak>0){
        damage*=0.75;
    }
    if(enemy->vulnerable>0){
        damage*=1.5;
    }
    if(enemy->ghost>0){
        damage=1;
    }
    if(enemy->block<=damage){
        enemy->hp-=(damage-enemy->block);
        printf("%s dealt %d damage to %s\n",self->name,damage-enemy->block,enemy->name);       
    }enemy->block=0;
        if(enemy->hp<=0){
        return;
    }        
    }else if(turns%3==2){//盾击
        self->block+=5;
        printf("jaw worm gain 5 block\n");
            int damage=7;
    damage+=self->strength;
    if(self->weak>0){
        damage*=0.75;
    }
    if(enemy->vulnerable>0){
        damage*=1.5;
    }
    if(enemy->ghost>0){
        damage=1;
    }
    if(enemy->block<=damage){
        enemy->hp-=(damage-enemy->block);
        printf("%s dealt %d damage to %s\n",self->name,damage-enemy->block,enemy->name);       
    }enemy->block=0;
        if(enemy->hp<=0){
        return;
    }        
    }else{//咆哮
        self->block+=9;
        printf("jaw worm gain 9 block\n"); 
        self->strength+=5;
        printf("jaw worm gain 5 strength\n");       
    }
        self->weak--;
    self->vulnerable--;

}
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


//怪物数据保存
character kakaa={"kakaa",56,0,0,0,0,0,0};
character tester={"tester",70,0,0,0,0,0,0};
character jaw_worm={"jaw_worm",46,0,0,0,0,0,0};
character monsters[20]={"kakaa",56,0,0,0,0,0,0,"tester",70,0,0,0,0,0,0,"jaw_worm",46,0,0,0,0,0,0};

void (*monster_acts[20])(character* self,character* enemy,int turns)={kakaa_act,tester_act,jaw_worm_act};
int monsternum=3;


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


