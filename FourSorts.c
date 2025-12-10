#include<stdio.h>
void bubblesort(int *a,int len){
	int temp;
	for(int i=0;i<len-1;i++){
		for(int j=0;j<len-1-i;j++){
			if(a[j]>a[j+1]){
				temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
			}
		}
	}
	for(int i=0;i<len;i++){
		printf("%d",a[i]);
	}
}
void choosesort1(int *a,int len){

	for(int i=0;i<len-1;i++){
		int min=a[i];
		int minspace=i;
		for(int j=i+1;j<len;j++){
			if(a[j]<min){
				min=a[j];
				minspace=j;
			}
			if(minspace!=i){
				for(int k=i;k<j;k++){
					a[k+1]=a[k];
				}
				a[i]=min;
			}
		}
	}
	for(int i=0;i<len;i++){
		printf("%d",a[i]);
	}
	


}
void choosesort2(int *a,int len){
	for(int i=0;i<len-1;i++){
		int temp;
		int minspace=i;
		int min=a[i];
		for(int j=i+1;j<len;j++){
			if(a[j]<min){
				min=a[j];
				minspace=j;
			}
			
		}
		if(minspace!=i){
			temp=a[i];
			a[i]=a[minspace];
			a[minspace]=temp;
		}
	}
	for(int i=0;i<len;i++){
		printf("%d",a[i]);
	}
	
	
}
void insertsort(int *a,int len){
	for(int i=1;i<len;i++){
		for(int j=i;j>0;j--){
			if(a[j]<a[j-1]){
				int temp=a[j];
				a[j]=a[j-1];
				a[j-1]=temp;
			}
		}
	}
	for(int i=0;i<len;i++){
		printf("%d",a[i]);
	}
	
}
int main(){
	int arr[13]={1,1,4,5,1,4,1,9,1,9,8,1,0};
	printf("bubblesort:\n");
	bubblesort(arr,13);
	printf("\n\n");
	printf("choosesort1:\n");
	choosesort1(arr,13);
	printf("\n\n");
	printf("choosesort2:\n");
	choosesort2(arr,13);
	printf("\n\n");
	printf("insertsort:\n");
	insertsort(arr,13);
	return 0;
}
