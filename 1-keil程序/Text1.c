#include<reg51.h>
#include<intrins.h>
sbit smg1=P2^0;		//定义数码管第一位
sbit smg2=P2^2;		//定义数码管第二位
sbit smg3=P2^4;		//定义数码管第三位
sbit smg4=P2^6;
sbit keyks=P3^0;	//定义开始按键
sbit keytz=P3^1;	//定义停止按键
sbit keyqc=P3^2;	//定义清除按键
sbit keysz=P3^3;	//定义设置按键
sbit keyjia=P3^4;	 //定义加
sbit keyjian=P3^5;	 //定义减
sbit key1=P1^0;		//定义1号抢答选手
sbit key2=P1^1;		//定义2号抢答选手
sbit key3=P1^2;		//定义3号抢答选手
sbit key4=P1^3;		//定义4号抢答选手
sbit spk=P3^7;		//定义蜂鸣器
int qdsj=20,dtsj=20; //定义抢答时间、答题时间
int qdsjsz=20,dtsjsz=20; //变量，可以存储设置的抢答时间、答题时间
int flag,num,szflag;	 //flag为未开始、抢答、答题切换标志位，num定时、szflag为设置抢答时间答题时间位
int qdplayer;			 //抢答选手号
int fen1,fen2,fen3,fen4;
int jjfflag=1;
int table[]={0xc0,0xf9,0xa4,0xb0, 0x99,0x92,0x82,0xf8, 0x80,0x90,0xbf};
void w1(int num);
void w2(int num);
void w3(int num);
void w4(int num);
void delay(int z)	   //延时函数
{
	int x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}
void keypro()		   //各按键处理函数
{
	if(keyks==0)	 //开始按键
	{
		TR0=1;
		flag=1;
		qdplayer=0;
		szflag=0;
		qdsj=qdsjsz;
		dtsj=dtsjsz;
		while(!keyks);
	}
	if(keytz==0)	//暂停、开始按键
	{
		TR0=~TR0;
		while(!keytz);
	}
	if(keyqc==0)		//复位按键
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
	if(flag==0)			   //当为未开始状态才可进行设置抢答时间、答题时间
	{
		if(keysz==0)		//设置按键
		{
			szflag++;
			if(szflag>=4)
			{
				szflag=0;	
			}
			while(!keysz);	
		}
		if(szflag==1)		//设置抢答时间
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
		if(szflag==2)		   //设置答题时间
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
void keyqd()			  //抢答
{
	if(key1==0)			   //一号选手抢答
	{
		qdplayer=1;		   //编号置1
		flag=2;			   //进入答题状态
		spk=1;			   //关闭蜂鸣器
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
void init()				//定时器中断1初始化
{
	TMOD=0x01;
	TH0=(65536-45872)/256;
	TL0=(65536-45872)%256;
	EA=1;
	ET0=1;
	TR0=0;
}
void main()				 //主函数
{
	int t;			   //t局部变量
	init();
	while(1)
	{
 	 AA:	w4(10);
	keypro();
		if(szflag==0)		   //未进行时间设置状态
		{
			if(flag==0)			//未开始抢答
			{
				keyqd();		//抢答、此时抢答属于违规抢答
				if(qdplayer==0)		 //显示---
				{
				 	w1(10);
					w2(10);
					w3(10);
				}else
				{
					while(1)		   //显示选手编号
					{
						w1(qdplayer);
						w2(10);
						w3(10);
						spk=0;
						if(keyqc==0)	   //复位
						{
							spk=1;
							goto AA;   //强行跳转，程序重新执行
						}
					}
				}
			}
		  if(flag==1)                         //抢答
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
		  if(flag==2)			              //答题
			{
				w1(qdplayer);
			  	t=dtsj/10;
			  	w2(t);
				t=dtsj%10;
				w3(t);	
			}
		}
		if(szflag==1)	                  //设置抢答时间
		{
		  	t=qdsjsz/10;
		  	w2(t);
			t=qdsjsz%10;
			w3(t);	
		}
		if(szflag==2)		             //设置答题时间
		{
		  	t=dtsjsz/10;
		  	w2(t);
			t=dtsjsz%10;
			w3(t);	
		}
	}
}
void T0_time() interrupt 1			  //定时器中断
{
	TH0=(65536-45872)/256;			  //装初值
	TL0=(65536-45872)%256;
	num++;
	if(num>=20)						//中断20次为1s
	{
		num=0;
		if(flag==1)						  //当为抢答状态
		{
		 qdsj--;					//倒计时一次减一秒
		 if(qdsj<=5)				//最后5秒一秒一响
		 {
		 	spk=~spk;
		 }
		 if(qdsj<=0)			//倒计时结束没有人抢答
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