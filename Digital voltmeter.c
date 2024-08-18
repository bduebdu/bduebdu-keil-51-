#include <reg51.h>
#define uchar unsigned char
#define uint unsigned int
uchar code wei[] ={0x04,0x02,0x01};        
uchar code duan[] ={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};    //����ܶ�λѡ
uchar pos[3];
sbit START = P3 ^0;      
sbit OE =P3 ^1;        
sbit EOC = P3 ^2;     
sbit dot =P1 ^7;   //С�������λ 
static char i =0;
uint temp,num;
void delay()
{
	uint n =1000;
	while(n--);
}
void display()           //�������ʾ
{
	pos[0]= num /100;       //��λ
	pos[1]= num /10%10;       //ʮλ
	pos[2]= num %10;          //��λ
	P2=wei[i];              
	P1=duan[pos[i]];           	
	if(i ==0)
	{
	  dot = 0;
	}         //������Ϊ0ʱС������
	i++;
	if(i ==3)
	{
	  i=0;
	}
}
void INT_0() interrupt 0
{
	OE=1;         //�ſ�������
	temp=P0;     //��ȡ����
	num = temp *1.0/255 * 500;  //��ֵת��Ϊģ���ѹֵ
	OE=0;       //D0��D7�ʸ���״̬
	display();
	START=1;      //�ٴ������ظ�λ
	START=0;         //�½���������һ��ת��
}
void main()
{
 	EX0=1;           //���ⲿ�ж�0
	IT0=1;         //�ⲿ�ж��½��ش���
	EA=1;              //�����ж�
	display();
	delay();
	START =0;   
	OE=0;      
	START =1;      //������һ��A/Dת��
	START =0; 
	while(1);
}