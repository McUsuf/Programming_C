/*#include "pch.h"*/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

typedef struct Stack{
	short int ind;
	struct Stack *prev;
}stack;

void sPush(stack **head, int ind)
{
	stack *newNode = (stack*)malloc(sizeof(stack));
	newNode->prev = (*head);
	newNode->ind = ind;
	*head = newNode;
}

void PrintStack(stack **head)
{
	stack *curr = *head;
	while (curr) {
		printf("%d ", curr->ind+1);
		curr = curr->prev;
		free(*head);
		*head = curr;
	}
}

bool TopSort(bool **verteces, int ind, bool *visited, bool *inStack, stack **head, bool err, int N)
{
	if (verteces[ind]) {
		for (int j = 0; j < N; j++) {
			if (verteces[ind][j]) {
				if (inStack[j]) {
					continue;
				}
				else if (visited[j]) {
					printf("impossible to sort\n");
					return true;
				}
				visited[j] = true;
				err = TopSort(verteces, j, visited, inStack, head, err, N);
				if (err) return true;
				if (!inStack[j]) sPush(head, j);
				inStack[j] = true;
			}
		}
	}
	if (!inStack[ind]) sPush(head, ind);
	inStack[ind] = true;
	return false;
}

int main()
{
	int N, M;
	FILE* f = fopen("in.txt", "r");
	int count = 2, a = 0;
	if (a = fscanf(f, "%d %d", &N, &M) < 2) {
		if (a == 0) return 0;
		printf("bad number of lines");
		return 0;
	}
	if (N > 1000 || N < 0) {
		printf("bad number of vertices");
		return 0;
	}
	else if (M > N*(N + 1) / 2 || M < 0) {
		printf("bad number of edges");
		return 0;
	}

	bool **verteces = (bool**)malloc(sizeof(bool*)*N);
	for (int i = 0; i < N; i++) {
		verteces[i] = NULL ;
	}

	while(!feof(f)) {
		int from, to;
		if (fscanf(f, "%d %d", &from, &to) != 2) {
			if (feof(f) && (count >= M + 2)) {
				break;
			}
			printf("bad number of lines");
			return 0;
		}
		if (from > N || from < 1 || to> N || to < 1) {
			printf("bad vertex");
			return 0;
		}

		if (!verteces[from - 1]) {
			verteces[from - 1] = (bool*)malloc(sizeof(bool)*N);
			for (int j = 0; j < N; j++) {
				verteces[from - 1][j] = false;
			}
		}
		verteces[from - 1][to - 1] = 1;
		count++;
		char c[1];
		fread(c, sizeof(char), 1, f);
	}
	fclose(f);

	bool *visited = (bool*)malloc(sizeof(bool)*N);
	bool *inStack = (bool*)malloc(sizeof(bool)*N);
	for (int i = 0; i < N; i++) {
		visited[i] = false;
		inStack[i] = false;
	}
	stack *out = NULL;
	for (int i = 0; i < N; i++) {
		if (!inStack[i]) {
			if (TopSort(verteces, i, visited, inStack, &out, 0, N)) return 0;
		}
	}
	PrintStack(&out);
	printf("\n");
}
