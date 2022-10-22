#include<stdio.h>
#include"C:\BasicProgramming\PhanTich&ThietKeThuatToan\tvSapXep.c"
int main(){
	recordtype a[20];
	int n;
	Readfromfile(a,&n);
	Print(a,n);
	printf("\nSau khi sap xep vun dong:\n");
	Heapsort(a,n);
	Print(a,n);
}
