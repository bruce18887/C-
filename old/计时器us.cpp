#include "mydefineheader/mytimer.h"
#include<iostream>

using namespace std;

int main()
{
	Timer MY1;
	int i = 0;
	double a= MY1.Start();
	while(i++<100){
		cout<<" "<<endl;
	}
	cout<<MY1.Stop()-a<<"us"<<endl;
}

