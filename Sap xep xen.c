#include<stdio.h>
#include"C:\BasicProgramming\PhanTich&ThietKeThuatToan\tvSapXep.c"
int main(){
	recordtype A[30];
	int n;
	printf("Nhap so luong phan tu: ");scanf("%d",&n);
	Read(A,&n);
	printf("\n\tDu lieu ban dau:\n");
	Print(A,n);
	printf("\n\tDu lieu sau khi sap xep xen(khong giam):\n");
	Insertionsort1(A,n);
	Print(A,n);
	printf("\n\tDu lieu sau khi sap xep xen(khong tang):\n");
	Insertionsort2(A,n);
	Print(A,n);
}
