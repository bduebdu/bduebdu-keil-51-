#include <reg51.h>
#include <intrins.h>
#define uchar unsigned char//����ͷ�ļ�
void delay(uchar c)
{
	uchar a,b;
	for(;c>0;c--)
	for(b=142;b>0;b--)
	for(a=2;a>0;a--);     //��ʱ����
}
void INT_0() interrupt 0//�ⲿ�ж��ӳ���(��ˮ��)
{
	uchar i,temp;//�����м�ֵtemp�Է�ֹ��ˮ���ȱ�����
P1=0xfe;
		  temp=P1;
		for(i=0;i<8;i++)
		{		
			delay(1000);	
			temp=_crol_(temp,1);//����ѭ����λ
			P1=temp;
		}
		P1=0xff;//Ϩ�����е�
}
void INT_1() interrupt 2//�ⲿ�ж��ӳ���(��˸3�Σ�
{
	uchar a;
	for(a=3;a>0;a--)
	{
		P1=0x00;
		delay(1000);
		P1=0xff;
		delay(1000);
	}	
}
void main()
{
	EX0=1;//���ⲿ�ж�0
	IP=0x04;//�����ⲿ�ж�1Ϊ�����ȼ�
	IT0=0;//�����жϴ�����ʽΪ�͵�ƽ������ʽ
	EX1=1;
	IT1=0;
	EA=1;//�����ж�
  while(1);//�ȴ��жϷ���
}