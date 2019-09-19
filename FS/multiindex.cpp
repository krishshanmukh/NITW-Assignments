#include<iostream>
#include<cstring>
#include<fstream>
using namespace std;

struct student
{
	char rollno[7];
	char name[10];
	char year[2];
	char state[3];
	char cgpa[5];
};

struct sindex
{
	char state[3];
	char rollno[7];
};

struct cindex
{
	char cgpa[4];
	char rollno[7];
};

struct yindex
{
	char year[2];
	char rollno[7];
};

struct buffer
{
	char buff[40];
	void pack1(char a[]);
    void pack(char a[]);
    void store(ofstream &out);
};

void buffer :: pack1 (char a[])
{
	strcpy(buff,a);
	strcat(buff,"$");
}

void buffer :: pack (char a[])
{
	strcat(buff,a);
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

ifstream & operator >> (ifstream &in,sindex &s)
{
	char ch;
	int ctr=0;
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
    in>>s.state[0];
    in>>s.state[1];
    s.state[2]='\0';
    in>>ch>>ch;
    while(ch!='$')
    in>>ch;
	return in;
}

ifstream & operator >> (ifstream &in,yindex &s)
{
	char ch;
	int ctr=0;
	in>>ch;
	while(ch!='$')
	{
		s.rollno[ctr]=ch;
		ctr++;
		in>>ch;
	}
	s.rollno[ctr]='\0';
	ctr=0;
	while(ctr!=1)
	{
		in>>ch;
		if(ch=='$')
		ctr++;
	}
    in>>s.year[0];
    s.year[1]='\0';
    while(ctr!=4)
    {
    	in>>ch;
    	if(ch=='$')
    	ctr++;
    }
	return in;
}

ifstream & operator >> (ifstream &in,cindex &s)
{
//	int x=in.tellg();
//	student t;
	char ch;
	in.unsetf(ios::skipws);
	int ctr=0;
//	in>>ch;
//	//while(ch!='$')
////	{
////		s.rollno[ctr++]=ch;
////		in>>ch;
////	}
////	s.rollno[ctr]='\0';
//	ctr=0;
//	while(ctr!=4)
//	{
//		in>>ch;
//		if(ch=='$')
//			ctr++;
//	}
//	ctr=0;
//	in>>ch;
//    while(ch!='$')
//    {
//    	s.cgpa[ctr]=ch;
//    	ctr++;
//    	in>>ch;
//    }
//    s.cgpa[ctr]='\0';
//	cout<<s.cgpa;
//    while(in.tellg()!=x)
//	{
//		in.seekg(-1,ios::cur);
//	}
	//in>>ch;
	//while(ch!='$')
//	{
//	    s.rollno[ctr]=ch;cout<<s.rollno[ctr];
//	    in>>ch;
//	    ctr++;
//	}
//	s.rollno[ctr]='\0';
	in.get(s.rollno,7,'$');cout<<s.rollno;
//		cout<<endl<<s.rollno<<endl;
//	ctr=0;
//	cout<<s.rollno;
	while(ctr!=4)
	{
		in>>ch;
		if(ch=='$')
		ctr++;
	}
	in.get(s.cgpa,5,'$');
	cout<<s.cgpa<<s.rollno;
	in>>ch>>ch;
	return in;
}

/*void sort(char a[],int size)
{
	int x=0;
	for(int i=0;i<size-1;i++)
	for(int j=1;j<size;j++)
	{
		x=strcmp(a[j-1],a[j]);
		if(x>0)
		{
			string s;
			strcpy(s,a[j]);
			strcpy(a[j],a[j-1]);
			strcpy(a[j-1],s);
		}
	}
}*/

void sortstate(sindex s[],int size)
{
	int x=0;
	for(int i=0;i<size-1;i++)
	for(int j=1;j<size;j++)
	{
		x=strcmp(s[j-1].state,s[j].state);
		if(x>0)
		{
			sindex s1;
			s1=s[j];
			s[j]=s[j-1];
			s[j-1]=s1;
		}
	}
}

void sortyear(yindex s[],int size)
{
	int x=0;
	for(int i=0;i<size-1;i++)
	for(int j=1;j<size;j++)
	{
		x=strcmp(s[j-1].year,s[j].year);
		if(x>0)
		{
			yindex s1;
			s1=s[j];
			s[j]=s[j-1];
			s[j-1]=s1;
		}
	}
}

void sortcgpa(cindex s[],int size)
{
	int x=0;
	for(int i=0;i<size-1;i++)
	for(int j=1;j<size;j++)
	{
		x=strcmp(s[j-1].cgpa,s[j].cgpa);
		if(x>0)
		{
			cindex s1;
			s1=s[j];
			s[j]=s[j-1];
			s[j-1]=s1;
		}
	}
}

int main()
{
	ofstream out("buffer.txt",ios::app);
	student s;
	buffer b;
	char ch;
	while(ch=='y')
	{
	    cout<<"Enter roll no:";
		cin>>s.rollno;b.pack1(s.rollno);
		cout<<"Enter name:";	
		cin>>s.name;b.pack(s.name);
		cout<<"Enter year:";	
		cin>>s.year;b.pack(s.year);
		cout<<"Enter state:";	
		cin>>s.state;b.pack(s.state);
		cout<<"Enter cgpa:";
		cin>>s.cgpa;	b.pack(s.cgpa);
		b.store(out);
		cout<<"Enter y to continue: ";
		cin>>ch;
	}
	out.close();
	cindex c[50];
	yindex y[50];
	sindex st[50];
	int cgpa=0,year=0,state=0;
	ifstream in;
	in.open("buffer.txt");
	while(!in.eof())
	{
		in>>c[cgpa++];
	}
	in.close();
	in.open("buffer.txt");
	while(state!=cgpa)
	{
		in>>st[state++];
	}
	in.close();
	in.open("buffer.txt");
	while(year!=cgpa)
	{
		in>>y[year++];
	}
	in.close();
	sortcgpa(c,cgpa-1);
	sortyear(y,year-1);
	sortstate(st,state-1);
	out.open("yearindex.txt");
	for(int i=0;i<year-1;i++)
	{
		b.pack1(y[i].year);
		b.pack(y[i].rollno);
		b.store(out);
	}
	out.close();
	out.open("stateindex.txt");
	for(int i=0;i<state-1;i++)
	{
		b.pack1(st[i].state);
		b.pack(st[i].rollno);
		b.store(out);
	}
	out.close();
	out.open("cgpaindex.txt");
	for(int i=0;i<cgpa-1;i++)
	{
		b.pack1(c[i].cgpa);
		b.pack(c[i].rollno);
		b.store(out);
	}
	out.close();
	return 0;
}
