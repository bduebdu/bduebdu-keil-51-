#include<reg51.h>
#define uint unsigned int
#define uchar unsigned char
sbit cs=P3^7;//Ƭѡ���ƶ�
sbit wr=P3^6;//����Ĵ���дѡͨ�ź�
sbit s1=P1^0;
sbit s2=P1^1;
sbit s3=P1^2;
uchar k=0;//ȫ�ֱ���
void delay(uint m)//��ʱ����
{  
  while(m--);
}
void tri_waves()//���ǲ�����
{
	while(1)//��ѭ��
  {
		P0=k++;//��kֵ��0��255ͨ��P0�����뵽DAC0832
	  delay(100);
	  if(k==0xff)
	  break;
	}	
	while(1)
	{
		P0=k--;//��kֵ��255��0ͨ��P0�����뵽DAC0832
	  delay(100);
	  if(k==0) 
	  break;
  }
}
void square_wave()//��������
{ 
	P0=0;
	delay(100000);
	P0=0xff;
	delay(100000);//kֵ��0��255֮��任
}
void serrated_waves()//�����β�����
{
		P0=k++;
	  delay(100);
	  P0=0;//kֵ����һ��ʱ������
}
void INT_0() interrupt 0//�����жϺ������ѡ���P1�ڸ�����Ӧ�Ĳ���
{
		if(s1==0)
	  {
		tri_waves();
	  }
	if(s2==0)
	{
			square_wave();
	}
	if(s3==0)
	{
		serrated_waves();
	}
}
void main()
{
	EX0=1;
	IT0=0;
	EA=1;//���ⲿ�жϺ����ж�
	cs=0;
	wr=0;
	while(1);//�ȴ��жϷ���
}