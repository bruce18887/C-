#include<iostream>
//#include<conio.h>
#include<random>
//#include<ctime>
#include<fstream>
#include<vector>
#include<algorithm>
#include<windows.h>

using namespace std;

class GameBasic {
	//"■"  游戏的基本元素方块 由于目前控制台打印的问题，目前单个元素Row = 2,Col =1
	//"★"
	//"●"
	//"█"
private:
//	HWND GetConsoleHwnd();           //获取当前句柄
//	int KeyBoardChar;
	struct GameRank {
		string RankVersion;
		unsigned int RankSetValue;
	};
protected:
	struct Pos{
		int x_pos;
		int y_pos;
		bool operator == (const Pos &StrutMem)
		{
			return (this->x_pos == StrutMem.x_pos) && (this->y_pos==StrutMem.y_pos);
		}
	};                           //逻辑坐标 Pos
	const int U = -1;				//方向常量
	const int D = 1;
	const int L = -2;
	const int R = 2;
	int MoveJudge = R;  //Snake移动的方向，初始为 Right
	GameRank RANK[9] = {
		{"一",200},{"二",180},{"三",160},{"四",140},
		{"五",120},{"六",100},{"七",80},{"八",60},
		{"九",40}
	};
	//随机坐标产生器 两个参数为map的限定区域
	Pos randVec_int(int edge_x = 60,int edge_y = 30) const
	{
		// 基于当前系统的当前日期/时间
		time_t now = time(0);
		//cout << "1970 到目前经过秒数:" << now << endl;
		tm *ltm = localtime(&now);
		// 由于我们希望引擎和分布对象保持状态，因此应该将他们定义为
		// static 的，从而每次调用都生成新的数
		static default_random_engine e(ltm->tm_sec);
		static uniform_int_distribution<unsigned> u1(2,edge_x-1);
		static uniform_int_distribution<unsigned> u2(1,edge_y-1);
		Pos ret;
		for(size_t i = 0; i<2;i++){
			ret.x_pos = u1(e);
			ret.y_pos = u2(e);
		}
		//cout<<"\n"<<ret.x_pos<<"  "<<ret.y_pos<<endl;
		return ret;
	}

	void SnakeMoveJudge()
	{
		//GetAsyncKeyState函数用来判断调用时指定虚假键的状态
		if(GetAsyncKeyState(VK_UP) && MoveJudge != D){
			MoveJudge = U;
		}
		else if(GetAsyncKeyState(VK_DOWN) && MoveJudge != U){
			MoveJudge = D;
		}
		else if(GetAsyncKeyState(VK_LEFT) && MoveJudge != R){
			MoveJudge = L;	
		}
		else if(GetAsyncKeyState(VK_RIGHT) && MoveJudge != L){
			MoveJudge = R;
		}
	}
	//设置颜色
	void color(int col)
	{
		//调用API改变控制台字体颜色
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), col);
	}
	//核心功能 改变字体位置
	void gotoxy(Pos input)
	{
		COORD Position;//光标坐标
		Position.X = input.x_pos;
		Position.Y = input.y_pos;
		//调用API改变字体位置
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Position);
	}
public:
	GameBasic(){

	}
	~GameBasic(){}
};
class GameScore{
private:
	struct GameFilePointer{
		ifstream ReadLog;
		ofstream WriteLog;
	};
	struct PlayerMessage{
		string PlayerName;
		int PlayerScore;
	};

	GameFilePointer RealPointStruct;
	vector<PlayerMessage> MessageSum;
	bool GameRecordFileSet(GameFilePointer* Input)
	{
		(*Input).ReadLog.open("贪吃蛇.log",ios::in);
		if(!(*Input).ReadLog.is_open()){
			cout<<"\n未检测到游戏记录，正在创建。。。"<<endl;
			Sleep(300);
			(*Input).WriteLog.open("贪吃蛇.log",ios::out);
			(*Input).WriteLog<<"dev_zhuliqun"<<"-"<<0<<endl;
			(*Input).ReadLog.open("贪吃蛇.log",ios::in);
			if(!(*Input).ReadLog.is_open()){
				cout<<"\n无法创建游戏记录，程序正在退出。。。"<<endl;
				(*Input).ReadLog.close();
				(*Input).WriteLog.close();
				return 0;
			}
			else{
				cout<<"\n创建成功，正在打开游戏。。。"<<endl;
				Sleep(300);
				system("cls");
				return 1;
			}
		}
		return 1;
	}
protected:
	PlayerMessage ReadFormFile;
	PlayerMessage PlayerInGame;
	void InitScore()
	{
		if(GameRecordFileSet(&RealPointStruct)){
			int linecount = 0;
			string linestring;
			int findlabel;
			MessageSum.clear();
			while(getline(RealPointStruct.ReadLog,linestring)){
				if(linestring.at(0)==' '){
					ReadFormFile.PlayerName = "dev_zhuliqun";
					ReadFormFile.PlayerScore = 0;
				}
				else{
					linecount+=1;
					findlabel = linestring.find('-',0);
					ReadFormFile.PlayerName = linestring.substr(0,findlabel);
					ReadFormFile.PlayerScore = stoi(linestring.substr(findlabel+1,linestring.length()));
				}
			}
			if(linecount==0){
				ReadFormFile.PlayerName = "dev_zhuliqun";
				ReadFormFile.PlayerScore = 0;
			}
		}
		else{
			ReadFormFile.PlayerName = "dev_zhuliqun";
			ReadFormFile.PlayerScore = 0;
		}
		RealPointStruct.ReadLog.close();//关闭log读取
	}
	int UpdateScore()
	{
		return PlayerInGame.PlayerScore+=1;
	}
	void UpdateScoreFile()
	{
		RealPointStruct.WriteLog.open("贪吃蛇.log",ios::out);
		RealPointStruct.WriteLog<<PlayerInGame.PlayerName<<"-"<<PlayerInGame.PlayerScore;
	}
	bool EndScore()
	{
		if(PlayerInGame.PlayerScore>ReadFormFile.PlayerScore){
			return 1;
		}
		return 0;
	}
public:
	GameScore() {
		PlayerInGame.PlayerName = "游客";
		PlayerInGame.PlayerScore = 0;
	}
	~GameScore() {
		RealPointStruct.WriteLog.close();
	}
	
};
class Game:public GameBasic,public GameScore {
private:
	const Pos START_POS = {2,10}; //Snake生成的初始点位 正所谓一生二，二生三，三生万物
	vector<Pos> SnakeBody;  //Snake的本质，vector容器
	Pos SnakeHead;  //Snake的Head parm 作为判定死亡，吃到食物的计算标志基础(实际判定由Next_Pos完成)
	Pos food_pos;
	int RankJudge = 0;
protected: 
	Pos creatfood(vector<Pos>& Input)
	{
		Pos Output = {0,0};
		while(1){
			Output = randVec_int();
			for(vector<Pos>::iterator iter=Input.begin();iter!=Input.end();iter++){
				if(Output.x_pos%2==0){
					if((iter->x_pos!=Output.x_pos)&&(iter->y_pos!=Output.y_pos)){
						return Output;
					}
				}
			}
		}
		return Output;
	}

	void creatmap(const int width = 60,const int height = 30)
	{
		color(0x79);
		Pos start_pos = {0,0};
		int creatspeed = 5;//创建的速度，人往往想看清楚实现的过程
		for(;start_pos.x_pos<=width;start_pos.x_pos+=2){
			gotoxy({start_pos.x_pos,start_pos.y_pos});
			Sleep(creatspeed);
			cout<<"■";
		}
		for(;start_pos.y_pos<=height;start_pos.y_pos+=1){
			gotoxy({start_pos.x_pos,start_pos.y_pos});
			Sleep(creatspeed);
			cout<<"■";
		}
		for(;start_pos.x_pos>0;start_pos.x_pos-=2){
			gotoxy({start_pos.x_pos,start_pos.y_pos});
			Sleep(creatspeed);
			cout<<"■";
		}
		for(;start_pos.y_pos>0;start_pos.y_pos-=1){
			gotoxy({start_pos.x_pos,start_pos.y_pos});
			Sleep(creatspeed);
			cout<<"■";
		}
	}
	void InitFood()
	{
		food_pos = creatfood(SnakeBody);
		gotoxy(food_pos);
		cout<<"●";
	}
	void InitSnake()
	{
		for(int i=0;i<=2;i++){
			SnakeBody.push_back({START_POS.x_pos+2*i,START_POS.y_pos});
		}
		for(vector<Pos>::iterator iter=SnakeBody.begin();iter!=SnakeBody.end();iter++){
			gotoxy(*iter);
			cout<<"■";
		}
		SnakeHead ={(SnakeBody.end()-1)->x_pos,START_POS.y_pos};
	}
	void InitConscole()
	{
		//关闭鼠标光标
		CONSOLE_CURSOR_INFO cursor_info = {1, 0};
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), 
			&cursor_info);
		//设置长宽
		system("mode con cols=110 lines=40");
		
		//得分板
		color(0x97);
		gotoxy({70,3});
		cout<<"最高分:  ";
		gotoxy({80,3});
		cout<<ReadFormFile.PlayerScore;
		gotoxy({84,3});
		cout<<ReadFormFile.PlayerName;
		gotoxy({70,2});
		cout<<"您的得分:";
		color(0xc0);
		gotoxy({80,2});
		cout<<"   ";
		gotoxy({84,2});
		cout<<PlayerInGame.PlayerName;
		//难度板
		color(0x9e);
		gotoxy({70,6});
		cout<<"难度:    ";
		GameSetRank();
		
		//绘制围墙	
		creatmap(60,30);
		//设置标题
		SetConsoleTitle("贪吃蛇");

		color(0x0b);
	}
	void GameInit()
	{
		InitScore();
		InitConscole();
		InitSnake();
		InitFood(); //食物的产生需要判定SnakeBody 所以在InitSnake的后面
	}
	void GameCreatFood()
	{
		if((food_pos.x_pos==0)&&(food_pos.y_pos==0)){
			food_pos = creatfood(SnakeBody);
			gotoxy(food_pos);
			cout<<"●";
		}
	}
	bool DeathJudge(vector<Pos>& Input,Pos Next_Pos,int edge_x,int edge_y)
	{
		if((Next_Pos.x_pos==0)||(Next_Pos.x_pos==(edge_x+2))||(Next_Pos.y_pos==0)||(Next_Pos.y_pos==(edge_y+1))){
			return 0;
		}
		vector<Pos>::iterator iter= find(Input.begin(),Input.end(),Next_Pos);
		if(iter==Input.end()){
			return 1;
		}
		return 0;
	}
	void GameDelay(int Delay=50)
	{
		Sleep(Delay);
	}
	void PrintSnake()
	{
		for(vector<Pos>::iterator iter=SnakeBody.begin();iter!=SnakeBody.end();iter++){
			gotoxy(*iter);
			cout<<"■";
		}
	}
	void GameSetRank()
	{
		//难度板
		color(0x9e);
		gotoxy({80,6});
		cout<<RANK[RankJudge].RankVersion;
		color(0x0b);
		RankJudge += 1;
	}
	void GameUpdateScore()
	{
		color(0x97);
		gotoxy({80,2});
		color(0xc0);
		int Score = UpdateScore();
		cout<<Score;
		color(0x0b);
		if((Score%2==0)&&(Score>0)&&(RankJudge<9)){
			GameSetRank();
		}		
	}
public:
	Game() {}
	~Game() {}

	int GameStart()
	{
		GameInit();
		while(1){
			GameCreatFood();
			SnakeMoveJudge();
			if(abs(MoveJudge)==1){ //对上下
				if(!DeathJudge(SnakeBody,{SnakeHead.x_pos,SnakeHead.y_pos+MoveJudge},60,30)){
					break;
				}
				gotoxy(*SnakeBody.begin());
				cout<<"  ";
				SnakeBody.push_back({SnakeHead.x_pos,SnakeHead.y_pos+=MoveJudge});
				if((SnakeHead.x_pos==food_pos.x_pos)&&((SnakeHead.y_pos)==food_pos.y_pos)){//蛇的下一帧头接到食物，则直接在头部增加两位数据
					food_pos = {0,0};//food eat reset to zero,zero
					//修改为尾部闪烁一次，头部增加一位，相当于吃到食物后原地闪烁了一次
					//SnakeBody.push_back({SnakeHead.x_pos,SnakeHead.y_pos+=MoveJudge});
					GameUpdateScore();
				}
				else{
					SnakeBody.erase(SnakeBody.begin());
				}
			}
			else{  //对左右
				if(!DeathJudge(SnakeBody,{SnakeHead.x_pos+MoveJudge,SnakeHead.y_pos},60,30)){
					break;
				}
				gotoxy(*SnakeBody.begin());
				cout<<"  ";
				SnakeBody.push_back({SnakeHead.x_pos+=MoveJudge,SnakeHead.y_pos});
				if((SnakeHead.x_pos==food_pos.x_pos)&&((SnakeHead.y_pos)==food_pos.y_pos)){//蛇的下一帧头接到食物，则直接在头部增加两位数据
					food_pos = {0,0};
					//修改为尾部闪烁一次，头部增加一位，相当于吃到食物后原地闪烁了一次
					//SnakeBody.push_back({SnakeHead.x_pos+=MoveJudge,SnakeHead.y_pos});
					GameUpdateScore();
				}
				else{
					SnakeBody.erase(SnakeBody.begin());
				}
			}
			PrintSnake();
			GameDelay(RANK[RankJudge].RankSetValue);
		}
		return 0;
	}
	void GameEnd()
	{
		if(EndScore()){
			color(0x2f);
			gotoxy({0,32});
			cout<<"\n恭喜你打破记录了！";
			GameDelay(500);
			gotoxy({0,32});
			cout<<"\n                  ";
			GameDelay(300);
			gotoxy({0,32});
			cout<<"\n能否留下大侠名字呢？请输入英文哟：";
			cin>>PlayerInGame.PlayerName;
			GameDelay(200);
			color(0x0b);
			gotoxy({0,32});
			cout<<"\n                                         ";
			UpdateScoreFile();
			GameDelay(400);
			gotoxy({0,32});
			color(0x2f);
			cout<<"\n记录已更新！";
			GameDelay(300);
			gotoxy({0,32});
			cout<<"\n                  ";
			GameDelay(300);
		}	
		color(0x69);
		gotoxy({0,32});
		cout<<"Game Over"<<endl;
	}
};

int main()
{
	Game test;
	if(!test.GameStart())
	{
		test.GameEnd();
	}
	system("pause");
}
