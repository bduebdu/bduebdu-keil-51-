#include<reg51.h>
#define uchar unsigned char
uchar t=0;
uchar code table[]=
{0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe0,0xfe,0xf6,0xee,0x3e,0x9c,0x7a,0x9e,0x8e};//��������ܱ���
void delay(uchar c)
{
	uchar a,b;
	for(;c>0;c--)
	for(b=142;b>0;b--)
	for(a=2;a>0;a--);     //��ʱ����
}
void main()
{
	uchar sw,gw;
	while(1)
		{
		sw=t/10;   //��ʾʮλ
		gw=t%10;  //��ʾ��λ
		P2=0xfe;     //p2ѡ�ж�Ӧ�������
		P1=table[gw];  //p1�����λ
		delay(30);
		P2=0xfd;    
		P1=table[sw];     //p1���ʮλ
		delay(30);
		t++;       //������Ҫ����������100ǰ��0
		if(t==100)
			t=0;
	}
}