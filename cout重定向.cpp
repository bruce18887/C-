#include<iostream>
#include<fstream>
using namespace std;


int main()
{
	auto coutbuffer = cout.rdbuf();
	ofstream of("out.log");
	auto filebuffer = of.rdbuf();
	
	cout.rdbuf(filebuffer);
	
	cout<<"hello world"<<endl;
	of.flush();
	of.close();
	
	cout.rdbuf(coutbuffer);
}
