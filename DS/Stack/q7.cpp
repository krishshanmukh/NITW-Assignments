#include<iostream>
#include<cstring>
using namespace std;
class stackc
{
public:
    char e[150];
    int top=-1;
    int size=150;
    void push(char a);
    char pop();
};
void stackc::push(char a)
{
    if(top<size-1)
        e[++top]=a;
    else
        cout<<"\nStack is Full!\n";
}
char stackc::pop()
{
    if(top>=0)
        return e[top--];
    else
        cout<<"\nStack is Empty!\n";
}
class stacki
{
public:
    int e[150];
    int top=-1;
    int size=150;
    void push(int a);
    int pop();
};
void stacki::push(int a)
{
    if(top<size-1)
        e[++top]=a;
    else
        cout<<"\nStack is Full!\n";
}
int stacki::pop()
{
    if(top>=0)
        return e[top--];
    else
        cout<<"\nStack is Empty!\n";
}
int main()
{
    char ch[150];
    int z=0;
    cout<<"\nEnter the infix expression:\n";
    cin.getline(ch,150);
    stacki num;
    stackc sym;
    int l=strlen(ch);
    for(int i=0;i<l;i++)
    {
        if(ch[i]>=48&ch[i]<=57)
        {
            int b=int(ch[i])-48;
            num.push(b);
        }
         else if((ch[i]=='+'||ch[i]=='*'||ch[i]=='-'||ch[i]=='/')&sym.top==(-1))
                sym.push(ch[i]);
         else if((ch[i]=='*'||ch[i]=='/')&(sym.e[sym.top]=='-'||sym.e[sym.top]=='+'))
                sym.push(ch[i]);
         else
         {
             while(sym.top>-1)
             {
                 int x,y;
                 y=num.pop();
                 x=num.pop();
                 char c=sym.pop();
                 if(c=='+')
                 z=x+y;
                 else if(c=='-')
                 z=x-y;
                 else if(c=='*')
                 z=x*y;
                 else if(c=='/')
                 z=x/y;
                 num.push(z);
             }
             sym.push(ch[i]);
         }
    }
    while(sym.top!=-1)
             {
                 int x,y;
                 y=num.pop();
                 x=num.pop();
                 char c=sym.pop();
                 if(c=='+')
                 z=x+y;
                 else if(c=='-')
                 z=x-y;
                 else if(c=='*')
                 z=x*y;
                 else if(c=='/')
                 z=x/y;
             }
             cout<<z;
             return 0;
}
