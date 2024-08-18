#include <reg51.h>
#define FOSC 12000000L
#define T1MS (65536 - FOSC / 12 / 1000) //1����
#define OW_SKIP_ROM 0xcc
#define DS18B20_CONVERT 0x44
#define DS18B20_READ 0xbe
unsigned char code T_display[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x40, 0x00}; //����������ܱ����
unsigned char code T_COM[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
unsigned char TABLE[8] = {11, 11, 11};
bit flag;
sbit DQ = P3 ^ 0;
sbit dot = P1 ^ 7;
void Delay_OneWire(unsigned int t) //STC89C52RC
{
    while (t--);
}

//ͨ����������DS18B20дһ���ֽ�
void Write_DS18B20(unsigned char dat)
{
    unsigned char i;
    for (i = 0; i < 8; i++)
    {
        DQ = 0;
        DQ = dat & 0x01;
        Delay_OneWire(5);
        DQ = 1;
        dat >>= 1;
    }
    Delay_OneWire(5);
}
//��DS18B20��ȡһ���ֽ�
unsigned char Read_DS18B20(void)
{
    unsigned char i;
    unsigned char dat;
    for (i = 0; i < 8; i++)
    {
        DQ = 0;
        dat >>= 1;
        DQ = 1;
        if (DQ)
        {
            dat |= 0x80;
        }
        Delay_OneWire(5);
    }
    return dat;
}

//DS18B20�豸��ʼ��
bit init_DS18B20(void)
{
    bit initflag = 0;
    DQ = 1;
    Delay_OneWire(12);
    DQ = 0;
    Delay_OneWire(80);
    DQ = 1;
    Delay_OneWire(10);
    initflag = DQ;
    Delay_OneWire(5);
    return initflag;
}
void DS18B20_Start(void) //�����¶�ת��
{
    init_DS18B20();
    Write_DS18B20(OW_SKIP_ROM);
    Write_DS18B20(DS18B20_CONVERT);
}
int DS18B20_Get(void) //��ȡ����(����16λ����������)
{
    unsigned int low = 0, high = 0;
    int temp;
    init_DS18B20();
    Write_DS18B20(OW_SKIP_ROM);
    Write_DS18B20(DS18B20_READ);
    low = Read_DS18B20();
    high = Read_DS18B20();
    temp = (high << 8) | low;
    return temp;
}
void init_time() //��ʱ��0��ʼ��
{
    TMOD = 0x11;
    TL0 = T1MS; //��ʼ����ʱֵ
    TH0 = T1MS >> 8;
    TL1 = T1MS; //��ʼ����ʱֵ
    TH1 = T1MS >> 8;
    TR0 = 1; //��ʱ��0��ʼ��ʱ
    ET0 = 1; //ʹ�ܶ�ʱ��0�ж�
    TR1 = 1; //��ʱ��1��ʼ��ʱ
    ET1 = 1; //ʹ�ܶ�ʱ��1�ж�
    EA = 1;
}
void Time0() interrupt 1
{
    static char i = 0;
    TL0 = T1MS; //��װ��
    TH0 = T1MS >> 8;
    P2 = ~T_COM[i];
    P1 = T_display[TABLE[i]]; //��ʾ
    if (i == 3)
        dot = 1;
    if (++i == 8)
        i = 0;
}
void Time1() interrupt 3
{
    static unsigned char count = 0,i;
    long temp;
    count++;
    TL1 = T1MS; //��װ��
    TH1 = T1MS >> 8;
    if (count == 200) //200ms�ӳ�
    {
        count = 0;
        flag = 0;
        DS18B20_Start();
        temp = DS18B20_Get();
        if (temp < 0) //�ж�����
        {
            flag = 1;
            temp = -temp;
        }
        if (flag == 1) //���Ϊ������ӡ�-����
        {
            TABLE[0] = 10;
        }
        else
        {
            TABLE[0] = 11;
        }
        temp = temp * 625; //����1000��
        for (i = 7; i > 1; i--)
        {
            TABLE[i] = temp % 10;
            temp /= 10;
        }
    }
}
void main()
{
    init_time();
    DS18B20_Start();
    while (1);
}
