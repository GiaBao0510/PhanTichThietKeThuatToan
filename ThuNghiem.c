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
int T_search(int l,int r,int x,int *a){
	if(l <= r){
		int m1 = l+(r-l)/3,
			m2 = r -(r-l)/3;
		if(a[m1] == x || a[m2] == x){
			return 1; 
		}
		if(a[m1] > x){//Tim mang ben trai tu l den m1-1
			return T_search(l,m1-1, x,a);
		}
		else{
			if(a[m2] > x){//Tim mang o giua tu  m1+1 den m2-1
				return T_search(m1+1,m2-1, x,a);
			}
			else if(a[m2] < x){//Tim mang ben phai tu m2+1 den r
				return T_search(m2+1,r, x,a);
			}
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
	printf("\n%d",T_search(0,n-1, x,a));
}
