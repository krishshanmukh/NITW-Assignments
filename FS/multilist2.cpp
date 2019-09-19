#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>
using namespace std;

struct student
{
	char rollno[7];
	char name[20];
	char cgpa[5];
	int index;
};

struct course
{
	char number[10];
	char name[15];
	int index;
};

struct index
{
	int Index;
	char rollno[7];
	int sfptr;
	int sbptr;
	char cnumber[10];
	int cfptr;
	int cbptr;
};

fstream & operator >> (fstream &in,student &s)
{
	char ch;
	int ctr=0;
	in>>ch;
	s.index=0;
	while(ch!='$')
	{cout<<"A";
		s.index=s.index*10+(ch-'0');
		in>>ch;
	}
	in>>ch;
	while(ch!='$')
	{cout<<"b";
		s.rollno[ctr]=ch;
		ctr++;
		in>>ch;
	}
	s.rollno[ctr]='\0';
	ctr=0;
	while(ctr!=2)
	{cout<<"c";
		in>>ch;
		if(ch=='$')
		ctr++;
	}
	return in;
}

fstream & operator >> (fstream &in,course &c)
{
	char ch;
	int ctr=0;
	in>>ch;
	c.index=0;
	while(ch!='$')
	{
		c.index=c.index*10+(ch-'0');
		in>>ch;
	}
	in>>ch;
	while(ch!='$')
	{
		c.number[ctr]=ch;
		ctr++;
		in>>ch;
	}
	c.number[ctr]='\0';
	ctr=0;
	in>>ch;
	while(ch!='$')
	{
		in>>ch;
	}
	return in;
}

fstream & operator >> (fstream &in,index &i)
{
	char ch;
	int ctr=0;
    in>>i.Index;
    in>>ch;
	while(ch!='$')
	{
		i.rollno[ctr]=ch;
		ctr++;
		in>>ch;
	}
	i.rollno[ctr]='\0';
	in>>i.sfptr;
	in>>i.sbptr;
	ctr=0;
	in>>ch;
	while(ch!='$')
	{
		i.cnumber[ctr]=ch;
		ctr++;
		in>>ch;
	}
	i.cnumber[ctr]='\0';
	in>>i.cfptr;
	in>>i.cbptr;
	return in;
}

struct buffer
{
	char buff[40];
    void pack(char a[]);
    void pack1(char a[]);
    void store(fstream &out);
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
void buffer :: store (fstream &out)
{
	int l;
	l = strlen(buff);
    for(int i=0;i<l;i++)
    out<<buff[i];
    out<<endl;
}

int main()
{
	buffer b1,b2,b;
	student s,S;
	course c,C;
	index i,I;
	int k=0,j=0,l=0;
	fstream in1,in2,in;
	in1.open("studentdata.txt",ios::in|ios::out);
	in2.open("coursedata.txt",ios::in|ios::out);
	in.open("index.txt",ios::in|ios::out);
	int a=0,x;
	char ch;
	do
	{
		a=0;
		cout<<"Enter rollno: ";
		in1.seekg(0,ios::beg);
		cin>>s.rollno;
		while(a<k)
		{
			in1>>S;
			x=strcmp(s.rollno,S.rollno);
			if(x==0)
			break;
			a++;
		}a=0;
		if(x!=0)
		in<<l<<" "<<s.rollno<<"$"<<" -1 -1 ";
		if(x!=0||k==0)
		{
		    cout<<"Enter name of student: ";
    		cin>>s.name;
	    	cout<<"Enter cgpa: ";
		    cin>>s.cgpa;
    		in1.open("studentdata.txt",ios::app);
	    	in1<<k<<"$";
		    b1.pack1(s.rollno);b1.pack(s.name);b1.pack(s.cgpa);
		    b1.store(in1);
		    k++;
		}
	    cout<<"Enter course no: ";
        cin>>c.number;
        in2.seekg(0,ios::beg);
		while(a<j)
		{
			in2>>C;
			x=strcmp(C.number,c.number);
			if(x==0)
			break;
			a++;
		}a=0;
		if(x!=0||j==0)
		{
		    cout<<"Enter course name: ";
		    cin>>c.name;
		    b2.pack1(c.number);b2.pack(c.name);
	    	in2.open("coursedata.txt",ios::app);
		    in2<<j<<"$";
		    b2.store(in2);
		    in<<c.number<<"$ -1 -1"<<endl;
		    j++;
		}
		cout<<"Do you want to enter more entries: ";
		cin>>ch;
	}while(ch=='y');
	in.close();
	in1.close();
	in2.close();
	return 0;
}
