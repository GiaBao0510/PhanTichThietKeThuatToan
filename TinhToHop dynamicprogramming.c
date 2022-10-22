#include<stdio.h>
int Tohop(int c[][50],int n,int k){
	int i,j;
	c[0][0]=1;
	for(i=1;i<=n;i++){
		c[i][0]=1;
		c[i][i]=1;
		for(j=1;j<i;j++){
			c[i][j]=c[i-1][j-1]+c[i-1][j];
		}
	}
	return c[n][k];
}
int main(){
	int C[50][50];
	int n,k;
	printf("\nTinh to hop chap k cua n\n");
	printf("Nhap n: ");scanf("%d",&n);
	printf("Nhap k: ");scanf("%d",&k);
	int i,j;
	printf("\nKet qua: %d",Tohop(C,n,k));
	printf("\nTam Giac Pascal\n");
	for(i=1;i<=n;i++){
		for(j=1;j<i;j++){
			printf("%d ",C[i][j]);
		}printf("\n");
	}
	
}
