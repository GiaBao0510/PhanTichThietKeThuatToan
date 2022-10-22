#include<stdio.h>
#include<malloc.h>
#include<string.h>
typedef struct{
	int TL,
	so_do_vat_duoc_chon;
	float GT;
	char ten[20];
}dovat;
dovat * readfromfile(int *n,int *w){//Doc so luong do vat va trong luong cua balo3
	FILE *f=fopen("balo3.txt","r");
	dovat *dsdv=(dovat*)malloc(sizeof(dovat));
	int i=0;
	fscanf(f,"%d",w);//doc trong luong cua balo
	while(!feof(f)){
		fscanf(f,"%d %f %[^\n]",&dsdv[i].TL,&dsdv[i].GT,&dsdv[i].ten);
		dsdv[i].so_do_vat_duoc_chon=0;
		i++;
		dsdv=realloc(dsdv,sizeof(dovat)*(i+1));
	}
	*n=i;
	fclose(f);
	return dsdv;
}
void Indsdv(dovat *dsdv,int n,int w){
	int i,TTL=0;
	float TGT=0;
	printf("Ap dung ky thuat huy hoach dong\n");
	printf("STT \t Ten do vat \t Gia tri \t Trong luong \t So do vat duoc chon\n");
	for(i=0;i<n;i++){
		printf("%d \t %s \t %.2f\t\t\t%d\t\t\t%d\n",i+1,dsdv[i].ten,dsdv[i].GT,dsdv[i].TL,dsdv[i].so_do_vat_duoc_chon);
		TTL += dsdv[i].so_do_vat_duoc_chon *dsdv[i].TL; //Cong trong luong cho moi loai do vat
		TGT += dsdv[i].so_do_vat_duoc_chon * dsdv[i].GT;//Cong gia tri cho moi loai do vat
	}
	printf("\nTrong luong toi da balo co the chua: %d",w);
	printf("\nTong gia tri: %.2f",TGT);
	printf("\nTong trong luong: %d",TTL);
}
/*---------Ky thuat huy hoach dong-----------*/
void TaoBang(dovat *dsdv,int n,int w,float F[][w+1],int X[][w+1]){
	int xk,//Chay tu 0 den V/gk
		yk,
		k,		//Chay tu do vat thu 1 den do vat thu n
		V,		//Trong luong con lai cua balo
		Xmax;	//Luu tru gia tri lon nhat cua XkV lon nhat
	float Fmax;	//Luu tru gia tri lon nhat cua FkV
	//Dien gia tri cho dong dau tien X[1,V] = V/g1 va F[1,V] = X[1,V] * v1
	for(V=0;V<=w;V++){
		X[0][V]= V / dsdv[0].TL;
		F[0][V]= X[0][V] * dsdv[0].GT;
	}
	//Dien vao cac dong con lai, su dung cong thuc truy hoi
	for(k=1;k<n;k++){//tim gia tri lon nhat cua F
		for(V=0;V<=w;V++){
			Fmax = F[k-1][V];
			Xmax=0;
			yk= V/dsdv[k].TL;
			for(xk=1;xk<=yk;xk++){
				if(F[k-1][V-xk*dsdv[k].TL]+xk*dsdv[k].GT > Fmax){
					//cap nhat
					Fmax=F[k-1][V-xk*dsdv[k].TL]+xk*dsdv[k].GT;
					Xmax=xk;
				}
			}
			//Da tim duoc Fmax va Xmax
			F[k][V]=Fmax;
			X[k][V]=Xmax;
		}
	}
}
void InBang(int n,int w,float F[][w+1],int X[][w+1]){
	int V,k;
	printf("\n\nIn bang.Cot ben trai luu F, cot ben phai luu X\n\n");
	for(k=0;k<n;k++){
		for(V=0;V<=w;V++){
			printf("%c%5.2f|%3d",186,F[k][V],X[k][V]);
		}printf("%c\n",186);
	}
}
void TraBang(dovat *dsdv,int n,int w,int X[][w+1]){
	int k,V;
	V=w;
	for(k=n-1;k>=0;k--){
		dsdv[k].so_do_vat_duoc_chon=X[k][V];
		V= V- X[k][V]*dsdv[k].TL;
	}
}
int main(){
	int n,w;
	dovat *dsdv;
	dsdv=readfromfile(&n,&w);
	
	float F[n][w+1];	//La tong gia troi cua do vat thu k duoc chon
	int X[n][w+1];		//la luong do vat thu k duoc chon
	
	TaoBang(dsdv,n,w,F,X);
	InBang(n,w,F,X);
	TraBang(dsdv,n,w,X);
	
	Indsdv(dsdv,n,w);
	free(dsdv);
	return 0;
}
