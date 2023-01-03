#include<iostream>
#include<random>
using namespace std;

vector<unsigned> randVec_int(int seed)
{
	// 由于我们希望引擎和分布对象保持状态，因此应该将他们定义为
	// static 的，从而每次调用都生成新的数
	static default_random_engine e(seed);
	static uniform_int_distribution<unsigned> u(1,7);
	vector<unsigned> ret;
	for(size_t i = 0; i<10;i++)
		ret.push_back(u(e));
	return ret;
}
vector<double> randVec_double(int seed)
{
	// 由于我们希望引擎和分布对象保持状态，因此应该将他们定义为
	// static 的，从而每次调用都生成新的数
	static default_random_engine e(seed);
	static uniform_real_distribution<double> u(0,1);
	vector<double> ret;
	for(size_t i = 0; i<10;i++)
		ret.push_back(u(e));
	return ret;
}
int main()
{
	auto a = randVec_int(241);
	for(auto iter=a.begin();iter!=a.end();iter++){
		cout<<*iter<<endl;
	}
	auto b = randVec_double(241);
	for(auto iter=b.begin();iter!=b.end();iter++){
		cout<<*iter<<endl;
	}
	
}
