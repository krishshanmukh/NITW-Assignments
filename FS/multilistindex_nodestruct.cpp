#include<iostream>
#include<fstream>
#include<cstring>

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
	buffer b1,b2,b;
	student s,S;
	course c,C;
	int k=0,j=0,l=0;
	fstream in1,in2,in;
	in1.open("studentdata.txt",ios::in|ios::out);
	in2.open("coursedata.txt",ios::in|ios::out);
	in.open("index.txt",ios::in|ios::out);
	int a=0,x;
	char ch;
	do
	{
		cout<<"Enter rollno: ";
		cin>>s.rollno;
		in1.seekg(0,ios::beg);
		while(a<k)
		{
			in1>>S;
			x=strcmp(s.rollno,S.rollno);
			if(x==0)
			break;
			a++;
		}a=0;
		if(x!=0)
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
	    in2.seekg(0,ios::beg);
		while(a<j)
		{
			in2>>C;
			x=strcmp(C.number,c.number);
			if(x==0)
			break;
			a++;
		}a=0;
		if(x!=0)
		{
		    cout<<"Enter course name: ";
		    cin>>c.name;
		    b2.pack1(c.number);b2.pack(c.name);
		    in2<<j<<"$";
		    b2.store(in2);
		    j++;
		}
		cout<<"Do you want to enter more entries: ";
		cin>>ch;
	}while(ch=='y');
	in1.close();
	in2.close();
	in.close();
	return 0;
}
