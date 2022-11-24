#include <stdio.h>
#include <conio.h>
#include<math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MAX 10

int daDuyet[MAX];

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

void duyetDFS(int dinhXP,DOTHI g)
{
	daDuyet[dinhXP]=1;
	for (int i=0;i<g.n;i++)
		if (daDuyet[i]==0 && g.a[dinhXP][i]!=0)
		{
			duyetDFS(i,g);
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

int ChuaXet[MAX];// goa tri chua xet =0, xet roi =1

typedef struct EDGE // khai báo cấu trúc cạnh của đồ thị
{
	int u;
	int v;
	int value;
} CANH;

CANH T[MAX]; //MẢNG LƯU CÁC CẠNH trong thuật toán Prim

void Prim(DOTHI g)
{
	if (soTPLT(g)!=1)
	{
		printf ("DO THI ko lien thong \n");
		return ;
	}
	
	int nT=0; //dùng để lưu số cạnh
	
	for (int i=0;i<g.n;i++){
		ChuaXet[i]=0; // chưa vào thuật toán nên gán tất cả = 0;
	}
	
	ChuaXet[0]=1;//bắt đầu thuật toán Prim ,xuất phát từ đỉnh 0;
	
	while (nT< g.n-1)
	{
		CANH Canhmin;//dùng để lưu cạnh nhỏ nhất  nối từ tập những đỉnh đã xét đến 1 đỉnh chưa xét nào đo
		
		int TSmin =100;
		
		for (int i=0;i<g.n;i++)
		{
			if (ChuaXet[i]==1)// xem đỉnh đã xét chưa
			{
				for (int j=0;j<g.n;j++)
				{
					if (ChuaXet[j]==0 && g.a[i][j]!=0 && TSmin>g.a[i][j])//tìm đỉnh chưa xét j , có cạnh nối từ i đến j và giá trị của cạnh đó nhỏ hơn min
					{
					Canhmin.u=i;//cập nhật đỉnh đầu 
					Canhmin.v=j;//cập nhật lại giá trị đỉnh cuối
					Canhmin.value=g.a[i][j];
					TSmin = g.a[i][j];//cập nhật lại TSmin
					}
				}
			}
		}
		T[nT++]=Canhmin;
		ChuaXet[Canhmin.v]=1;
	}
	
	int TTS=0;
	printf ("CAY KHUNG NHO NHAT LA : \n");
	for (int i=0;i<nT;i++){
		printf ("(%d,%d)",T[i].u,T[i].v);
		TTS+= T[i].value;
	}
	
	printf ("TSS LA : %d \n",TTS);
	
}


// -----------KRUSTAL

void SapXepTang (CANH E[100],int tongsocanh)
{
CANH canhtam;
	for (int i=0;i<tongsocanh;i++)
	{
		for (int j=i+1;j<tongsocanh;j++){
			if (E[i].value > E[j].value){
				canhtam = E[i];
				E[i]=E[j];
				E[j]=canhtam;
			}
		}
	}
}

void Kruskal(DOTHI g)
{
	CANH ListEdge [MAX];//danh sach cac canh
	int tongsocanh=0;//chua tong so canh trong do thi
	
	int i,j;
	for (i=0;i<g.n;i++)
	{
		for (j=i+1;j<g.n;j++)
		if (g.a[i][j]>0)
		{
			ListEdge[tongsocanh].u=i;
			ListEdge[tongsocanh].v=j;
			ListEdge[tongsocanh].value=g.a[i][j];
			tongsocanh++;
		}
	}
	//tien hanh sap xep canh tron ListEdge tang dan ts
	SapXepTang(ListEdge,tongsocanh);
	int nT=0;//So luong canh trong cay khung
	CANH T[MAX];//chua cac canh cay khung
	int nhan[MAX];//chua nhan cac dinh 
	for (int k=0;k<g.n;k++)
		nhan[k]=k;
		int canhdangxet=0;
		while (nT < g.n && canhdangxet < tongsocanh){
			// tien hanh them 1 canh vao cay ma khong tao chu trinh , bang cach chon canh ma dinh tai nhan khac nhau
			if (nhan[ListEdge[canhdangxet].u]!=nhan[ListEdge[canhdangxet].v])
			{
				T[nT++]=ListEdge[canhdangxet];
			}
			//TIEN HANH SUA NHAN CUA TAT CA CAC DINH  co cung gia tri voi nhan cua dinh v thanh nhan dinh u
			int giatri = nhan[ListEdge[canhdangxet].v];
			for (j=0;j<g.n;j++)
			{
				if (nhan[j]==giatri)
					nhan[j]=nhan[ListEdge[canhdangxet].u];
			}
			canhdangxet++;
		}

		
		if (nT != g.n-1)
		{
			printf ("DO THI khong lien thong \n");
			return;
		}
		else //co cay khung , xuat
		{
			int TSS=0;
			for (int k=0;k<nT;k++){
				printf ("(%d,%d) \n",T[k].u,T[k].v);
				TSS+= T[k].value;
			}
			printf ("tong TS : %d \n ",TSS);				
		}				
}

int main()
{
	DOTHI g;
	
	clock_t start , end;
	double cpu_time_used;
	start = clock();
	
	if (DocMaTranKe((char*)"text2.txt",g) == 1)
	{
		printf("Da lay thong tin do thi tu file thanh cong.\n\n");
		XuatMaTranKe(g);
	}

//	printf ("%d",soTPLT(g));
//	Prim(g);
	Kruskal(g);
	
	end=clock();
	
	cpu_time_used = (double)(end-start)/ CLOCKS_PER_SEC;
	
	cpu_time_used*=1000;
	
	printf ("thoi gian chay : %f",cpu_time_used);
return 0;
}
