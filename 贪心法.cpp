#include<bits/stdc++.h>
using namespace std;

struct Item {
	double weight,value;
	double ratio; //价值-重量比
};

int n=40; //物品个数

// 比较函数，用于按价值-重量比降序排序
bool cmp(Item a, Item b) {
	return a.ratio > b.ratio;
}

// 贪心算法解决 0 - 1 背包问题
vector<int> greedyKnapsack(const vector<Item>& items, int capacity) {
	int n = items.size();
	vector<int> solution(n, 0);
	vector<Item> sortedItems = items;
	
	// 计算每个物品的价值-重量比
	for (int i = 0; i < n; ++i) {
		sortedItems[i].ratio = (double)sortedItems[i].value / sortedItems[i].weight;
	}
	
	// 按价值-重量比 降序排序
	sort(sortedItems.begin(), sortedItems.end(), cmp);
	
	double currentWeight = 0;
	for (int i = 0; i < n; ++i) {
		if (currentWeight + sortedItems[i].weight <= capacity) {
			solution[i] = 1;
			currentWeight += sortedItems[i].weight;
		}
	}
	
	return solution;
}

int main() {
	vector<Item> items;
	srand(time(0));
	for(int i=0;i<n;i++){
		double a = (rand() % 9901 + 100)/100.0;
		double b = (rand() % 90001 + 10000)/100.0;
		items.push_back({a,b});
	}
	int capacity = 20*n;
	
	// 记录开始时间
	auto start_time = chrono::high_resolution_clock::now();
	
	vector<int> solution = greedyKnapsack(items, capacity);
	
	// 记录结束时间
	auto end_time = chrono::high_resolution_clock::now();
	
	// 计算执行时间
	auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
	
	double totalValue = 0;
	
	cout << "选中的物品信息如下：" << endl;
	cout << "编号\t重量\t价值" << endl;
	for (int i = 0; i < solution.size(); ++i) {
		if (solution[i] == 1) {
			cout << i << "\t" << items[i].weight << "\t" << items[i].value << endl;
			totalValue += items[i].value;
		}
	}
	
	cout << "最终总价值: " << totalValue << endl;
	
	// 输出程序执行时间
	cout<<"程序总的执行时间: "<<'\t'<< duration << " ms" << endl;
	
	return 0;
}
