#include<bits/stdc++.h>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include<fstream>
using namespace std;


vector<int> knapsack(int n, int capacity, const vector<double>& weights, const vector<double>& values) {
	vector<vector<double>> dp(n + 1, vector<double>(capacity + 1, 0));
	vector<vector<bool>> choices(n + 1, vector<bool>(capacity + 1, false));
	
	for(int i = 1; i <= n; ++i){
		for(int w = 1; w <= capacity; ++w){
			if(weights[i - 1] <= w){
				if(values[i - 1] + dp[i - 1][w - weights[i - 1]] > dp[i - 1][w]) {
					dp[i][w] = values[i - 1] + dp[i - 1][w - weights[i - 1]];
					choices[i][w] = true;
				} 
			    else{
					dp[i][w] = dp[i - 1][w];
				}
			} 
			else{
				dp[i][w] = dp[i - 1][w];
			}
		}
	}
	
	// 回溯找出选择的物品
	vector<int> selected_items;
	int w = capacity;
	for (int i = n; i > 0; --i) {
		if (choices[i][w]) {
			selected_items.push_back(i - 1);
			w -= weights[i - 1];
		}
	}
	
	return selected_items;
}

int main() {
	int n = 1000; // 物品数量
	int capacity = 5000; // 背包容量
	//freopen("D:\\算法实验数据.xlsx","w",stdout);
	std::ofstream outFile("D:\\20231120135-吴思奇-数据.xlsx");
	if (!outFile) {
		std::cerr << "无法打开文件！" << std::endl;
		return 1;
	}
	
	outFile<<"以下是随机生成的物品信息："<<'\n';
	// 随机生成物品的重量和价值
	vector<double> weights(n);
	vector<double> values(n);
	srand(time(0));
	for (int i = 0; i < n; ++i) {
		weights[i] = (rand() % 9901 + 100)/100.0;
		values[i] = (rand() % 90001 + 10000)/100.0;
		outFile<<"物品重量"<<'\t'<<weights[i]<<'\t'<<"物品价值"<<'\t'<<values[i]<<'\n';
	}
	
	// 记录开始时间
	auto start_time = chrono::high_resolution_clock::now();
	
	vector<int> selected_items = knapsack(n, capacity, weights, values);
	
	// 记录结束时间
	auto end_time = chrono::high_resolution_clock::now();
	
	// 计算执行时间
	auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
	
	// 输出选择的物品信息
	outFile << "选择的物品信息："<<'\n';
	outFile << fixed << setprecision(2);
	double total_value = 0;
	for (int item : selected_items) {
		outFile <<"物品编号: "<<'\t'<< item + 1 <<'\t'<<" 重量: "<<'\t'<< weights[item] <<'\t'<<" 价值: "<<'\t'<< values[item]<<'\n';
		total_value += values[item];
	}
	outFile <<"物品装入背包获得的总价值: "<<'\t'<< total_value <<'\n';
	
	// 输出程序执行时间
	outFile<<"程序总的执行时间: "<<'\t'<< duration << " ms" << endl;
	
	return 0;
}
