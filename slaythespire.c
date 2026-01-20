////杀戮尖塔赛博斗蛐蛐，看b站斗蛐蛐视频之后一时兴起
//后续开发：
//输入部分需满足选择对战怪物的种类与数量
//战斗方面：概率性的意图实现
//增加更多怪物
#include<stdio.h>
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
character kakaa={"kakaa",56,0,0,0,0,0,0};
character tester={"tester",70,0,0,0,0,0,0};
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
int main(){
    if(fight(&kakaa,&tester,kakaa_act,tester_act)){
        printf("kakaa wins");
    }else{
        printf("tester wins");
    }
    return 0;
}


