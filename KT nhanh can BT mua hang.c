#include<stdio.h>
#include<malloc.h>
#include<string.h>
typedef struct{
	float GT;			//Gia tien
	float GTDD;			//Gia tri dinh duong 
	int SL;				//So luong do vat
	int so_LH_duoc_chon;//So loai hang duoc chon
	float DVDD;			//Don vi dinh duong
	char TenHang[20];	//Ten sap pham
}LoaiHang;
LoaiHang *readfromfileLoaiHang(float *m,int *n){
	FILE *f;
	f=fopen("LoaiHang.txt","r");
	LoaiHang *dslh;
	dslh=(LoaiHang*)malloc(sizeof(LoaiHang));
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
	,TGTDD=0;
	printf("STT\tGia tien\tGia tri dinh duong\tDon vi dinh duong\tSo luong\tSo do vat duoc chon\tTen hang\n");
	for(i=0;i<n;i++){
		printf("%d\t%.2f\t\t%.2f\t\t\t%.2f\t\t\t%d\t\t %d\t\t%s\n",i+1,dslh[i].GT,dslh[i].GTDD,dslh[i].DVDD,dslh[i].SL,dslh[i].so_LH_duoc_chon,dslh[i].TenHang);
		TGT+=dslh[i].so_LH_duoc_chon*dslh[i].GT;
		TGTDD+=dslh[i].so_LH_duoc_chon*dslh[i].GTDD;
	}
	printf("\nSo tien hien co la: %.2f",m);
	printf("\nSo tien cac phai tra: %.2f",TGT);
	printf("\nTong gia tri dinh duong: %.2f",TGTDD);
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
void TaoNutGoc(float m,float *TGTDD,float *CT,float *GTconlai,float *GTDDLNTT,float Don_vi_dinh_duong_lon_nhat){
	*TGTDD=0;
	*GTconlai=m;
	*CT= *GTconlai * Don_vi_dinh_duong_lon_nhat;
	*GTDDLNTT=0;
}
void CapNhatPATNTT(float TGTDD,float *GTDDLNTT,int x[],LoaiHang *dslh,int n){
	int i;
	if(*GTDDLNTT<TGTDD){
		*GTDDLNTT=TGTDD;
		for(i=0;i<n;i++){
			dslh[i].so_LH_duoc_chon=x[i];
		}
	}
}
void KT_nhanh_can(int i,float *TGTDD,float *CT,float *GTconlai,float *GTDDLNTT,int x[],LoaiHang *dslh,int n){
	int j;
	int So_do_vat_lon_nhat_duoc_chon=MinLoaiHang(dslh[i].SL,*GTconlai/dslh[i].GT);
	for(j=So_do_vat_lon_nhat_duoc_chon;j>=0;j--){
		*TGTDD= *TGTDD + j * dslh[i].GTDD;
		*GTconlai=*GTconlai - j * dslh[i].GT;
		*CT = *TGTDD + *GTconlai * dslh[i+1].DVDD;
		if(*CT>*GTDDLNTT){
			x[i]=j;
			if((i==n-1)||(*GTconlai==0)){
				 CapNhatPATNTT(*TGTDD,GTDDLNTT,x,dslh,n);
			}
			else{
				KT_nhanh_can(i+1,TGTDD,CT,GTconlai,GTDDLNTT,x,dslh,n);
			}
		}
		//Quay lui
		x[i]=0;
		*TGTDD=*TGTDD - j * dslh[i].GTDD;
		*GTconlai=*GTconlai + j * dslh[i].GT;
	}
}
int main(){
	int n;
	float m,TGTDD,GTconlai,CT,GTDDLNTT;
	LoaiHang *dslh=readfromfileLoaiHang(&m,&n);
	bublesort(dslh,n);
	int x[n];
	TaoNutGoc(m,&TGTDD,&CT,&GTconlai,&GTDDLNTT,dslh[0].DVDD);
	KT_nhanh_can(0,&TGTDD,&CT,&GTconlai,&GTDDLNTT,x,dslh,n);
	INdslh(dslh,n,m);
	free(dslh);
	return 0;
}
