#include<stdio.h>
#include<windows.h>

#define MAX 10

#define inputfile "C:/test.txt"

struct Graph {
	int n;
	int a[MAX][MAX];
};

int readMatr(Graph &g, char fileName[MAX]) {
	FILE* f = fopen(fileName, "r");
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
bool checkMatr(Graph g) {
	for(int i = 0; i < g.n; i++) {
		if(g.a[i][i] != 0) return 0;
	}
	return 1;
}
bool isOMatr(Graph g) {
	for(int i = 0; i < g.n; i++) {
		for(int j = 0; j < g.n; j++) {
			if(g.a[i][j] != g.a[j][i]) return 1;
		}
	}
	return 0;
}
void timDinhLT(Graph g, int tag[MAX], int i) {
	for(int j = 0; j < g.n; j++) {
		if(g.a[i][j] != 0 && tag[i] != tag[j]) {
			tag[j] = tag[i];
			timDinhLT(g, tag, j);
		}
	}
}
void xetLT(Graph g) {
	int tag[MAX];
	for(int i = 0; i < g.n; i++) {
		tag[i] = 0;
	}
	int soThanhPhanLT = 0;
	for(int i = 0; i < g.n; i++) {
		if(tag[i] == 0) {
			soThanhPhanLT++;
			tag[i] = soThanhPhanLT;
			timDinhLT(g, tag, i);
		}
	}
	printf("\nSo thanh phan lien thong: %d.\n", soThanhPhanLT);
	for(int i = 1; i <= soThanhPhanLT; i++) {
		printf("\nThanh phan lien thong thu %d gom: ", i);
		for(int j = 0; j < g.n; j++) {
			if(tag[j] == i) printf("%d ", j);
		}
	}
}
int main() {
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	
	char fileName[] = "test_1.txt";
	
	Graph g;
	
	readMatr(g, fileName);
	printMatr(g);
	
	if(checkMatr(g) == 0) printf("\nDo thi khong hop le!\n");
	else printf("\nDo thi ke hop le!\n");
	
	if(isOMatr(g)) printf("\nDo thi co huong.\n");
	else printf("\nDo thi vo huong.\n");

	xetLT(g);
}
