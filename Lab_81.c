#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <malloc.h>
#include <stdbool.h>

void Errors_check(int number_of_vertex, int number_of_edges,FILE* output) {
	if (number_of_vertex == 0)
	{
		fprintf(output,"%s","no spanning tree");
		exit(0);
	}
	

	if (number_of_vertex < 0 || number_of_vertex>5000) {
		fprintf(output,"%s","bad number of vertices");
		exit(0);
	}


	if (number_of_edges<0 || number_of_edges>number_of_vertex*(number_of_vertex + 1) / 2) {
		fprintf(output,"%s","bad number of edges");
		exit(0);
	}

	if(number_of_edges<number_of_vertex-1) {
		fprintf(output, "%s", "no spanning tree");
		exit(0);
	}
}

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

void printMST(int parent[], int n, unsigned int **graph, int V, FILE* output)
{
	for (int i = 1; i < V; i++) {
		fprintf(output, "%d ", parent[i] + 1);
		fprintf(output, "%d\n", i + 1);
	}
}

int minKey(unsigned int key[], bool mstSet[], int V)
{

	unsigned int min = ULONG_MAX;
	int min_index;

	for (int v = 0; v < V; v++) {
		if (mstSet[v] == false && key[v] < min)
		{
			min = key[v];
			min_index = v;
		}
	}

	return min_index;
}

void primMST(unsigned int** graph, int numOfVerts, FILE* output){
	int *parent= (int*)malloc(numOfVerts*sizeof(int));
	unsigned int* key= (unsigned int*)malloc(numOfVerts*sizeof(unsigned int));
	bool *mstSet= (bool*)malloc(numOfVerts*sizeof(bool));
	
	for(int i=0; i<numOfVerts;i++){
		key[i]= ULONG_MAX;
		mstSet[i]=false;
	}
	
	key[0]=0;
	parent[0]=-1;
	
	for(int count=0;count<numOfVerts-1;count++){
		int u= minKey(key, mstSet, numOfVerts);
		mstSet[u]=true;
		for(int v=0; v<numOfVerts;v++){
			if((graph[u][v]) && (mstSet[v]==false)&&(graph[u][v]<key[v])){
				parent[v]=u;
				key[v]=graph[u][v];	
			}	
		}
	}
	for(int i=0;i<numOfVerts;i++){
		if(key[i]==ULONG_MAX){
			fprintf(output,"no spanning tree");
			exit(0);
		}
	}
	printMST(parent, numOfVerts, graph, numOfVerts, output);	
}

int main(){
	FILE* input;
	input=fopen("in.txt","r");
	FILE* output;
	output=fopen("out.txt","w");
	int numOfVerts;
	fscanf(input, "%d", &numOfVerts);
	int numOfEdges;
	fscanf(input, "%d", &numOfEdges);
	Errors_check(numOfVerts,numOfEdges,output);
	unsigned int** graph= getGraph(numOfVerts, numOfEdges, input, output);
	primMST(graph, numOfVerts, output);
	fclose(input);
	fclose(output);
	return 0;
}
