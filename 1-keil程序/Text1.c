#include<reg51.h>
#include<intrins.h>
sbit smg1=P2^0;		//��������ܵ�һλ
sbit smg2=P2^2;		//��������ܵڶ�λ
sbit smg3=P2^4;		//��������ܵ���λ
sbit smg4=P2^6;
sbit keyks=P3^0;	//���忪ʼ����
sbit keytz=P3^1;	//����ֹͣ����
sbit keyqc=P3^2;	//�����������
sbit keysz=P3^3;	//�������ð���
sbit keyjia=P3^4;	 //�����
sbit keyjian=P3^5;	 //�����
sbit key1=P1^0;		//����1������ѡ��
sbit key2=P1^1;		//����2������ѡ��
sbit key3=P1^2;		//����3������ѡ��
sbit key4=P1^3;		//����4������ѡ��
sbit spk=P3^7;		//���������
int qdsj=20,dtsj=20; //��������ʱ�䡢����ʱ��
int qdsjsz=20,dtsjsz=20; //���������Դ洢���õ�����ʱ�䡢����ʱ��
int flag,num,szflag;	 //flagΪδ��ʼ�����𡢴����л���־λ��num��ʱ��szflagΪ��������ʱ�����ʱ��λ
int qdplayer;			 //����ѡ�ֺ�
int fen1,fen2,fen3,fen4;
int jjfflag=1;
int table[]={0xc0,0xf9,0xa4,0xb0, 0x99,0x92,0x82,0xf8, 0x80,0x90,0xbf};
void w1(int num);
void w2(int num);
void w3(int num);
void w4(int num);
void delay(int z)	   //��ʱ����
{
	int x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}
void keypro()		   //������������
{
	if(keyks==0)	 //��ʼ����
	{
		TR0=1;
		flag=1;
		qdplayer=0;
		szflag=0;
		qdsj=qdsjsz;
		dtsj=dtsjsz;
		while(!keyks);
	}
	if(keytz==0)	//��ͣ����ʼ����
	{
		TR0=~TR0;
		while(!keytz);
	}
	if(keyqc==0)		//��λ����
	{
		flag=0;
		qdplayer=0;
		szflag=0;
		spk=1;
		qdsj=qdsjsz;
		dtsj=dtsjsz;
		jjfflag=1;
		while(!keyqc);
	}
	if(flag==0)			   //��Ϊδ��ʼ״̬�ſɽ�����������ʱ�䡢����ʱ��
	{
		if(keysz==0)		//���ð���
		{
			szflag++;
			if(szflag>=4)
			{
				szflag=0;	
			}
			while(!keysz);	
		}
		if(szflag==1)		//��������ʱ��
		{
			if(keyjia==0)
			{
				qdsjsz++;
				qdsj=qdsjsz;
				while(!keyjia);
			}
			if(keyjian==0)
			{
				qdsjsz--;
				qdsj=qdsjsz;
				while(!keyjian);
			}
		}
		if(szflag==2)		   //���ô���ʱ��
		{
			if(keyjia==0)
			{
				dtsjsz++;
				dtsj=dtsjsz;
				while(!keyjia);
			}
			if(keyjian==0)
			{
				dtsjsz--;
				dtsj=dtsjsz;
				while(!keyjian);
			}		
		}
		if(szflag==3)
		{
			if(key1==0)
			{
				jjfflag=1;
				while(!key1);
			}
			if(key2==0)
			{
				jjfflag=2;
				while(!key2);
			}
			if(key3==0)
			{
				jjfflag=3;
				while(!key3);
			}
			if(jjfflag==1)
			{
				w1(1);
				w2(fen1/10);
				w3(fen1%10);
				if(keyjia==0)
				{
					fen1++;
					while(!keyjia);
				}
				if(keyjian==0)
				{
					fen1--;
					while(!keyjian);
				}
			}
			if(jjfflag==2)
			{
				w1(2);
				w2(fen2/10);
				w3(fen2%10);
				if(keyjia==0)
				{
					fen2++;
					while(!keyjia);
				}
				if(keyjian==0)
				{
					fen2--;
					while(!keyjian);
				}
			}
			if(jjfflag==3)
			{
				w1(3);
				w2(fen3/10);
				w3(fen3%10);
				if(keyjia==0)
				{
					fen3++;
					while(!keyjia);
				}
				if(keyjian==0)
				{
					fen3--;
					while(!keyjian);
				}
			}	
		}
	}
}
void keyqd()			  //����
{
	if(key1==0)			   //һ��ѡ������
	{
		qdplayer=1;		   //�����1
		flag=2;			   //�������״̬
		spk=1;			   //�رշ�����
	}	
	if(key2==0)
	{
		qdplayer=2;
		flag=2;
		spk=1;
	}
	if(key3==0)
	{
		qdplayer=3 ;
		flag=2;
		spk=1;
	}
	if(key4==0)
	{
		qdplayer=4	;
		flag=2;	
		spk=1;   
	}

}
void w1(int num)
{
	smg1=0;
	P0=table[num];
	delay(5);
	P0=0xff;
	smg1=1;	
}
void w2(int num)
{
	smg2=0;
	P0=table[num];
	delay(5);
	P0=0xff;
	smg2=1;	
}
void w3(int num)
{
	smg3=0;
	P0=table[num];
	delay(5);
	P0=0xff;
	smg3=1;	
}
void w4(int num)
{
	smg4=0;
	P0=table[num];
	delay(5);
	P0=0xff;
	smg4=1;	
}
void init()				//��ʱ���ж�1��ʼ��
{
	TMOD=0x01;
	TH0=(65536-45872)/256;
	TL0=(65536-45872)%256;
	EA=1;
	ET0=1;
	TR0=0;
}
void main()				 //������
{
	int t;			   //t�ֲ�����
	init();
	while(1)
	{
 	 AA:	w4(10);
	keypro();
		if(szflag==0)		   //δ����ʱ������״̬
		{
			if(flag==0)			//δ��ʼ����
			{
				keyqd();		//���𡢴�ʱ��������Υ������
				if(qdplayer==0)		 //��ʾ---
				{
				 	w1(10);
					w2(10);
					w3(10);
				}else
				{
					while(1)		   //��ʾѡ�ֱ��
					{
						w1(qdplayer);
						w2(10);
						w3(10);
						spk=0;
						if(keyqc==0)	   //��λ
						{
							spk=1;
							goto AA;   //ǿ����ת����������ִ��
						}
					}
				}
			}
		  if(flag==1)                         //����
		  {
			  	t=10;
				w1(t);
			  	t=qdsj/10;
			  	w2(t);
				t=qdsj%10;
				w3(t);
				if(TR0==1)
				{
					keyqd();
				}
			}
		  if(flag==2)			              //����
			{
				w1(qdplayer);
			  	t=dtsj/10;
			  	w2(t);
				t=dtsj%10;
				w3(t);	
			}
		}
		if(szflag==1)	                  //��������ʱ��
		{
		  	t=qdsjsz/10;
		  	w2(t);
			t=qdsjsz%10;
			w3(t);	
		}
		if(szflag==2)		             //���ô���ʱ��
		{
		  	t=dtsjsz/10;
		  	w2(t);
			t=dtsjsz%10;
			w3(t);	
		}
	}
}
void T0_time() interrupt 1			  //��ʱ���ж�
{
	TH0=(65536-45872)/256;			  //װ��ֵ
	TL0=(65536-45872)%256;
	num++;
	if(num>=20)						//�ж�20��Ϊ1s
	{
		num=0;
		if(flag==1)						  //��Ϊ����״̬
		{
		 qdsj--;					//����ʱһ�μ�һ��
		 if(qdsj<=5)				//���5��һ��һ��
		 {
		 	spk=~spk;
		 }
		 if(qdsj<=0)			//����ʱ����û��������
		 {
		 	qdsj=0;
			TR0=0;
			spk=1;
			flag=0;
		 }
		 }
		if(flag==2)
		{
			dtsj--;
			if(dtsj<=5)
			 {
			 	spk=~spk;
			 }
			if(dtsj<=0)
			{
				dtsj=0;
				TR0=0;
				spk=1;
				flag=0;
			}
		}
	}	
}