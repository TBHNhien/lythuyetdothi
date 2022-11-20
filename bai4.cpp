#include <stdio.h>
#include <conio.h>
#include<math.h>
#include <string.h>
#define MAX 10
int daDuyet[MAX];

typedef struct GRAPH
{
	int n;
	int a[MAX][MAX];
}DOTHI;

struct CANH
{
	int v1,v2,ts;//đỉnh đầu v1, cuối v2 ,trọng số ts
};

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

void duyetDFS(int dinhXP,DOTHI g)
{
	daDuyet[dinhXP]=1;
	for (int i=0;i<g.n;i++)
		if (daDuyet[i]==0 && g.a[dinhXP][i]!=0)
		{
			duyetDFS(i,g);
		}
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

int soTPLT (DOTHI g)
{
	int dem=0;
	for (int i=0;i<g.n;i++)
	{
		daDuyet[i]=0;
	}
	
	for (int i=0;i<g.n;i++)
		if (daDuyet[i]==0)
		{
			dem++;
			duyetDFS (i,g);
		}	
	return dem;		
}


void Prim (DOTHI g)
{
	if(soTPLT(g)>1)
		{
		printf ("\n Do Thi khong lien thong \n");
		return;	
		}	
		
	int VT[MAX]={0};//VT[MAX]={0,0,0 ....}	
	CANH ET[MAX];
	int nET=0;//số phần tử lúc đầu của mảng ET là 0 (chưa có cạnh nào)
	VT[0]=1; //chọn đỉnh 0 bỏ vào VT
	while (nET<(g.n-1)){
		int min = 100;//viết hàm tìm max trọng số
		CANH tam ;//để xét hết các cạnh liên kết VT
		for (int v=0;v<g.n;v++)
			if (VT[v]==1)//đỉnh v nằm trong VT 
				for (int s=0;s<g.n;s++)
					if(VT[s]==0 && g.a[v][s]!=0 && g.a[v][s] <min){
						tam.v1=v;
						tam.v2=s;
						tam.ts=g.a[v][s];
						min=g.a[v][s];
					}
			//bỏ tam vào ET
			ET[nET]=tam;//tam.v2
			nET++;
			
			VT[tam.v2]=1;
	}
	// xuất ra màn hình cây khung  và tổng trọng số cây khung
	int tongts=0;
	for (int i=0;i<nET;i++){
		tongts+= ET[i].ts;
		printf("\n (%d,%d) = %d",ET[i].v1,ET[i].v2,ET[i].ts);
	}
	
	printf ("\n Tong TS cay khung min : %d ",tongts);
}



int main()
{
	DOTHI g;
	if (DocMaTranKe((char*)"text3.1.txt",g) == 1)
	{
		printf("Da lay thong tin do thi tu file thanh cong.\n\n");
		XuatMaTranKe(g);
	}

	printf ("%d",soTPLT(g));
	Prim(g);
return 0;
}
