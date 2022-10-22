#include<stdio.h>
#include<string.h>
#include<malloc.h>
typedef struct{
	int so_DV_duoc_chon	//so luong san pham duoc chon
	,SL;				//So luong san pham
	float GT			//Gia tri san pham
	,TL					//trong luong sap pham
	,DG;				//Don gia
	char ten_SP[20];
}Sanpham;
Sanpham *readfromfilebalo2(int *n,float *w){
	FILE *f=fopen("balo2.txt","r");
	Sanpham *dssp=(Sanpham*)malloc(sizeof(Sanpham));
	fscanf(f,"%f",w);
	int i=0;
	while(!feof(f)){
		fscanf(f,"%f%f%d%[^\n]",&dssp[i].TL,&dssp[i].GT,&dssp[i].SL,&dssp[i].ten_SP);
		dssp[i].so_DV_duoc_chon=0;
		dssp[i].DG=dssp[i].GT/dssp[i].TL;
		i++;
		dssp=realloc(dssp,sizeof(Sanpham)*(i+1));//Cap nhap lai bo nho
	}
	*n=i;
	fclose(f);
	return dssp;
}
void InDSBALO2(Sanpham *dssp,int n,float w){
	int i;
	float TGT=0		//Tong gia tri
	,TTL=0;			//tong trong luong
	printf("STT\tTrong luong\tGia tri\t\tDon gia\t\tSo luong\tSo do vat duoc chon\tTen do vat\n");
	for(i=0;i<n;i++){
		printf("%d\t%.2f\t\t%.2f\t\t%.2f \t\t%d\t\t%d\t\t\t%s\n",i+1,dssp[i].TL,dssp[i].GT,dssp[i].DG,dssp[i].SL,dssp[i].so_DV_duoc_chon,dssp[i].ten_SP);
		TGT+=dssp[i].so_DV_duoc_chon*dssp[i].GT;
		TTL+=dssp[i].so_DV_duoc_chon*dssp[i].TL;
	}
	printf("\nTrong luong toi da ba lo co the dung: %.2f",w);
	printf("\nTong gia tri: %.2f",TGT);
	printf("\nTong trong luong: %.2f",TTL);
}
/*sap xep thu tu don gia giam dan*/
void swapbalo2(Sanpham *a,Sanpham *b){
	Sanpham temp =*a;
	*a=*b;
	*b=temp;
}
void bublesortbalo2(Sanpham *A,int n){
	int i,j;
	for(i=0;i<=n-2;i++){
		for(j=n-1;j>=i+1;j--){
			if(A[j].DG>A[j-1].DG){
				swapbalo2(&A[j],&A[j-1]);
			}
		}
	}
}
//Ham tim min
int Min(int a,int b){
	return(a<b)? a:b;
}
//Tao nut goc
void Tao_nut_goc(float w,float *TLconlai,float *CT,float *GiaLNTT,float *TGT,float Don_gia_lon_nhat){
	*TGT=0;
	*TLconlai=w;
	*CT=w * Don_gia_lon_nhat;//Can tren cua nut goc
	*GiaLNTT=0;
}
//Luu tru phuong an tot nhat tam thoi
void cap_nhat_PATNTT(float TGT,float *GiaLNTT,int x[],Sanpham *dssp,int n){
	int i;
	//Neu gia tri lon nhat tam thoi nho hon tong gia tri vua duoc tim thay thi ta cap nhat lai
	if(*GiaLNTT<TGT){
		*GiaLNTT=TGT;
	//Cap nhat lai so do vat duoc chon cua moi do vat I chinh la so do vat duoc chon da luu trong phuong an tot nhat tam thoi
		for(i=0;i<n;i++){
			dssp[i].so_DV_duoc_chon=x[i];
		}
	}
}
//Ky thuat nhanh can. phan nhanh cho do vat thu I
void Nhanh_can(int i,float *TGT,float *CT,float *TLconlai,float *GiaLNTT,int x[],Sanpham *dssp,int n){
	int j;			//La so do vat duoc chon. VD: Xa = n; Xa =n-1; Xa = n-2;...Xa=0
	int So_do_vat_lon_nhat_duoc_chon=Min(dssp[i].SL , *TLconlai/dssp[i].TL);
	for(j=So_do_vat_lon_nhat_duoc_chon;j>=0;j--){		//xet tat ca cac kha nang co the phan nhanh theo do vat I
		//ung voi mot gia tri cua j,ta co mot nut tren cay
		//Tinh 3 thong so tren cay
		*TGT=*TGT + j * dssp[i].GT;
		*TLconlai=*TLconlai - j * dssp[i].TL;
		*CT=*TGT + *TLconlai * dssp[i+1].DG;//dssp[i+1].DG la nhan cho don gia do vat ke tiep
		if(*CT>*GiaLNTT){					//Neu CT<=Gia lon nhat tam thoi thi ta CAT TIA. Nguoc lai thi ta xet tiep
			x[i]=j;										//So do vat thu i duoc chon = j
			if((i==n-1)||(*TLconlai==0)){				//Neu xet den nut la(nut cuoi cung ) hoac balo day khong con cho nua thi:
				cap_nhat_PATNTT(*TGT,GiaLNTT,x,dssp,n);				//Cap nhat lai phuong an tot nhat tam thoi
			}
			else{//Nguoc lai ta phan nhanh cho do vat thu I+1(Do vat ke tiep)
				Nhanh_can(i+1,TGT,CT,TLconlai,GiaLNTT,x,dssp,n);	//Xet nut con cua i
			}
		}
		//Quay lui de xet nut khac(ung voi gia tri khac cua j)
		x[i]=0;
		*TGT=*TGT-j * dssp[i].GT;		//Tra lai tong gia tri cua nut cha
		*TLconlai=*TLconlai+j * dssp[i].TL;//Tra lai trong luong cua nut cha
	}
}
int main(){
	int n;		//So luong loai do vat
	float w		//Trong luong toi da ma balo co the chua dung
	,CT			//Can tren
	,TGT		//Tong gia tri cua cac loai do vat duoc chon
	,TLconlai	//Trong luong con lai cua balo
	,GiaLNTT;	//Gia lon nhat tam thoi
	Sanpham *dssp=readfromfilebalo2(&n,&w);
	int x[n];	//Luu tru phuong an tot nhat tam thoi
	bublesortbalo2(dssp,n);
	Tao_nut_goc(w,&TLconlai,&CT,&GiaLNTT,&TGT,dssp[0].DG);
	//Truyen so 0 la ta thuc hien phan nhanh do vat thu 0(Nghia la do vat dau tien)
	Nhanh_can(0,&TGT,&CT,&TLconlai,&GiaLNTT,x,dssp,n);
	InDSBALO2(dssp,n,w);
	free(dssp);
	return 0;
}
