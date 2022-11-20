#include<stdio.h>
#include<windows.h>

#define MAX 100

#define inputfile "C:\Users\Administrator\Downloads"

struct Stack {
	int n;
	int a[MAX];
};
void Init(Stack &s) {
	s.n = 0;
}
void Push(Stack &s, int x) {
	if(s.n + 1 >= MAX) return;
	else {
		s.a[s.n] = x;
		s.n++;
	}
}

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

void findPath(Graph &g, Stack &s, int i) {
	for(int j = 0; j < g.n; j++) {
		if(g.a[i][j] != 0) {
			g.a[i][j] = g.a[j][i] = 0;
			findPath(g, s, j);
		}
	}
	Push(s, i);
}
void checkEulerLoop(Graph g) {
	int i = 0, count = 0, x = 0;
	
	do {
		for(int j = 0; j < g.n; j++) {
			if(g.a[i][j] != 0)
				count++;
		}
		if(count % 2 != 0) {
			printf("\nKhong ton tai chu trinh!\n");
			return;
		}
		else i++;
	} while(i < g.n);
	
	i = 0; count = 0;
	do {
		for(int j = 0; j < g.n; j++) {
			if(g.a[i][j] != 0)
				count++;
		}
		if(count > 0) x = i;
		else i++;
	} while(count == 0);
	
	Graph temp = g;
	
	Stack s;
	Init(s);
	
	findPath(temp, s, x);
	
	for(int i = 0; i < temp.n; i++) {
		for(int j = 0; j < temp.n; j++) {
			if(temp.a[i][j] != 0) {
				printf("\nTon tai canh! Khong tim thay chu trinh!\n");
				return;
			}
		}
	}
	
	if(s.a[0] != s.a[s.n]) {
		printf("\nDinh dau khac dinh cuoi! Khong tim thay chu trinh!\n");
		return;
	}
	
	printf("\nChu trinh Euler: ");
	for(int i = s.n - 1; i >= 0; i--) {
		printf("%d ", s.a[i] + 1);
	}
}
void checkEulerPath(Graph g) {
	int i = 0, count = 0, countOdd = 0, x = NULL;
	
	do {
		for(int j = 0; j < g.n; j++) {
			if(g.a[i][j] != 0)
				count++;
		}
		if(count % 2 != 0) {
			countOdd++;
		}
		else {
			count = 0;
			i++;
		}
	} while(i < g.n);
	
	if(countOdd != 2) {
		printf("\nKhong ton tai duong di!\n");
		return;
	} 
	
	i = 0, count = 0;
	do {
		for(int j = 0; j < g.n; j++) {
			if(g.a[i][j] != 0)
				count++;
		}
		if(count % 2 != 0) {
			x = i;
		}
		else {
			count = 0;
			i++;
		}
	} while(x == 0);
	
	Graph temp = g;
	
	Stack s;
	Init(s);
	
	findPath(temp, s, x);
	
	for(int i = 0; i < temp.n; i++) {
		for(int j = 0; j < temp.n; j++) {
			if(temp.a[i][j] != 0) {
				printf("\nTon tai canh trong Stack! Khong tim thay duong di!\n");
				return;
			}
		}
	}
	
	if(s.a[1] == s.a[s.n]) {
		printf("\nDinh dau bang dinh cuoi! Khong tim thay duong di!\n");
		return;
	}
	
	printf("\nDuong di Euler: ");
	for(int i = s.n - 1; i >= 0; i--) {
		printf("%d ", s.a[i] + 1);
	}
}

int main() {
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	
	char fileName[] = "test_4.txt";
	
	Graph g;
	
	readMatr(g, fileName);
	printMatr(g);
	
	checkEulerLoop(g);
	checkEulerPath(g);
}
