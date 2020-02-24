#include <stdlib.h>
#include <stdio.h>

//создание кучи
void sieve(int a[],int base, int front){
	int maxChild;
	int ready=0;
	
	while((base*2<=front)&&(!ready)){
		if(base*2==front){
			maxChild=front;
		}
		else if(a[base*2]>a[base*2+1]){
			maxChild=base*2;
		}
		else{
			maxChild=base*2+1;
		}
		if(a[base]<a[maxChild]){
			int tmp= a[base];
			a[base]= a[maxChild];
			a[maxChild]= tmp;
			base= maxChild;
		}
		else{
			ready=1;
		}
	}
}

//просеивание элементов
void heapSort(int a[],int arraySize){
	for(int i= (arraySize/2); i>=0; --i){
		sieve(a, i, arraySize-1);
	}
	for(int i=arraySize-1;i>=0; --i){
		int tmp= a[0];
		a[0]= a[i];
		a[i]= tmp;
		sieve(a, 0, i-1);
	}
}

int main(){
	int N;
	int *a;
	
	scanf("%d", &N);
	
	a=malloc(N*sizeof(int));
	for(int i=0;i<N;++i){
		scanf("%d", &a[i]);
	}	
	heapSort(a, N);

	for(int i=0;i<N;i++){
		printf("%d ", a[i]); 
	}
	free(a);
	return 0;
}
