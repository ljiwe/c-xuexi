#include <stdio.h>
#include <stdlib.h>
#include<string.h>
/*模拟实现道具店购物功能（商店暂时只支持一种类型的商品）
  1.商店结构-名称、单价、库存量、描述
  2.背包结构-玩家编号、商品[10]、道具数量、最大道具数
  3玩家结构-编号、名称、密码、金钱、[背包]
  模拟玩家购买游戏道具
  1.玩家选择要购买的道具
  2.玩家同意交易后扣除相应游戏币
  3.对应商品库存-1
  *4.玩家背包中增加商品或该商品数量+1
  */
//商品结构
typedef struct _prop
{
    int id;         //道具唯一编号
    char name[50];  //道具名称
    double price;   //道具单价
    int stock;      //库存量：如果在背包中，表示此道具的叠加数量
    char desc[200];      //道具的功能描述
}Prop;
//背包结构
typedef struct _bag
{
    int player;   //所属玩家的编号
    int count;     //当前背包中的道具数量
    int max;      //当前背包的插槽总数
    Prop props[8];   //当前背包中的道具数组
}Bag;
//玩家结构
typedef struct _player
{
    int id;       //玩家编号
    char name[50];//用户名昵称
    char pass[50];//密码
    Bag bag;      //玩家背包
    double gold;  //玩家金币
    double sysee; //元宝数量
}Player;
Prop *props;
Player *players;
int propsCount=0;
int playersCount=0;
void Init();   //用来初始化数据
void ShowProps();
void ShowPlayers();
/*交易函数
参数1：参与交易的玩家指针-为了方便修改交易后的金币
参数2；玩家购买的商品的编号
*/
void Trade(Player *player,int propId);

int main()
{
   //1、初始化游戏数据
   Init();
   printf("\n****************交易前**************\n");
   //2、打印这些初始化数据
   ShowProps();
   ShowPlayers();
   Trade(&players[0],3);
   printf("\n****************交易后**************\n");
     ShowProps();
   ShowPlayers();
    return 0;
}
/*交易函数
参数1：参与交易的玩家指针-为了方便修改交易后的金币
参数2；玩家购买的商品的编号
*/
void Trade(Player *player, int propId)
{
    //需要判断：商品的库存，玩家余额够不够，玩家背包空间够不够
    int i;
    Prop *tradeProp=NULL;//要购买商品指针
    for(i=0;i<propsCount;i++){
        if(propId==props[i].id)
        {
            tradeProp=&props[i];//tradeProp=props+i;
            break;
        }
    }
    if(tradeProp->stock<=0)
    {
        printf("商品已售完！\n");
        return;
    }
    if(player->gold<tradeProp->price)
    {
        printf("金钱不足！\n");
        return;
    }
    if(player->bag.count>=player->bag.max&&player->bag.count!=0)
    {
        printf("背包已满！\n");
        return;
    }
    //满足交易条件，执行交易的业务操作
    //1、商品库存-1；
    tradeProp->stock--;
    //2、玩家金币-商品单价
    player->gold -= tradeProp->price;
    //*3、玩家背包道具增加
    //如果没有该商品，该商品添加到背包中即可
    //如果有该商品，背包中的商品总数+1
    for(i=0;i<player->bag.count;i++)
    {
        //如果要购买的商品id跟背包中的耨个商品id相同
        if(propId == player->bag.props[i].id)
        {
            player->bag.props[i].stock++;
            break;
        }
    }
        if(i==player->bag.count);//如果没有该商品，该商品添加到背包中即可
        {
            //向背包中创建一个商品-复制一份要交易的商品信息到背包中
            int newIndex=player->bag.count;
            player->bag.props[newIndex].id=tradeProp->id;
            player->bag.props[newIndex].price=tradeProp->price;
            player->bag.props[newIndex].stock=1;
            strcpy(player->bag.props[newIndex].name,tradeProp->name);
            strcpy(player->bag.props[newIndex].desc,tradeProp->desc);
            player->bag.count++;
        }
}
void Init()
{
     //1、初始化数据
static Prop propArray[]={
       {1,"双倍经验卡",3000,10,"双倍666"},
       {2,"腐烂的道袍",5000,8,"只可远观不可亵玩"},
       {3,"生锈的铁剑",8000,10,"新手专用"},
       {4,"无极袍",13000,5,"刀枪不入水火不侵"},
       {5,"直升1级丹",83000,10,"大力"},
   };
   propsCount=5;
   props=propArray;//设定指针
static Player playerArray[]={
      {1,"超级毛毛虫","123456",.gold=50000,.bag.max=8},
      {2,"奥特曼","123456",.gold=150000,.bag.max=8},
      {3,"元始天尊","123456",.gold=500000,.bag.max=8},
      {4,"太阳系","123456",.gold=100000,.bag.max=8},
   };
   playersCount=sizeof(playerArray)/sizeof(Player);
   players=playerArray;
}
void ShowProps()
{
    int i;
   if(props==NULL)return;
    printf("%-6s%-14s%-7s%-6s%-12s\n","编号","名称","单价","库存","商品介绍");
    for(i=0;i<propsCount;i++)
    {
        printf("%-6d%-14s%-7.0lf%-6d%-12s\n",props[i].id,props[i].name,props[i].price,props[i].stock,props[i].desc);
    }
}
void ShowPlayers()
{
     int i,j;
     if(players==NULL)return;
     printf("编号\t%-14s金币\n","名称");
     for(i=0;i<playersCount;i++)
     {
         printf("%d\t%-14s%.0lf\n",players[i].id,players[i].name,players[i].gold);
         for(j=0;j<players[i].bag.count;j++)
         {
             printf("物品");
             printf("\t%s\t%d\t",players[i].bag.props[j].name,players[i].bag.props[j].stock);
         }
         printf("\n");
    }
}
