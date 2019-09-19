#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
union u
{
	char perm[11];
	char temp[9];
};
struct employee
{
	public:
		char empno[7];
		char name[15];
		int tag;
		u payscale;
		char chname[20];
		char chage[2];
		char buf[100];
};
struct buffer
{
	char buff[100];
    void pack1(char a[]);
    void pack(char a[]);
    void store(ofstream &out);
};
void buffer :: pack (char a[])
{
	strcat(buff,a);
	strcat(buff,"$");
}
void buffer :: pack1 (char a[])
{
	strcpy(buff,a);
	strcat(buff,"$");
}
void buffer :: store (ofstream &out)
{
	int l;
	l = strlen(buff);
    for(int i=0;i<l;i++)
    out<<buff[i];
    out<<endl;
}
ifstream & operator >> (ifstream & in,employee &s)
{
	in.unsetf(ios::skipws);
	char ch;int i=0;in>>ch;
	while(ch!='$')
	{
		s.empno[i]=ch;
		i++;
		in>>ch;
	}
    s.empno[i]='\0';
	i=0;in>>ch;
	while(ch!='$')
	{
		s.name[i]=ch;
		i++;
		in>>ch;
	}
	s.name[i]='\0';
    i=0;in>>ch;
    s.tag=ch-'0';
	if(s.tag==1)
	{i=0;in>>ch>>ch;
		while(ch!='$')
	{
		s.payscale.perm[i]=ch;
		i++;
		in>>ch;
	}
	s.payscale.perm[i]='\0';
	}
	else
	{
	    i=0;in>>ch>>ch;
		while(ch!='$')
	{
		s.payscale.temp[i]=ch;
		i++;
		in>>ch;
	}
	s.payscale.temp[i]='\0';
	
	}
	i=0;in>>ch;
		while(ch!='\n')
	{
		if(ch=='$')
		{
			s.buf[i]=' ';
			i++;
			continue;
		}
		s.buf[i]=ch;
		i++;
		in>>ch;
	}
	s.buf[i]='\0';
}


int main()
{
	ofstream out;
	employee s;
	buffer b;out.open("emprec.txt");
	char choice='y';
	while(choice=='y')
	{
	cout<<"Enter emp no:";
	cin>>s.empno;	b.pack1(s.empno);
	cout<<"Enter name:";
	cin>>s.name;b.pack(s.name);
	cout<<"1.permanent\n2.temporary";
	cin>>s.tag;
	if(s.tag==1)
	{
		b.pack("1");
	    cin>>s.payscale.perm;	b.pack(s.payscale.perm);
	}
	if(s.tag==2)
	{
		b.pack("2");
	    cin>>s.payscale.temp;	b.pack(s.payscale.temp);
	}
	cout<<"Enter no. of children: ";
	int ch;
	cin>>ch;
	for(int i=0;i<ch;i++)
	{
		cout<<"Enter name and age of child "<<i+1<<":";
		cin>>s.chname;b.pack(s.chname);
		cin>>s.chage;b.pack(s.chage);
	}
	b.store(out);
	cout<<"Enter y to continue: ";
	cin>>choice;}
	out.close();	
	ifstream in("emprec.txt");
    char c[20];
	cout<<"Enter name to search : ";
    cin>>c;int a;
    in>>s;
    while(!in.eof())
    {
    	a=strcmp(s.name,c);
    	if(a==0)
    	{
    		cout<<s.empno<<" "<<s.name;
    		if(s.tag==1)
    		cout<<" "<<s.payscale.perm;
    		else
    		cout<<" "<<s.payscale.temp;
    		cout<<" "<<s.buf;
    		break;
    	}
    	else
    	in>>s;
    }	
	return 0;
}
