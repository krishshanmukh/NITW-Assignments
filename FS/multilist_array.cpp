#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;

struct mlnode
{
	char rollno[7];
	int sindex;
	int sfptr;
	int sbptr;
	char cnum[10];
	int cindex;
	int cfptr;
	int cbptr;
	mlnode()
	{
		sfptr=-1;
		sbptr=-1;
		cfptr=-1;
		cbptr=-1;
	}
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
	mlnode M[15];
	int k=0,j=0,l=0;
	ofstream out1("studentdata.txt"),out2("coursedata.txt");
	out1.close();
	out2.close();
	fstream in1,in2;
	in1.open("studentdata.txt",ios::in|ios::out);
	in2.open("coursedata.txt",ios::in|ios::out);
	ofstream out("index.txt");
	int a=0,z=1,b;
	char ch;
	do
	{
		cout<<"Enter rollno: ";
		cin>>s.rollno;
		a=0;
    	in1.seekg(0,ios::beg);
		while(a<l)
		{
			z=strcmp(s.rollno,M[a].rollno);
			if(z==0&&M[a].sfptr!=-1)
			{
				a=M[a].sfptr;
			}
			else if(z==0)
			break;
			else
			a++;
		}
		b=a;
		a=0;
		if(z==0)
		{
			strcpy(M[l].rollno,s.rollno);
			M[b].sfptr=l;
			M[l].sbptr=b;
		}
		else
		{
		    cout<<"Enter name of student: ";
    		cin>>s.name;
	    	cout<<"Enter cgpa: ";
		    cin>>s.cgpa;
	    	in1<<k<<"$";
		    b1.pack1(s.rollno);b1.pack(s.name);b1.pack(s.cgpa);
		    b1.store(in1);
		    k++;
		    strcpy(M[l].rollno,s.rollno);
		}
	    cout<<"Enter course no: ";
        cin>>c.number;
		while(a<l)
		{
			z=strcmp(c.number,M[a].cnum);
			if(z==0&&M[a].cfptr!=-1)
			{
				a=M[a].cfptr;
			}
			else if(z==0)
			break;
			else
			a++;
		}
		if(z==0)
		{
			strcpy(M[l].cnum,c.number);
			M[a].cfptr=l;
			M[l].cbptr=a;
		}
		else
		{
		    cout<<"Enter course name: ";
		    cin>>c.name;
		    b2.pack1(c.number);b2.pack(c.name);
		    in2<<j<<"$";
		    b2.store(in2);
		    j++;
		    strcpy(M[l].cnum,c.number);
		}
		l++;
		cout<<"Do you want to enter more entries: ";
		cin>>ch;
	}while(ch=='y');
	for(int i=0;i<l;i++)
	out<<M[i].rollno<<"$"<<M[i].sfptr<<"$"<<M[i].sbptr<<"$"<<M[i].cnum<<"$"<<M[i].cfptr<<"$"<<M[i].cbptr<<"$\n";
	in1.close();
	in2.close();
	out.close();
	return 0;
}

