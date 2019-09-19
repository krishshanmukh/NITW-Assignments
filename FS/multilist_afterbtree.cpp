#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;

struct snode
{
	char rollno[7];
	int sindex;
	int cindex[10];
	int count=0;
};

struct cnode
{
	char number[10];
	int cindex;
	int sindex[10];
	int count=0;
};

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

fstream & operator >> (fstream &in,student &s)
{
	char ch;
	int ctr=0;
	in>>ch;
	s.index=0;
	if(!in.eof())
	{
	while(ch!='$')
	{
		s.index=s.index*10+(ch-'0');
		in>>ch;
	}
	in>>ch;
	while(ch!='$')
	{
		s.rollno[ctr]=ch;
		ctr++;
		in>>ch;
	}
	s.rollno[ctr]='\0';
	ctr=0;
	while(ctr!=2)
	{
		in>>ch;
		if(ch=='$')
		ctr++;
	}
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
	buffer b1,b2;
	student s,S;
	course C,c;
	snode st[15];
	cnode co[15];
	int k=0,j=0,l=0;
	ofstream out1("studentdata.txt"),out2("coursedata.txt");
	out1.close();
	out2.close();
	fstream in1,in2;
	in1.open("studentdata.txt",ios::in|ios::out);
	in2.open("coursedata.txt",ios::in|ios::out);
	ofstream out("sindex.txt");
	int a=0,z=1,z1=1,b;
	char ch;
	do
	{
		cout<<"Enter rollno: ";
		cin>>s.rollno;
		a=0;
    	in1.seekg(0,ios::beg);
		while(a<k)
		{
			z=strcmp(s.rollno,st[a].rollno);
			if(z==0)
			break;
			else
			a++;
		}
		b=a;
		a=0;
	    if(z!=0)
		{
		    cout<<"Enter name of student: ";
    		cin>>s.name;
	    	cout<<"Enter cgpa: ";
		    cin>>s.cgpa;
	    	in1<<k<<"$";
		    b1.pack1(s.rollno);b1.pack(s.name);b1.pack(s.cgpa);
		    b1.store(in1);
		    k++;
		}
	    cout<<"Enter course no: ";
        cin>>c.number;
		while(a<j)
		{
			z1=strcmp(c.number,co[a].number);
			if(z==0)
			break;
			else
			a++;
		}
		if(z1!=0)
		{
		    cout<<"Enter course name: ";
		    cin>>c.name;
		    b2.pack1(c.number);b2.pack(c.name);
		    in2<<j<<"$";
		    b2.store(in2);
		    j++;
		}
		if(z==0)
		st[b].cindex[st[b].count++]=a;
		else
		{
			strcpy(st[b].rollno,s.rollno);
			st[b].cindex[st[b].count++]=a;
			st[b].sindex=b;
		}
		if(z1==0)
		co[a].sindex[co[a].count++]=b;
		else
		{
			strcpy(co[a].number,c.number);
			co[a].sindex[co[a].count++]=b;
			co[a].cindex=a;
		}
		cout<<"Do you want to enter more entries: ";
		cin>>ch;
	}while(ch=='y');
	for(int i=0;i<k;i++)
	{
		out<<st[i].rollno<<"$"<<st[i].sindex;
		for(int m=0;m<st[i].count;m++)
		out<<"$"<<st[i].cindex[m];
		out<<"!"<<endl;
	}
	out.close();
	out.open("cindex.txt");
	for(int i=0;i<k;i++)
	{
		out<<co[i].number<<"$"<<co[i].cindex;
		for(int m=0;m<co[i].count;m++)
		out<<"$"<<co[i].sindex[m];
		out<<"!"<<endl;
	}
	out.close();
	in1.close();
	in2.close();
	out.close();
	return 0;
}

