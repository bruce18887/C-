#include<iostream>
#include<vector>
using namespace std;
//struct Pos{
//	int x;
//	int y;
//	bool operator == (const Pos& Input) const
//	{
//		return this->x == Input.x && this->y == Input.y?true:false; 
//	};
//	
//};

class Jager {
private:
	struct Pos{
		int x;
		int y;
	};
	Pos pos[4];

public:
	Jager(){
		
	}
	Jager(const int& Input1,const int& Input2)
	{
		for(int i=0;i<4;i++){
			pos[i].x = Input1;
			pos[i].y = Input2;
		}
	}
	~Jager(){
		
	}
	Jager operator+(int& Input){
		for(int i=0;i<4;i++){
			this->pos[i].x += Input;
			this->pos[i].y += Input;
		}
		return *this;
	}
	Jager operator+(Jager& Input){
		for(int i=0;i<4;i++){
			this->pos[i].x += Input.pos[i].x;
			this->pos[i].y += Input.pos[i].y;
		}
		return *this;
	}
	void ShowJager() const
	{
		for(int i=0;i<4;i++){
			cout<<this->pos[i].x<<endl;
			cout<<this->pos[i].y<<endl;
		}
	
	}
	friend Jager operator+(int& Input,const Jager& InInput);
	friend ostream& operator<<(ostream &a,const Jager&b);
};
Jager operator+(int& Input,const Jager& InInput)
{
	Jager jager;
	jager = InInput;
	for(int i=0;i<4;i++){
		jager.pos[i].x += Input ;
		jager.pos[i].y += Input ;
	}
	return jager;
}
ostream& operator<<(ostream& a,const Jager& b)
{
	a<<"Point1 x"<<(b.pos[0].x)<<"Point y"<<(b.pos[0].y)<<endl;
	return a;
}
int main()
{
	Jager p(30,30);
//	int cal = 30;
//	(p+cal).ShowJager();
//	Jager P1 = cal + p;
//	P1.ShowJager();
	cout<<"Print only point1 "<<p<<endl;
//	Pos b{4,4};
//	cout<<((a==b)?"True":"False")<<endl;
}
