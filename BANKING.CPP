//////////////////////////////////////Sandeep Kumar//////////////////////////////////////

#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<bios.h>
#include<dos.h>

#define up    18432
#define down  20480
#define enter 7181

#define nocursor _setcursortype(_NOCURSOR);
#define solid    _setcursortype(_SOLIDCURSOR);

int x=10,y=5;
char opt[][25]={"   INDIAN BANK   ",
	"  Open Account   ",
	"  Transaction    ",
	"  Account Detail ",
	"  Bank Accounts  ",
	"  Close Account  ",
	"  Exit           "};

class bank
	{
	private:
		int acc,bal;
		char nm[25],adr[25];
	protected:
		void add();
		void show();
		void del();
		void search();
		void update();
		int tranmode();
		int transfer();
		int detail();
	public:
		void choice(int);
		void menu(int);
		void shuffle();
	}s;

void clean()
	{
	clrscr();
	int j,k;
	gotoxy(5,3);for(j=0;j<70;j++)cout<<(char)205;
	gotoxy(5,24);for(j=0;j<70;j++)cout<<(char)205;
	for(k=0;k<20;k++) {gotoxy(5,4+k);cout<<(char)186;}
	for(k=0;k<20;k++) {gotoxy(75,4+k);cout<<(char)186;}
	gotoxy(5,3);cout<<(char)201;
	gotoxy(5,24);cout<<(char)200;
	gotoxy(75,3);cout<<(char)187;
	gotoxy(75,24);cout<<(char)188;
	gotoxy(7,5);
	}
void heading(char str[])
	{
	gotoxy(x+22,y);
	textcolor(5+143);textbackground(BLUE);
	cprintf(str);
	textbackground(BLACK);textcolor(GREEN);
	gotoxy(32,6);for(int j=0;j<17;j++)cout<<(char)205;
	}
void shut()
	{
	clean();
	gotoxy(35,10);cout<<"   Indian Bank   ";
	gotoxy(35,11);cout<<" Banking Project ";
	gotoxy(35,12);cout<<"  Sandeep Kumar  ";
	gotoxy(35,14);cout<<"   XII/A2(49)    ";
	gotoxy(35,15);cout<<" Session 2013-14 ";
	gotoxy(35,16);cout<<"  DAV Bistupur   ";
	delay(2000);exit(0);
	}

int bank::detail()
	{
	solid;
	gotoxy(30,13);cout<<"Account no.: ";int acc0;cin>>acc0;
	clean();
	int found=0;
	ifstream fin("banking.dat",ios::binary);
	while(fin.read((char*)&s,sizeof(s)))
		{
		if(acc==acc0)
			{
			gotoxy(x,y+4);cout<<"Account no. # "<<acc;
			gotoxy(x,y+5);cout<<"Name : "<<nm;
			gotoxy(x,y+6);cout<<"Address : "<<adr;
			gotoxy(x,y+7);cout<<"Balance : "<<bal;
			found++;
			}
		}
	fin.close();
	if(found==0)
		{
		gotoxy(35,22);cout<<"Not Found!!!";delay(2000);
		clean();shuffle();
		}
	return(acc0);
	}
int bank::transfer()
	{
	int found=0;
	gotoxy(x,y+13);cout<<"Account no. : ";int accn;cin>>accn;
	gotoxy(x+9,y+14);int amt0;cin>>amt0;
	ifstream fin("banking.dat",ios::binary);
	ofstream fout("Temp.dat",ios::binary);
	while(fin.read((char*)&s,sizeof(s)))
		{
		if(acc==accn)
			{
			bal=bal+amt0;
			found++;
			}
		fout.write((char*)&s,sizeof(s));
		}
	fin.close();fout.close();
	remove("banking.dat");rename("Temp.dat","banking.dat");
	if(found==0)
		{
		gotoxy(35,22);cout<<"Not Found!!!";delay(2000);
		clean();shuffle();
		}
	return(amt0);
	}
int bank::tranmode()
	{
	int amt0;
	gotoxy(x+25,y+9);cout<<"1. Deposit";
	gotoxy(x+25,y+10);cout<<"2. Withdraw";
	gotoxy(x+25,y+11);cout<<"3. Transfer";
	gotoxy(x,y+13);cout<<"Option : ";
	gotoxy(x,y+14);cout<<"Amount : ";
	again:
	gotoxy(x+9,y+13);char ch=getche();
	if(ch>='1'&&ch<='3') {gotoxy(x+22,y+ch-40);cout<<">>";}
	switch(ch)
		{
		case '1':gotoxy(x+9,y+14);cin>>amt0;return(amt0);break;
		case '2':gotoxy(x+9,y+14);cin>>amt0;return(-1*amt0);break;
		case '3':gotoxy(x+9,y+14);amt0=s.transfer();return(-1*amt0);break;
		default :goto again;
		}
	}
void bank::update()
	{
	int acc0=detail();
	heading(opt[2]);
	int amt0=tranmode();
	ifstream fin("banking.dat",ios::binary);
	ofstream fout("Temp.dat",ios::binary);
	while(fin.read((char*)&s,sizeof(s)))
		{
		if(acc==acc0)
			{
			if(bal+amt0>500)
				bal=bal+amt0;
			else{gotoxy(35,22);cout<<"Aborting!!!";delay(2000);}
			}
		fout.write((char*)&s,sizeof(s));
		}
	fin.close();fout.close();
	remove("banking.dat");rename("Temp.dat","banking.dat");
	gotoxy(30,22);cout<<"Operation Successful!!";delay(2000);
	}
void bank::search()
	{
	int acc0=detail();
	clean();
	int found=0;
	nocursor;
	heading(opt[3]);
	ifstream fin("banking.dat",ios::binary);
	while(fin.read((char*)&s,sizeof(s)))
		{
		if(acc==acc0)
			{
			gotoxy(x,y+4);cout<<"Account no. # "<<acc;
			gotoxy(x,y+6);cout<<"Name : "<<nm;
			gotoxy(x,y+8);cout<<"Address : "<<adr;
			gotoxy(x,y+10);cout<<"Balance : "<<bal;
			found++;getche();
			}
		}
	fin.close();
	if(found==0)
		{
		gotoxy(35,22);cout<<"Not Found!!!";delay(2000);
		clean();shuffle();
		}
	}
void bank::add()
	{
	solid;
	heading(opt[1]);
	ifstream fin("banking.dat",ios::binary);
	while(fin.read((char*)&s,sizeof(s)));
	fin.close();
	if(acc==0)acc=1000;
	gotoxy(x,y+4);cout<<"Account no. # "<<acc+1;
	gotoxy(x,y+6);cout<<"Enter Your Name : ";
	gotoxy(x,y+8);cout<<"Enter Your Address : ";
	gotoxy(x,y+10);cout<<"Initial Deposit (Min.500) : ";
	gotoxy(x+18,y+6);gets(nm);strupr(nm);
	gotoxy(x+21,y+8);gets(adr);strupr(adr);
	gotoxy(x+28,y+10);cin>>bal;
	if(bal>=500)
		{
		acc=acc+1;
		ofstream fout("banking.dat",ios::binary|ios::app);
		fout.write((char*)&s,sizeof(s));
		fout.close();
		gotoxy(30,22);cout<<"Operation Successful!!";delay(2000);
		}
	else{gotoxy(35,22);cout<<"Aborting!!!";delay(2000);}
	}
void bank::show()
	{
	nocursor;
	int l=0,dash=0;
	heading(opt[4]);
	gotoxy(x,y+3);cout<<"Acc.no\t\tName\t\t    Address\t        Balance";
	gotoxy(x-4,y+2);for(dash=1;dash<70;dash++)cout<<"=";
	gotoxy(x-4,y+4);for(dash=1;dash<70;dash++)cout<<"=";
	ifstream fin("banking.dat",ios::binary);
	while(fin.read((char*)&s,sizeof(s)))
		{
		gotoxy(x,y+5+l);cout<<acc;
		gotoxy(x+15,y+5+l);cout<<nm;
		gotoxy(x+35,y+5+l);cout<<adr;
		gotoxy(x+55,y+5+l);cout<<bal;
		l++;
		}
	fin.close();
	getche();
	}
void bank::del()
	{
	int acc0=detail();
	heading(opt[5]);
	gotoxy(x,y+10);cout<<"Are you sure ? (Y/N) : ";char ch=getche();
	if(ch=='Y'||ch=='y')
		{
		ifstream fin("banking.dat",ios::binary);
		ofstream fout("Temp.dat",ios::binary);
		while(fin.read((char*)&s,sizeof(s)))
			if(acc!=acc0)
				fout.write((char*)&s,sizeof(s));
		fin.close();fout.close();
		remove("banking.dat");rename("Temp.dat","banking.dat");
		gotoxy(30,22);cout<<"Operation Successful!!";delay(2000);
		}
	else {gotoxy(35,22);cout<<"Aborting!!!";delay(2000);}
	}

void bank::menu(int z)
	{
	nocursor;
	int x=32,y=8;
	gotoxy(x,y);
	textcolor(5+143);textbackground(BLUE);
	cprintf(opt[0]);
	textbackground(BLACK);textcolor(GREEN);
	gotoxy(32,9);for(int j=0;j<17;j++)cout<<(char)205;
	for(int i=1;i<=6;i++)
		{
		if(z==y+3+i)
			{
			gotoxy(x,y+3+i);
			textcolor(GREEN+143);textbackground(CYAN);
			cprintf(opt[i]);
			textcolor(GREEN);textbackground(BLACK);
			}
		else{gotoxy(x,y+3+i);cprintf(opt[i]);}
		}
	}
void bank::choice(int ch)
	{
	clean();
	switch(ch)
		{
		case 1 :add();break;
		case 2 :update();break;
		case 3 :search();break;
		case 4 :show();break;
		case 5 :del();break;
		case 6 :shut();break;
		}
	clean();
	shuffle();
	}
void bank::shuffle()
	{
	int x=25,y=12;
	int min=12,max=17;
	shuff:
	menu(y);
	int key=bioskey(0);
	if(key==enter) choice(y-11);
	else if(key==up) {if(y>min)y=y-1;else y=max;}
	else if(key==down) {if(y<max)y=y+1;else y=min;}
	goto shuff;
	}

void main()
	{
	clean();
	nocursor;
	s.shuffle();
	}