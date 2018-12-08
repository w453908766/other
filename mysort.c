




///////////////////////////////////////////////////////////////
void csbsort(int* arr,int n){		//n^3
	if(n>1){
		csbsort(arr+1,n-1);
		if(arr[0]>arr[1]){
			swap(arr,arr+1);
			csbsort(arr+1,n-1);
		}
	}
}

void quiffsort(int* arr,int n){		//n^2
	if(n>1){
		condswap(arr,arr+1);
		quiffsort(arr+1,n-1);
		if(arr[0]>arr[1])quiffsort(arr,n-1);
	}
}
void quiffsort2(int* arr,int n){		//n^2
	if(n>1){
		condswap(arr,arr+1);
		quiffsort2(arr+1,n-1);
		if(condswap(arr,arr+1))quiffsort2(arr+1,n-1);
	}
}
void ccsort(int* arr,int n){				//catch chicken		T(n)=T(n-1)+2T(n/2)+1
	if(n==2)condswap(arr,arr+1);
	else{
		ccsort(arr,n/2+1);
		ccsort(arr+n/2,n-n/2);
		ccsort(arr,n-1);
	}
}

void ccsort2(int* arr,int n){				//catch chicken		T(n)=n*n*logn
	if(n==2)condswap(arr,arr+1);
	else{
		ccsort2(arr,n/2+1);
		ccsort2(arr+n/2,n-n/2);
		if(arr[n/2-1]>arr[n/2])ccsort2(arr,n-1);
	}
}



void busort2(int* arr,int n){				//T(n)=T(n-1)+2T(n/2)+1
	if(n==2)condswap(arr,arr+1);
	else{

		busort2(arr,n/2+1);
		busort2(arr+n/2,n-n/2);
		if(arr[n/2-1]>arr[n/2])busort2(arr,n-1);
	}
}

void mastersort(int* arr,int n){			//?
	if(n>1){
		mastersort(arr+1,n-1);
		if(arr[0]>arr[1]){
			condswap(arr,arr+n/2);
			mastersort(arr,n/2);
			mastersort(arr+n/2,n-n/2);
		}
	}
}
void mastersort2(int* arr,int n){			//?
	if(n>1){
		mastersort2(arr+1,n-1);
		if(arr[0]>arr[1]){
			mastersort2(arr,n/2+1);
			mastersort2(arr+n/2,n-n/2);
		}
	}
}

void cdsort(int* arr,int n){				//T(n)=T(n-1)+2T(n/2)+1  ?
	if(n>1){
		cdsort(arr+1,n-1);
		if(arr[0]<=arr[n/2])cdsort(arr,n/2);
		else{
			swap(arr,arr+n/2);
			cdsort(arr,n/2);
			cdsort(arr+n/2,n-n/2);
		}
	}
}

void cusort(int* arr,int n){				//?
	if(n>1){
	
		if(arr[0]<=arr[n/2])cusort(arr,n/2);
		else{
			swap(arr,arr+n/2);
			cusort(arr,n/2);
			cusort(arr+n/2,n-n/2);
		}
		cusort(arr+1,n-1);
	}
}

/**/
void stoogesort(int* arr,int n){
	if(n==2)condswap(arr,arr+1);
	else{
		stoogesort(arr,n-n/3);
		stoogesort(arr+n/3,n-n/3);
		if(arr[n/3-1]>arr[n/3])stoogesort(arr,n-n/3);
	}
}
void shellsort(int* arr,int n,int k){			//T(n)=T(n-1)+2T(n/2)+1
	if(n>1){
		shellsort(arr,n-n/2,2*k);
		shellsort(arr+k,n/2,2*k);
		condswap(arr,arr+k);
		shellsort(arr+1,n-1,k);
	}
}

void sbsort(int* arr,int n){
	int i,j;
	for(i=0;i<n;i++)
		for(j=0;j<i;j++)
			condswap(arr+j,arr+i);
}
void mrrightsort(int* arr,int n){
	if(n>1){
		condswap(arr,arr+1);
		mrrightsort(arr+1,n-1);
		if(arr[0]>arr[1])mrrightsort(arr,n-1);
	}
}


