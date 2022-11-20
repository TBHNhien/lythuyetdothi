#include<stdio.h>
#include<string.h>
#include<windows.h>

#define MAX 100

struct Queue {
	int a[MAX];
	int n;
};
void Init(Queue &q) {
	q.n = 0;
}
void Push(Queue &q, int x) {
	if(q.n + 1 >= MAX) return;
	
	q.a[q.n] = x;
	q.n++;
	return;
}
void Pop(Queue &q, int &x) {
	if(q.n <= 0) return;
	
	x = q.a[0];
	for(int i = 0; i < q.n - 1; i++)
		q.a[i] = q.a[i + 1];
	q.n--;
	return;
}
bool isEmpty(Queue q) {
	if(q.n <= 0)
		return true;
	return false;
}

struct Graph {
	int n;
	int a[MAX][MAX];
};
int readMatr(char *argv[], int num, Graph &g) {
	char path[] = "C:\\Users\\Administrator\\Downloads\\";
	strcat(path, argv[num]);
	
	FILE* f = fopen(path, "r");
	if(f == NULL) {
		printf("Khong mo duoc file!\n");
		return 0;
	}
	fscanf(f, "%d", &g.n);
	for(int i = 0; i < g.n; i++) {
		for(int j = 0; j < g.n; j++) {
			fscanf(f, "%d", &g.a[i][j]);
		}
	}
	fclose(f);
	return 1;
}
void printMatr(Graph g) {
	printf("So dinh cua do thi: %d.\n", g.n);
	printf("\nMa tran ke cua do thi:\n");
	for(int i = 0; i < g.n; i++) {
		printf("\t");
		for(int j = 0; j < g.n; j++) {
			printf("%d ",g.a[i][j]);
		}
		printf("\n");
	}
}

void dfs(Graph g, int ChuaXet[], int LuuVet[], int i) {
	ChuaXet[i] = 1;
	for(int j = 0; j < g.n; j++) {
		if(g.a[i][j] == 1 && ChuaXet[j] == 0) {
			LuuVet[j] = i;
			dfs(g, ChuaXet, LuuVet, j);
		}
	}
}
void DFS(Graph g, int a, int b) {
	int ChuaXet[g.n],
		LuuVet[g.n];
	for(int i = 0; i < g.n; i++) {
		ChuaXet[i] = 0;
		LuuVet[i] = -1;
	}
	
	dfs(g, ChuaXet, LuuVet, a);
	printf("Mang LuuVet:\t");
	for(int i = 0; i < g.n; i++) {
		printf("%d ", LuuVet[i]);
	}
	printf("\nMang ChuaXet:\t");
	for(int i = 0; i < g.n; i++) {
		printf("%d ", ChuaXet[i]);
	}
	printf("\n");
	
	if(ChuaXet[b] == 1) {
		printf("\nDuong di tu dinh %d den dinh %d:\t", a, b);
		int i = b;
		printf("%d", b);
		do {
			printf(" <- %d", LuuVet[i]);
			i = LuuVet[i];
		} while(i != a);
	}
	else printf("\nKhong ton tai duong di tu dinh %d den dinh %d!", a, b);
}

void bfs(Graph g, int ChuaXet[], int LuuVet[], int i) {
	Queue q;
		Init(q);
		Push(q, i);
	
	while(!isEmpty(q)) {
		Pop(q, i);
		ChuaXet[i] = 1;
		for(int j = 0; j< g.n; j++) {
			if(g.a[i][j] == 1 && ChuaXet[j] == 0) {
				Push(q, j);
				if(LuuVet[j] == -1) LuuVet[j] = i;
			}
		}
	}
}
void BFS(Graph g, int a, int b) {
	int ChuaXet[g.n],
		LuuVet[g.n];
	for(int i = 0; i < g.n; i++) {
		ChuaXet[i] = 0;
		LuuVet[i] = -1;
	}
	
	bfs(g, ChuaXet, LuuVet, a);
	printf("Mang LuuVet:\t");
	for(int i = 0; i < g.n; i++) {
		printf("%d ", LuuVet[i]);
	}
	printf("\nMang ChuaXet:\t");
	for(int i = 0; i < g.n; i++) {
		printf("%d ", ChuaXet[i]);
	}
	printf("\n");
	
	if(ChuaXet[b] == 1) {
		printf("\nDuong di tu dinh %d den dinh %d:\t", a, b);
		int i = b;
		printf("%d", b);
		do {
			printf(" <- %d", LuuVet[i]);
			i = LuuVet[i];
		} while(i != a);
	}
	else printf("\nKhong ton tai duong di tu dinh %d den dinh %d!", a, b);
}

void menu(int &key) {
	printf("DANH SACH CHUC NANG:\n");
	printf("\t0. Thoat chuong trinh.\n");
	printf("\t1. Chon file.\n");
	printf("\t2. Duyet duong di theo chieu sau.\n");
	printf("\t3. Duyen duong di theo chieu rong.\n");
	printf("Chon mot chuc nang (0 -> 3): ");
	scanf("%d", &key);
}

int main(int argc, char *argv[]) {
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	
	Graph g;
	int num, a, b;
	
	int key;
	do {
		menu(key);
		system("cls");
		switch(key) {
			case 0: {
				printf("Da thoat khoi chuong trinh!");
				return 0;
			}
			case 1: {
				printf("\nDANH SACH FILE DUA VAO:\n");
				for(int i = 1; i < argc; i++)
					printf("\t%d : %s\n", i, argv[i]);
				
				printf("Chon mot file (1 -> %d): ", argc - 1);
					scanf("%d", &num);
					
				system("cls");
					
				readMatr(argv, num, g);
				printMatr(g);
				
				break;
			}
			case 2: {
				printf("Dinh bat dau: "); scanf("%d", &a);
				printf("Dinh ket thuc: "); scanf("%d", &b);
				DFS(g, a, b);
				break;
			}
			case 3: {
				printf("Dinh bat dau: "); scanf("%d", &a);
				printf("Dinh ket thuc: "); scanf("%d", &b);
				BFS(g, a, b);
				break;
			}
		}
	} while(key != 0);
}
