#include<iostream>
#include<fstream>
//#include<cstdlib>
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

void write(fstream &in,int r,int key,char recbuff[])
{
	in.seekp((26*r)+1,ios::beg);
	in<<endl<<r<<" ";
	in<<key<<" ";
	for(int i=0;i<19;i++)
	in<<recbuff[i];
	recbuff[19]='\0';
}

int read(fstream &in,int r,char buff[])
{
	char ch;
	int i=0,ctr=0;
	in.seekg((26*r)+4,ios::beg);
	in>>ch;
	buff[0]=ch;
	in>>ch;
	while(ch!='\n')
	{
		if(ch!=' ')
		ctr=1;
		buff[++i]=ch;
		in>>ch;
	}
	if(ctr==1)
	return 1;
	else 
	return 0;
}

void add(fstream &in, int r, char recbuff[], int n, int key)
{
	int c=0;
	char buff[20];
	if(!read(in,r,buff))
	{
	write(in,r,key,recbuff);
    }
	else
	{
		while(read(in,++r%n,buff)&&c!=n)
		{
		c++;
		}
		if(c<n)
		write(in,r,key,recbuff);
	}
}


int main()
{
	hashing h;
	char recbuff[30],choice;
	ofstream out("datafile.txt");
	out.close();
	cout<<"Enter size :" ;
	cin>>h.n;
	fstream f("datafile.txt",ios::in|ios::out);
	f.unsetf(ios::skipws);
	int i=0;
	while(i<h.n)
	{
		f<<i;
		for(int j=0;j<24;j++)
		f<< " ";
		f<<endl;
		i++;
	}
	do
	{
		cout<<"Enter key: ";
		cin>>h.key;
		h.r=h.key%h.n;cout<<h.r;
		cout<<"Enter name: ";
		cin>>h.name;
		i=strlen(h.name);
		strcpy(recbuff,h.name);
		while(i!=15)
		{
			strcat(recbuff," ");
			i++;
		}
		cout<<"Enter cgpa: ";
		cin>>h.cgpa;
		strcat(recbuff,h.cgpa);
		add(f,h.r,recbuff,h.n,h.key);
		cout<<"Enter y to continue: ";
		cin>>choice;
	}while(choice=='y');
	f.close();
	return 0;
}
