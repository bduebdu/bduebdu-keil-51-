#include<reg51.h>
#define uint unsigned int
#define uchar unsigned char
uchar code KEY_TABLE[]={0xee,0xde,0xbe,0x7e,0xed,0xdd,0xbd,0x7d,0xeb,0xdb,0xbb,0x7b,0xe7,0xd7,0xb7,0x77};//���̱���
uchar code TABLE[]={0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe0,0xfe,0xf6,0xee,0x3e,0x9c,0x7a,0x9e,0x8e};//��������ܱ���
uchar i,key,temp,num;//ȫ�ֱ���
void delay()//��ʱ����
{
	uint n =1000;
	while(n--);
}
void input()
{
		P2=0xf0;//����ֵ
		if(P2!=0xf0)//�ж����ް�������
	{
			delay();
		if(P2!=0xf0)//�ж����ް�������
		{
			temp=P2;
		  P2=0x0f;//����ֵ
		  key=temp|P2;//���У������
		  for(i=0;i<16;i++)
		 {
			 if(key==KEY_TABLE[i])//��ѯ���̱�
		  { 
				num=i;
		    break;
		  }
	   }
		 SBUF=TABLE[num];//���ܲ����Ͱ�����Ϣ
  	}
   }
}
void serial(void) interrupt 4
{
	TI=0;//TI����
	if(RI)
	{
		RI=0;
		P0=0xfe;
		P1=SBUF;//�������ݣ���������ܣ���ʾ����ֵ
	}
}
void main()
{ 
	TMOD=0x20;//��ʱ��1ѡ������ʽ2
	TH1=0xfd;
	TL1=0xfd;//9600������
	SM0=0;//���ڹ�����ʽ1
	SM1=1;
	REN=1;//�����������
	EA=1;//�����ж�
	ES=1;//�򿪴����ж�
	TR1=1;//������ʱ/������1
	input();
}