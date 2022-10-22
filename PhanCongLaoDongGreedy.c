#include<stdio.h>
#define time 50
typedef struct{
	int CN	//Cong nhan
	,CV		//Cong viec
	,TG;	//thoi gian cong nhan hoan thanh cong viec
}PhanCong;
typedef struct{
	int ThoiGian	//thoi gian
	,mark;		//Danh dau cong viec hoac cong nhan hoac cong viec va cong nhan da thuc hien
}Data;
void readfromfilePhanCong(Data A[][time],int *n){
	FILE *f=fopen("PhanCongLaoDong.txt","r");
	if(f==NULL){
		printf("LOI MO TEP");
		return;
	}
	fscanf(f,"%d",n);//Doc so luong cong nhan va cong viec
	int i,j;
	for(i=0;i<*n;i++){
		for(j=0;j<*n;j++){
			fscanf(f,"%d",&A[i][j].ThoiGian);//Doc thoi gia ma cong nhan thu I hoan thanh cong viec thu J
			A[i][j].mark=0;	//Ban chua co cong viec J hoac cong nhan I hoanh thanh thi ta danh dau la 0, nguoc lai thi danh dau 1 
		}
	}
	fclose(f);
}
void InDSPCLD(Data A[][time],int n){
	int i,j;
	printf("Phan cong lao dong theo nguoi chon viec:\n");
	printf("Cong Nhan|Cong viec:\t1\t2\t3\t4\t5\n");
	for(i=0;i<n;i++){
		printf("\n\t\t%d:",i+1);
		for(j=0;j<n;j++){
			printf("\t%d",A[i][j]);
		}
	}
}
//Cap nhat cong viec(Danh dau cong viec nay da co nguoi lam)
void Cap_nhat_cong_viec(Data a[][time],int n,int cv/*Cong viec*/){
	//La cong viec thu J da co nguoi lam
	int i;
	for(i=0;i<n;i++){
		a[i][cv].mark=1;
	} 
}
//Tim so dong cong nhan thuc hien cong viec tren cot co thoi gian nho nhat
int Min_of_row(Data a[][time],int n,int cn/*Cong nhan*/,int *cv/*Cong viec*/){
	int TGmin=999,k;
	for(k=0;k<n;k++){
		if(a[cn][k].mark==0 && a[cn][k].ThoiGian<TGmin){//Neu cong viec K nao do chua duoc danh dau va thoi gian thuc hien nho hon thoi gian min thi:
			TGmin=a[cn][k].ThoiGian;//ta gan TGNN bang thoi gian cong nhanthuc hien cong viec thu K
			*cv=k;					//Dat cong viec co thoi gian nho nhat bang K
		}		
	}
	return TGmin;//Tra ve thoi gian nho nhat 
}
//Ky thuat tham an
void GreedyPCLD(Data a[][time],int n,PhanCong PA[]){
	int i,j;
	for(i=0;i<n;i++){//Xet cac cong nhan i tu 0 den n-1
		PA[i].CN=i+1;
		PA[i].TG=Min_of_row(a,n,i,&j);//Voi moi cong nha i ta tim thoi gian nho nhat de thuc hien cong viec
		PA[i].CV=j+1;
		Cap_nhat_cong_viec(a,n,j);//Danh dau cong viec J da thuc hien roi
	}
}
//In phuong an
void InPAPCLD(PhanCong PA[],int n){
	int i,tongTG=0;
	printf("\nAp dung ky thuat tham an cho bai toan phan cong lao dong\n");
	for(i=0;i<n;i++){
		printf("\t%d\t%d\t%d\n",PA[i].CN,PA[i].CV,PA[i].TG);
		tongTG+=PA[i].TG;
	}
	printf("\nTong thoi gian thuc hien la: %d",tongTG);
}
int main(){
	int n;
	Data A[time][time];
	readfromfilePhanCong(A,&n);
	PhanCong PA[n];
	InDSPCLD(A,n);
	GreedyPCLD(A,n,PA);
	InPAPCLD(PA,n);
	return 0;
}
