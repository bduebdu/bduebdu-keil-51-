#include<reg51.h>
#define uint unsigned int
#define uchar unsigned char
uchar code KEY_TABLE[]={0xee,0xde,0xbe,0x7e,0xed,0xdd,0xbd,0x7d,0xeb,0xdb,0xbb,0x7b,0xe7,0xd7,0xb7,0x77};//���̱���
uchar code TABLE[]={0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe0,0xfe,0xf6,0xee,0x3e,0x9c,0x7a,0x9e,0x8e};//��������ܱ���
uchar i;//ȫ�ֱ���
void output();
void delays()//��ʱ������������
{
	uint n =1000;
	while(n--);
}
void delayl()
{
	uint n =5000;
	while(n--);
}
void input()
{
    uchar key,temp;
		P3=0xf0;//����ֵ
		if(P3!=0xf0)//�ж����ް�������
	{
			delays();
		if(P3!=0xf0)//�ж����ް�������
		{
			temp=P3;
		  P3=0x0f;//����ֵ
		  key=temp|P3;//���У������
		  for(i=0;i<16;i++)
		 {
			 if(key==KEY_TABLE[i])//��ѯ���̱�
		  { 
		    break;
		  }
	   }
  	}
   }
}
void output()//���̵ó���ֵ�ɴ���ʾ
{
	uchar sw,gw;
		sw=i/10;   
		gw=i%10; 
		P2=0xfe;    
		P1=TABLE[gw];	
	  delays();	
		P2=0xfd;    
		P1=TABLE[sw];	   		
}
void main()//�������������Ӻ�������ѭ��
{ 
	while (1)
	{
	input();
  output();
  delayl();
	}
}