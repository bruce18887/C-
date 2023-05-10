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
	//"��"  ��Ϸ�Ļ���Ԫ�ط��� ����Ŀǰ����̨��ӡ�����⣬Ŀǰ����Ԫ��Row = 2,Col =1
	//"��"
	//"��"
	//"��"
private:
//	HWND GetConsoleHwnd();           //��ȡ��ǰ���
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
	};                           //�߼����� Pos
	const int U = -1;				//������
	const int D = 1;
	const int L = -2;
	const int R = 2;
	int MoveJudge = R;  //Snake�ƶ��ķ��򣬳�ʼΪ Right
	GameRank RANK[9] = {
		{"һ",200},{"��",180},{"��",160},{"��",140},
		{"��",120},{"��",100},{"��",80},{"��",60},
		{"��",40}
	};
	//������������ ��������Ϊmap���޶�����
	Pos randVec_int(int edge_x = 60,int edge_y = 30) const
	{
		// ���ڵ�ǰϵͳ�ĵ�ǰ����/ʱ��
		time_t now = time(0);
		//cout << "1970 ��Ŀǰ��������:" << now << endl;
		tm *ltm = localtime(&now);
		// ��������ϣ������ͷֲ����󱣳�״̬�����Ӧ�ý����Ƕ���Ϊ
		// static �ģ��Ӷ�ÿ�ε��ö������µ���
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
		//GetAsyncKeyState���������жϵ���ʱָ����ټ���״̬
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
	//������ɫ
	void color(int col)
	{
		//����API�ı����̨������ɫ
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), col);
	}
	//���Ĺ��� �ı�����λ��
	void gotoxy(Pos input)
	{
		COORD Position;//�������
		Position.X = input.x_pos;
		Position.Y = input.y_pos;
		//����API�ı�����λ��
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
		(*Input).ReadLog.open("̰����.log",ios::in);
		if(!(*Input).ReadLog.is_open()){
			cout<<"\nδ��⵽��Ϸ��¼�����ڴ���������"<<endl;
			Sleep(300);
			(*Input).WriteLog.open("̰����.log",ios::out);
			(*Input).WriteLog<<"dev_zhuliqun"<<"-"<<0<<endl;
			(*Input).ReadLog.open("̰����.log",ios::in);
			if(!(*Input).ReadLog.is_open()){
				cout<<"\n�޷�������Ϸ��¼�����������˳�������"<<endl;
				(*Input).ReadLog.close();
				(*Input).WriteLog.close();
				return 0;
			}
			else{
				cout<<"\n�����ɹ������ڴ���Ϸ������"<<endl;
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
		RealPointStruct.ReadLog.close();//�ر�log��ȡ
	}
	int UpdateScore()
	{
		return PlayerInGame.PlayerScore+=1;
	}
	void UpdateScoreFile()
	{
		RealPointStruct.WriteLog.open("̰����.log",ios::out);
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
		PlayerInGame.PlayerName = "�ο�";
		PlayerInGame.PlayerScore = 0;
	}
	~GameScore() {
		RealPointStruct.WriteLog.close();
	}
	
};
class Game:public GameBasic,public GameScore {
private:
	const Pos START_POS = {2,10}; //Snake���ɵĳ�ʼ��λ ����νһ����������������������
	vector<Pos> SnakeBody;  //Snake�ı��ʣ�vector����
	Pos SnakeHead;  //Snake��Head parm ��Ϊ�ж��������Ե�ʳ��ļ����־����(ʵ���ж���Next_Pos���)
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
		int creatspeed = 5;//�������ٶȣ��������뿴���ʵ�ֵĹ���
		for(;start_pos.x_pos<=width;start_pos.x_pos+=2){
			gotoxy({start_pos.x_pos,start_pos.y_pos});
			Sleep(creatspeed);
			cout<<"��";
		}
		for(;start_pos.y_pos<=height;start_pos.y_pos+=1){
			gotoxy({start_pos.x_pos,start_pos.y_pos});
			Sleep(creatspeed);
			cout<<"��";
		}
		for(;start_pos.x_pos>0;start_pos.x_pos-=2){
			gotoxy({start_pos.x_pos,start_pos.y_pos});
			Sleep(creatspeed);
			cout<<"��";
		}
		for(;start_pos.y_pos>0;start_pos.y_pos-=1){
			gotoxy({start_pos.x_pos,start_pos.y_pos});
			Sleep(creatspeed);
			cout<<"��";
		}
	}
	void InitFood()
	{
		food_pos = creatfood(SnakeBody);
		gotoxy(food_pos);
		cout<<"��";
	}
	void InitSnake()
	{
		for(int i=0;i<=2;i++){
			SnakeBody.push_back({START_POS.x_pos+2*i,START_POS.y_pos});
		}
		for(vector<Pos>::iterator iter=SnakeBody.begin();iter!=SnakeBody.end();iter++){
			gotoxy(*iter);
			cout<<"��";
		}
		SnakeHead ={(SnakeBody.end()-1)->x_pos,START_POS.y_pos};
	}
	void InitConscole()
	{
		//�ر������
		CONSOLE_CURSOR_INFO cursor_info = {1, 0};
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), 
			&cursor_info);
		//���ó���
		system("mode con cols=110 lines=40");
		
		//�÷ְ�
		color(0x97);
		gotoxy({70,3});
		cout<<"��߷�:  ";
		gotoxy({80,3});
		cout<<ReadFormFile.PlayerScore;
		gotoxy({84,3});
		cout<<ReadFormFile.PlayerName;
		gotoxy({70,2});
		cout<<"���ĵ÷�:";
		color(0xc0);
		gotoxy({80,2});
		cout<<"   ";
		gotoxy({84,2});
		cout<<PlayerInGame.PlayerName;
		//�ѶȰ�
		color(0x9e);
		gotoxy({70,6});
		cout<<"�Ѷ�:    ";
		GameSetRank();
		
		//����Χǽ	
		creatmap(60,30);
		//���ñ���
		SetConsoleTitle("̰����");

		color(0x0b);
	}
	void GameInit()
	{
		InitScore();
		InitConscole();
		InitSnake();
		InitFood(); //ʳ��Ĳ�����Ҫ�ж�SnakeBody ������InitSnake�ĺ���
	}
	void GameCreatFood()
	{
		if((food_pos.x_pos==0)&&(food_pos.y_pos==0)){
			food_pos = creatfood(SnakeBody);
			gotoxy(food_pos);
			cout<<"��";
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
			cout<<"��";
		}
	}
	void GameSetRank()
	{
		//�ѶȰ�
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
			if(abs(MoveJudge)==1){ //������
				if(!DeathJudge(SnakeBody,{SnakeHead.x_pos,SnakeHead.y_pos+MoveJudge},60,30)){
					break;
				}
				gotoxy(*SnakeBody.begin());
				cout<<"  ";
				SnakeBody.push_back({SnakeHead.x_pos,SnakeHead.y_pos+=MoveJudge});
				if((SnakeHead.x_pos==food_pos.x_pos)&&((SnakeHead.y_pos)==food_pos.y_pos)){//�ߵ���һ֡ͷ�ӵ�ʳ���ֱ����ͷ��������λ����
					food_pos = {0,0};//food eat reset to zero,zero
					//�޸�Ϊβ����˸һ�Σ�ͷ������һλ���൱�ڳԵ�ʳ���ԭ����˸��һ��
					//SnakeBody.push_back({SnakeHead.x_pos,SnakeHead.y_pos+=MoveJudge});
					GameUpdateScore();
				}
				else{
					SnakeBody.erase(SnakeBody.begin());
				}
			}
			else{  //������
				if(!DeathJudge(SnakeBody,{SnakeHead.x_pos+MoveJudge,SnakeHead.y_pos},60,30)){
					break;
				}
				gotoxy(*SnakeBody.begin());
				cout<<"  ";
				SnakeBody.push_back({SnakeHead.x_pos+=MoveJudge,SnakeHead.y_pos});
				if((SnakeHead.x_pos==food_pos.x_pos)&&((SnakeHead.y_pos)==food_pos.y_pos)){//�ߵ���һ֡ͷ�ӵ�ʳ���ֱ����ͷ��������λ����
					food_pos = {0,0};
					//�޸�Ϊβ����˸һ�Σ�ͷ������һλ���൱�ڳԵ�ʳ���ԭ����˸��һ��
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
			cout<<"\n��ϲ����Ƽ�¼�ˣ�";
			GameDelay(500);
			gotoxy({0,32});
			cout<<"\n                  ";
			GameDelay(300);
			gotoxy({0,32});
			cout<<"\n�ܷ����´��������أ�������Ӣ��Ӵ��";
			cin>>PlayerInGame.PlayerName;
			GameDelay(200);
			color(0x0b);
			gotoxy({0,32});
			cout<<"\n                                         ";
			UpdateScoreFile();
			GameDelay(400);
			gotoxy({0,32});
			color(0x2f);
			cout<<"\n��¼�Ѹ��£�";
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
