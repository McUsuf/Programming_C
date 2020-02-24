#include <stdio.h>
#include <string.h>
#include <limits.h>

const unsigned int INF = 2*INT_MAX-1;
#define unused -1

void inputError(int N, int M)
{
	if (N < 0 || N > 5000) {
		printf("bad number of vertices");
		exit(0);
	}
	if (M < 0 || M > N*(N + 1) / 2) {
		printf("bad number of edges");
		exit(0);
	}
}

void vertError(int V, int N)
{
	if (V < 1 || V > N) {
		printf("bad vertex");
		exit(0);
	}
}

void dataError(int from, int to, int weight, int N)
{
	vertError(from, N);
	vertError(to, N);
	if (weight < 0 || weight > INT_MAX) {
		printf("bad length");
		exit(0);
	}
}


void strError(int countStr, int M)
{
	if (countStr < M + 3) {
		printf("bad number of lines");
		exit(0);
	}
}


void swap(int* a, int* b)
{
	int c = *a;
	*a = *b;
	*b = c;
}

int cmp(unsigned long long len, unsigned long long vP, unsigned long long tP)
{
	if (len == INF) return 0;
	if (tP == INF) return 1;
	return len + vP <= tP;
}


void countInf(int to, int F, unsigned int* sPath, int* countOfInf)
{
	if (to == F && sPath[to] > INT_MAX) {
		(*countOfInf)++;
	}
	else if (to == F && sPath[to] <= INT_MAX) {
		(*countOfInf) = 0;
	}
}

int main()
{
	int N, M, S, F;
	FILE* f = fopen("in.txt", "r");
	fscanf(f, "%d%d%d%d", &N, &S, &F, &M);
	inputError(N, M);

	if (N == 0 && M == 0 && F == 0 && S == 0) {
		printf("bad vertex");
		exit(0);
	}
	F--;
	S--;

	unsigned int** adjMatrix = (unsigned int**)calloc(N, sizeof(unsigned int*));
	int countStr = 3;
	for (int i = 0; i < M; i++) {
		int from, to, weight;
		if (!(fscanf(f, "%d%d%d", &from, &to, &weight) / 3)) {
			printf("bad number of lines");
			exit(0);
		}
		countStr++;
		dataError(from--, to--, weight, N);
		if (from < to) swap(&from, &to);
		if (!adjMatrix[from]) {
			adjMatrix[from] = (unsigned int*)calloc((from + 1), sizeof(unsigned int));
			for (int j = 0; j < from + 1; j++) {
				adjMatrix[from][j] = INF;
			}
		}
		adjMatrix[from][to] = weight;
	}
	strError(countStr, M);

	char* used = (char*)calloc(N, sizeof(char));
	unsigned int* sPath = (unsigned int*)calloc(N, sizeof(unsigned int));
	for (int i = 0; i < N; i++) {
		sPath[i] = INF;
	}
	int* parents = (int*)malloc(N * sizeof(int));
	memset(parents, unused, N * sizeof(int));
	parents[S] = S;

	sPath[S] = 0;
	int countOfinf = 0;
	for (int i = 0; i < N; i++) {
		int vMinE = -1, minE = INF;
		for (int j = 0; j < N; j++) {
			if (!used[j] && (sPath[j] < minE)){
				vMinE = j;
				minE = sPath[j];
			}
		}
		if (minE == INF) {	
			break;
		}
		used[vMinE] = 1;
		for (int to = 0; to < N; to++) {
			if (to < vMinE) {
				if (adjMatrix[vMinE] && cmp(adjMatrix[vMinE][to], sPath[vMinE], sPath[to])) {
					sPath[to] = adjMatrix[vMinE][to] + sPath[vMinE];
					parents[to] = vMinE;
					countInf(to, F, sPath, &countOfinf);
				}
				
			}
			else if (to > vMinE) {
				if (adjMatrix[to] && cmp(adjMatrix[to][vMinE], sPath[vMinE], sPath[to])) {
					sPath[to] = adjMatrix[to][vMinE] + sPath[vMinE];
					parents[to] = vMinE;
					countInf(to, F, sPath, &countOfinf);
				}
			}
		}
	}
	for (int i = 0; i < N; i++) {
		if (sPath[i] == INF) printf("oo ");
		else if (sPath[i] > INT_MAX) printf("INT_MAX+ ");
		else printf("%d ", sPath[i]);
	}
	printf("\n");
	if (parents[F] == -1) { 
		printf("no path"); 
		exit(0);
	}
	else if (countOfinf >= 2) {
		printf("overflow");
		exit(0);
	}
	int curV = F;
	do {
		printf("%d ", curV + 1);
		curV = parents[curV];
	} while (curV != S);
	printf("%d", S+1);
	return 0;
}
