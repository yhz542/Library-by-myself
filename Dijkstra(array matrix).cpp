#include<vector>
#include<iostream>
#include<algorithm>
#include<set>
#include<forward_list>
using namespace std;
class Graph//采用堆方法，适合稀疏图
{
#define INFINITE 65535//设置的无穷值 用于初始化
	int numOfNode,numOfEdge;//点的数目 与边的数目
	int startNode,destination;//起始点与目的地
	vector<vector<int>> G;//邻接矩阵，适合存储稠密图
	vector<int> pred;//最短路径上，每个点的前一个结点
	vector<int> shortest;//存储起始点到每个点的距离
	int FindMin(vector<int>& index)
	{
		if (0 == index.size())
			return -1;
		int minNodeIndex = 0;
		int minNode;
		for (int nodeIndex = 0 ; nodeIndex <index.size();++nodeIndex)
		{
			int curNode = index[nodeIndex];
			minNode = index[minNodeIndex];
			if (shortest[curNode] < shortest[minNode])
			{
				minNodeIndex = nodeIndex;
			}
		}
		minNode = index[minNodeIndex];
		index[minNodeIndex] = index[index.size() - 1];//将取出的最小距离结点的下标与最后一个元素交换，并将数组规模减1
		index.pop_back();
		return minNode;
	}
public:
	Graph()
	{
		cin >> numOfNode>>numOfEdge;//设置点的个数与边的个数
		cin >> startNode >> destination;//设置起始点与目的地
		shortest.resize(numOfNode, INFINITE);//初始化shortest将所有点到远点的距离设置为无穷
		pred.resize(numOfNode, -1);//初始化，设置所有点的前一个点为-1
		G.resize(numOfNode,vector<int> (numOfNode,INFINITE));//图的初始化
		int node1, node2,lenOfEdge;
		for (size_t i = 0; i < numOfEdge; ++i)//读入边长
		{
			cin >> node1 >> node2 >> lenOfEdge;//读入点1 点2 以及两点间的距离
			G[node1][node2]= lenOfEdge ;//设置距离，这里假设的是有向图，如果是无向图，则反方向也需要设置
		}
	}
	void Dijkstra()
	{
		shortest[startNode] = 0;//设置起始点到自己的距离为0
		vector<int> shortestIndex;
		for (int i = 0; i < numOfNode; ++i)
			shortestIndex.push_back(i);
		int curNode = startNode;
		while (curNode != destination)//点到单点的算法 如果是需要寻找点到所有点的算法需将条件改成shortestIndex.size()
		{
			curNode = FindMin(shortestIndex);//从堆中取出距离远点最近的点
			for (size_t i = 0; i < numOfNode;++i )//遍历当前点的所有边
			{
				if (shortest[curNode] + G[curNode][i] < shortest[i])//如果经过本点到其他点的路径距离可以缩短
				{
					shortest[i] = shortest[curNode] + G[curNode][i];
					pred[i] = curNode;//设置最短路径上其他点的前一个结点为本节点
				}
			}
		}
	}
	void Print()//输出路径
	{
		vector<int> path;
		path.reserve(numOfNode);
		int cur = destination;
		while (cur != -1)//将路径上的点逆序放入path数组中
		{
			path.push_back(cur);
			cur = pred[cur];
		}
		reverse(path.begin(), path.end());//逆转path数组得到正序
		cout << shortest[destination] << endl;//输出起始点到目标点的距离
		for (auto elem : path)//输出
			cout << elem << ' ';
	}
};
int main()
{
	Graph question;
	question.Dijkstra();
	question.Print();
}
/***************
Dijkstra算法思想及步骤
shortest[i]表示从起始点到点i的最短路径,pred[i]表示在这条最短路径上出现在顶点i之前的顶点。
对于起始点s来说，shortest[s]=0,pred[s]=null(这里null用-1代替).如果从起点到i之前没有路径
那么shortest[i] = INFINITE，表示路径长度无穷大,同时pred[i]=null.
步骤:
1.对于除了起点之外的任何顶点i,shortest[i]均被赋值为INFINITE,将shortest[s]设置为0(s代表起点),对于所有点i，设置pred[i]=null
2.让集合Q包含所有点。(这里由于只针对点对点，所以并没有按步骤的方法)
3.只要Q不为空，执行以下操作:
  A.在集合Q中找出shortest最小的点，并将该点从集合中移除
  B.对于每个与A中点相邻接的顶点v,执行Relax操作（即如果从该点到v的距离比shortest[v]更短，就更新)
****************/
