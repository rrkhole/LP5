#include<stdio.h>
#include<omp.h>

void swap(int *x,int *y){
int temp=*x;
*x=*y;
*y=temp;
}
void exchangeMax(int array[],int id){

if(array[id+1]<array[id]){
swap(&array[id+1],&array[id]);
}

}
void exchangeMin(int array[],int id){

if(array[id-1]>array[id]){
swap(&array[id-1],&array[id]);
}

}

/*void bubbleSort(int array[],int n)
{
#pragma omp parallel sections num_threads(n)
{
#pragma omp section
{
int id=omp_get_thread_num();
for(int i=1;i<=n;i++)
{
if(i%2){
if(id%2 && id+1<n)exchangeMin(array,id+1);
else if(id%2==0 && id-1>=0)exchangeMax(array,id-1);
}
else{
if(id%2 && id-1>=0)exchangeMax(array,id-1);
else if(id%2==0 && id+1<n)exchangeMin(array,id+1);
}
}
}
}
}*/
void SerialBubbleSort(int *a,int n){
	
	for(int i=0;i<n;i++){
		for(int j=0;j<n-1;j++){
			int flag=0;
			if(a[j]>a[j+1]){
				int temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
				flag=1;
			}
			if(flag==0)return;
			n--;
		}
	}
}
void odd_even_sort_openmp_method1(int* a, int n)
{
  /* 
     Method 1: Use 2 "parallel for" directives
  */
  int phase, i, temp;
  for(phase=0;phase<n;++phase)
  {
    if(phase%2==0) //even phase
    {
#pragma omp parallel for num_threads(n) default(none) shared(a,n) private(i,temp)
      for(i=1;i<n;i+=2)
	if(a[i-1] > a[i])
	{
	  temp = a[i];
	  a[i] = a[i-1];
	  a[i-1] = temp;
	}
    }
    else //odd phase
    {
#pragma omp parallel for num_threads(n) default(none) shared(a,n) private(i,temp)
      for(i=1;i<n-1;i+=2)
	if(a[i] > a[i+1])
	{
      	  temp = a[i];
	  a[i] = a[i+1];
	  a[i+1] = temp;
	}
    }
  }
}

int main()
{
	int array[50];
	int i,size;
	printf("Enter total no. of elements:\n");
	scanf("%d",&size);
	printf("Enter %d elements:\n",size);
	for(i=0; i<size; i++)
	{
	   scanf("%d",&array[i]);
	}
	double start=omp_get_wtime();
	odd_even_sort_openmp_method1(array,size);
	double end=omp_get_wtime();
	double t=end-start;
	printf("Time for parallel bubble sort is %f\n",t*1000);
	
	for(i=0; i<size; i++)
	    printf("%d ",array[i]);
	printf("\n");
	int array2[50];
	for(int i=0;i<size;i++){
		array2[i]=array[i];
	}
	start=omp_get_wtime();
	SerialBubbleSort(array2,size);
	end=omp_get_wtime();
	t=end-start;
	printf("Time for serial bubble sort is %f\n",t*1000);
	printf("Sorted Elements as follows:\n");
	for(i=0; i<size; i++)
	    printf("%d ",array2[i]);
	printf("\n");
	return 0;
}
