#include<bits/stdc++.h>
using namespace std;

struct Item {
	double weight,value;
};

int n=20;//物品个数


vector<int> bruteForce(const vector<Item>& items, int capacity) {
	int n = items.size();
	double maxValue = 0;
	vector<int> bestSolution;
	
	// 遍历所有可能的物品组合
	for (int i = 0; i < (1 << n); ++i) {
		int currentWeight = 0;
		int currentValue = 0;
		vector<int> currentSolution(n, 0);
		
		// 检查每一位对应的物品是否被选中
		for (int j = 0; j < n; ++j) {
			if ((i & (1 << j)) != 0) {
				currentWeight += items[j].weight;
				currentValue += items[j].value;
				currentSolution[j] = 1;
			}
		}
		
		// 如果当前组合的重量不超过背包容量且价值更高，则更新最优解
		if (currentWeight <= capacity && currentValue > maxValue) {
			maxValue = currentValue;
			bestSolution = currentSolution;
		}
	}
	
	return bestSolution;
}

int main() {
	vector<Item> items;
	srand(time(0));
	for(int i=0;i<n;i++){
		double a = (rand() % 9901 + 100)/100.0;
		double b = (rand() % 90001 + 10000)/100.0;
		items.push_back({a,b});
	}
	int capacity = 40*n;
	
	// 记录开始时间
	auto start_time = chrono::high_resolution_clock::now();
	
	vector<int> solution = bruteForce(items, capacity);
	
	// 记录结束时间
	auto end_time = chrono::high_resolution_clock::now();
	// 计算执行时间
	auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
	
	double totalValue =0;
	
	cout<< "选中的物品信息如下：" << endl;
	cout<< "编号\t重量\t价值" << endl;
	for (int i = 0; i < solution.size(); ++i) {
		if (solution[i] == 1) {
			cout << i << "\t" << items[i].weight << "\t" << items[i].value << endl;
			totalValue += items[i].value;
		}
	}
	
	cout<<"最终总价值: "<< totalValue << endl;
	cout<<"程序总的执行时间: "<< duration << " ms" << endl;
	
	return 0;
}
