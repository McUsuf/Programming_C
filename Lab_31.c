#include <stdlib.h>
#include <stdio.h>

int part(int a[], int left, int right){
	int v=a[(left+right)/2];
	int i=left;
	int j=right;
	while(i<=j){
		while(a[i]<v){
			i++;
		}
		while(a[j]>v){
			j--;
		}
		if(i>=j){
			break;
		}
		int tmp=a[i];
		a[i]=a[j];
		a[j]=tmp;
		++i;
		--j;
	}
	return j;
}

void quickSort(int a[],int left, int right){
	if(left<right){
		int q=part(a, left, right);
		quickSort(a, left, q);
		quickSort(a, q+1 , right); 
	}
}

int main(){
	int *a;
	int N;
	
	scanf("%d",&N);
	a=malloc(N*sizeof(int));
	for(int i=0;i<N;++i){
		scanf("%d", &a[i]);
	}
	
	quickSort(a,0,N-1);
	
	for(int i=0;i<N;++i){
		printf("%d ", a[i]);
	}
	return 0;
}
