#include<iostream>
#include<fstream>
#include<cstring>

using namespace std;

const int d=26;
int v,m=0;

struct trie_node;
struct member;
union u;

struct member2
{
	char ch[d+1];
	trie_node *child[d+1];
};

struct member1
{
	char ch[15];
	int rno;
};

union u
{
	member1 m1;
	member2 m2;
};

struct trie_node
{
	int tag;
	u data;
};

void sort(char ch[],int i)
{
	for(int j=0;j<i-1;j++)
	{
		for(int k=0;k<i-j-1;k++)
		if(ch[k]>ch[k+1])
		{
			char c=ch[k];
			ch[k]=ch[k+1];
			ch[k+1]=c;
		}
	}
}

void make_null(trie_node *T)
{
	for(int i=0;i<=d;i++)
	T->data.m2.child[i]=NULL;
}

void create(trie_node* &T,char ch[])
{
	trie_node *M=new(trie_node);
	M->tag=1;
	strcpy(M->data.m1.ch,ch);
	make_null(M);
	int i;
	if(T->data.m1.ch[v]=='\0')
	i=d;
	else
	for(i=0;i<d;i++)
	{
	    if(M->data.m2.ch[i]==T->data.m1.ch[v])
	    break;
	}
	M->data.m2.child[i]=T;
	T=M;
}

void create_trie(trie_node* &T,char ch[],char elt[],int rno)
{
	if(T==NULL)
	{
		if(m<v)
		m=v;
		T=new(trie_node);
		T->tag=0;
		T->data.m1.rno=rno;
		strcpy(T->data.m1.ch,elt);
	}
	else if(T->tag==1)
	{
		int i;
		for(i=0;i<d;i++)
		if(T->data.m2.ch[i]==elt[v])
		break;
		v++;
		create_trie(T->data.m2.child[i],ch,elt,rno);
	}
	else
	{
		create(T,ch);
		int i;
		if(elt[v]=='\0')
		i=d;
		else
		for(i=0;i<d;i++)
		if(T->data.m2.ch[i]==elt[v])
		break;
		v++;
		create_trie(T->data.m2.child[i],ch,elt,rno);
	}
}

void store(trie_node *T,ofstream &out,int x)
{
	if(T!=NULL)
	{
		if(T->tag==1)
		{
			if(x==0)
			{
			    out<<T->tag<<" ";
				out<<T->data.m2.ch;
				out<<"    ";
			}
			else
			for(int i=0;i<=d;i++)
			store(T->data.m2.child[i],out,x-1);
		}
		else
		{
			if(x==0)
			out<<T->tag<<" "<<T->data.m1.rno<<" "<<T->data.m1.ch<<"    ";
		}
	}
}

int search(trie_node *T,char ch[])
{
	if(T==NULL)
	return -1;
	else
	{
		if(T->tag==1)
		{
			int i;
			for(i=0;i<d;i++)
			if(T->data.m2.ch[i]==ch[v])
			break;
			v++;
			return search(T->data.m2.child[i],ch);
		}
		else
		{
			int w=strcmp(T->data.m1.ch,ch);
			if(w==0)
			return T->data.m1.rno;
			else
			return -1;
		}
	}
	
}

int main()
{
	char ch[15],alpha[27];
	int choice,i=0,no=0,count;
	m=0;
	trie_node *T=new(trie_node);
	T->tag=1;
	make_null(T);
	ofstream out("triedata.txt");
	do
	{
		cout<<"Enter name: ";
		cin>>ch;
		out<<i++<<" "<<ch<<endl;
	//	for(int j=0;j<strlen(ch);j++)
//		{
//			int count=0;
//		    for(int k=0;k<no;k++)
//		    {
//		    	if(ch[j]==alpha[k])
//		    	{
//		    		count=1;
//		    		break;
//		    	}
//		    }
//		    if(count==0)
//		    alpha[no++]=ch[j];
//		}
		cout<<"Press 1 to enter more records: ";
		cin>>choice;
	}while(choice==1);
	for(no=0;no<26;no++)
	alpha[no]=97+no;
	alpha[no]='\0';
	v=no;
	sort(alpha,no);
	strcpy(T->data.m2.ch,alpha);
	out.close();
	ifstream in("triedata.txt");
	in.unsetf(ios::skipws);
	char c;
	in>>count>>c;
	while(!in.eof())
	{
		v=0;
		in.getline(ch,15,'\n');cout<<ch<<" ";
		create_trie(T,alpha,ch,count);
		in>>count>>c;
	}
	in.close();
	out.open("trie_index.txt");
	cout<<m;
	for(int i=0;i<=m;i++)
	{
		store(T,out,i);
		out<<endl;
	}
	out.close();
	cout<<"Enter elt to search: ";
	cin>>ch;
	v=0;
	choice=search(T,ch);
	if(choice==-1)
	cout<<"Elt not found";
	else
	cout<<"Elt found at rec location: "<<choice;
	return 0;
}
