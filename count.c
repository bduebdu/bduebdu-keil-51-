#include<reg51.h>
#define uint unsigned int
#define uchar unsigned char
uchar code TABLE[]={0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe0,0xfe,0xf6,0xee,0x3e,0x9c,0x7a,0x9e,0x8e};//��������ܱ���
uchar code wei[]={0xfd,0xfe};
uchar temp[]={0,0};
uchar i;
uchar count=0;
void init()//��ʼ����ʱ��
{
	TMOD=0x15;//���ö�ʱ��0������ʽΪ��ʽ1����ʱ��1������ʽΪ��ʽ1
	TH0=(65536-1)/256;
	TL0=(65536-1)%256;//������0ÿ��һ�������ж�һ��
  TH1=(65536-1000)/256;//��ʱ��1ÿ1ms�ж�һ��
	TL1=(65536-1000)%256;
	EA=1;//�������ж�
	ET0=1;//����������0�ж�
	ET1=1;//������ʱ��1�ж�
	TR0=1;//����������0
	TR1=1;//������ʱ��1
}
void count0()interrupt 1
{
	TH0=(65536-1)/256;
	TL0=(65536-1)%256;//������0ÿ��һ�������ж�һ��
	count++;
	if(count==100)//������100��0
		count=0;
}
void time1() interrupt 3
{
	static int timecount=0,weicount=0;//���þ�̬����
	TH1=(65536-1000)/256;//��ʱ��1ÿ1ms�ж�һ��
	TL1=(65536-1000)%256;//ÿ2msˢ�������
	if(++timecount>=2)
	{
		P2=wei[weicount];
		P1=TABLE[temp[weicount]];//�����λѡ�Ͷ�ѡ
		weicount++;
		timecount=0;//����2ms��ʱ
		if(weicount==2)
			weicount=0;//����λѡ�Ͷ�ѡ��־λ
	}
}
void display()//���������������
{
  temp[0]=count/10;
	temp[1]=count%10;
}
void main()
{
	init();
	while(1)
	{
	display();
	}
}
