#include<stdio.h>
#include<string.h>
#include<malloc.h>
typedef struct{
	int GiaTien,
	So_luong_loai_hang_duoc_chon;
	float GiaTriDinhDuong;
	char TenHang[20];	//Ten sap pham
}LoaiHang;
LoaiHang *readfromfileLoaiHang(int *m,int *n){//Doc gia tien hien co va dem so luong loai hang
	FILE *f;
	f=fopen("LoaiHang2.txt","r");
	LoaiHang *dslh;
	dslh=(LoaiHang*)malloc(sizeof(LoaiHang));
	int i=0;
	fscanf(f,"%dujp",m);//Doc so tien hien co
	while(!feof(f)){
		fscanf(f,"%d %f %[^\n]",&dslh[i].GiaTien,&dslh[i].GiaTriDinhDuong,&dslh[i].TenHang);
		dslh[i].So_luong_loai_hang_duoc_chon=0;
		i++;
		dslh=realloc(dslh,sizeof(LoaiHang)*(i+1));
	}
	*n=i;
	fclose(f);
	return dslh;
}
void INdslh(LoaiHang *dslh,int n,int m){
	int TGT=0,i=0;
	float TGTDD=0;
	printf("Ap dung ky thuat huy hoach dong.\n");
	printf("STT\tTen hang\tGia tien\tGia tri dinh duong\tSo do vat duoc chon\n");
	for(i=0;i<n;i++){
		printf("%d\t%s\t\t%d\t\t%.2f\t\t\t %d\n",i+1,dslh[i].TenHang,dslh[i].GiaTien,dslh[i].GiaTriDinhDuong,dslh[i].So_luong_loai_hang_duoc_chon);
		TGT += dslh[i].So_luong_loai_hang_duoc_chon * dslh[i].GiaTien;
		TGTDD += dslh[i].So_luong_loai_hang_duoc_chon * dslh[i].GiaTriDinhDuong;
	}
	printf("\nSo tien hien co la: %d",m);
	printf("\nSo tien cac phai tra: %d",TGT);
	printf("\nTong gia tri dinh duong: %.2f",TGTDD);
}
void TaoBangDSLH(LoaiHang *dslh,int n,int m,float F[][m+1],int X[][m+1]){
	int k,	//K loai do vat trong sieu thi
	V		//So tien con lai
	,xk		//xk chay tu 0 den V/gtk
	,Xmax;
	float Fmax;
	//1.Tinh dong dau tien
	for(V=0;V<=m;V++){
		X[0][V]=V/dslh[0].GiaTien;
		F[0][V]=X[0][V]*dslh[0].GiaTriDinhDuong;
	}
	//2.dien vao cac dong con lai
	for(k=1;k<n;k++){
		for(V=0;V<=m;V++){
			Fmax=F[k-1][V];
			Xmax=0;
			for(xk=1;xk<=V/dslh[k].GiaTien;xk++){
				if(F[k-1][V-xk*dslh[k].GiaTien]+xk*dslh[k].GiaTriDinhDuong>Fmax){
					//Cap nhat lai Fmax
					Fmax=F[k-1][V-xk*dslh[k].GiaTien]+xk*dslh[k].GiaTriDinhDuong;
					Xmax=xk;
				}
			}
			//Tim duoc Fmax va Xmax cho moi loai hang
			F[k][V]=Fmax;
			X[k][V]=Xmax;
		}
	}
}
void InBangLoaiHang(int n,int m,float F[][m+1],int X[][m+1]){
	int k,V;
	printf("\n\nIn bang.Cot ben trai luu F, cot ben phai luu X\n\n");
	for(k=0;k<n;k++){
		for(V=0;V<=m;V++){
			printf("%c%.2f|%d",186,F[k][V],X[k][V]);
		}
		printf("%c\n",186);
	}
}
void TraBangLoaiHang(LoaiHang *dslh,int m,int n,int X[][m+1]){
	int k,V;
	V=m;
	for(k=n-1;k>=0;k--){
		dslh[k].So_luong_loai_hang_duoc_chon=X[k][V];
		V= V -X[k][V]*dslh[k].GiaTien;
	}
}
int main(){
	int m,n;
	LoaiHang *dslh=readfromfileLoaiHang(&m,&n);
	
	float F[n][m+1];//Tong gia tri dinh duong cua k loai do vat duoc chon
	int X[n][m+1];//Tong so luong cua k loai do vat duoc chon
	
	TaoBangDSLH(dslh,n,m,F,X);
	InBangLoaiHang(n,m,F,X);
	TraBangLoaiHang(dslh,m,n,X);
	INdslh(dslh,n,m);
	free(dslh);
	//return 0;
}
