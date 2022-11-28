#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#define MAX 10
#define vocuc 9999

int D[MAX][MAX]; //chứa độ dài ngắn nhất từ i đến j bất kỳ
int dinhSau[MAX][MAX];

typedef struct GRAPH
{
	int n;
	int a[MAX][MAX];
}DOTHI;

int DocMaTranKe(char TenFile[100], DOTHI &g)
{
	FILE* f;
	f=fopen(TenFile, "rt");
	if(f==NULL)
	{
		printf("Khong mo duoc file\n");
		return 0;
	}
	fscanf(f,"%d",&g.n);
	int i,j;
	for(i=0; i<g.n; i++)
	{
		for(j=0; j<g.n;j++)
		{
			fscanf(f,"%d",&g.a[i][j]);
		}
	}
	fclose(f);
	return 1;
}

void XuatMT(int a[][MAX],int n)
{

	for(int i=0; i<n;i++)
	{
		printf("\t");
		for(int j=0;j<n;j++)
		{
			printf("%3d\t",a[i][j]);
		}
		printf("\n");
	}
}

void inDuongDiF(int S,int F){
	printf ("\n(%d,%d)=%d - Duong di :%d",S,F,D[S][F],S);
	int k=S;
	while (k!=F){
		printf(" ->%d",dinhSau[k][F]);
		k=dinhSau[k][F];
	}
}

void Floy (DOTHI g)
{

	for (int i=0;i<g.n;i++)
		for (int j=0;j<g.n;j++){
			if(g.a[i][j]>0){
				D[i][j]= g.a[i][j];
				dinhSau[i][j]=j;
			}
			else{
				D[i][j]=vocuc;
				dinhSau[i][j]=-1;
			}
			D[i][i]=0;
		}
	printf ("\n MA TRAN D :\n");
	XuatMT(D,g.n);
	printf ("\n MA TRAN DINH SAU :\n");			
	XuatMT(dinhSau,g.n);

printf ("------------------------SAU KHI CHAY --------------------");
	for (int k=0;k<g.n;k++)
		for (int i=0;i<g.n;i++)	
			for (int j=0;j<g.n;j++)
				if (D[i][j]>D[i][k]+D[k][j]){//nếu đi trực tiếp lớn hơn
				D[i][j]=D[i][k]+D[k][j];
				 dinhSau[i][j]=dinhSau[i][k];
				}
				
	printf ("\n MA TRAN D :\n");
	XuatMT(D,g.n);
	printf ("\n MA TRAN DINH SAU :\n");			
	XuatMT(dinhSau,g.n);
	
	//in ra đường đi ngắn nhất của các cặp đỉnh
	
	for (int i=0;i<g.n;i++)
		for (int j=0;j<g.n;j++)
			if(D[i][j]>0&& D[i][j]<vocuc)	
			inDuongDiF (i,j)	;
}

int main ()
{
DOTHI g;
DocMaTranKe((char*)"text1.1.txt",g);
Floy(g);

return 0;
}
