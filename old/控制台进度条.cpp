#include<iostream>
#include<Windows.h>

using namespace std;
int main()
{
	int total = 100;
	for(int i=0;i<=total;i++){
		cout<<"\r"<<(i==100?"已完成":"加载中")<<i<<"%"<<' ';
		for(int j=0;j<=i/10;j++){
			cout<<"█ ";
		}
		Sleep(80);
	}
}

