#include <reg51.h>
#define uchar unsigned char
#define uint unsigned int
uchar code TDUAN[]={ 
0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,
0x00,0x40,0x76,0x1E,0x70,0x38,0x37,0x5C,0x73,0x3E,0x78,0x3d,0x67,0x50,0x37,0x6e,
0xBF,0x86,0xDB,0xCF,0xE6,0xED,0xFD,0x87,0xFF,0xEF,0x46}; //�������������
uchar code TWEI[]={0x80,0x40,0x20,0x10,0x08}; //λ��
uchar pos[5]={16,16,16,16,16}; //��ʼ1s����ʾ�����
uchar i;
uint num;
bit flag_1s,flag_2ms;
void TimerInit(void) 
{
   TMOD= 0x25; //����t0������Ϊģʽ1��t1��ʱ��Ϊģʽ2
   TL1 = 256-200; 
   TH1 = 256-200; //���ö�ʱ��ֵ������ֵ
   TH0 = 0; //��������ʼ��
   TL0 = 0;
   TF1 = 0; //���TF1��־
   EA = 1; //�����ж�
   ET1 = 1; //�򿪶�ʱ��1�ж�
   TR1 = 1; //��ʱ��1��ʱ
   TR0 = 1;//����������0
}
void NumSet()//��ѡ�Ӹ�λ����λ
{
   pos[0]= num%10; 
   pos[1]= num/10%10; 
   pos[2]= num/100%10; 
   pos[3]= num/1000%10; 
   pos[4]= num/10000; 
}
void Display()
{
   P2=0x00; //��Ӱ
   P2=TWEI[i]; //λѡ��ѡ
   P1=~TDUAN[pos[i]]; //~�����л��������������
   if(++i>=5) 
		 i=0;
}
void Timer1() interrupt 3
{
   static uint count_1s,count_2ms;
   if(++count_1s>=5000)//ÿ���ȡһ��Ƶ��
	{ 
   count_1s=0;
   num=TH0<<8|TL0; 
   TH0=TL0=0;//����
   flag_1s=1;
  }
   if(++count_2ms>=2)//��̬��ʾ
   { 
   count_2ms=0;
   flag_2ms=1;
   }
}
void main()
{
   TimerInit();
   while(1) 
	{
    if(flag_1s==1) 
    { 
			flag_1s=0; 
		  NumSet(); //����ÿλ����
		}
    if(flag_2ms==1) 
     { 
			 flag_2ms=0; 
		   Display(); //�������ʾ
		 }
  }
}