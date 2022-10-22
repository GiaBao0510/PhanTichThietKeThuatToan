#include<stdio.h>
#include"C:\BasicProgramming\PhanTich&ThietKeThuatToan\tvSapXep.c"
int main(){
	recordtype A[30];
	int n;
	Readfromfile(A,&n);
	Print(A,n);
	printf("\n\tSau khi sap xep chon(Khong giam):\n");
	sortselection1(A,n);
	Print(A,n);
	printf("\n\tSau khi sap xep chon(Khong tang):\n");
	sortselection2(A,n);
	Print(A,n);
}
