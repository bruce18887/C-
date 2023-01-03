#include <iostream>
using namespace std;
int main()
{
	int num1;
	cout<<"please enter num1:"<<endl;
	cin>>num1;
	int num2;
	cout<<"please enter num2:"<<endl;
	cin>>num2;
	char way;
	cout<<"please enter calcway:"<<endl;
	cin>>way;
	
	auto Calc_Lambda = [num1,num2](char calcinput)->int{
		if(calcinput=='+'){
			return num1+num2;
		}
		else if(calcinput=='-'){
			return num1-num2;
		}
		else if(calcinput=='*'){
			return num1*num2;
		}
		else{
			return num1/num2;
		}
		
	};
	cout<<Calc_Lambda(way)<<endl;
		cout<<Calc_Lambda(way)<<endl;
}
