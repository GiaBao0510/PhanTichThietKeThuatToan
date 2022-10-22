// Goi L[i]: la do dai day con tang co duoc tu day a1,a2,...,ai
//Nhu vay L[n] se la do dai con tang co duoc tu day a1,a2,...,an
//De cho L[n] lon nhat thi L[i] phai lon nhat voi moi i tu 1 den n
//Ta dung mang T de luu vet cac phan tu tao nen day con tang: T[i] la chi so cua phan tu dung truoc phan tu i
/*-------Cong thuc truy hoi------*/
	//1.khi day chi co mot phan tu thi L[1]=1 va "Dung truoc" phan tu do chinh la no do do T[1]=1
	//2.Ta dang cet phan tu ai de co the xay dung mot day con tang den ai dai nhat.Trong cac day con tang den aj dung truoc ai, ta tim 1 ajmax <= ai ma L[jmax] lon nhat.Khi do L[i] = L[jmax]+1 va T[i] = jamx
	// => L[1]=1, T[1]=1
	//=> L[i] = 1 + max{ L[j] } voi moi j tu 1 den i-1
	//Gia su L[jmax] la gia tri lon nhat, thi ajmax la phan tu dung truoc ai nen T[i]=jmax
#include<stdio.h>
#include<malloc.h>
typedef struct{
	int CS,		//chi so
		GT;		//Gia tri
}phantu;
int * readformfileDaySo(int *n){
	FILE *f=fopen("DaySo.txt","r");
	int *A=(int*)malloc(sizeof(int));//Cap phat cho A mot o phan tu
	int i=0;
	while(!feof(f)){
		fscanf(f,"%d",&A[i]);
		i++;
		A=realloc(A,sizeof(int)*(i+1));//Tai cap phat voi so luong la 2 o
	}
	*n=i;//so phan tu trong mang A
	fclose(f);
	return A;//Tra ve mang dong da duoc doc tu file
}
void Tao_Bang(int a[],int n,int L[],int T[]){
	int i,j
		,Ljmax	//Dung de luu tru gia tri lon nhat
		,jmax;	//Dung de luu tru chi so lon nhat tuong ung Lj
	//=>L[1]=1, T[1]=1
	L[0]=1;//Do dai cua mang con tang dai nhat tu a0 den a0 la bang 1
	T[0]=0;//Phan tu dung truoc a0 la bang 0
	
	for(i=1;i<n;i++){
		Ljmax=0;
		jmax=i;
		for(j=0;j<i;j++){
			if(a[j]<=a[i] && Ljmax<L[j]){
				//Cap nhat lai
				Ljmax=L[j];
				jmax=j;
			}
		}
		//Sau khi vong lap J ket thuc ta da xac dinh duoc gia tri
		L[i]=Ljmax+1;
		T[i]=jmax;
	}	
}
void In_so_lieu(int a[],int L[],int T[],int n){
	int i;
	printf("Day so da cho:\n");
	printf("Chi so:");
	for(i=0;i<n;i++){
		printf(" %d",i);
	}
	printf("\nGia tri:");
	for(i=0;i<n;i++){
		printf(" %d",a[i]);
	}
	printf("\nBang Chieu dai cac day con don dieu tang \n");
	for(i=0;i<n;i++){
		printf(" %d",L[i]);
	}
	printf("\nBang luu vet cua cac chi so:\n");
	for(i=0;i<n;i++){
		printf(" %d",T[i]);
	}
}
int Max_lenght(int L[],int n,int *maxindex){
	int max=L[0];
	*maxindex=0;
	int i;
	for(i=1;i<n;i++){
		if(max<L[i]){
			max=L[i];
			*maxindex=i;
		}
	}
	return max;//tra va gia tri lon nhat trong mang L
}
void Tra_Bang(int a[],int L[],int T[],int n,phantu PA[],int *m){
	int i,maxindex;
	*m=Max_lenght(L,n,&maxindex);//Se cho chung ta gia tri lon nhat va phan tu lon nhat do chinh la do dai cua dai con tang dai nhat so phan tu cua phuong an
	//maxindex xac dinh duoc chi so cua phan tu cuoi cung trong day con tang dai nhat
	for(i=*m-1;i>0;i--){
		PA[i].CS=maxindex;
		PA[i].GT=a[maxindex];
		maxindex=T[maxindex];
	}
	PA[0].CS=maxindex;
	PA[0].GT=a[maxindex];
}
void In_PA(phantu PA[],int m){
	printf("\nKet qua: day con tang dai nhat la:\n");
	printf("chi so:");
	int i;
	for(i=0;i<m;i++){
		printf(" %d",PA[i].CS);
	}
	printf("\nGia tri:");
	for(i=0;i<m;i++){
		printf(" %d",PA[i].GT);
	}
	printf("\nSo phan tu cua day tang dai nhat la %d",m);
}
int main(){
	int n
		,m 		//Dung de luu tru do dai cua day con tang lon nhat
		,*a=readformfileDaySo(&n);
	int L[n], //La luu tru do dai cua cac day con tang
		T[n]; //Dung de luu tru chi so cua cac phan tu dung truoc phan tu do
	phantu PA[n]; //la phuong an luu tru day con tang dai nhat
	Tao_Bang(a,n,L,T);
	Tra_Bang(a,L,T,n,PA,&m);
	In_so_lieu(a,L,T,n);
	In_PA(PA,m);
	free(a);
	return 0;
}	
