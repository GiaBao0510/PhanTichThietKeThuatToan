#include<stdio.h>
#include<malloc.h>
typedef int keytype;		//Quy dinh keytype la kieu so nguyen
typedef float othertype;	//Quy dinh othertype la kieu so thuc
typedef struct{
	keytype key;
	othertype otherfields;
}recordtype;
	/*********************Ham hoan doi vi tri hoac gia tri cua cac cau truc******************/
void swap(recordtype *A,recordtype *B){		
	recordtype temp;
    //hoan doi gia tri hoac vi tri cua hai cau truc
	temp = *A;
	*A=*B;
	*B=temp;
}
	/**********************Ham doc du lieu tu tep(Read from file):**************************/
void Readfromfile(recordtype A[],int *n){
	int i=0;
	FILE *f=fopen("DataText.txt","r");
	if(f!=NULL){
		while(!feof(f)){			//Kiem tra da den cuoi tap tin chua.Neu chua thi tiep tuc duyet
			fscanf(f,"%d%f",&A[i].key,&A[i].otherfields);
			i++;
		}
	}else printf("@@@ Loi mo tep @@@");
	fclose(f);	//Dong tep
	*n=i;		//Gan cho con tro  *n = i;
}
	/***********************Ham doc du lieu (Read):**************************/
void Read(recordtype A[],int *n){
	int i;
	for(i=0;i<*n;i++){
		printf("Nhap gia tri [%d]: ",i);scanf("%d",&A[i].key);
		printf("Nhap gia tri khac [%d]: ",i);scanf("%f",&A[i].otherfields);
	}
}
	/***********************Ham doc du lieu tu tep.Su dung mang Dong (ReadFromFile):**************************/
recordtype * ReadFromFile(int *n){
	int i=0;
	FILE *f=fopen("DataText.txt","r");
	recordtype *a;
	a=(recordtype*)malloc(sizeof(recordtype));			//Ban dau cap phat bo nho cua mang la 1
	if(f!=NULL){
		while(!feof(f)){								//Kiem tra da den cuoi tap tin chua.Neu chua thi tiep tuc duyet
			fscanf(f,"%d%f",&a[i].key,&a[i].otherfields);
			i++;
			a=realloc(a,sizeof(recordtype)*(i+1));		//Cap phat lai bo nho tang kich co cua bo nho
		}
	}else printf("@@@ Loi mo tep @@@");
	fclose(f);	//Dong tep
	*n=i;		//Gan cho con tro  *n = i;
	return a;
}	
	/************************In du lieu da duoc nhap ra man hinh********************/ 		
void Print(recordtype A[],int n){
	int i;
	printf("STT\tKeytype:\tOthertype:\n");
	for(i=0;i<n;i++){
		printf("%d\t%d\t-\t%.2f\n",i,A[i].key,A[i].otherfields);
	}
}						
/*----------------------Sap xep lua chon( Sort selection )---------------------*/
//(Tang dan) :
void sortselection1(recordtype a[],int n){
	int i,j,lowindex;
	keytype lowkey;
	for(i=0;i<=n-2;i++){
		lowkey=a[i].key; 		//Gan cho lowkey = gia tri dau tien cua a[i]
		lowindex=i;				//Gan cho lowindex = chi so dau tien cua a[i]
		for(j=i+1;j<=n-1;j++){
			if(a[j].key<lowkey){
				lowkey=a[j].key;
				lowindex=j;
			}
		}
		swap(&a[i],&a[lowindex]);
	}
}
//(Giam dan) :
void sortselection2(recordtype a[],int n){
	int i,j,lowindex;
	keytype lowkey;
	for(i=0;i<=n-2;i++){
		lowkey=a[i].key; 		//Gan cho lowkey = gia tri dau tien cua a[i]
		lowindex=i;				//Gan cho lowindex = chi so dau tien cua a[i]
		for(j=i+1;j<=n-1;j++){
			if(a[j].key>lowkey){
				lowkey=a[j].key;
				lowindex=j;
			}
		}
		swap(&a[i],&a[lowindex]);
	}
}
/*--------------------------Sap xep xen(Insertion sort)-------------------------*/
//(Tang dan):
void Insertionsort1(recordtype a[],int n){
	int i,j;
	for(i=1;i<n;i++){
		j=i;									//Gan j = i
		while((j>0)&&(a[j].key<a[j-1].key)){	//Neu j>0 va gia tri cua a[j] < gia tri cua a[j-1]
			swap(&a[j],&a[j-1]);				//Doi cho cho 2 cau truc
			j--;								//Moi lan dung theo dieu kien thi giam j di 1 don vi
		}
	}
}
//(Giam dan):
void Insertionsort2(recordtype a[],int n){
	int i,j;
	for(i=1;i<n;i++){
		j=i;									//Gan j = i
		while((j>0)&&(a[j].key>a[j-1].key)){	//Neu j>0 va gia tri cua a[j] > gia tri cua a[j-1]
			swap(&a[j],&a[j-1]);				//Doi cho cho 2 cau truc
			j--;								//Moi lan dung theo dieu kien thi giam j di 1 don vi
		}
	}
}
/*--------------------------Sap xep noi bot(Bubble sort)-------------------------*/
void Bubblesort(recordtype a[],int n){
	int i,j;
	for(i=0;i<=n-2;i++){
		for(j=n-1;j>=i+1;j--){
			if(a[j].key<a[j-1].key){
				swap(&a[j],&a[j-1]);
			}
		}
	}
}
/*--------------------------Sap xep nhanh chong(Quick sort)-------------------------*/
//Phuong phap chon chot(Find pivot):
int FindPivot(recordtype a[],int i,int j){
	keytype firstkey;
	int k=i+1;			//Gan cho chi so cua K lon hon i mot don vi
	firstkey=a[i].key;	//Gan cho FirstKey = gia tri dau tien
	while((k<=j)&&(a[k].key==firstkey)){//Neu K <= J va gia tri tai vi tri K bang nhau voi FirstKey thi K tang len 1 don vi 
		k++;
	}
	if(k>j){							//Truong hop cac phan tu co khoa bang nhau thi khong co chot
		return -1;
	}
	else{
		if(a[k].key>firstkey){			//So sanh de tim chot tinh tu trai qua phai
			return k;
		}
		else{
			return i;
		}
	}
}
//phuong phap phan hoach(Partition):
int Partition(recordtype a[],int i,int j,keytype pivot){
	int L,R;
	L=i;		//Cho L chay tu trai sang phai 
	R=j;		//Cho R chay tu phai sang trai 
	while(L<=R){
		while(a[L].key<pivot){L++; }	//cho den khi L co khoa >= chot.Thi dung
		while(a[R].key>=pivot){R--; }	//cho den khi R co khoa < chot.Thi dung
		if(L<R){						//Neu chi so phan tu cua L < R thi hoan doi vi tri cua cau truc
			swap(&a[L],&a[R]);
		}
	}
	return L; //L gio da la diem phan hoach, khoa a[L].key la gia tri dau tien ben mang ben phai
}
//Ham Quick sort
void QuickSort(recordtype a[],int i,int j){
	keytype pivot;	
	int pivotindex,k;	
	pivotindex= FindPivot(a,i,j);	//Luu tru chi so cua chot
	if(pivotindex!=-1){
		pivot=a[pivotindex].key;		//Luu tru gia tri cua chot
		k=Partition(a,i,j,pivot);	//Luu tru phan tu dau tien mang con ben phai
		QuickSort(a,i,k-1);	//Mang con ben trai
		QuickSort(a,k,j);	//Mang con ben phai
	}
}
/*--------------------------Sap xep vun dong(Heap sort)-------------------------*/
//Ham Pushdown
void pushdown(recordtype a[],int first,int last){
	int r=first;						//Dat R la gia tri dau
	while(r<=(last-1)/2){				//Neu R >((last-1)/2) thi thoat khoi vong lap
		//1.Truong hop co mot co trai
		if(last==2*r+1){				//Neu chi so cua Last bang			
			if(a[r].key>a[last].key){	//So sanh khoa va khoa cua nut la
				swap(&a[r],&a[last]);
			}
			r=last;
		}
		//2.Neu khoa cua R > con trai va con trai cua R < con phai cua R,thi doi vi tri cua R cho con trai
		else 
			if((a[r].key>a[2*r+1].key)&&(a[2*r+1].key<=a[2*r+2].key)){
				swap(&a[r],&a[2*r+1]);
				r=2*r+1;		//Dat la R bang vi tri cua con trai de tiep tuc xet
			}
		//3.Neu khoa cua R > con phai va con phai cua R < con trai cua R,thi doi vi tri cua R cho con phai	
		else 
			if((a[r].key>a[2*r+2].key)&&(a[2*r+2].key<a[2*r+1].key)){
				swap(&a[r],&a[2*r+2]);
				r=2*r+2;		//Dat la R bang vi tri cua con trai de tiep tuc xet
			}
		//Neu con trai va con phai bang nhau thi thuong uu tien ve ben con trai	
		else r=last;		
	}
}
//Ham Heap sort
void Heapsort(recordtype a[],int n){
	int i;
	//Tao Heap
	for(i=(n-2)/2;i>=0;i--){
		pushdown(a,i,n-1);		//Sap xep lai cac nut gan nut la
	}
	//Sap xep
	for(i=n-1;i>=2;i--){
		swap(&a[0],&a[i]);
		pushdown(a,0,i-1);
	}
	swap(&a[0],&a[1]);
}
/*--------------------------Sap xep Hop nhat(Merge sort)-------------------------*/
void merge(recordtype a[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    /* Tao các mang tam */
    int L[n1], R[n2];
 
    /* Copy du lieu sang các mang tam */
    for (i = 0; i < n1; i++)
        L[i] = a[l + i].key;
    for (j = 0; j < n2; j++)
        R[j] = a[m + 1+ j].key;
 
    /* Gop hai mang tam vua roi vào mang A*/
    i = 0; // Khoi tao chi so bat dau caa mang con dau tiên
    j = 0; // Khoi tao chi so bat dau cua mang con thu hai
    k = l; // IKhai tao chi so bat dau cua mang luu ket qua
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            a[k].key = L[i];
            i++;
        }
        else
        {
            a[k].key = R[j];
            j++;
        }
        k++;
    }
 
    /* Copy các phan tu con lai cua mang L vào A neu có */
    while (i < n1)
    {
        a[k].key = L[i];
        i++;
        k++;
    }
 
    /* Copy các phan tu con lai cua mang R vào  A neu có */
    while (j < n2)
    {
        a[k].key = R[j];
        j++;
        k++;
    }
}
 
/* L là chi so trái và r là chi so phai cua mang can duoc sap xep */
void mergeSort(recordtype a[], int l, int r)
{
    if (l < r)
    {	// Tuong tu (l+r)/2, nhung cách này tránh tràn so khi l và r lon
        int m = l+(r-l)/2;
        // Goi hàm de quy ti?p tuc chia dôi tung nua mang
        mergeSort(a, l, m);
        mergeSort(a, m+1, r);
 
        merge(a, l, m, r);
    }
}

