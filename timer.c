#include<reg51.h>
#include<intrins.h>
#define uchar unsigned char
uchar count=0;
void time0(void) interrupt 1
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;//����װ�ؼ�����ֵ
  count++;
}
void light()//��ˮ��
{
	uchar i=0;
	P1=_crol_(P1,1);//�ú�����P1��ֵ����ѭ����λ
}
void main()
{  
	P1=0xFE;
	TMOD=0x01;//��ʱ��������ʽ1
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;//��ֵ50ms
	EA=1;//�����ж�
	ET0=1;//�򿪶�ʱ/������0�ж�
	TR0=1;//������ʱ/������0
	while(1)
	{
		if(count==20)//����1s
		{
			light();
			count=0;//��λ��ˮ�Ʋ����ü���
		}
	}
}