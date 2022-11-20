#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#define MAX 10

typedef struct GRAPH {
	int n ; //so dinh do thi
	int a[MAX][MAX];//MA tran ke cua do thi
}DOTHI;

struct STACK {
	int array [100];// luu lai thu tu cac dinh chu trinh euler
	int size; // so luong cac dinh trong chu trinh
};

int DocMaTranKe(const char* TenFile, DOTHI &g) 
{ 
FILE* f;
printf("%s",TenFile);
f = fopen(TenFile,"rt");
	if(f==NULL)
	{ 
	printf("Khong mo duoc file\n"); 
	}
	fscanf(f, "%d", &g.n);
	int i, j; 
	for (int i=0; i<g.n; i++) {
		for (int j=0; j<g.n; j++) {
			fscanf (f,"%d",&g.a[i][j]);
		}
	}
fclose(f);
return 1;
}

void XuatMaTranKe (DOTHI g)
{
	printf("So dinh cua do thi la %d\n", g.n);
	printf("Ma tran ke cua do thi la\n");
	for (int i = 0; i < g.n; i++)
	{
		printf ("\t");
		for (int j = 0; j < g.n; j++)
		{
		printf("%d ",g.a[i][j]);
		}
		printf("\n");
	}
}

int KiemTraDoThiVoHuong (DOTHI g){
	int i,j;
	for (i=0;i<g.n;i++){
		for (j=0;j<g.n;j++){
			if (g.a[i][j]!=g.a[j][i])
				return 0;
		}
	}
	return 1;
}


void TimDinhLT(int dinhk,DOTHI g,int nhan[]){//tìm đỉnh liên thông của dinhk , trong DOTHI g, nếu LT dinhk thì lưu vào nhãn đỉnh đó=nhãn dinhk
	for (int i=0;i<g.n;i++)//duyệt tất cả các đỉnh DOTHI
		if (g.a[i][dinhk]!=0 && nhan[i]==0)//đỉnh i đó mà có đường nối đến dinhk && đỉnh i đó chưa thuộc TPLT nào
		{
			nhan[i]=nhan[dinhk];//đỉnh i có đường đi tới dinhk(dinhi vs dinhk cùng TPLT)
			//có đỉnh i là LT với đỉnh k thì gọi dequy
			TimDinhLT(i,g,nhan);
		}
}

int SoThanhPhanLT (DOTHI g){
	int nhan[MAX]={0};//để tất cả các thành phần từ 0 ->99 đều bằng 0
	int soTPLT=0 ;
	for (int i=0;i<g.n;i++){
		//xét đỉnh i từ 0 ->n-1 , nếu nhãn i==0 -> chưa xét đỉnh đó chưa thuộc thành phần LT NÀO
		if (nhan[i]==0){
			soTPLT++; // tăng sốTPLT 
			nhan[i]=soTPLT;
			//tìm đỉnh liên thông với đỉnh i(đỉnh từ i đến nó có đường)
			TimDinhLT (i,g,nhan);//hàm tìm đỉnh liên thông của i trong DOTHI g->gán nhãn đỉnh đó = nhãn đỉnh i	
		}
	}
	return soTPLT;
}

int BacCuaDinh (int dinhk,DOTHI g){
	int bac=0;
	for (int i=0;i<g.n;i++){
		if (g.a[dinhk][i]!=0) bac++;
	}
	return bac;
}

//kt có chu trình or đường đi euler ko
int KiemTraXemCoChuTrinhHoacDuongDiEuler (DOTHI g){
	//nếu có chu trình thì reuturn 1; có đường đi thì return 2; không có cả 2 return 0;
	int soDinhBacLe=0;
	for (int i=0;i<g.n;i++){
		if (BacCuaDinh(i,g)%2==1)
		soDinhBacLe++;
	}
	//đủ 3 điều kiện
	if (KiemTraDoThiVoHuong(g)==1 && SoThanhPhanLT(g)==1 && soDinhBacLe==0 )//nếu đồ thị vô hướng và STPLT chỉ có 1 
		return 1;//có chu trình euler
	if (KiemTraDoThiVoHuong(g)==1 && SoThanhPhanLT(g)==1 && soDinhBacLe==2 )
		return 2;//có đường đi euler
		
	return 0; // không có cả 2		
}


void khoitaoStack (STACK &stack){
	stack.size=0 ; // khoi tao stack khi kich thuoc cua stack =0
}

//de day 1 gia tri vao 
void DayGiaTriVaoStack (STACK &stack , int value){
	if (stack.size +1 >=100)// nếu stack đã đầy thì không đẩy nữa
	return ; // thoát không thực hiện đẩy giá trị vào stack nữa 
	stack.array[stack.size]=value; // đẩy giá trị vào stack
	stack.size++; //tăng kích thước stack lên
}

void TimDuongDi (int i,DOTHI &g,STACK &stack){
	for (int j=0;j<g.n;j++){
		if (g.a[i][j]!=0)// vì đồ thị vô hướng nên đối xứng do đó chỉ cần kt g.a[i][j]!=0 thôi , không cần kt g.a[j][i]!=0
		{
			g.a[i][j]=g.a[j][i]=0;//loại bỏ cạnh nối đỉnh i tới đỉnh j khỏi đồ thị
			TimDuongDi(j,g,stack);// gọi đệ quy tìm đường đi tại đỉnh j
		}
	}
	DayGiaTriVaoStack(stack,i);//đẩy đỉnh i vào stack
}

void TimDuongDi2(int dinhXP,DOTHI &g,int S[],int &nS){//đồ thị sẽ bị thay đổi &g
	for (int i=0;i<g.n;i++){
		if(g.a[i][dinhXP]!=0){
		g.a[i][dinhXP]=g.a[dinhXP][i]=0;//xóa cạnh đã liên thông 
		TimDuongDi2(i,g,S,nS);			
		}
	}
	S[nS++]=dinhXP;
}


void TimChuTrinhHoacDuongDiEuler (DOTHI g){
	
	//tìm đỉnh xuất phát
	int dinhXP=-1;
	for (int i=0;i<g.n;i++){
		if (BacCuaDinh(i,g)%2==1){
			dinhXP=i;
			break; // xuất phát từ đỉnh bậc lẻ đầu tiên
		}
	}
	if (dinhXP==-1){//có chu trình đỉnh nào cũng đc
		printf ("\n Nhap vao dinh muon xuat phat:");
		scanf ("%d",&dinhXP);
	}
	
	//tìm đường đi -> đi được đỉnh nào thì lưu vào mảng 1 chiều (stack)
	int S[MAX*2];
	int nS=0;
	TimDuongDi2 (dinhXP,g,S,nS);
/*	printf ("\n XUAT S : ");
	for (int i=0;i<nS;i++){
		printf ("%3d",S[i]);
	}
*/	
	
	//dựa vào mảng S tìm xem có chu trình hoặc đường đi euler
	if (S[0]==S[nS-1]){
		printf("\n Chu Trinh euler cua do thi la :");
			for (int i=nS-1;i>=0;i--){
				printf ("%3d",S[i]);	
			}
	}
	else{
		printf("\n Duong Di euler cua do thi la :");
			for (int i=nS-1;i>=0;i--){
				printf ("%3d",S[i]);	
			}		
	}
}



//theo sách

int empty (STACK s){
	return (s.size==0);
}


int pop (STACK &s,int &x){
	x=s.array[s.size-1];
	s.size--;
	return x;
}

int KiemTraChuTrinhEuler (DOTHI g){
	int i,j;
	int x=0;// x là giá trị đỉnh xuất phát , điều kiện x là đỉnh có bậc >0
	
	printf ("\n Nhap vao dinh xuat phat : ");
	scanf ("%d",&x);
	if (BacCuaDinh(x,g)>0){
		DOTHI temp = g; 
		STACK stack;
		khoitaoStack(stack);
		TimDuongDi(x,temp,stack);
		//kiem tra ham TimDuongDi có tìm thấy chu trình euler ko
		int gtCuoi ; 
		pop(stack,gtCuoi);
	//	printf ("\n gia tri dau stack :%d , gia tri cuoi stack :%d",stack.array[0],gtCuoi);
		for(int i=0;i<g.n;i++){
			if(BacCuaDinh(i,temp)!=0)
			return 0;
		}
		if (gtCuoi!=stack.array[0])
			return 0;
		
		return 1;	
	}
	else
	return 0;
}

int KiemTraDuongDiEuler (DOTHI g)
{
	int i,j;
	int count =0;
	int x=0;//x là đỉnh bắt đầu xét đường đi , đk x phải là bậc lẻ
	
		for (int i=0;i<g.n;i++)
		if (BacCuaDinh(i,g)%2==1){
			count++;
		}
		
		if (count != 2) return 0;	
	
	//tìm 1 đỉnh x bắt đầu tìm chu trình euler 
		printf ("\n Nhap vao dinh xuat phat : ");
		scanf ("%d",&x);
	
//		for (int i=0;i<g.n;i++){
//		if (BacCuaDinh(i,g)%2==1){
//			x=i;
//			break; // xuất phát từ đỉnh bậc lẻ đầu tiên
//			}
//		}

		if (BacCuaDinh(x,g)%2==0){
			return 0;
			}
		
		DOTHI temp = g;
		STACK stack;
		khoitaoStack(stack);
		TimDuongDi(x,temp,stack);
		// kt temp có tồn tại cung hay đường đi nào còn lại k
		int dem=0;
		for (int j=0;j<temp.n;j++)
			if(BacCuaDinh(j,temp)!=0)
				dem++;
		if (dem!=0) return 0;	
		
		//kt đỉnh đầu và cuối trùng nhau ko
		int gtCuoi ; 
		pop(stack,gtCuoi);
		if (gtCuoi==stack.array[0])
			return 0;	
		
		//xuất đường đi ra
		printf ("\n Xuat duong di euler :\n");
		printf ("%d ",gtCuoi);
		while(!empty(stack))
		printf("%d \t",pop(stack,x));
		
		return 1;
							
}

int main (){
	DOTHI g;
	if (DocMaTranKe((char*)"text7.txt",g) == 1)
	{
		printf("Da lay thong tin do thi tu file thanh cong.\n\n");
		XuatMaTranKe(g);
		printf("Bam 1 phim bat ki de bat dau xet tinh lien thong cua do thi ...\n\n");
		getch();
		printf ("\n Do thi %d thanh phan lien thong .",SoThanhPhanLT(g));
	}
	
	int dinh;
	printf ("\n Tim bac cua dinh nao : ");
	scanf ("%d",&dinh);
	
	printf ("\n dinh %d co bac la : %d",dinh,BacCuaDinh(dinh,g));
	
	int kqkt=KiemTraXemCoChuTrinhHoacDuongDiEuler(g);
	switch (kqkt){
		case 1:printf ("\n DOTHI co chu trinh euler"); break;
		case 2:printf ("\n DOTHI co duong di euler"); break;
		case 0:printf ("\n KHONG xet TH nay"); break;
	}
	
//	TimChuTrinhHoacDuongDiEuler(g);

	int check = KiemTraChuTrinhEuler(g);
	printf ("\n gia tri check : %d ",check);
	
	int check1=KiemTraDuongDiEuler(g);
	printf ("\n gia tri check duong di euler : %d ",check1);
	
	
getch();


return 0;
}
