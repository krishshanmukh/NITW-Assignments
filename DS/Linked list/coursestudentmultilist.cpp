#include<iostream>
#include<cstring>
using namespace std;

struct student
{
	char rollno[7];
	char name[10];
	student *next;
};

struct course
{
	char name[10];
	course *next;
};

struct mlnode
{
	student *sptr;
	course *cptr;
	mlnode *next;
};

void addcourse(mlnode *M,char c[])
{
	while(M->next!=NULL)
	M=M->next;
	M->next=new(mlnode);
	M=M->next;
	M->next=NULL;
	M->cptr=new(course);
	strcpy(M->cptr->name,c);
	M->cptr->next=NULL;
	M->sptr=NULL;
}

void addstudent(student *M,char c[],char d[])
{
	while(M->next!=NULL)
	M=M->next;
	M->next=new(student);
	M=M->next;
	strcpy(M->name,c);
	strcpy(M->rollno,d);
	M->next=NULL;
}

void display(mlnode *M)
{
	while(M!=NULL)
	{
		cout<<"course name: ";
		cout<<M->cptr->name<<endl;
		cout<<"Student details: \n";
		while(M->sptr!=NULL)
		{
			cout<<M->sptr->rollno<<"  "<<M->sptr->name<<endl;
			M->sptr=M->sptr->next;
		}
		M=M->next;
	}
}

void display1(mlnode *M)
{
	while(M!=NULL)
	{
		cout<<"Student name: ";
		cout<<M->sptr->name<<endl;
		cout<<"course details: \n";
		while(M->cptr!=NULL)
		{
			cout<<M->cptr->name<<endl;
			M->cptr=M->cptr->next;
		}
		M=M->next;
	}
}

void addcourse(course *M,char c[])
{
	while(M->next!=NULL)
	M=M->next;
	M->next=new(course);
	M=M->next;
	strcpy(M->name,c);
	M->next=NULL;
}

void copy(mlnode *N,char a[],char d[],char c[])
{
	int x;
	mlnode *T;
	while(N!=NULL)
	{
		T=N;
		x=strcmp(N->sptr->rollno,a);
		if(x==0)
		{	
		    addcourse(N->cptr,c);
		    break;
		}
		else
		N=N->next;
	}
	N=T;
	if(x!=0)
	{
		N->next=new(mlnode);
		N=N->next;
		N->sptr=new(student);
		strcpy(N->sptr->name,d);
		strcpy(N->sptr->rollno,a);
		N->cptr=new(course);
		N->cptr->next=NULL;
		strcpy(N->cptr->name,c);
		N->next=NULL;
		N->sptr->next=NULL;
	}
}

int main()
{
	mlnode *M,*N,*O;
	student *s;
	char c[10],d[7],co[10],choice='n';
	M=new(mlnode);
	O=M;
	M->cptr=new(course);
	M->cptr->next=NULL;
	M->next=NULL;
	M->sptr=NULL;
	N=new(mlnode);
	N->next=NULL;
	N->sptr=NULL;
	N->cptr=NULL;
	cout<<"Enter course name: ";
	cin>>co;
	strcpy(M->cptr->name,co);
	l:if(choice=='y')
	{
	    cout<<"Enter course name: ";
	    cin>>co;
	    addcourse(M,co);
    }
	cout<<"Enter no. of students who registered for the course: ";
	int a;
	cin>>a;
	while(M->next!=NULL)
	M=M->next;
	for(int j=0;j<a;j++)
	{
		cout<<"Enter rollno: ";
		cin>>d;
		cout<<"Enter name: ";
		cin>>c;
		if(M->sptr==NULL)
		{
			M->sptr=new(student);
			strcpy(M->sptr->name,c);
	        strcpy(M->sptr->rollno,d);
	        M->sptr->next=NULL;
		}
		else
		addstudent(M->sptr,c,d);
		if(N->sptr==NULL)
		{
			N->sptr=new(student);
			strcpy(N->sptr->name,c);
	        strcpy(N->sptr->rollno,d);
	        N->sptr->next=NULL;
	        N->cptr=new(course);
	        strcpy(N->cptr->name,co);
	        N->cptr->next=NULL;
		}
		else
		copy(N,d,c,co);
	}
	cout<<"Enter y to enter more courses: ";
	cin>>choice;
	if(choice=='y')
	goto l;
	cout<<"Enter 1 for course-sublist students ...other for student-sublist courses";
	cout<<endl;
	int ch;
	cin>>ch;
	if(ch==1)
	display(O);
	else
	display1(N);
	return 0;
}
