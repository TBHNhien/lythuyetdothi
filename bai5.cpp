#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#define MAX 10
#define vocuc 9999
int d[MAX],dinhTruoc[MAX],daDuyet[MAX]={0};

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

void XuatMaTranKe(DOTHI g)
{
	printf("So dinh cua do thi la %d\n",g.n);
	printf("Ma Tran ke cua do thi la\n");
	for(int i=0; i<g.n;i++)
	{
		printf("\t");
		for(int j=0;j<g.n;j++)
		{
			printf("%d\t",g.a[i][j]);
		}
		printf("\n");
	}
}

int dinhChuaDuyetVaCoduMin(DOTHI g){
	int u = -1;
	int min=vocuc;
	
	for(int i=0;i<g.n;i++)
		if (daDuyet[i]==0 && d[i]<min){
			u=i;
			min = d[i];
		}
		return u;
}

void inDuongDi (int S,int F)
{
	printf ("\n(%d,%d)= %d: DUONG DI:%d",S,F,d[F],F);
	int k=F;
	while (k!=S){
		printf (" <- %d",dinhTruoc[k]);
		k=dinhTruoc[k];
	}
}

void Dijkstra(DOTHI g, int S){// TIM duong di ngan nhat tu S toi cac dinh con lai
		
	for (int i=0;i<g.n;i++){
		dinhTruoc [i]=-1;
		d[i]=vocuc;
	}
	d[S]=0;
	
	int soDinhDaDuyet = g.n;
	int u;
	while (soDinhDaDuyet>0){
		u=dinhChuaDuyetVaCoduMin(g);
		if (u==-1) break;
		daDuyet[u]=1;
		for (int v=0;v<g.n;v++)
			if(daDuyet[v]==0 && g.a[u][v]!=0 && d[v]>d[u]+g.a[u][v]){
				d[v]=d[u]+g.a[u][v];
				dinhTruoc[v]=u;
			}
		soDinhDaDuyet--;	
	}
	
	//xong thuat toan 
	//in duong di neu co ngan nhat neu co tu S 
	printf ("\n duong di tu dinh %d den cac dinh con lai : ",S);
	for (int i=0;i<g.n;i++){
		if(d[i]>0 && d[i]<vocuc)
		inDuongDi (S,i);
//		else
//		printf ("\n Khong co duong di tu %d den %d ",S,i);
	}
	
	
}




int main ()
{
	DOTHI g;
		
	if (DocMaTranKe((char*)"text1.1.1.txt",g) == 1)
	{
		printf("Da lay thong tin do thi tu file thanh cong.\n\n");
		XuatMaTranKe(g);
	}
	
	int S=0;
	Dijkstra(g,S);


return 0;
}
