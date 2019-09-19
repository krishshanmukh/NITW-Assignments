#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstring>
using namespace std;

struct hashing
{
	int key;
	int r;
	int n;
	char name[15];
	char cgpa[5];
};

void write(fstream &in, int r,int key, char recbuff[])
{
	in.unsetf(ios::skipws);
	in.clear();
	char ch;
	int ctr=0;
	while(ctr!=r)
	{
		in>>ch;
		if(ch=='\n')
		ctr++;
	}
	while(ch!='$')
	in>>ch;
	int j=in.tellg();
	in.seekp(0,ios::end);
	ctr=strlen(recbuff);
	in<<key<<" ";
	for(int i=0;i<ctr;i++)
	in<<recbuff[i];
}

int key(char recbuff[],fstream &in)
{
	char ch,k[5];
	int i=0;
	in>>ch;
	while(ch!='$')
	{
		k[i]=ch;
		in>>ch;
		i++;
	}
	k[i]='\0';
	return atoi(k);
} 

int read(fstream &in,int r, char buff[])
{
	int i=0,ctr=0;
	char ch;
	in>>ch;
	while(ctr!=r)
	{
		if(ch=='\n')
		ctr++;
	}
	ctr=0;
	in>>ch;
	while(ch!='\n')
	{
		buff[i]=ch;
		if(ch=='$')
		ctr++;
		in>>ch;
		i++;
	}
	if(ctr==1)
	return 1;
	else return 0;
} 

void add(fstream &in, int r,char recbuf[], int n,int key)
{
	in.clear();
	int c=0;
	char buff[30];
	if(!read(in,r,buff))
	write(in,r,key,recbuf);
	else
	{
		while(read(in,(++r)%n,buff)&&c!=n)
		{
			c++;
		}
		if(c<n)
		write(in,r,key,recbuf);
	}
}


int main()
{
	hashing h;
	char recbuff[30],choice;
	cout<<"Enter size: ";
	cin>>h.n;
	fstream out("datafile1.txt",ios::in|ios::out);
	int i=0;
	while(i<h.n)
	{
	    out<<i<<"$\n";
	    i++;
	}
	do
	{
	    cout<<"Enter key: ";
	    cin>>h.key;
	    h.r=h.key%h.n;
	    cout<<"Enter name: ";
	    cin>>h.name;
	    strcpy(recbuff,h.name);
	    strcat(recbuff," ");
	    cout<<"Enter cgpa: ";
	    cin>>h.cgpa;
	    strcat(recbuff,h.cgpa);
	    strcat(recbuff," ");
	    add(out,h.r,recbuff,h.n,h.key);
	    cout<<"Enter choice: ";
	    cin>>choice;
	}while(choice=='y');
	return 0;
}
