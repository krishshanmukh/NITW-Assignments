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

struct node
{
	int index;
	node *next;
};

struct studindex
{
	int index;
	char rollno[7];
	node *ind;
	studindex *next;
};

struct courseindex
{
	int index;
	char number[10];
	node *ind;
	courseindex *next;
};

void addbegin(node* &T,int x)
{
	node *L=new(node);
	L->index=x;
	L->next=T;
	T=L;
}

void addend(node *T,int x)
{
	while(T->next!=NULL)
	T=T->next;
	T->next=new(node);
	T->next->next=NULL;
	T->next->index=x;
}

void addbefore(node *T,int x,int y)
{
	while(T->next->index!=y)
	T=T->next;
	node *L=T->next;
	T->next=new(node);
	T->next->index=x;
	T->next->next=L;
}

int ctr;
node *M;

void insert(node* &T,int x)
{
	if(x>T->index&&T->next!=NULL)
	{
	    insert(T->next,x);
	    ctr++;
	}
	else if(x<T->index)
	{
		if(ctr==0)
		{
		    addbegin(M,x);
		}
		else
		addbefore(M,x,T->index);
	}
	else
	addend(M,x);
}

void addbegins(studindex* &T,char rollno[],int index,int x)
{
	studindex *L=new(studindex);
	strcpy(L->rollno,rollno);
	L->ind=new(node);
	L->index=index;
	L->ind->index=x;
	L->ind->next=NULL;
	L->next=T;
	T=L;
}

void addends(studindex *T,char rollno[],int index,int x)
{
	while(T->next!=NULL)
	T=T->next;
	T->next=new(studindex);
	strcpy(T->rollno,rollno);
	T->next->next=NULL;
	T->next->index=index;
	T->next->ind=new(node);
	T->next->ind->index=x;
	T->next->ind->next=NULL;
}

void addbefores(studindex *T,char rollno[],char rollno1[],int index,int x)
{
	int w=strcmp(T->rollno,rollno1);
	while(w!=0)
	{
	    T=T->next;
	    w=strcmp(T->rollno,rollno1);
	}
	studindex *L=T->next;
	T->next=new(studindex);
	strcpy(T->rollno,rollno);
	T->next->ind=new(node);
	T->next->index=index;
	T->next->ind->index=x;
	T->next->ind->next=NULL;
	T->next->next=L;
}

int x,m;
studindex *N;

void inserts(studindex* &T,char rollno[],int index,int x)
{
    if(T!=NULL)
    {
   	 	x=strcmp(T->rollno,rollno);
   	 	if(x!=0&&T->next!=NULL)
		{
	    	inserts(T->next,rollno,index,x);
	    	m++;
		}
//		else if(x>0)
//		{
//			if(m==0)
//			addbegins(N,rollno,index,x);
//			else
//			addbefores(N,rollno,T->rollno,index,x);
//		}
		else if(T->next==NULL&&x!=0)
		addends(T,rollno,index,x);
		else
		{
			M=T->ind;
		    insert(T->ind,x);
		    T->ind=M;
		}
    }
	else
	{
		T=new(studindex);
		strcpy(T->rollno,rollno);
		T->ind=new(node);
		T->index=index;
		T->ind->index=x;
		T->ind->next=NULL;
		T->next=NULL;
	}	
}

void addbeginc(courseindex* &T,char number[],int index,int x)
{
	courseindex *L=new(courseindex);
	strcpy(L->number,number);
	L->ind=new(node);
	L->ind->index=x;
	L->ind->next=NULL;
	L->next=T;
	T->index=index;
	T=L;
}

void addendc(courseindex *T,char number[],int index,int x)
{
	while(T->next!=NULL)
	T=T->next;
	T->next=new(courseindex);
	strcpy(T->number,number);
	T->next->next=NULL;
	T->next->index=index;
	T->next->ind=new(node);
	T->next->ind->index=x;
	T->next->ind->next=NULL;
}

void addbeforec(courseindex *T,char number[],char number1[],int index,int x)
{
	int w=strcmp(T->number,number1);
	while(w!=0)
	{
	    T=T->next;
	    w=strcmp(T->number,number1);
	}
	courseindex *L=T->next;
	strcpy(T->number,number);
	T->next->ind=new(node);
	T->next->index=index;
	T->next->ind->index=x;
	T->next->ind->next=NULL;
	T->next->next=L;
}

courseindex *O;

void insertc(courseindex* &T,char number[],int index,int x)
{
	if(T!=NULL)
	{
        	x=strcmp(T->number,number);
   	     	if(x!=0&&T->next!=NULL)
		{
		    insertc(T->next,number,index,x);
	    m++;
		}
//		else if(x>0)
//		{
//			if(m==0)
//			addbeginc(O,number,index,x);
//			else
//			addbeforec(O,number,T->number,index,x);
//		}
		else if(T->next==NULL&&x!=0)
		addendc(T,number,index,x);
		else
		{
			M=T->ind;
	    	insert(T->ind,x);
	    	T->ind=M;
		}
	}
	else
	{
		T=new(courseindex);
		strcpy(T->number,number);
		T->ind=new(node);
		T->index=index;
		T->ind->index=x;
		T->ind->next=NULL;
		T->next=NULL;
	}	
}

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

void storestudent(ofstream &out,studindex *S)
{
	while(S!=NULL)
	{
		out<<S->rollno<<"$"<<S->index;
		while(S->ind!=NULL)
		{
			out<<"$"<<S->ind->index;
			S->ind=S->ind->next;
		}
		out<<"*"<<endl;
		S=S->next;
	}
}

void storecourse(ofstream &out,courseindex *S)
{
	while(S!=NULL)
	{
		out<<S->number<<"$"<<S->index;
		while(S->ind!=NULL)
		{
			out<<"$"<<S->ind->index;
			S->ind=S->ind->next;
		}
		S=S->next;
		out<<"*"<<endl;
	}
}

int main()
{
	buffer b1,b2;
	student s,S;
	course c,C;
	studindex *i1=NULL;
	courseindex *i2=NULL;
	int k=0,j=0,l=0;
	ofstream out1("studentdata.txt"),out2("coursedata.txt");
	out1.close();
	out2.close();
	fstream in1,in2,in;
	in1.open("studentdata.txt",ios::in|ios::out);
	in2.open("coursedata.txt",ios::in|ios::out);
	in.open("index.txt");
	int a=0,z=1,b;
	char ch;
	do
	{
		cout<<"Enter rollno: ";
		cin>>s.rollno;
		a=0;
    	in1.seekg(0,ios::beg);
		while(a<k)
		{
			in1>>S;
			z=strcmp(s.rollno,S.rollno);
			if(z==0)
			{b++;
			break;
		}
			a++;
		}
		b=a;
		a=0;
		l++;
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
		    b++;
		}
	    cout<<"Enter course no: ";
        cin>>c.number;
	    in2.seekg(0,ios::beg);
		while(a<j)
		{
			in2>>C;
			z=strcmp(C.number,c.number);
			if(z==0)
			{
			a++;
			break;
		}
			a++;
		}
		if(z!=0)
		{
		    cout<<"Enter course name: ";
		    cin>>c.name;
		    b2.pack1(c.number);b2.pack(c.name);
		    in2<<j<<"$";
		    b2.store(in2);
		    j++;
		    a++;
		}
		ctr=0;m=0;
		inserts(i1,s.rollno,b-1,a-1);
		ctr=0;m=0;
		insertc(i2,c.number,a-1,b-1);
		cout<<"Do you want to enter more entries: ";
		cin>>ch;
	}while(ch=='y');
	in1.close();
	in2.close();
	in.close();
	out1.open("studentindex.txt");
	out2.open("courseindex.txt");
	storestudent(out1,i1);
	storecourse(out2,i2);
	out1.close();
	out2.close();
	return 0;
}
