#include <stdio.h>       // including libraries   
#include <string.h>
#include <ctype.h>
long int sd[100];
int top1=-1,flag1=0;
struct stack
{
	char str[100];
	int top;
}stack;
char ch[100],cpy[100],Space_Remover[100]; 
int l;
void input()
{
	int i=0,d=0,j=0;              
    fgets (ch,100, stdin);   //to get space seperated input
	l=strlen(ch);           //calculating the length of the string
	while(i<l)//removes spaces if there are any in the expression provided
    {   
        if((ch[i]!=' '))
            Space_Remover[d++]=ch[i];
       i++;
    }
	strcpy(ch,Space_Remover);        //reassigning array 
	l=strlen(ch)-1;         
	ch[l]='\0'; //fgets doesnt provide NULL char like scanf so adding manually

}
void error_check()// checks error
{
	int count1=0,count2=0,i=0;
	if(ch[0]=='-' || ch[0]=='*' || ch[0]=='/' || ch[0]==')')    // the ischecking statements return non zero if true and 0 if false
	{
		printf("please enter a valid input\n");
        input();
        error_check();
	}
	else
            if(ch[l-1]=='-' || ch[l-1]=='*' || ch[l-1]=='/' || ch[l-1]=='(' || ch[l-1]=='+')
	       {
		    printf("please enter a valid input\n");
            input();
            error_check();
	       }
	while(i<l)
    {   int Check =0;
    	if((isdigit(ch[i]) && ch[i+1]=='(') || (isdigit(ch[i]) && ch[i-1]==')'))
    	Check =1;
    	else if(((ch[i]=='-' || ch[i]=='*' || ch[i]=='/') && ch[i-1]=='(') || ((ch[i]=='+' || ch[i]=='-' || ch[i]=='*' || ch[i]=='/') && ch[i+1]==')'))
    	Check =1;
    	else if((ch[i]=='+' || ch[i]=='-' || ch[i]=='*' || ch[i]=='/') && (ch[i+1]=='+' || ch[i+1]=='-' || ch[i+1]=='*' || ch[i+1]=='/'))
    	Check =1;

    	else if((ch[i]=='(' && ch[i+1]==')') || (ch[i+1]=='(' && ch[i]==')') || (ch[i]=='(' && ch[i+1]=='+' && ch[i+2]==')'))
    	Check =1;
    	else if(isalpha(ch[i]))
    	Check =1;
         if(Check==1)
        {
            printf("invalid input!!please enter a valid input\n");
            input();
            error_check();
        }
        if(ch[i]=='(')
        	count1++;
        else if(ch[i]==')')
        	count2++;
        i++;
    }
    if(count1!=count2)    //number of opening and closing brackets
    {
    	printf("please enter a valid input\n");
        input();
    	error_check();
    }
}
void initialisation(struct stack *s)
{
	s->top=-1;
}
int empty(struct stack *s)   //checking if empty
{
	if(s->top==-1)
		return(1);
	else
		return(0);
}
char top(struct stack *s)  //traversing through stack by using top
{
	return(s->str[s->top]);
}
void push(struct stack *s,char c)     
{
	s->top=s->top+1;
    s->str[s->top]=c;
}
char pop(struct stack *s)
{
	char x=s->str[s->top];
	s->top=s->top-1;
	return(x);
}
int priority(char x)
{
    switch(x)
{
    case'(':return(0);break;
    case'+':return(1);break;
    case'-':return(1);break;
    case'*':return(2);break;
    case'/':return(2);break;
}
   return(3);
}
int pop_postfix()
{
	return(sd[top1--]);
}
int Push_Post(int e)
{
	if(flag1==1)
	{
		long int num;
		num=pop_postfix();
		sd[++top1]=e+10*num;
	}
	else if(flag1==0)
	{
		sd[++top1]=e;
		flag1=1;
	}
}
void evaluate()    // evaluating the postfix
{
	long int i=0,op1,op2,f=0;
	char c;
	while(((c=cpy[i++])!='\0')&&(f!=1))
	{
		if(isdigit(c))
			Push_Post(c-'0');
		else if(c==' ')
			flag1=0;
		else
		{
			flag1=0;
            op2=pop_postfix();
            op1=pop_postfix();
            switch(c)
            {
            	case '+':Push_Post(op1+op2);
            			break;
            	case '-':Push_Post(op1-op2);
            			break;
                case '*':Push_Post(op1*op2);
                		break;
                case '/':{
                			if(op2!=0)
                				Push_Post(op1/op2);
                			if(op2==0)
                			{
                				printf("divide by zero error enter valid expression\n");
                				f=1;
                			}
                			break;
                		 }	
            }
		}
	}
	if(f==0)
	printf("The result is: %ld\n",sd[top1]);
}
int main()
{
	int j=0,i=0;
	input();
    error_check();
    struct stack s;
    initialisation(&s);
    char c,flag[100];
    strcat(ch,")");
    strcpy(flag,"(");
    strcat(flag,ch);
    strcpy(ch,flag);
    l=strlen(ch);
    while(i<l)
    {
    	if((isdigit(ch[i]))&&(isdigit(ch[i+1])))
    	{
    		cpy[j]=ch[i];                               //creating additional data for priority and evaluation
    		j++;
    	}
    	else if((isdigit(ch[i]))&&(!isdigit(ch[i+1])))
    	{
    		cpy[j++]=ch[i];
    		cpy[j++]=' ';
    	}

    	else if(ch[i]=='(')
    		push(&s,'(');
    	else
    	{
    		if(ch[i]==')')
    		{
    			for(;(c=pop(&s))!='(';)
    			{	
    				cpy[j++]=c;
    				cpy[j++]=' ';
                }
       		}
       		else
       		{
       			for(;priority(ch[i])<=priority(top(&s)) && !empty(&s);)
       			{
       				c=pop(&s);
       				cpy[j++]=c;
       				cpy[j++]=' ';         //space after operator
       			}
       			push(&s,ch[i]);
       		}
    	}
        i++;
    }
    evaluate();
    return 0;
}
