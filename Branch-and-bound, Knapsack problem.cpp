//背包问题
//分支限界,（广度优先） 
//C++
//Yang Jiangling
//如有错误，请指正 
//输入: weights, values, wtLmt
//输出: the sequence of putting items

/*
1、输入
	——任意数量物品 
2、排序
	——价值质量比与item的序号对应，使用了pair结构和vector容器
	——要对vector排序，使用了sort方法，定义了比较所用的函数 
3、优先对UB高的节点进行扩展
	——使用了优先级队列，定义了比较所用的类（函数） 
	
4、算法 
	——每一次取出UB最高的节点 
		——是否可以扩展出左子节点？ 
			可——左子节点是叶子节点？ 
				是——左子节点可以更新答案？
					是——先更新，然后开始新的循环（右节点不用考虑了） 
				否——UB是否大于LB？ 
					是——更新左子节点信息，加入队列
		——右子节点是否是叶子节点？ 
			是——是否可以更新答案？ 
				是——更新
			否——判断 UB是否大于LB
				是——更新右子节点信息，加入队列
*/
#include<iostream> 
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

struct node
{
	int w;
	int v;
	double uB;
	int layer; //扩展当前节点时，将要考虑的物品序号 
	vector<int> layerList;
	
	node(){	}
	
	node(int _w, int _v, double _uB, int _layer)
	:w(_w), v(_v), uB(_uB), layer(_layer)
	{	}
	
	void operator= (node _node)
	{
		w=_node.w;
		v=_node.v;
		uB=_node.uB;
		layer=_node.layer;
		layerList=_node.layerList;
	}
};

bool compFunc(pair<double, int> left, pair<double, int> right);
class compClass_priQue
{
public:
	bool operator()(node left, node right);
};

int main()
{
	//1、输入
	int weights[]={5,7,3,4};
	int values[]={25,42,12,40};
	int wtLmt=10;
	
	//变量 
	int itemTtlNmb=sizeof(weights)/sizeof(int);
	node resultNode;
	resultNode.v=-1;//lB
	
	//2、价值重量比的排序
	vector<pair<double, int> > rateNsnVector;//价值重量比和原物品序号 
	for(int i=0;i<itemTtlNmb;i++) 
		rateNsnVector.push_back(pair<double, int>(values[i]/1.0/weights[i],i) );
	
	sort(rateNsnVector.begin(),rateNsnVector.end(),compFunc);
	
	for(int i=0;i<itemTtlNmb;i++) 
		cout<<rateNsnVector[i].first<<':'<<rateNsnVector[i].second<<endl;

	//3、使用优先级队列，每次取出uB最高的节点扩展 
	priority_queue<node, vector<node>, compClass_priQue> nodeQueue;
	node curNode(0,0,wtLmt*rateNsnVector[0].first,0);
	nodeQueue.push(curNode);
	
	//cout<<nodeQueue.top()<<endl<<endl;
	//4、 
	while(!nodeQueue.empty())
	{
		node curNode=nodeQueue.top();//非叶子节点 
		nodeQueue.pop();
		
		if(curNode.uB<=resultNode.v)//所有节点都不值得扩展 
			break;
				
		//生成左子节点的条件：在加上item后，重量不超
		int newW=curNode.w+weights[rateNsnVector[curNode.layer].second];
		if(newW<=wtLmt)
		{	
			int newV=curNode.v+values[rateNsnVector[curNode.layer].second];
			if(curNode.layer==itemTtlNmb-1)//如果是叶子节点
			{
				if(newV>resultNode.v)//则比较newV和lB 
				{
					curNode.w=newW;
					curNode.v=newV;
					curNode.layerList.push_back(curNode.layer);
					resultNode=curNode;
					continue; 
				}
			}
			else//不是叶子节点 
			{
				//是否可以添加到队列 
				double newUB= newV+(wtLmt-newW)*rateNsnVector[curNode.layer+1].first;
				if(newUB>resultNode.v)
				{						
					node left= curNode;
					left.w=newW;
					left.v=newV;
					left.layerList.push_back(left.layer);
					left.layer++; 
					left.uB=newUB;
					nodeQueue.push(left);
				}
			}
		}
		
		//右子节点 
		if(curNode.layer==itemTtlNmb-1)//如果是叶子节点
		{
			if(curNode.v>resultNode.v)
				resultNode=curNode;
		}
		else
		{
			curNode.layer++; 
			curNode.uB= curNode.v+(wtLmt-curNode.w)*rateNsnVector[curNode.layer].first;
			if(curNode.uB>resultNode.v)
				nodeQueue.push(curNode);
		}
	}
	
	for(int i=0;i<resultNode.layerList.size();i++)
		cout<<rateNsnVector[resultNode.layerList[i]].second<<endl;
}


bool compFunc(pair<double, int> left, pair<double, int> right)
{
	return left.first>right.first;
}

bool compClass_priQue::operator()(node left, node right)
{
	return left.uB>right.uB;
}
