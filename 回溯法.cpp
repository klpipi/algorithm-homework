#include <bits/stdc++.h>
using namespace std;

const int n=20;//物品个数
double maxValue = 0; //最大价值
int capacity = 20*n; //背包容量

vector<int> chose; //是否选取了物品

void backtrack(const vector<double>& weights, const vector<double>& values,vector<int>currentchose,int index, int currentWeight, double currentValue) {
	// 如果已经遍历完所有物品
	if(index==weights.size()){
		// 更新最大价值
		if(currentValue>maxValue){
			maxValue=currentValue;
			for(int i=0;i<n;i++){
				chose[i]=currentchose[i];
			}
		}
		return;
	}
	
	// 不选当前物品
	backtrack(weights,values,currentchose,index+1,currentWeight,currentValue);
	
	// 选择当前物品
	if (currentWeight+weights[index]<=capacity) {
		currentchose[index]=1;
		backtrack(weights,values,currentchose,index+1,currentWeight + weights[index],currentValue+values[index]);
	}
}


double knapsack(const vector<double>& weights, const vector<double>& values,vector<int> cur) {
	backtrack(weights, values,cur,0, 0, 0);
	return maxValue;
}

int main() {
	vector<double> weights,values;
	chose.resize(n);
	vector<int> currentchose(n,0);
	
	srand(time(0));
	for(int i=0;i<n;i++){ //随机生成物品重量和价值
		double a = (rand() % 9901 + 100)/100.0;
		double b = (rand() % 90001 + 10000)/100.0;
		weights.push_back(a);
		values.push_back(b);
	}
	
	// 记录开始时间
	auto start_time = chrono::high_resolution_clock::now();
	
	double result = knapsack(weights, values,currentchose);
	
	// 记录结束时间
	auto end_time = chrono::high_resolution_clock::now();
	// 计算执行时间
	auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
	
	cout<< "选中的物品信息如下：" << endl;
	cout<< "编号\t重量\t价值" << endl;
	for (int i = 0; i < n; ++i) {
		if (chose[i]) {
			cout << i <<"\t"<<weights[i]<<"\t"<<values[i]<< endl;
		}
	}
	cout << "最大价值是: " << result << endl;
	
	cout<<"程序总的执行时间: "<< duration << " ms" << endl;
	
	return 0;
}
