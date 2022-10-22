#include<stdio.h>
#include<malloc.h>
void doteptin(int a[][50],int *n){
	FILE *f=fopen("TamGiacSo.txt","r");
	if(f==NULL){
		printf("loi mo tep");
		return;
	}
	int i=0,j;
	while(!feof(f)){
		for(j=0;j<=i;j++){
			fscanf(f,"%d",&a[i][j]);
		}
		i++;
	}
	*n=i;
	fclose(f);
}
void intetin(int a[][50],int n){
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<=i;j++){
			printf("%3d",a[i][j]);
		}
		printf("\n");
	}
}
//Ham max nhan vao dong i trong mang A va cot J
int max(int a[],int j){
	//tra ve chi so cot cua phan tu lon nhat
	if(j==0){//Cot dau tien
		return (a[0]>a[1])? 0:1;
	}
	if(a[j-1]>a[j] && a[j-1]>a[j+1]){
		return j-1;
	}
	if(a[j]>a[j-1] && a[j]>a[j+1]){
		return j;
	}
	if(a[j+1]>a[j] && a[j+1]>a[j-1]){
		return j+1;
	}
}
void Greedy(int a[][50],int n,int Pa[]){
	int i,j=0,sum=0;
	Pa[0]=a[0][0];
	printf("\nKy thuat tham an\n");
	for(i=0;i<n;i++){
		j= max(a[i],j);//trong dong a[i] cua cot J
		Pa[i]=a[i][j];
		sum+=Pa[i];
	}
	printf("\nChieu dai duong di duong di: %d\n",sum);
	printf("Duong di: ");
	for(i=0;i<n;i++){
		printf("%d ",Pa[i]);
	}
}
int main(){
	int a[50][50],n,
		Pa[50];	//Luu tru vet duong di
	doteptin(a,&n);
	intetin(a,n);
	Greedy(a,n,Pa);
	return 0;
}
