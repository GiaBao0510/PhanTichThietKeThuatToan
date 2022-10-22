#include<stdio.h>
#include"C:\BasicProgramming\PhanTich&ThietKeThuatToan\tvSapXep.c"
int main(){
	recordtype a[20];
	int n; 
	printf("Nhap so luong phan tu: ");scanf("%d",&n);
	Read(a,&n);
	printf("\n\tDu lieu ban dau:\n");
	Print(a,n);
	printf("\n\tDu lieu sau khi sap xep nhanh chong:\n");
	QuickSort(a,0,n-1);//Chay tu phan tu thu 0 den n-1
	Print(a,n);
}
