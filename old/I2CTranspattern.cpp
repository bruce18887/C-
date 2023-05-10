#include<fstream>
#include<iostream>
#include<map>
#include<bitset>
#include<algorithm>
#include<vector>
using namespace std;

class TransClass {
	map<char, int> Database;
public:
	TransClass() {
		Database['0'] = 0x0;Database['1'] = 0x1;Database['2'] = 0x2;Database['3'] = 0x3;Database['4'] = 0x4;
		Database['5'] = 0x5;Database['6'] = 0x6;Database['7'] = 0x7;Database['8'] = 0x8;Database['9'] = 0x9;
		Database['a'] = 0xa;Database['b'] = 0xb;Database['c'] = 0xc;Database['d'] = 0xd;Database['e'] = 0xe;
		Database['f'] = 0xf;Database['A'] = 0xa;Database['B'] = 0xb;Database['C'] = 0xc;Database['D'] = 0xd;
		Database['E'] = 0xe;Database['F'] = 0xf;
	}
	~TransClass() {
		Database.clear();
	}
	int HexToDec(const char& input='0')
	{
		map<char,int>::iterator iter = Database.find(input);
		if(iter!=Database.end()){
			return iter->second;
		}
		else{
			cout<<"In "<<__FUNCTION__<<"() Input a wrong key->"<<input<<" !"<<endl;
			cout<<"return with -1"<<endl;
			return -1;
		}
	}
	string DecToBin(const int& input=0)
	{
		bitset<4> TransBitset(input);
		return TransBitset.to_string();
	}
	string HexToBin(const char& input='0')
	{
		map<char,int>::iterator iter = Database.find(input);
		if(iter!=Database.end()){
			bitset<4> TransBitset(iter->second);
			return TransBitset.to_string();
		}
		else{
			cout<<"In "<<__FUNCTION__<<"() Input a wrong key->"<<input<<" !"<<endl;
			cout<<"return with ????"<<endl;
			return "????";
		}
		
	}
	void ShowMap()
	{
		for(map<char,int>::iterator iter=Database.begin();iter!=Database.end();iter++){
			cout<<"["<<iter->first<<"] = "<<iter->second<<endl;
		}
	}
};
void Chuangshiwei_I2C_PAT_WRITE(string patname,vector<string> reg_value)
{
	ofstream TransPat(patname,ios::out);
	TransClass chuangshiwei_I2C;
	TransPat<<"Label,WFT,Sequence";//固定的header
	TransPat<<",SDA,SCL";
	TransPat<<endl;
	string wftname = "TS1";
	string WRITE;
	//string reg_value = "6A_30_00_00";
	for(vector<string>::iterator iter=reg_value.begin();iter!=reg_value.end();iter++){
		TransPat<<","<<wftname<<",repeat 23,1,1,"<<endl;//first line 
		TransPat<<","<<wftname<<",nop,1,1,//START"<<endl;
		TransPat<<","<<wftname<<",repeat 2,0,1"<<endl;
		TransPat<<","<<wftname<<",nop,0,0"<<endl;
		for(int label=0;label<4;label++){
			WRITE = chuangshiwei_I2C.HexToBin((*iter)[0+3*label]);
			for(int i=0;i<4;i++){
				TransPat<<","<<wftname<<",nop,"<< WRITE[i]<<",0,//"<<(i==0?(*iter)[0+3*label]:' ')<<endl;       //slave id
				TransPat<<","<<wftname<<",repeat 2,"<<WRITE[i]<<",1"<<endl;
				TransPat<<","<<wftname<<",nop,"<<WRITE[i]<<",0"<<endl;
			}
			WRITE = chuangshiwei_I2C.HexToBin((*iter)[1+3*label]);
			for(int i=0;i<4;i++){
				TransPat<<","<<wftname<<",nop,"<< WRITE[i]<<",0,//"<<(i==0?(*iter)[1+3*label]:' ')<<endl;       //slave id
				TransPat<<","<<wftname<<",repeat 2,"<<WRITE[i]<<",1"<<endl;
				TransPat<<","<<wftname<<",nop,"<<WRITE[i]<<",0"<<endl;
			}
			TransPat<<","<<wftname<<",nop,"<<"X"<<",0,//ACK"<<endl;       //ACK
			TransPat<<","<<wftname<<",repeat 2,"<<"L"<<",1"<<endl;
			TransPat<<","<<wftname<<",nop,"<<"0"<<",0"<<endl;
		}
		TransPat<<","<<wftname<<",nop,"<<"0"<<",1,//STOP"<<endl;       //STOP
		TransPat<<","<<wftname<<",repeat 2,"<<"0"<<",1"<<endl;
		TransPat<<","<<wftname<<",nop,"<<"1"<<",1"<<endl;
		TransPat<<","<<wftname<<",repeat 238,"<<"1"<<",1"<<endl;     //DELAY
	}

	TransPat<<","<<wftname<<",stop,"<<"1"<<",1"<<endl;           //patstop
	
	TransPat.close();
}

struct TransValue{
	int SlaveID = 0x00;
	int Address1 = 0x0000;
	int Data = 0x00;
};
void Chuangshiwei_I2C_PAT_WRITE(string patname,vector<TransValue> &reg_value)
{
	ofstream TransPat(patname,ios::out);
	TransClass chuangshiwei_I2C;
	TransPat<<"Label,WFT,Sequence";//固定的header
	TransPat<<",SDA,SCL";
	TransPat<<endl;
	string wftname = "TS1";
	string WRITE;
	unsigned long long int transvalue = 0;
	//string reg_value = {0x6a,0x3000,0x01};
	
	for(vector<TransValue>::iterator iter=reg_value.begin();iter!=reg_value.end();iter++){
		TransPat<<","<<wftname<<",repeat 23,1,1,//"<<hex<<(*iter).Address1<<"_"<<(*iter).Data<<endl;//first line 
		TransPat<<","<<wftname<<",nop,1,1,//START"<<endl;
		TransPat<<","<<wftname<<",repeat 2,0,1"<<endl;
		TransPat<<","<<wftname<<",nop,0,0"<<endl;

		auto pointer = &((*iter).SlaveID);
		for(int i=0;i<3;i++){  //结构体成员的数量
			if(i==1){
				transvalue =((*(pointer+i))>>12)&0xf;
				WRITE = chuangshiwei_I2C.DecToBin(transvalue);
				for(int i=0;i<4;i++){
					if(i==0){
						TransPat<<","<<wftname<<",nop,"<< WRITE[i]<<",0,//"<<hex<<transvalue<<endl;       //slave id
					}else{
						TransPat<<","<<wftname<<",nop,"<< WRITE[i]<<",0,"<<endl;       //slave id
					}
					TransPat<<","<<wftname<<",repeat 2,"<<WRITE[i]<<",1"<<endl;
					TransPat<<","<<wftname<<",nop,"<<WRITE[i]<<",0"<<endl;
				}
				transvalue =((*(pointer+i))>>8)&0xf;
				WRITE = chuangshiwei_I2C.DecToBin(transvalue);
				for(int i=0;i<4;i++){
					if(i==0){
						TransPat<<","<<wftname<<",nop,"<< WRITE[i]<<",0,//"<<hex<<transvalue<<endl;       //slave id
					}else{
						TransPat<<","<<wftname<<",nop,"<< WRITE[i]<<",0,"<<endl;       //slave id
					}
					TransPat<<","<<wftname<<",repeat 2,"<<WRITE[i]<<",1"<<endl;
					TransPat<<","<<wftname<<",nop,"<<WRITE[i]<<",0"<<endl;
				}
				
				TransPat<<","<<wftname<<",nop,"<<"X"<<",0,//ACK"<<endl;       //ACK
				TransPat<<","<<wftname<<",repeat 2,"<<"L"<<",1"<<endl;
				TransPat<<","<<wftname<<",nop,"<<"0"<<",0"<<endl;
			}
			transvalue =((*(pointer+i))>>4)&0xf;
			WRITE = chuangshiwei_I2C.DecToBin(transvalue);
			for(int i=0;i<4;i++){
				if(i==0){
					TransPat<<","<<wftname<<",nop,"<< WRITE[i]<<",0,//"<<hex<<transvalue<<endl;       //slave id
				}else{
					TransPat<<","<<wftname<<",nop,"<< WRITE[i]<<",0,"<<endl;       //slave id
				}
				TransPat<<","<<wftname<<",repeat 2,"<<WRITE[i]<<",1"<<endl;
				TransPat<<","<<wftname<<",nop,"<<WRITE[i]<<",0"<<endl;
			}
			transvalue =(*(pointer+i))&0xf;
			WRITE = chuangshiwei_I2C.DecToBin(transvalue);
			for(int i=0;i<4;i++){
				if(i==0){
					TransPat<<","<<wftname<<",nop,"<< WRITE[i]<<",0,//"<<hex<<transvalue<<endl;       //slave id
				}else{
					TransPat<<","<<wftname<<",nop,"<< WRITE[i]<<",0,"<<endl;       //slave id
				}
				TransPat<<","<<wftname<<",repeat 2,"<<WRITE[i]<<",1"<<endl;
				TransPat<<","<<wftname<<",nop,"<<WRITE[i]<<",0"<<endl;
			}

			TransPat<<","<<wftname<<",nop,"<<"X"<<",0,//ACK"<<endl;       //ACK
			TransPat<<","<<wftname<<",repeat 2,"<<"L"<<",1"<<endl;
			TransPat<<","<<wftname<<",nop,"<<"0"<<",0"<<endl;
		}
		
		TransPat<<","<<wftname<<",nop,"<<"0"<<",1,//STOP"<<endl;       //STOP
		TransPat<<","<<wftname<<",repeat 2,"<<"0"<<",1"<<endl;
		TransPat<<","<<wftname<<",nop,"<<"1"<<",1"<<endl;
		TransPat<<","<<wftname<<",repeat 238,"<<"1"<<",1"<<endl;     //DELAY
	}
	
	TransPat<<","<<wftname<<",stop,"<<"1"<<",1"<<endl;           //patstop
	
	TransPat.close();
}
int main()
{


//	
//	write_reg.push_back({0x6a,0x30,0x1D,0x00});
//	write_reg.push_back({0x6a,0x30,0x24,0xDC});
//	write_reg.push_back({0x6a,0x30,0x25,0x0A});
//	write_reg.push_back({0x6a,0x30,0x26,0x00});
//	write_reg.push_back({0x6a,0x30,0x28,0x88});
//	write_reg.push_back({0x6a,0x30,0x29,0x02});
//	write_reg.push_back({0x6a,0x30,0x32,0x00});
//	write_reg.push_back({0x6a,0x30,0x33,0x00});
//	write_reg.push_back({0x6a,0x33,0x00,0x00});
//	write_reg.push_back({0x6a,0x34,0x01,0x01});
//	write_reg.push_back({0x6a,0x34,0x3E,0x00});
//	write_reg.push_back({0x6a,0x38,0x06,0x01});
//	write_reg.push_back({0x6a,0x39,0x08,0x5A});
//	write_reg.push_back({0x6a,0x39,0x09,0x00});
//	write_reg.push_back({0x6a,0x39,0x0A,0x02});
//	write_reg.push_back({0x6a,0x33,0x38,0x00});
//	write_reg.push_back({0x6a,0x35,0xB3,0x0A});
//	write_reg.push_back({0x6a,0x3B,0x74,0x00});
//	write_reg.push_back({0x6a,0x31,0x28,0x02});
//	write_reg.push_back({0x6a,0x31,0x2E,0x0C});
//	write_reg.push_back({0x6a,0x31,0x1C,0x01});
//	write_reg.push_back({0x6a,0x31,0x1D,0x0C});
//	write_reg.push_back({0x6a,0x30,0x35,0x01});
//	write_reg.push_back({0x6a,0x34,0x40,0x02});
//	write_reg.push_back({0x6a,0x34,0x42,0x02});
//	write_reg.push_back({0x6a,0x34,0x5F,0x00});
//	write_reg.push_back({0x6a,0x36,0x10,0x00});
//	write_reg.push_back({0x6a,0x36,0x4D,0x00});
//	write_reg.push_back({0x6a,0x37,0x83,0x00});
//	write_reg.push_back({0x6a,0x38,0x52,0x00});
//	write_reg.push_back({0x6a,0x30,0x00,0x00});
//	
//	Chuangshiwei_I2C_PAT_WRITE("IDD.csv",write_reg);
//	write_reg.clear();
//	write_reg.push_back({0x6a,0x3b,0xb0,0x01});
//	write_reg.push_back({0x6a,0x3b,0xb2,0x05});
//	write_reg.push_back({0x6a,0x39,0x04,0x4a});
//	write_reg.push_back({0x6a,0x39,0x05,0x02});
//	write_reg.push_back({0x6a,0x39,0x07,0x20});
//	write_reg.push_back({0x6a,0x30,0x00,0x00});
//	Chuangshiwei_I2C_PAT_WRITE("PLL_CURRENT_UP.csv",write_reg);
//	write_reg.clear();
//	write_reg.push_back({0x6a,0x3b,0xb0,0x01});
//	write_reg.push_back({0x6a,0x3b,0xb2,0x05});
//	write_reg.push_back({0x6a,0x39,0x04,0x0a});
//	write_reg.push_back({0x6a,0x39,0x05,0x03});
//	write_reg.push_back({0x6a,0x39,0x07,0x20});
//	write_reg.push_back({0x6a,0x30,0x00,0x00});
//	Chuangshiwei_I2C_PAT_WRITE("PLL_CURRENT_DOWN.csv",write_reg);
//	write_reg.clear();
//	write_reg.push_back({0x6a,0x34,0x40,0x02});
//	write_reg.push_back({0x6a,0x34,0x42,0x02});
//	write_reg.push_back({0x6a,0x34,0x5F,0x00});
//	write_reg.push_back({0x6a,0x30,0x00,0x00});
//	Chuangshiwei_I2C_PAT_WRITE("MIPI_DC_HS0.csv",write_reg);
//	write_reg.clear();
//	write_reg.push_back({0x6a,0x34,0x40,0x02});
//	write_reg.push_back({0x6a,0x34,0x42,0x03});
//	write_reg.push_back({0x6a,0x34,0x5F,0x00});
//	write_reg.push_back({0x6a,0x30,0x00,0x00});
//	Chuangshiwei_I2C_PAT_WRITE("MIPI_DC_HS1.csv",write_reg);
//	write_reg.clear();

	/*CV5001*/
//	write_reg.push_back({0x6a,
//		0x3081,0x00});
//	write_reg.push_back({0x6a,
//		0x3308,0x30});
//	Chuangshiwei_I2C_PAT_WRITE("IOH.csv",write_reg);
//	write_reg.clear();
//
//	write_reg.push_back({0x6a,
//		0x3081,0x00});
//	write_reg.push_back({0x6a,
//		0x3308,0x20});
//	Chuangshiwei_I2C_PAT_WRITE("IOL.csv",write_reg);
	vector<TransValue> write_reg{
		{0x6a,0x3028, 0xAC},
		{0x6a,0x3029, 0x0D},
		{0x6a,0x302A, 0x00},
		{0x6a,0x302C, 0x12}, 
		{0x6a,0x302D, 0x03},
		{0x6a,0x3030, 0x00},
		{0x6a,0x3035, 0x00},  
		{0x6a,0x3036, 0x00},  
		{0x6a,0x3304, 0x01},  
		{0x6a,0x3305, 0x02},  
		{0x6a,0x3401, 0x03}, 
		{0x6a,0x3418, 0x9F},  
		{0x6a,0x3419, 0x00},
		{0x6a,0x341A, 0x57}, 
		{0x6a,0x341B, 0x00},
		{0x6a,0x341C, 0x57},  
		{0x6a,0x341D, 0x00},
		{0x6a,0x341E, 0x6F}, 
		{0x6a,0x341F, 0x01},
		{0x6a,0x3420, 0x57},
		{0x6a,0x3421, 0x00},
		{0x6a,0x3422, 0x9F}, 
		{0x6a,0x3423, 0x00},
		{0x6a,0x3424, 0x57},  
		{0x6a,0x3425, 0x00},
		{0x6a,0x3426, 0x8F},  
		{0x6a,0x3427, 0x00},
		{0x6a,0x3428, 0x47}, 
		{0x6a,0x3429, 0x00},
		{0x6a,0x343C, 0x01}, 
		{0x6a,0x343E, 0x00}, 
		{0x6a,0x3807, 0x80}, 
		{0x6a,0x3908, 0x6E}, 
		{0x6a,0x3909, 0x00},
		{0x6a,0x3930, 0x00},
		{0x6a,0x3347, 0x01},
		{0x6a,0x3348, 0x00},
		{0x6a,0x3000, 0x00}
	};
//	for(auto iter=write_reg.begin();iter!=write_reg.end();iter++){
//		//TODO
//	}
	Chuangshiwei_I2C_PAT_WRITE("IDD.csv",write_reg);
//	write_reg.clear();
//	vector<TransValue> write_reg;
//	write_reg.clear();
//	write_reg.push_back({0x6a,0x3580,0x03});
//	write_reg.push_back({0x6a,0x3581,0x11});
//	write_reg.push_back({0x6a,0x3581,0x04});
//	write_reg.push_back({0x6a,0x3000, 0x00});
//	Chuangshiwei_I2C_PAT_WRITE("IM_BIAS.csv",write_reg);
	
//	write_reg.clear();
//	write_reg.push_back({0x6a,	0x3BB0, 0x01});
//	write_reg.push_back({0x6a,	0x3BB1, 0x01});
//	write_reg.push_back({0x6a,	0x3BB2, 0x05});
//	write_reg.push_back({0x6a,	0x3907, 0x20 });
//	write_reg.push_back({0x6a,0x3000, 0x00});
//	Chuangshiwei_I2C_PAT_WRITE("PLL_VOLTAGE.csv",write_reg);
//	write_reg.clear();
//	write_reg.push_back({0x6a,	0x3BB0, 0x01});
//	write_reg.push_back({0x6a,	0x3BB2, 0x05});
//	write_reg.push_back({0x6a,	0x3904, 0x8A});
//	write_reg.push_back({0x6a,	0x3905, 0x02});
//	write_reg.push_back({0x6a,	0x3907, 0x20 });
//	write_reg.push_back({0x6a,0x3000, 0x00});
//	Chuangshiwei_I2C_PAT_WRITE("PLL_CURRENT_UP.csv",write_reg);
//	write_reg.clear();
//	write_reg.push_back({0x6a,	0x3BB0, 0x01});
//	write_reg.push_back({0x6a,	0x3BB2, 0x05});
//	write_reg.push_back({0x6a,	0x3904, 0x0A});
//	write_reg.push_back({0x6a,	0x3905, 0x03});
//	write_reg.push_back({0x6a,	0x3907, 0x20 });
//	write_reg.push_back({0x6a,0x3000, 0x00});
//	Chuangshiwei_I2C_PAT_WRITE("PLL_CURRENT_DOWN.csv",write_reg);
//	write_reg.clear();
//	write_reg.push_back({0x6a,	0x3440, 0x02});
//	write_reg.push_back({0x6a,	0x3442, 0x02});
//	write_reg.push_back({0x6a,0x3000, 0x00});
//	Chuangshiwei_I2C_PAT_WRITE("MIPI_DC_HS0.csv",write_reg);
//	write_reg.clear();
//	write_reg.push_back({0x6a,	0x3440, 0x02});
//	write_reg.push_back({0x6a,	0x3442, 0x03});
//	write_reg.push_back({0x6a,0x3000, 0x00});
//	Chuangshiwei_I2C_PAT_WRITE("MIPI_DC_HS1.csv",write_reg);
//	vector<TransValue> write_reg;
//	write_reg.clear();
//	write_reg.push_back({0x6a,0x3BB0, 0x01});
//	write_reg.push_back({0x6a,0x3BB1, 0x00});
//	write_reg.push_back({0x6a,0x3BB2, 0x0B});
//	write_reg.push_back({0x6a,0x3000, 0x00});
//	Chuangshiwei_I2C_PAT_WRITE("IM_BIAS_3.csv",write_reg);
}
