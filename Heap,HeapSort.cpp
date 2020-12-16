//堆，堆排序
//C++
//Yang Jiangling

/*
大根堆：每一个节点大于其左右子树节点 
 
1、构造堆结构
	——从最后一个非叶子节点到根节点，对每一个非叶子节点cur，进行A操作 

2、A操作
	——条件：左右子树分别是堆结构
	——比较左右子节点哪一个大，假设是LorR节点
	——比较LorR节点和cur节点的大小
		后者大——则cur为根的子树已经是一个堆
		前者大——交换cur和LorR的值（此时cur节点已经比左右子节点都大，
					但是被交换的那个子节点所代表的树可能不再是堆，
					所以对这个节点进行A操作。如此往复直到叶子节点。）
					
3、堆排序
 	——堆是存在数组中的。
	——大根堆对应从小到大排序 
	——将根节点（数组位置0）与最后一个叶子节点（数组位置i）互换值，
			此时根节点需要进行A操作，使得树重新满足堆定义，树的节点个数为i 
*/
#include<iostream>

using namespace std;

void makeHeap(int arr[],int n);
void heapSort(int *arr,int n);
void funcA(int arr[],int n,int cur);

int main() 
{
	int arr[]={13,56,76,23,67,98,3,46,82,44};
	int n=sizeof(arr)/sizeof(int);
	for(int i=0;i<n;i++) 
		cout<<arr[i]<<' ';
	cout<<endl;
	
	makeHeap(arr,n);
	for(int i=0;i<n;i++) 
		cout<<arr[i]<<' ';
	cout<<endl;
	
	heapSort(arr,n);
	for(int i=0;i<n;i++) 
		cout<<arr[i]<<' ';
	cout<<endl;
}

void makeHeap(int arr[],int n)
{
	for(int i=(n-2)/2;i>=0;i--)
		funcA(arr,n,i);
}

void heapSort(int *arr,int n)
{
	for(int i=n-1;i>=1;i--)
	{
		int temp=arr[i];
		arr[i]=arr[0];
		arr[0]=temp;
		
		funcA(arr,i,0);
	}
}

void funcA(int arr[],int n,int cur)
{
	if(n<=1)
		return;
	
	if(cur>(n-2)/2) //如果是叶子节点，直接结束 
		return;
	
	int leftORright=cur*2+1;//left
	if(cur*2+2<n && arr[cur*2+2]>arr[leftORright] )//右节点存在，并且比左节点大 
		leftORright=cur*2+2; 
	
	if(arr[cur]<arr[leftORright])
	{
		int temp=arr[cur];
		arr[cur]=arr[leftORright];
		arr[leftORright]=temp;
		
		if(leftORright<=(n-2)/2) 
			funcA(arr,n,leftORright);
	}
}



