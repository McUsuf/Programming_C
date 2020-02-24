#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
	char alphabet[11]={'0','1','2','3','4','5','6','7','8','9','\0'};
	char inputNum[11];
	int numOfPerms;
	int* permutation;
	int length=0;
	scanf("%s", inputNum);
	scanf("%d", &numOfPerms);
	length=strlen(inputNum);
	permutation = malloc(length*sizeof(int));
	for(int i=0; inputNum[i]!='\0';++i){
		int j;
		for(j=0;(alphabet[j]!=inputNum[i])&&(alphabet[j]!='\0');++j);
		if(alphabet[j]=='\0'){
			printf("bad input");
			return 0;
		}
		permutation[i]=j;
	}
	for(int i=0; i<length-1;++i){
		for(int j=i+1;j<length-1;++j){
			if(permutation[i]==permutation[j]){
				printf("bad input");
				return 0;
			}
		}
	}
	while(numOfPerms){
		int maxPoint=-1;
		int i=length-1;
		if(i==0){
			return 0;
		}
		while(i){
			int max=permutation[i];
			for(int j=length-1;j>=i;--j){
				if(max<=permutation[j]){
					max=permutation[j];
					break;
				}
			}
			if((max==permutation[i])&&(permutation[i-1]<max)){
				maxPoint=i;
				break;
			}
			if(i==1){
				return 0;
			}
			--i;
		}
		int minPoint=maxPoint;
		int min=permutation[maxPoint];
		for(int i=maxPoint;i<length;i++){
			if((permutation[i]<=min)&&(permutation[i]>permutation[maxPoint-1])){
				minPoint=i;
				min=permutation[i];
			}
		}
		int tmpNum=permutation[minPoint];
		permutation[minPoint]=permutation[maxPoint-1];
		permutation[maxPoint-1]=tmpNum;
		int j=length-1;
		for(int i=maxPoint;i<j;++i,--j){
			tmpNum=permutation[i];
			permutation[i]=permutation[j];
			permutation[j]=tmpNum;
		}
		for(int i=0;i<length;++i){
			printf("%d", permutation[i]);
		}
		printf("\n");
		numOfPerms--;
	}
	return 0;
}
