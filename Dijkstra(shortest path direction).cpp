#include<vector>//这里使用的dijkstra方法只适用于稀疏图 ，本方法使用的邻接表以及堆优化
#include<iostream>
#include<algorithm>
#include<set>
#include<queue>
using namespace std;
struct nodeInfo//堆中存放的数据
{
	int node;
	int distance;
	bool operator>(const nodeInfo& other)const
	{
		return this->distance > other.distance;
	}
};
class Graph//采用堆方法，适合稀疏图
{
#define INFINITE 65535//设置的无穷值 用于初始化
	int numOfNode,numOfEdge;//点的数目 与边的数目
	int startNode,destination;//起始点与目的地
	vector<vector<int>> G;//存储边长
	vector<int> pred;//最短路径上，每个点的前一个结点
	vector<int> shortest;//存储起始点到每个点的距离
public:
	Graph()
	{
		cin >> numOfNode>>numOfEdge;//设置点的个数与边的个数
		cin >> startNode >> destination;//设置起始点与目的地
		shortest.resize(numOfNode, INFINITE);//初始化shortest将所有点到远点的距离设置为无穷
		pred.resize(numOfNode, -1);//初始化，设置所有点的前一个点为-1
		G.resize(numOfNode, vector<int>(numOfNode, INFINITE));//初始化，将图里所有的边长设置为无穷
		int node1, node2,lenOfEdge;
		for (size_t i = 0; i < numOfEdge; ++i)//读入边长
		{
			cin >> node1 >> node2 >> lenOfEdge;//读入点1 点2 以及两点间的距离
			G[node1][node2] = lenOfEdge;//设置距离，这里假设的是有向图，如果是无向图，则反方向也需要设置
		}
	}
	void Dijkstra()
	{
		priority_queue<nodeInfo,vector<nodeInfo>,greater<nodeInfo>> heap;
		vector<bool> visited(numOfNode, false);//设置一个数组用于判别当前点是否已经访问过。
		shortest[startNode] = 0;//设置起始点到自己的距离为0
		heap.push({ startNode,shortest[startNode] });//将起始点的数据塞入堆中
		int curNode;
		while (heap.size())//如果堆中无数据则说明已遍历完最短路径上所有可抵达的点
		{
			curNode = heap.top().node;//从堆中取出距离最小的点
			heap.pop();
			if (visited[curNode])//如果当前点已经访问过，且堆中还有其他数据，则直接跳过本次处理继续取点。
				continue;
			visited[curNode] = true;//将取出的点设置为已访问
			for (size_t i = 0; i < numOfNode; ++i)//遍历当前点的所有边
			{
				if (shortest[curNode] + G[curNode][i] < shortest[i])//如果经过本点到其他点的路径距离可以缩短
				{
					shortest[i] = shortest[curNode] + G[curNode][i];//缩短距离
					pred[i] = curNode;//设置最短路径上其他点的前一个结点为本节点
					heap.push({ (int)i,shortest[i] });//将更新后的其他结点数据塞入堆中
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

//优缺点分析
//与一般的数组方法相比的区别
//1.寻找当前未遍历的结点中，距离起始点距离最近的结点的时间复杂度更小，数组法每次遍历采用线性遍历，所以遍历n个结点时间复杂度为O(n^2)，而堆的时间复杂度为(nlogn);
//2.寻找当前未遍历的节点中，距离起始点距离最近的结点的空间复杂度更大，数组法空间复杂度为O(n),而堆的空间复杂度在极端情况可能达到O(m)，如果此时图为稠密图，即m = n^2 则堆的空间复杂度会达到O(n^2)
//3.在更新相邻结点到起始点的最短距离时,数组法只需要更新shortest,不需要其他额外的操作,而堆方法需要将更新后的相邻结点及距离数据加入到堆中。

//总结：只有确定图是稀疏图时才考虑使用堆优化,并且这时候图建议使用邻接表的表示方法。
//如果是稠密图或者更多的未知情况，个人还是更倾向于使用数组法以及邻接矩阵表示法。
