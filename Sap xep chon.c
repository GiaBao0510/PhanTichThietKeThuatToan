#include<stdio.h>
#include"C:\BasicProgramming\PhanTich&ThietKeThuatToan\tvSapXep.c"
int main(){
	recordtype A[30];
	int n;
	printf("Nhap so luong phan tu: ");scanf("%d",&n);
	Read(A,&n);
	Print(A,n);
	printf("\n\tSau khi sap xep chon(Khong giam):\n");
	sortselection1(A,n);
	Print(A,n);
	printf("\n\tSau khi sap xep chon(Khong tang):\n");
	sortselection2(A,n);
	Print(A,n);
}
