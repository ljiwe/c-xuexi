#include <stdio.h>
#include <stdlib.h>
#include<string.h>
/*ģ��ʵ�ֵ��ߵ깺�﹦�ܣ��̵���ʱֻ֧��һ�����͵���Ʒ��
  1.�̵�ṹ-���ơ����ۡ������������
  2.�����ṹ-��ұ�š���Ʒ[10]��������������������
  3��ҽṹ-��š����ơ����롢��Ǯ��[����]
  ģ����ҹ�����Ϸ����
  1.���ѡ��Ҫ����ĵ���
  2.���ͬ�⽻�׺�۳���Ӧ��Ϸ��
  3.��Ӧ��Ʒ���-1
  *4.��ұ�����������Ʒ�����Ʒ����+1
  */
//��Ʒ�ṹ
typedef struct _prop
{
    int id;         //����Ψһ���
    char name[50];  //��������
    double price;   //���ߵ���
    int stock;      //�����������ڱ����У���ʾ�˵��ߵĵ�������
    char desc[200];      //���ߵĹ�������
}Prop;
//�����ṹ
typedef struct _bag
{
    int player;   //������ҵı��
    int count;     //��ǰ�����еĵ�������
    int max;      //��ǰ�����Ĳ������
    Prop props[8];   //��ǰ�����еĵ�������
}Bag;
//��ҽṹ
typedef struct _player
{
    int id;       //��ұ��
    char name[50];//�û����ǳ�
    char pass[50];//����
    Bag bag;      //��ұ���
    double gold;  //��ҽ��
    double sysee; //Ԫ������
}Player;
Prop *props;
Player *players;
int propsCount=0;
int playersCount=0;
void Init();   //������ʼ������
void ShowProps();
void ShowPlayers();
/*���׺���
����1�����뽻�׵����ָ��-Ϊ�˷����޸Ľ��׺�Ľ��
����2����ҹ������Ʒ�ı��
*/
void Trade(Player *player,int propId);

int main()
{
   //1����ʼ����Ϸ����
   Init();
   printf("\n****************����ǰ**************\n");
   //2����ӡ��Щ��ʼ������
   ShowProps();
   ShowPlayers();
   Trade(&players[0],3);
   printf("\n****************���׺�**************\n");
     ShowProps();
   ShowPlayers();
    return 0;
}
/*���׺���
����1�����뽻�׵����ָ��-Ϊ�˷����޸Ľ��׺�Ľ��
����2����ҹ������Ʒ�ı��
*/
void Trade(Player *player, int propId)
{
    //��Ҫ�жϣ���Ʒ�Ŀ�棬�������������ұ����ռ乻����
    int i;
    Prop *tradeProp=NULL;//Ҫ������Ʒָ��
    for(i=0;i<propsCount;i++){
        if(propId==props[i].id)
        {
            tradeProp=&props[i];//tradeProp=props+i;
            break;
        }
    }
    if(tradeProp->stock<=0)
    {
        printf("��Ʒ�����꣡\n");
        return;
    }
    if(player->gold<tradeProp->price)
    {
        printf("��Ǯ���㣡\n");
        return;
    }
    if(player->bag.count>=player->bag.max&&player->bag.count!=0)
    {
        printf("����������\n");
        return;
    }
    //���㽻��������ִ�н��׵�ҵ�����
    //1����Ʒ���-1��
    tradeProp->stock--;
    //2����ҽ��-��Ʒ����
    player->gold -= tradeProp->price;
    //*3����ұ�����������
    //���û�и���Ʒ������Ʒ��ӵ������м���
    //����и���Ʒ�������е���Ʒ����+1
    for(i=0;i<player->bag.count;i++)
    {
        //���Ҫ�������Ʒid�������е������Ʒid��ͬ
        if(propId == player->bag.props[i].id)
        {
            player->bag.props[i].stock++;
            break;
        }
    }
        if(i==player->bag.count);//���û�и���Ʒ������Ʒ��ӵ������м���
        {
            //�򱳰��д���һ����Ʒ-����һ��Ҫ���׵���Ʒ��Ϣ��������
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
     //1����ʼ������
static Prop propArray[]={
       {1,"˫�����鿨",3000,10,"˫��666"},
       {2,"���õĵ���",5000,8,"ֻ��Զ�۲�������"},
       {3,"���������",8000,10,"����ר��"},
       {4,"�޼���",13000,5,"��ǹ����ˮ����"},
       {5,"ֱ��1����",83000,10,"����"},
   };
   propsCount=5;
   props=propArray;//�趨ָ��
static Player playerArray[]={
      {1,"����ëë��","123456",.gold=50000,.bag.max=8},
      {2,"������","123456",.gold=150000,.bag.max=8},
      {3,"Ԫʼ����","123456",.gold=500000,.bag.max=8},
      {4,"̫��ϵ","123456",.gold=100000,.bag.max=8},
   };
   playersCount=sizeof(playerArray)/sizeof(Player);
   players=playerArray;
}
void ShowProps()
{
    int i;
   if(props==NULL)return;
    printf("%-6s%-14s%-7s%-6s%-12s\n","���","����","����","���","��Ʒ����");
    for(i=0;i<propsCount;i++)
    {
        printf("%-6d%-14s%-7.0lf%-6d%-12s\n",props[i].id,props[i].name,props[i].price,props[i].stock,props[i].desc);
    }
}
void ShowPlayers()
{
     int i,j;
     if(players==NULL)return;
     printf("���\t%-14s���\n","����");
     for(i=0;i<playersCount;i++)
     {
         printf("%d\t%-14s%.0lf\n",players[i].id,players[i].name,players[i].gold);
         for(j=0;j<players[i].bag.count;j++)
         {
             printf("��Ʒ");
             printf("\t%s\t%d\t",players[i].bag.props[j].name,players[i].bag.props[j].stock);
         }
         printf("\n");
    }
}
