#include<reg51.h>
#include<intrins.h>
#define uchar unsigned char   //����ͷ�ļ�
void delay()
{
  uchar i,j;
	for(i=200;i>0;i--)
	for(j=150;j>0;j--);
}
void main()
{
	uchar i;
	uchar temp=0xFF;
	P1=temp;
	while(1)
	{
		P1=0xFE;//������P1���ӵĵ�
		for(i=0;i<8;i++)
		{
			P1=_crol_(P1,1);//�ú�����P1��ֵ����ѭ����λ
			delay();//��ʱһ��ʱ��
		}
	}
}