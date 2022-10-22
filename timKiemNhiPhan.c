#include<stdio.h>
#include<malloc.h>
int * Readfromfile(int *n){
	FILE *f =fopen("mangDon.txt","r");
	int *A=(int*)malloc(sizeof(int));
	int i=0;
	while(!feof(f)){
		fscanf(f,"%d",&A[i]);
		i++;
		A=realloc(A,sizeof(int)*(i+1));
	}
	*n=i;
	fclose(f);
	return A;
}
void printdata(int *a,int n){
	int i;
	printf("\nTong so luong cac phan tu: %d\n",n);
	for(i=0;i<n;i++){
		printf("%3d",a[i]);
	}
}
//Tim kiem nhi phan
int TimKiemNhiPhan(int l,int r,int x,int *a){
	if(l<=r){
		int m=(l+r)/2;
		if(x==a[m]){
			return 1; 
		}
		if(a[m]>x){//tim mang con ben trai
			return TimKiemNhiPhan( l,m-1,x,a);
		}
		else if(a[m]<x){//tim mang con ben phai
			return TimKiemNhiPhan( m+1,r,x,a);
		}
	}
	else return 0;
}
int main(){
	int n,*a= Readfromfile(&n);
	printdata(a, n);
	printf("\nTim kiem nhi phan:\n");
	int x;
	printf("Nhap gia tri can tim: ");scanf("%d",&x);
	printf("\n%d",TimKiemNhiPhan(0,n-1,x,a));
}
