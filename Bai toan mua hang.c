#include<stdio.h>
#include<malloc.h>
#include<string.h>
typedef struct{
	float GT;				//Gia tien
	float GTDD;			//Gia tri dinh duong 
	int SL;				//So luong do vat
	int so_LH_duoc_chon;//So loai hang duoc chon
	float DVDD;			//Don vi dinh duong
	char TenHang[20];	//Ten sap pham
}LoaiHang;
LoaiHang *readfromfileLoaiHang(float *m,int *n){
	FILE *f=fopen("LoaiHang.txt","r");
	//f;
	LoaiHang *dslh=(LoaiHang*)malloc(sizeof(LoaiHang));
	//dslh;
	int i=0;
	fscanf(f,"%f",m);
	if(f!=NULL){
		while(!feof(f)){
			fscanf(f,"%f%f%d%[^\n]",&dslh[i].GT,&dslh[i].GTDD,&dslh[i].SL,&dslh[i].TenHang);
			dslh[i].so_LH_duoc_chon=0;
			dslh[i].DVDD=dslh[i].GTDD/dslh[i].GT;
			i++;
			dslh=realloc(dslh,sizeof(LoaiHang)*(i+1));
		}
	}else printf("Loi mo file");
	*n=i;
	fclose(f);
	return dslh;
}
void INdslh(LoaiHang *dslh,int n,float m){
	int i=0;
	float TGT=0
	,TGTDD=0
	,TSLSP=0;
	printf("STT\tGia tien\tGia tri dinh duong\tDon vi dinh duong\tSo luong\tSo do vat duoc chon\tTen hang\n");
	for(i=0;i<n;i++){
		printf("%d\t%.2f\t\t%.2f\t\t\t%.2f\t\t\t%d\t\t %d\t\t%s\n",i+1,dslh[i].GT,dslh[i].GTDD,dslh[i].DVDD,dslh[i].SL,dslh[i].so_LH_duoc_chon,dslh[i].TenHang);
		TGT+=dslh[i].so_LH_duoc_chon*dslh[i].GT;
		TGTDD+=dslh[i].so_LH_duoc_chon*dslh[i].GTDD;
		TSLSP+=dslh[i].so_LH_duoc_chon;
	}
	printf("\nSo tien hien co la: %.2f",m);
	printf("\nSo tien cac phai tra: %.2f",TGT);
	printf("\nTong gia tri dinh duong: %.2f",TGTDD);
	printf("\nTong so luong san phan trong gio hang: %d",TSLSP);
}
//Sap xep thu tu don vi dinh duong tu lon den be
void swapLoaiHang(LoaiHang *A,LoaiHang *B){
	LoaiHang temp=*A;
	*A=*B;
	*B=temp;
}
void bublesort(LoaiHang *DSLH,int n){
	int i,j;
	for(i=0;i<=n-2;i++){
		for(j=n-1;j>=i+1;j--){
			if(DSLH[j].DVDD>DSLH[j-1].DVDD){
				swapLoaiHang(&DSLH[j],&DSLH[j-1]);
			}
		}
	}
}
int MinLoaiHang(int a,int b){
	return(a<b)? a:b;
}
//Ky thuat tham an
void GreedyLoaiHang(LoaiHang *DSLH,int n,float m){
	int i;
	for(i=0;i<n;i++){
			DSLH[i].so_LH_duoc_chon=MinLoaiHang(DSLH[i].SL,m/DSLH[i].GT);/*De xac dinh so do vat duoc chon ta tim MIN giua 
			so luong do vat ,va, so tien hien co chia cho gia tien do vat thu I lay phan nguyen*/
			m-=DSLH[i].so_LH_duoc_chon*DSLH[i].GT;
			DSLH[i].SL-=DSLH[i].so_LH_duoc_chon;
	} 
}
int main(){
	int n;
	float m;
	LoaiHang *DSLH;
	DSLH=readfromfileLoaiHang(&m,&n);
	bublesort(DSLH,n);
	GreedyLoaiHang(DSLH,n,m);
	INdslh(DSLH,n,m);
	free(DSLH);
	return 0;
}
