#include<stdio.h>
#include<conio.h>
#define MAX 100
#define inputFile "D:/tranhuuthien/test.txt"
typedef struct GRAPH
{
	int n;
	int a[MAX][MAX];
}DOTHI;
struct STACK
{
	int array[100];
	int size;
};
struct QUEUE
{
	int size;
	int array[MAX];
};
int LuuVet[MAX];
int ChuaXet[MAX];
int DocMaTranKe(char TenFile[100], DOTHI &g);
void XuatMaTranKe(DOTHI g);
void DFS(int v, GRAPH g);
void duyettheoDFS (int S, int F, GRAPH g);
void DFS2(int v, GRAPH g);
void duyettheoDFS2 (int S, GRAPH g);
void duyettheoBFS2 (int S, GRAPH g);
void BFS2(int v,GRAPH g);
void KhoiTaoQueue(QUEUE &Q);
int DayGiaTriVaoQueue(QUEUE &Q, int value);
int LayGiaTriRaKhoiQueue(QUEUE &Q, int &value);
int KiemTraQueueRong(QUEUE Q);
void BFS (int v, GRAPH g);
void duyettheoBFS (int S, int F, GRAPH g);
int main ()
{
	DOTHI g;
	if(DocMaTranKe(inputFile, g)==1)
	{
		printf("Da lay thong tin do thi tu file thanh cong.\n\n");
		XuatMaTranKe(g);
		int n,x,s,f;
		printf("Nhap dinh can duyet: ");
		scanf("%d",&x);
		printf("Nhap dinh bat dau: ");
		scanf("%d",&s);
		printf("Nhap dinh ket thuc: ");
		scanf("%d",&f);
		printf("Nhap 1 de duyet theo DFS, 2 de duyet theo BFS: ");
		scanf("%d",&n);
		if(n==1)
		{
			printf("\nDuyet tu dinh %d: ",x);
			duyettheoDFS2(x,g);
			duyettheoDFS(s,f,g);
		}
		else
		{
			printf("\nDuyet tu dinh %d: ",x);
			duyettheoBFS2(x,g);
			duyettheoBFS(s,f,g);
		}
	}
	getch();
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
void DFS(int v, GRAPH g)
{
	ChuaXet[v]=1;
	int u;
	for(u=0; u<g.n; u++)
	{
		if(g.a[v][u]!=0 && ChuaXet[u]==0)
		{
			LuuVet[u]=v;
			DFS(u,g);
		}
	}
}
void duyettheoDFS (int S, int F, GRAPH g)
{
	int i;
	for(int j=0; j<g.n; j++)
	{
		LuuVet[i]=-1;
		ChuaXet[i]=0;
	}
	DFS(S,g);
	if(ChuaXet[F]==1)
	{
		printf("\nDuong di tu dinh %d den dinh %d la: \n\t",S,F);
		i=F;
		printf("%d",F);
		while(LuuVet[F]!=S)
		{
			printf("<--%d",LuuVet[F]);
			LuuVet[F]=LuuVet[LuuVet[F]];
		}
		printf("<--%d",S);
		
	}
	else
	{
		printf("Khong co duong di tu dinh %d den dinh %d \n",S,F);
	}
}
void DFS2(int v, GRAPH g)
{
	ChuaXet[v]=1;
	int u;
	for(u=0; u<g.n; u++)
	{
		if(g.a[v][u]!=0 && ChuaXet[u]==0)
		{
			LuuVet[u]=v;
			printf("%d ",u);
			DFS2(u,g);
		}
	}
}
void duyettheoDFS2 (int S, GRAPH g)
{
	int i;
	for(int j=0; j<g.n; j++)
	{
		LuuVet[i]=-1;
		ChuaXet[i]=0;
	}
	printf("%d ",S);
	DFS2(S,g);
}
void BFS (int v, GRAPH g)
{
	QUEUE Q;
	KhoiTaoQueue(Q);
	DayGiaTriVaoQueue(Q,v);
	while(!KiemTraQueueRong(Q))
	{
		LayGiaTriRaKhoiQueue(Q,v);
		ChuaXet[v]=1;

		for(int u=0; u<g.n; u++)
		{
			if(g.a[v][u]!=0 && ChuaXet[u]==0)
			{
				DayGiaTriVaoQueue(Q,u);
				if(LuuVet[u]==-1)
				{
					LuuVet[u]=v;
				}
			}
		}
	}
}
void BFS2 (int v, GRAPH g)
{
	QUEUE Q;
	KhoiTaoQueue(Q);
	DayGiaTriVaoQueue(Q,v);
	printf("%d ",v);
	while(!KiemTraQueueRong(Q))
	{
		LayGiaTriRaKhoiQueue(Q,v);
		ChuaXet[v]=1;

		for(int u=0; u<g.n; u++)
		{
			if(g.a[v][u]!=0 && ChuaXet[u]==0)
			{
				DayGiaTriVaoQueue(Q,u);
				if(LuuVet[u]==-1)
				{
					LuuVet[u]=v;
					printf("%d ",u);
				}
			}
		}
	}
}
void duyettheoBFS (int S, int F, GRAPH g)
{
	int i;
	for(int j=0; j<g.n; j++)
	{
		LuuVet[j]=-1;
		ChuaXet[j]=0;
	}
	BFS(S,g);
	if(ChuaXet[F]==1)
	{
		printf("\nDuong di tu dinh %d den dinh %d la: \n\t",S,F);
		i=F;
		printf("%d",F);
		while(LuuVet[F]!=S)
		{
			printf("<--%d",LuuVet[F]);
			LuuVet[F]=LuuVet[LuuVet[F]];
		}
		printf("<--%d",S);
		
	}
	else
	{
		printf("Khong co duong di tu dinh %d den dinh %d \n",S,F);
	}
}
void duyettheoBFS2 (int S, GRAPH g)
{
	int i;
	for(int j=0; j<g.n; j++)
	{
		LuuVet[j]=-1;
		ChuaXet[j]=0;
	}
	BFS2(S,g);

}
void KhoiTaoQueue(QUEUE &Q)
{
	Q.size=0;
}
int DayGiaTriVaoQueue(QUEUE &Q, int value)
{
	if(Q.size +1 >=100)
		return 0;
	Q.array[Q.size]= value;
	Q.size++;
	return 1;
}
int LayGiaTriRaKhoiQueue(QUEUE &Q, int &value)
{
	if(Q.size <=0)
		return 0;
	value =Q.array[0];
	for(int i=0; i<Q.size-1; i++)
		Q.array[i]=Q.array[i+1];
	Q.size--;
	return 1;
}
int KiemTraQueueRong(QUEUE Q)
{
	if(Q.size<=0)
		return 1;
	return 0;
}
