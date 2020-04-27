#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct
{
    int items[100];
    int top;
} stack;

void initialize(stack*s)
{
    s->top=0;
}

void push(stack*s,int number)
{
    s->items[s->top]=number;
    s->top++;
}

int pop(stack*s)
{
    int number;
    s->top--;
    number=s->items[s->top];
    return number;
}

int top(stack*s)
{
    return s->items[s->top-1];
}

int isEmpty(stack*s)
{
    if(s->top==0)
        return 1;
    else
        return 0;
}

int isFull(stack*s)
{
    if(s->top==100)
        return 1;
    else
        return 0;
}

void display(stack*s)
{
    stack copy;
    initialize(&copy);
    while(!isEmpty(s))
    {
        int x=pop(s);
        printf("%d\n",x);
        push(&copy,x);
    }
    while(!isEmpty(&copy))
    {
        push(s,pop(&copy));
    }
}

 int calculate(char operation,int number1,int number2)
 {
     if(operation=='+')
        return (number1+number2);
     if(operation=='-')
        return (number1-number2);
     if(operation=='*')
        return (number1*number2);
     if(operation=='/')
        return (number1/number2);
     if(operation=='%')
        return (number1%number2);
 }

 int operation( char op)
 {
     switch(op)
     {
     case'*':
     case'/':
     case'%':
        return 1;

     case'+':
     case'-':
        return 0;

     case'(':
        return 2;
     }
 }

 int evaluatePostfix(char postfix[])
{
    stack s;
    int number1,number2,result;
    initialize(&s);
    int i=0;

     while(postfix[i]!='\0')
     {
         if(isdigit(postfix[i]))

               push(&s,postfix[i]-'0');

         else
         {
             number2=pop(&s);
             number1=pop(&s);
             result=calculate(postfix[i],number1,number2);
             push(&s,result);
         }
         i++;
     }
    result=pop(&s);
    return result;
}


void infixTopostfix(char infix[],char postfix[])
{
    stack s;
    initialize(&s);
    int i=0;
    int j=0;


    while(infix[i]!='\0')
    {
      if(isdigit(infix[i]))
      {
          postfix[j]=infix[i];
          j++;
      }

      /*  else if(infix[i]=='(')
           {push(&s,infix[i]);
           } */

      else if(infix[i]==')')
      {
         while(!isEmpty(&s)&&top(&s)!='(')
         {
             postfix[j]=pop(&s);
             j++;
         }
         pop(&s);
      }
      else if(isEmpty(&s))
            push(&s,infix[i]);

      else
       {
            while(!isEmpty(&s)&& operation(top(&s))>= operation(infix[i]) && top(&s)!='(')
         {
             postfix[j]=pop(&s);
             j++;
         }
         push(&s,infix[i]);

       }
    i++;
    }
    while(!isEmpty(&s))
    {
        postfix[j]=pop(&s);
        j++;

    }
    postfix[j]='\0';

    // return postfix;
}


int main()
{
    int result;
    char infix[100],postfix[100];
    printf("\nEnter Infix: ");
    gets(infix);

    infixTopostfix(infix,postfix);
    printf("\nPostfix:%s",postfix);
    result=evaluatePostfix(postfix);

    printf("\nResult=%d",result);


    return 0;
}
