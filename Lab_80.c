#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <limits.h>

typedef struct Edge{
	short int from;
	short int to;
	int weight;
	char used;
} Edge;

void swap(Edge* a, Edge* b){
	Edge temp = *a;
	*a = *b;
	*b = temp;
}

void swapInt(int* a, int* b)
{
	int c = *a;
	*a = *b;
	*b = c;
}

void heapify(Edge* edges, int curIndex, int const len){
	int leftChild, rightChild, largestChild;
	while (1) {
		leftChild = 2 * curIndex + 1;
		rightChild = 2 * curIndex + 2;
		largestChild = curIndex;
		if (rightChild < len && edges[rightChild].weight < edges[leftChild].weight) {
			largestChild = rightChild;
		}
		else if (leftChild < len && edges[leftChild].weight < edges[curIndex].weight) {
			largestChild = leftChild;
		}
		if (largestChild == curIndex) {
			break;
		}
		swap(&(edges[curIndex]), &(edges[largestChild]));
		curIndex = largestChild;
	}
}

void buildHeap(Edge* edges, int length)
{
	for (int i = length / 2; i >= 0; i--) {
		heapify(edges, i, length);
	}
}

void heapSort(Edge* edges, int length)
{
	buildHeap(edges, length);
	for (int i = length - 1; i >= 0; i--) {
		swap(&(edges[i]), &(edges[0]));
		heapify(edges, 0, i);
	}
}

void makeSet(int* vertices, int x)
{
	vertices[x] = x;
}

int find(int vertices[], int x)
{
	if (vertices[x] == x){
		return x;	
	} 
	return (vertices[x] = find(vertices, vertices[x]));
}

void unite(int* vertices, int x, int y)
{
	x = find(vertices, x);
	y = find(vertices, y);
	if (rand() % 2 == 0){
		swapInt(&x,&y);	
	}
	vertices[x] = y;
}

int main(){
	FILE *input;
	int numOfVertices, numOfEdges;
	
	if(input=fopen("in.txt","r")){
		fscanf(input,"%d",&numOfVertices);
		if((numOfVertices>5000)||(numOfVertices<0)){
			printf("bad number of vertices");
			return 0;
		}
		fscanf(input,"%d",&numOfEdges);
		if ((numOfEdges < 0) || (numOfEdges > numOfVertices*(numOfVertices+1)/2)) {
			printf("bad number of edges");
			return 0;
		}
		Edge* edges = (Edge*)calloc(numOfEdges, sizeof(Edge));			
		int countOfStr=2;
		for(int i=0;i<numOfEdges;i++){
			int from,to, weight;
			if(fscanf(input,"%d %d %d",&from,&to,&weight)<3){
				printf("bad number of lines");
				return 0;
			}
			if((from<1)||(from>numOfVertices)||(to<1)||(to>numOfVertices)){
				printf("bad vertex");
				return 0;
			}
			if((weight > INT_MAX)||(weight<0)){
				printf("bad length");
				return 0;
			}
			edges[i].from=from;
			edges[i].to=to;
			edges[i].weight=weight;
			edges[i].used=0;
			countOfStr++;
		}
		if(countOfStr<numOfEdges+2){
			printf("bad number of lines");
			return 0;
		}
		heapSort(edges, numOfEdges);
		
		int *SetOfVertices=(int*)calloc(numOfVertices+1,sizeof(int));
		int countOfSet= numOfVertices;
		int countOfEdges= 0;
		for (int i=numOfEdges-1;i>=0;i--){
			int fromFind= find(SetOfVertices,edges[i].from);
			int toFind= find(SetOfVertices,edges[i].to);
			if(edges[i].from==edges[i].to){
				continue;
			}
			if((!toFind)&&(!fromFind)){
				makeSet(SetOfVertices, edges[i].from);
				makeSet(SetOfVertices, edges[i].to);
				unite(SetOfVertices, edges[i].to, edges[i].from);
				countOfSet--;
				edges[i].used=1;
				countOfEdges++;
			}
			else if(!fromFind){
				makeSet(SetOfVertices, edges[i].from);
				unite(SetOfVertices, edges[i].to, edges[i].from);
				countOfSet--;
				edges[i].used=1;
				countOfEdges++;		
			}
			else if(!toFind){
				makeSet(SetOfVertices, edges[i].to);
				unite(SetOfVertices, edges[i].to, edges[i].from);
				countOfSet--;
				edges[i].used=1;
				countOfEdges++;
			}
			else if(fromFind != toFind){
				unite(SetOfVertices, edges[i].to, edges[i].from);
				countOfSet--;
				edges[i].used=1;
				countOfEdges++;	
			}
			if(countOfEdges==numOfVertices-1){
				break;
			}
		}
		
		if (((countOfSet==1)||(countOfEdges==numOfVertices))&&(numOfVertices!=0)){
			for(int i=numOfEdges-1;i>=0;i--){
				if(edges[i].used==1){
					printf("%d %d\n", edges[i].from, edges[i].to);
					countOfEdges--;
				}
				if(!countOfEdges){
					break;
				}
			}	
		}
		else{
			printf("no spanning tree");
		}
	}
	else{
		printf("!dead input!");
		return 0;
	}
	return 0;
}
