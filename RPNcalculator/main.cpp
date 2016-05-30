#include "stack.h"


string InfixToPostfix(string expression);
double postfixEvaluation(string pfix);
bool HasHigherPrecedence(char operator1, char operator2);
bool IsOperator(char C);
bool IsOperand(char C);
double evaluate(double a,char op,double b);


int main(int argc, const char * argv[])
{
    string infix,postfix;
    double result;
//    cout<<"Enter an infixed expression:- ";
//    cin>>infix;
    infix="2^3+5-13/4";
    postfix=InfixToPostfix(infix);
    cout<<"\nPostfix expression:- "<<postfix;
    result=postfixEvaluation(postfix);
    cout<<"\nResult evaluation:- "<<result;
    return 0;
}

string InfixToPostfix(string infix)
{
    stack<char> OPERATOR;
    string postfix;
    int i=0;
    while (i<infix.length())
    {
        if (infix[i]==' ' || infix[i]==',') {
            continue;
        }
        else if (IsOperator(infix[i]))
        {
            while(!OPERATOR.empty() && OPERATOR.peep() != '(' && HasHigherPrecedence(OPERATOR.peep(),infix[i]))
			{
				postfix+= OPERATOR.pop();
                postfix+=',';
			}
			OPERATOR.push(infix[i]);
        }
        else if (IsOperand(infix[i]) || infix[i]=='.')
        {
            postfix+=infix[i];
            while (IsOperand(infix[i+1]) || infix[i+1]=='.') {
                postfix+=infix[i+1];
                i++;
            }
            postfix+=',';
        }
        else if (infix[i] == '(')
		{
			OPERATOR.push(infix[i]);
		}
        else if(infix[i] == ')')
		{
			while(!OPERATOR.empty() && OPERATOR.peep() !=  '(')
            {
				postfix += OPERATOR.pop();
                postfix+=',';
			}
			OPERATOR.pop();
		}
        i++;
    }
    while(!OPERATOR.empty())
    {
		postfix += OPERATOR.pop();
	}
	return postfix;
}



double postfixEvaluation(string pfix)
{
    stack<double> operand;
    double result;
    double op1,op2;
    int i=0;
    int j;
    while (i<pfix.length())
    {
        if (pfix[i]==',')
        {
            i++;
        }
        if (IsOperand(pfix[i]) || pfix[i]=='.')
        {
            j=1;
            result=(((double)pfix[i])-48);
            while (IsOperand(pfix[i+1]))
            {
                result*=10;
                result+=(((double)pfix[i+1])-48);
                i++;
            }
            if (pfix[i+1]=='.')
            {
                i++;
                while (IsOperand(pfix[i+1]))
                {
                    result+=(((double)pfix[i+1])-48)/(pow(10,j++));
                    i++;
                }
            }
            operand.push(result);
        }
        else if(IsOperator(pfix[i]))
        {
            op2=operand.pop();
            op1=operand.pop();
            result=evaluate(op1, pfix[i], op2);
            operand.push(result);
        }
        i++;
    }
    return operand.pop();
}



bool IsOperand(char C)
{
	if(C >= '0' && C <= '9')
        return true;
    else
        return false;
}

bool IsOperator(char C)
{
	if(C == '+' || C == '-' || C == '*' || C == '/' || C== '^')
		return true;
    else
        return false;
}


int IsRightAssociative(char op)
{
	if(op == '^')
        return true;
    else
        return false;
}


int GetOperatorWeight(char op)
{
	int weight = -1;
	switch(op)
	{
        case '-':
            weight =0;
            break;
        case '+':
            weight = 1;
            break;
        case '*':
            weight =2;
            break;
        case '/':
            weight = 3;
            break;
        case '^':
            weight = 4;
            break;
	}
	return weight;
}

bool HasHigherPrecedence(char op1, char op2)
{
	int op1Weight = GetOperatorWeight(op1);
	int op2Weight = GetOperatorWeight(op2);

	if(op1Weight == op2Weight)
	{
		if(IsRightAssociative(op1))
            return false;
		else
            return true;
	}
	return op1Weight > op2Weight ?  true: false;
}

double evaluate(double a,char op,double b)
{
	if(op == '+')
        return a+b;
	else if(op == '-')
        return a-b;
	else if(op == '*')
        return a*b;
	else if(op == '/')
        return a/b;
    else if(op=='^')
        return pow(a,b);
	else
        return -1;
}
