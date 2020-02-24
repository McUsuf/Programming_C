#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <malloc.h>
#include <stdbool.h>

void isCorrectVerEdLength(int start, int end, unsigned int length, int number_of_vertex, FILE* output) {
	if (start < 1 || start > number_of_vertex || end < 1 || end > number_of_vertex) {
		fprintf(output, "%s", "bad vertex");
		exit(0);
	}
	if (length < 0 || length > INT_MAX) {
		fprintf(output, "%s", "bad length");
		exit(0);
	}
}

unsigned int **getGraph(int number_of_vertex, int number_of_edges,  FILE* input,FILE* output) {
	unsigned int** graph = (unsigned int**)malloc(number_of_vertex * sizeof(unsigned int));
	
	for (int i = 0; i < number_of_vertex; i++) {
		graph[i] = (unsigned  int*)calloc(number_of_vertex, sizeof(unsigned int));
	}

	for (int i = 0; i < number_of_edges; ++i) {
		
		int n = 0, m = 0;
		unsigned int l=0;
		fscanf(input, "%d", &n);
		fscanf(input, "%d", &m);
		fscanf(input, "%d", &l);
		if (feof(input)) {
			if (i < number_of_edges) {
				fprintf(output, "%s", "bad number of lines");
				exit(0);
			}
		}
		
		isCorrectVerEdLength(n, m, l, number_of_vertex, output);
		n--;
		m--;
		//printf("Before: %d %d %d",n,m,graph[n][m]);
		graph[n][m] = (unsigned int)l;
		//printf("Before: %d %d %d",m,n,graph[m][n]);
		graph[m][n] = (unsigned int)l;	
	}
	return graph;
}

int main(){
	FILE* input;
	input=fopen("in.txt","r");
	FILE* output;
	output=fopen("out.txt","w");

	int numOfVerts;
	fscanf(input, "%d", &numOfVerts);
	if((numOfVerts<0) || (numOfVerts>5000)){
		fprintf(output, "bad number of vertices");
		return 0;
	}
	
	int S,F;
	fscanf(input,"%d %d", &S,&F);
	if((S<1)||(S>numOfVerts)||(F<1)||(F>numOfVerts)){
		fprintf(output,"bad vertex");
		return 0;	
	}
	
	int numOfEdges;
	fscanf(input, "%d", &numOfEdges);
	if((numOfEdges<0) || (numOfEdges>(numOfVerts*(numOfVerts-1))/2)){
		fprintf(output, "bad number of edges");
		return 0;	
	}
	
	unsigned int** graph= getGraph(numOfVerts, numOfEdges, input, output);
	unsigned int* minDist=(unsigned int*)malloc(numOfVerts*sizeof(unsigned int));
	unsigned int* parents=(unsigned int*)malloc(numOfVerts*sizeof(unsigned int));
	bool* visited=(bool*)malloc(numOfVerts*sizeof(bool));

	for(int i=0; i<numOfVerts;i++){
		minDist[i]=-1;
		visited[i]=false;	
	}
	minDist[S]=0;
	for(int i=0;i<numOfVerts;i++){
		unsigned int v=-1;
		for(int j=0;j<numOfVerts;j++){
			if((!visited[j])&&((v==-1)||(minDist[j]<minDist[v]))){
				v=j;
			}
		}
		if(minDist[v]==-1)
			break;
		visited[v]=true;
		
		for(int j=0;j<numOfVerts;j++){
			if(graph[v][i]>0){
				int temp=minDist[v]+graph[v][i];
				if(temp<minDist[i]){
					minDist[i]=temp;
					parents[i]=v;
				}
		}	
	}
	for(int i=0;i<numOfVerts;i++){
		if(minDist[i]=-1){
			fprintf(output,"oo ");
		}
		else if(minDist[i]>INT_MAX){
			fprintf(output,"INT_MAX+ ");
		}
		else{
			fprintf(output,"%d ",minDist[v]);
		}
	}
	fprintf(output,"%d ",S);
	fprintf(output,"\n");
	
	return 0;
}
