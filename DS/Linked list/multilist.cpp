#include<iostream>
#include<cstring>
using namespace std;

struct student;

struct course;

struct mlnode
{
	union
	{
		mlnode *next;
		student *sptr;
	}*down;
	union
	{
		mlnode *next;
		course *cptr;
	}*right;
	int tag1;
	int tag2;
};

struct student
{
	char name[10];
	char rollno[7];
	student *next;
	mlnode *down;
};

struct course
{
	char name[10];
	course *next;
	mlnode *right;
};

char ch[11];
int a;
void addstudcourse(student *s,course *c,mlnode *m)
{
	cout<<"Enter rollno of student: ";
	cin>>ch;
	a=1;
	while(s->next!=NULL)
	{
		a=strcmp(s->rollno,ch);
		if(a==0)
		break;
		s=s->next;
	}
	if(a!=0)
	{
		a=strcmp(s->rollno,ch);
		if(a!=0)
		{cout<<a;
			s->next=new(student);cout<<a;
			s=s->next;cout<<a;
			strcpy(s->rollno,ch);
			cout<<"Enter name of student: ";
			cin>>ch;
			strcpy(s->name,ch);
			s->next=NULL;
			s->down=NULL;
		}
	}
	a=1;
	cout<<"Enter course name: ";
	cin>>ch;
	while(c->next!=NULL)
	{
		a=strcmp(c->name,ch);cout<<a;
		if(a==0)
		break;
		c=c->next;
	}
	if(a!=0)
	{
		a=strcmp(c->name,ch);
		if(a!=0)
		{cout<<a;
			c->next=new(course);
			c=c->next;
			strcpy(c->name,ch);
			c->next=NULL;
			c->right=NULL;
		}
	}
	mlnode *l;
	if(s->down!=NULL)
	{
	    m=s->down;cout<<"!";
	    while(m->tag1==1)
	    m=m->down->next;
	    m->tag1=1;cout<<"!";
	    m->down->next=new(mlnode);
	    m=m->down->next;
	    m->tag1=2;cout<<"!";
	    m->down->sptr=s;cout<<"!";
	    m->tag2=0;
	    l=m;cout<<"@";
    }
    else
    {
    	s->down=new(mlnode);
    	m=s->down;
    	l=m;
    	m->tag1=2;
    	m->down->sptr=s;
    	m->tag2=0;
    }cout<<"#";
    if(c->right!=NULL)
	{
	    m=c->right;
	    while(m->tag1==1)
	    m=m->right->next;
	    m->right->next=l;
	    l->tag2=2;
	    l->right->cptr=c;cout<<"$";
    }
    else
    {cout<<"$";
    	c->right=m;
    	m->tag2=2;
    	m->right->cptr=c;
    }
}

void search(student *s,char ch[],mlnode *m)
{
	course *c;
	while(s!=NULL)
	{
		a=strcmp(s->rollno,ch);
		if(a==0)
		break;
		s=s->next;
	}
	if(s==NULL)
	{ 
	    cout<<"Student not found!";
	    return ;
	}
	else
	{
		m=s->down;
		while(m->tag1==1)
		{
			while(m->tag2==1)
			m=m->right->next;
			c=m->right->cptr;
			cout<<c->name<<" ";
		    m=m->down->next;
		}
		while(m->tag2==1)
			m=m->right->next;
			c=m->right->cptr;
			cout<<c->name<<" ";
	}
}

int main()
{
	student *s;
	course *c;
	mlnode *m;
	cout<<"Enter rollno and name of student: ";
	cin>>ch;
	s=new(student);
	strcpy(s->rollno,ch);
	cin>>ch;
	strcpy(s->name,ch);
	s->next=NULL;
	s->down=NULL;
	cout<<"Enter course choosen by student: ";
	cin>>ch;
	c=new(course);
	strcpy(c->name,ch);
	c->next=NULL;
	c->right=NULL;
	m=new(mlnode);
	s->down=m;
	c->right=m;
	m->tag1=2;
	m->down->sptr=s;
	m->tag2=2;
	m->right->cptr=c;
	cout<<"Enter y to continue: ";
	char choice;
	cin>>choice;
	while(choice=='y')
    {
    	addstudcourse(s,c,m);
    	cout<<"Enter y to continue: ";
    	cin>>choice;
	}
	cout<<"Enter rollno to search: ";
	cin>>ch;
	search(s,ch,m);
	return 0;
}
