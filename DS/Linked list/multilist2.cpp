#include<iostream>
#include<cstring>
using namespace std;

struct student
{
	char rollno[6];
	student *next;
};

struct course
{
	char name[10];
	student *ptr;
	course *next;
};


void addstud(course *c,char ch[])
{
	if(c->ptr==NULL)
	{
		c->ptr=new(student);
	}
	else
	{
        while(c->ptr->next!=NULL)	
        c->ptr=c->ptr->next;
        c->ptr->next=new(student);
        c->ptr=c->ptr->next;
    }
    strcpy(c->ptr->rollno,ch);
    c->next=NULL;
    c->ptr->next=NULL;
}

void addcourse(course* &c,char ch[])
{
	if(c==NULL)
	{
		c=new(course);
	}
	else
	{
        c->next=new(course);
        c=c->next;
    }
    c->ptr=NULL;
    strcpy(c->name,ch);
    c->next=NULL;
}

int main()
{
	student *s;
	course *c;
	c=NULL;
	char ch[10],choice='y';
	do
	{
	    cout<<"Enter course name: ";
	    cin>>ch;
	    addcourse(c,ch);
	    static course *C=c;
	    cout<<"Enter no. of students: ";
	    int i;
	    cin>>i;
	    for(int j=0;j<i;j++)
	    {
	    	cout<<"Enter roll no: ";
	    	cin>>ch;
	    	addstud(c,ch);
	    }
	    cout<<"Enter y too enter more courses: ";
	    cin>>choice;
	}while(choice=='y');
	return 0;
}
