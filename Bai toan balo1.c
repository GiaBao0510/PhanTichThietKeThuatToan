#include<stdio.h>
#include<malloc.h>
#include<string.h>
typedef struct{
	float Don_Gia,Gia_tri,Trong_luong;
	int So_do_vat_duoc_chon;
	char Ten[20];
}dovat;
dovat *ReadDataFromBAlO1(float *w,int *n){ //Chua trong luong toi da cua balo va so luong do vat
	FILE *f;
	f=fopen("balo1.txt","r");
	dovat *dsdv;
	dsdv=(dovat*)malloc(sizeof(dovat));	//Cap phat bo nho la 1
	int i=0;
	fscanf(f,"%f",w);	//Trong luong toi da ma ba lo co the dung
	if(f!=NULL){
		while(!feof(f)){
			fscanf(f,"%f%f%[^\n]",&dsdv[i].Trong_luong,&dsdv[i].Gia_tri,&dsdv[i].Ten);
			//Chon " %[^\n] thay cho gets va %s vi %[^\n] la dinh dang de doc mot chuoi ky tu bo qua xuong dong"
			dsdv[i].Don_Gia=dsdv[i].Gia_tri/dsdv[i].Trong_luong; //Don Gia = gia tri/trong luong
			dsdv[i].So_do_vat_duoc_chon=0; 
			i++;
			dsdv=realloc(dsdv,sizeof(dovat)*(i+1));	//Cap nhat lai kich thuoc cua bo nho
		}
	}else printf("@@@ Loi mo tep @@@");
	*n=i;		//So luong do vat
	fclose(f);
	return dsdv;//Tra ve danh sach do vat 
}
void printBalo1(dovat *dsdv,int n,float w){
	int i;
	float TGT=0;	//Tong gia tri
	float TTL=0;	//Tong trong luong
	printf("\nKy thuat tham an\n");
	printf("\nSTT\tTrong_Luong\tGia_Tri\t\tDon_Gia\t\tSo_do_vat_duoc_chon\tTen_do_vat\n");
	for(i=0;i<n;i++){
		printf("%d\t%.2f\t\t%.2f\t\t%.2f\t\t%d\t\t%s\n",i,dsdv[i].Gia_tri,dsdv[i].Trong_luong,dsdv[i].Don_Gia,dsdv[i].So_do_vat_duoc_chon,dsdv[i].Ten);
		TTL+=dsdv[i].So_do_vat_duoc_chon*dsdv[i].Trong_luong;
		TGT+=dsdv[i].So_do_vat_duoc_chon*dsdv[i].Gia_tri;
	}
	printf("\nTrong luong doi da cua Balo la: %.2f",w);
	printf("\nTong gia tri cua do vat duoc chon la: %.2f",TGT);
	printf("\nTong trong luong cua do vat duoc chon la: %.2f",TTL);
}
/*----Dung phuong phan sap xep noi bot ap dung cho don gia --- */
void Swap(dovat *A,dovat *B){
	dovat temp=*A;
	*A=*B;
	*B=temp;
}
void bubblesort(dovat *dsdv,int n){
	int i,j;
	for(i=0;i<=n-2;i++){
		for(j=n-1;j>=i+1;j--){
			if(dsdv[j].Don_Gia>dsdv[j-1].Don_Gia){//Doi dau vi de sap xep don gia tu be den lon
				Swap(&dsdv[j],&dsdv[j-1]);
			}
		}
	}
}
//Ky thuat tham an
void Greedy(dovat *dsdv,int n,float w){
	int i;
	for(i=0;i<n;i++){
		dsdv[i].So_do_vat_duoc_chon=w/dsdv[i].Trong_luong;	//So do vat duoc chon = trong luong cua ba lo/ trong luong cua do vat thu i
		w-=dsdv[i].So_do_vat_duoc_chon*dsdv[i].Trong_luong;	//Lay trong luong cua ba lo tru cho so do vat duoc chon o trong ba lo
	}
}
int main(){
	int n;
	float w;
	dovat *dsdv;
	dsdv=ReadDataFromBAlO1(&w,&n);
	bubblesort(dsdv,n);
	Greedy(dsdv,n,w);
	printBalo1(dsdv,n,w);
	free(dsdv);		//Giai phong bo nho
}
