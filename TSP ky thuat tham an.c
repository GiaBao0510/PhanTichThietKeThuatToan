#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<math.h>
typedef struct{
	float x,y;
	char tp[5];
}thongtin;
//Ban dau luu tru danh sach cac canh
typedef struct{
	float L[100][100];
}cung;
thongtin *thongtintp(int *n){
	FILE *f=fopen("TSP1.txt","r");
	thongtin *dstp = (thongtin*)malloc(sizeof(thongtin));
	int i=0;
	if(f==NULL){
		printf("Loi mo tep");
		return 0;
	}
	while(!feof(f)){
		fscanf(f,"%f %f %[^\n]",&dstp[i].x,&dstp[i].y,&dstp[i].tp);
		i++;
		dstp=realloc(dstp,sizeof(thongtin)*(i+1));
	}
	*n=i;
	fclose(f);
	return dstp;
}
void in(thongtin *dstp,int n){
	int i;
	for(i=0;i<n;i++){
		printf("%s %.2f %.2f\n",dstp[i].tp,dstp[i].x,dstp[i].y);
	}
}
//Khoi tao
void Create(cung *E,int n){
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			E->L[i][j]=0;
		}
	}
}
//them cung
void addedges(cung *E,int x,int y,float w){
	E->L[x][y] = E->L[y][x] =w;
}
//Tinh trong so cho moi canh
	void danhsachcung(thongtin *dstp,cung *E,int n){
		int i,j;
		for(i=0;i<n;i++){
			for(j=i;j<n;j++){
				float w=sqrt(pow(dstp[i].x - dstp[j].x,2)+pow(dstp[i].y - dstp[j].y,2));
				addedges(E,i,j,w);
			}
		}
	}
	void incung(cung *E,int n){
		int i,j;
		for(i=0;i<n;i++){
			printf("%3c\t\t",i+97);
		}
		for(i=0;i<n;i++){
			printf("\n%c ",i+97);
			for(j=0;j<n;j++){
				printf("%.2f\t\t",E->L[i][j]);
			}
		}
	}
	//Noi dung chinh
//Luu trong so cua cac cung nam tren duong cheo chinh
typedef struct{
	int u,v;//U la dinh dau, V la dinh cuoi
	float w;//trong so
}canh;
void doccaccanhchinh(thongtin *dstp,canh a[],int n){
	int i,j,k=0,temp;
	for(i=0;i<n;i++){
		for(j=i;j<n;j++){
			if(i==j){
				int t;
				for(t=0;t<=j;t++){//doc de bo qua cac so nam duoi duong cheo chinh
					temp=sqrt(pow(dstp[i].x - dstp[j].x,2)+pow(dstp[i].y - dstp[j].y,2));
				}
			}
			else{
				a[k].u=i;
				a[k].v=j;
				a[k].w=sqrt(pow(dstp[i].x - dstp[j].x,2)+pow(dstp[i].y - dstp[j].y,2));
				k++;
			}
		}
	}
}
void Indanhsachcanhchinh(canh a[],int m,int la_PA){
		int i,j;
		float tong=0;
		for(i=0;i<m;i++){
			printf("%d. %c-%c = %.2f\n",i+1,a[i].u+65,a[i].v+65,a[i].w);
			if(la_PA){
				tong+=a[i].w;
			}
		}
		if(la_PA){
			printf("\nTong do dai cac canh la %.2f",tong);
		}
}
//sap xep
void Swap(canh *x,canh *y){
	canh temp=*x;
	*x=*y;
	*y=temp; 
}
void bubblesort(canh A[],int m){
	int i,j;
	for(i=0;i<m-1;i++){
		for(j=m-1;j>i;j--){
			if(A[j].w < A[j-1].w){
				Swap(&A[j],&A[j-1]);
			}
		}
	}
}
//kiem tra dinh cap 3
int dinhcap3(canh PA[],int k/*Gom k canh*/, canh moi/*dua vao mot canh moi*/){		
	int i,dem;
	i=0;
	dem=1;//Dem = 1 la da co mot dinh la mot
	while(i<k && dem<3){
	/*Ta xet canh moi cua dinh dau co trung voi canh dau cua dinh hien tai khong hoac
	Ta xet canh moi cua dinh dau co trung voi canh cuoi cua dinh hien tai khong*/
		if(moi.u == PA[i].u || moi.u == PA[i].v){
			dem++;
		}
		i++;
	}
	if(dem==3) return 1;//Neu dem = 3 thi tra ve 1
	//nguoc lai
	i=0;
	dem=1;//Dem = 1 la da co mot dinh la mot
	while(i<k && dem<3){
	/*Ta xet canh moi cua dinh cuoi co trung voi canh dau cua dinh hien tai khong hoac
	Ta xet canh moi cua dinh cuoi co trung voi canh cuoi cua dinh hien tai khong*/
		if(moi.v == PA[i].u || moi.v == PA[i].v){
			dem++;
		}
		i++;
	}
	return dem==3;
}
//khoi tao rung
void init_forest(int parent[],int n){
	int i;
	//khoi tao moi dau cha cua tat ca cac dinh dieu bang chinh no
	for(i=0;i<n;i++){
		parent[i]=i;
	}
}
//Tim goc cua mot dinh bat ky trong mot rung cay
int find_root(int parent[],int x){
	while(x != parent[x]){
		x=parent[x];
	}
	return x;//tra ve goc
}
//kiem tra chu trinh
int chu_trinh(int r_dau,int r_cuoi){
	return (r_dau == r_cuoi);//Neu goc dinh dau == goc cua dinh cuoi thi do la mot chu trinh
}
//Hop nhat 2 cay lam mot
void update_forest(int parent[],int r_cay1,int r_cay2){
	parent[r_cay2]=r_cay1; //hop nhat lay goc cay 1 la cha cua cay 2
}
//ky thuat tham an
void greedy(canh dscanh[],int n,canh PA[]){
	int i,j;
	int parent[n];
	init_forest(parent,n);
	int r_dau,r_cuoi;
//Chon cac canh nho nhat khong tao thanh dinh cap 3 va khong tao thanh chu trinh thieu
	j=0;	
	for(i=0;i< n*(n-1)/2 && j<n-1 ;i++){
		r_dau = find_root(parent,dscanh[i].u);
		r_cuoi = find_root(parent,dscanh[i].v);
		if(!dinhcap3(PA,j,dscanh[i]) && !chu_trinh(r_dau,r_cuoi)){
			PA[j]=dscanh[i];//danh sach canh[i] khong tao dinh cap 3, khong tao thanh chu trinh thieu
			j++;
			update_forest(parent, r_dau, r_cuoi);//hop nhat 2 cay: dat cha cua goc cuoi cung bang goc dau
		}	
	}
//Den day PA da co n-1 canh
//Tim mot canh trong so canh chua xet dua vao PA neu no khong tao thanh dinh cap va khong tao thanh chu trinh thieu
	//Luc nay i danh o mot gia tri nao do
	for(;i<n*(n-1)/2;i++){
		r_dau = find_root(parent,dscanh[i].u);
		r_cuoi = find_root(parent,dscanh[i].v);
		if(!dinhcap3(PA,n-1,dscanh[i]) && !chu_trinh(r_dau,r_cuoi)){
			PA[n-1]=dscanh[i];//danh sach canh[i] khong tao dinh cap 3, khong tao thanh chu trinh thieu
			break;//Ket thuc vi PA da co du n canh, tao thanh chu trinh
		}
	} 	
}
int main(){
	int n;
	thongtin *dstp = thongtintp(&n);
	cung E;
	in(dstp,n);
	
	Create(&E,n);
	danhsachcung(dstp,&E,n);
	incung(&E,n);
	
	canh dscanh[100];
	doccaccanhchinh(dstp,dscanh,n);
	printf("\ndanh sach canh cua do thi:\n");
	Indanhsachcanhchinh(dscanh,n*(n-1)/2,0);
	printf("\ndanh sach canh cua do thi sau khi SAP XEP:\n");
	bubblesort(dscanh,n*(n-1)/2);
	Indanhsachcanhchinh(dscanh,n*(n-1)/2,0);
	canh PA[n];
	greedy(dscanh,n,PA);
	printf("\nPhuong an:\n");
	Indanhsachcanhchinh(PA,n,1);
	free(dstp);
	return 0;
}
