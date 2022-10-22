#include<stdio.h>
#include"C:\BasicProgramming\PhanTich&ThietKeThuatToan\tvSapXep.c"
int main(){
	int n;
	recordtype *a;
	printf("\tMerge-Sort\n");
	a=ReadFromFile(&n);
	printf("\nDu lieu ban dau:\n");
	Print(a,n);
	printf("\nSau khi sap xep Merge Sort:\n");
	mergeSort(a, 0, n-1);
	Print(a,n);
}
