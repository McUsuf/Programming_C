#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct SignStack{
	int sign;
	int count;
	struct SignStack* prev;
}SignStack;

void push(SignStack** curStack, int value){
	if(*curStack==NULL){
		SignStack* newStack=malloc(sizeof(*newStack));
		newStack->sign=value;
		newStack->count=1;
		newStack->prev=*curStack;
		*curStack=newStack;	
	}
	else{
		SignStack* newStack=malloc(sizeof(*newStack));
		newStack->sign=value;
		newStack->count=(*curStack)->count+1;
		newStack->prev=*curStack;
		*curStack=newStack;
	}
}
int pop(SignStack** curStack){
	if(*curStack==NULL){
		printf("syntax error");
		exit(0);
	}
	int value=(*curStack)->sign;
	SignStack* tmp= *curStack;
	*curStack=(*curStack)->prev;
	free(tmp);
	return value;	
}
int top(SignStack** curStack){
	if(curStack==NULL){
		printf("syntax error");
		exit(0);
	}
	return (*curStack)->sign;
}
int getPriority(char sign){
	switch(sign){
		case '(':
			return 0;
		case ')':
			return 1;
		case '+':
			return 3;
		case '-':
			return 3;
		case '*':
			return 4;
		case '/':
			return 4;
		default:
			return 5;
	}
}
bool isDigit(char c){
	if(('0'<=c)&&(c<='9')){
		return true;
	}
	else{
		return false;	
	}
}
bool isOperator(char c){
	switch(c){
		case '(':
			return true;
		case ')':
			return true;
		case '+':
			return true;
		case '-':
			return true;
		case '*':
			return true;
		case '/':
			return true;
		default:
			return false;
	}
}
bool isGood(char c){
	if(isDigit(c)){
		return true;
	}
	else if(isOperator(c)){
		return true;
	}
	else{
		return false;
	}
}

void makeReverse(char* input,char* rpn,int length){
	int i,j;
	SignStack* sigStack=NULL;
	for(i=0,j=0;i<length;i++){
		if(isDigit(input[i])){
			while((isDigit(input[i]))&&(i<length)){
				rpn[j]=input[i];
				j++;
				i++;
			}
			rpn[j]=' ';
			++j;	
		}
		if(isOperator(input[i])){
			if(input[i]=='('){
				
				push(&sigStack,input[i]);
			}
			else if(input[i]==')'){
				if(input[i-1]=='('){
					printf("syntax error");
					exit(0);
				}
				char c=pop(&sigStack);
				while(c!='('){
					rpn[j]=c;
					j++;
					rpn[j]=' ';
					j++;
					c=pop(&sigStack);
				}
			}
			else{
				while((sigStack!=NULL)&&(getPriority(input[i])<=getPriority(top(&sigStack)))){
						rpn[j]=pop(&sigStack);
						j++;
						rpn[j]=' ';
						j++;		
					}
				push(&sigStack, input[i]);
			}
		if((!isDigit(input[i]))&&(!isOperator(input[i]))){
			printf("syntax error");
			exit(0);	
		}
		}
	}
	while(sigStack!=NULL){
		rpn[j]=pop(&sigStack);
		if(rpn[j]=='('){
			printf("syntax error");
			exit(0);
		}
		rpn[++j]=' ';
		++j;
	}
	rpn[j]='\0';
}
int makeCount(char *rpn, int length){
	int result=0;
	SignStack* numStack=NULL;
	for(int i=0;i<length;i++){
		if(isDigit(rpn[i])){
			int curDig=0;
			while((isDigit(rpn[i]))&&(i<length)){
			curDig*=10;
			curDig+=rpn[i]-0x30;
			i++;	
			}
			push(&numStack, curDig);	
		}
		else if(isOperator(rpn[i])){
			int secondNum=pop(&numStack);
			int firstNum=pop(&numStack);
			switch(rpn[i]){
				case '+':
					result=firstNum+secondNum;
					break;
				case '-':
					result=firstNum-secondNum;
					break;
				case '*':
					result=firstNum*secondNum;
					break;
				case '/':
					if(secondNum==0){
						printf("division by zero");
						exit(0);
					}
					result=firstNum/secondNum;
					break;
			}
			push(&numStack,result);
		}
	}
	result= pop(&numStack);
	return result;
}
int main(){
	char input[1001];
	char rpn[1001];
	int result;
	scanf("%[^\n]s", &input);
	int length=strlen(input);
	for(int i=0;i<length;++i){
		if(!isGood(input[i])){
			printf("syntax error");
			return 0;
		}			
	}
	makeReverse(input, rpn, length);
	length=strlen(rpn);
	result=makeCount(rpn, length);
	printf("%d", result);
	return 0;
}
