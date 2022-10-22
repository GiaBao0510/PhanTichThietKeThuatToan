#include<stdio.h>
#include<malloc.h>
typedef struct{
	float MenhGia;
	int SL;	//So luong to tien
	int X; //Phuong an tra tien(So luong tien can phai tra)
}TraTien;
TraTien * ATM(int *n){
	FILE *f;
	f=fopen("TraTienATM.txt","r");
	TraTien *a=(TraTien*)malloc(sizeof(TraTien));
	int i=0;
	if(f!=NULL){
		while(!feof(f)){
			fscanf(f,"%f%d",&a[i].MenhGia,&a[i].SL);
			a[i].X=0;	//So tien can phai tra ban dau la 0
			i++;
			a=realloc(a,sizeof(TraTien)*(i+1));
		}
	}else printf("@@@ Loi mo tep @@@");
	*n=i;		//So luong cac loai to tien co menh khac nhau
	fclose(f);
	return a;//Tra ve danh sach TraTien
}
/*--- Dung phuong phap noi bot, de sap xep thu tu menh gia trong cay ATM ---*/
void SwapValue(TraTien *A,TraTien *B){
	TraTien temp =*A;
	*A=*B;
	*B=temp;
}
void bubblesorttratien(TraTien *a,int n){
	int i,j;
	for(i=0;i<=n-2;i++){
		for(j=n-1;j>=i+1;j--){
			if(a[j].MenhGia>a[j-1].MenhGia){
				SwapValue(&a[j],&a[j-1]);
			}
		}
	}
}
//Kiem tra so luong tien trong may ATM
int CheckTheNumberOfBills(TraTien *a,int n){
	int i,tong=0;
	for(i=0;i<n;i++){
		tong+=(a[i].MenhGia*a[i].SL);
	}
	return tong;
} 
int Min(int a,int b){
	return(a<b)? a:b;
}
//Ap dung ki thuat tham an
void GreedySoTienCanPhaiTra(TraTien *a,int n,int m){
	int i;
	int Tong = CheckTheNumberOfBills(a, n);
	if(Tong < m){
		printf("\n@@@May chung toi hien khong du tien cho ban rut@@@\n");
		return;
	}
	for(i=0;i<n;i++){
		if(a[i].SL>0){				    //Neu so luong to tien cua menh gia X ma lon hon 0 thi tiep tuc tra.Nguoc lai chuyen qua so luong to tien co luong gia khac
			a[i].X=Min(a[i].SL,m/a[i].MenhGia);		//So tien can phai tra = so tien can rut / to tien co menh gia lon nhat
			m-=a[i].X*a[i].MenhGia;		//So tien can rut tru cho so luong to tien can phai gia nhan cho menh gia cua no
			a[i].SL-=a[i].X;			//So luong to tien cua menh gia thu i tru cho so luong tien can phai tra
		}
	}
} 
void InKetQua(TraTien *a,int n){
	printf("\nAp dung ki thuat tham an cho bai toan tra tien tu dong\n");
	int i;
	printf("STT\tMenh_gia_to_tien\tSo_tien_can_phai_tra\tSo_luong_tien_con_lai\n");
	for(i=0;i<n;i++){
		printf("%d\t%f VND\t\t%d\t\t\t%d\n",i+1,a[i].MenhGia,a[i].X,a[i].SL);
	}
}
int main(){
	int n;
	float m;
	printf("Nhap so tien can rut: ");scanf("%f",&m);
	TraTien *A;
	A=ATM(&n);
	bubblesorttratien(A,n);
	GreedySoTienCanPhaiTra(A,n,m);
	InKetQua(A,n);
	free(A);
}
