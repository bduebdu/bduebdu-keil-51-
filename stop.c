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
void INT_0() interrupt 0//�ⲿ�ж��ӳ���
{
	uchar i;
		P0=0xfe;//����p0.0�ĵ�
		for(i=0;i<8;i++)
		{
			delay(1000);	
			P0=_crol_(P0,1);//����ѭ����λ
		}
		P0=0xff;//Ϩ�����е�
}
void main()
{
	EA=1;//��EA��EX0�øߵ�ƽ�������жϺ��ⲿ�ж�0��
	EX0=1;
	IT0=0;//�жϴ�����ʽΪ�͵�ƽ����
  while(1);
}