//八皇后
//回溯法，深度优先，所有结果
//C++
//Yang Jiangling
/*
——第row行第i个位置
	——是否可行？ 
		不可行——考虑第i+1<n位置或者回溯（即没有下一个位置） 
		可行——是否是叶子节点？ 
			是——记录，break即回溯（不用考虑下一个位置） 
			否——考虑下一行 
*/

#include<iostream> 
#include<vector> 
using namespace std;

void func(const int n);
void funcIn(const int n, const int row, int *vec);
void PRINT( const int * const result);

int n=8;
vector<int*> results;

int main()
{
	func(n); 
	
	cout<<"Count of solutions: " <<results.size()<<endl;
	for(int i=0;i<results.size();i++)
	{
		cout<<"%"<<i<<endl;
		PRINT(results[i]);
		cout<<endl;
	}
}

void func(const int n)
{
	int *vec=new int[n];//用于记录各行的位置 
	funcIn(n,0,vec);
}

void funcIn(const int n, const int row, int *vec)//总共n行，考虑第row行，0~row-1行位置的记录 
{
	
	for(int i=0;i<n;i++)//第row行选择第i个位置是否可行？ 
	{
		int j;
		for(j=0;j<row;j++)//将位置i与前面每一行的位置比较 
		{
			if(i==vec[j]||i+(row-j)==vec[j]||i-(row-j)==vec[j])//在同一列和斜线上，break，考虑下一个位置 
				break;
		}
		
		if(j==row)//可行 
		{
			vec[row]=i;//记录 
			if(row==n-1)//是最后一行 
			{
				//记录此结果 
				int *result=new int[n];
				copy(vec,vec+n,result);
				results.push_back(result);
				
				break; 
			}
			else//不是最后一行，考虑下一行 
				funcIn(n,row+1,vec);
		}
	}
}

void PRINT( const int * const result)
{
	for(int i=0;i<n;i++)//row	
	{
		for(int j=0;j<*(result+i);j++)
			cout<<'_';
		cout<<'#';
		for(int j=*(result+i)+1;j<n;j++)
			cout<<'_';
		cout<<endl;
	}
}
