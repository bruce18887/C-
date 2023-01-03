#include<iostream>
#include<string>
#include<fstream>
#include<algorithm>
#include<vector>
#include <io.h>
#include <direct.h>  
using namespace std;

void Transform(string orign,string trans)
{
	ifstream OringnPat(orign,ios::in);
	ofstream TransPat(trans,ios::out);
	
	if(!OringnPat.is_open()){
		cout<<"cannot open"<<endl;
	}
	TransPat<<"Label,WFT,Sequence,XPB10,XPB9,"<<endl;
	string linestrings;
	string wftname = "TS1_OTP";
	unsigned int line = 1;
	while(getline(OringnPat,linestrings)){
		if(line>4){
			if(linestrings[0]!='/'&&linestrings[0]!='g'){
				TransPat<<","<<wftname<<","<<"nop"<<","<<linestrings[31]<<","<<linestrings[33]<<",";
				for(int i=0;i<19;i++){
					TransPat<<linestrings[36+i];
				}
				TransPat<<endl;
			}
			if(linestrings[0]=='g'){
				linestrings = linestrings.erase(0,7);
				linestrings.erase(remove(linestrings.begin(),linestrings.end(),':'),linestrings.end());
				TransPat<<linestrings;
			}
		}  
		line++;
	}
	TransPat<<","<<wftname<<",stop,X,X,"<<endl;
	OringnPat.close();
	TransPat.close();
}
bool Transform_Multi(string orign,vector<string> PatSignals,unsigned int patstartline = 1,\
	unsigned int wfcstarterline = 1)
{
	orign.pop_back();
	orign.pop_back();
	orign.pop_back();
	orign.pop_back();
	string trans = orign + ".csv";
	orign = orign + ".atp";
	cout<<"750 "<<orign<<" transform to "<<trans<<" start"<<endl;
	ifstream OringnPat(orign,ios::in);
	
	ofstream TransPat(trans,ios::out);
	if(!OringnPat.is_open()){
		cout<<"cannot open"<<endl;
		return 0;
	}
	TransPat<<"Label,WFT,Sequence";//固定的header
	for(vector<string>::iterator iter=PatSignals.begin();iter!=PatSignals.end();iter++){
		TransPat<<","<<*iter;
	}
	TransPat<<endl;
	string linestrings;
	unsigned int line = 1;
	unsigned wfcstarter = 0;
	unsigned wftstarter = 0;
	//	unsigned int commenterstarter = 0;

	string sequence = "nop";
	string wftname = "TTT";
	
	while(getline(OringnPat,linestrings)){
		if(line==wfcstarterline){
			wfcstarter = linestrings.find('X',0);
			wftstarter = linestrings.find('>',0);
			//			commenterstarter = linestrings.find('/',0);
		}
		if(line>patstartline){
			if(linestrings[0]=='s'||linestrings[0]=='c'||linestrings[0]=='e'||linestrings[0]=='h'){
				continue;
			}
			if(linestrings[0]!='/'&&
				linestrings[0]!='g'&&
				linestrings[0]!='}'&&
				linestrings[0]!='h')
			{
				if(linestrings[0]=='r'){
					sequence = linestrings; 
					continue;
				}
				TransPat<<",";//for label
				if(linestrings[wftstarter+4]==' '){
					TransPat<<"TTT";
				}
				else{
					TransPat<<"TTT_1";
				}
				TransPat<<","<<sequence;
				for(unsigned i=0;i<PatSignals.size();i++){
					TransPat<<","<<linestrings[wfcstarter+2*i];
				}
				//for repeat sequence
//				if(commenterstarter!=0){
//					for(int i=0;i<19;i++){
//						TransPat<<linestrings[commenterstarter+i];
//					}
//				}
				TransPat<<endl;
				sequence = "nop";
			}
			//for gloabl label
//			if(linestrings[0]=='g'){
//				linestrings = linestrings.erase(0,7);
//				linestrings.erase(remove(linestrings.begin(),linestrings.end(),':'),linestrings.end());
//				TransPat<<linestrings;
//			}
		}

		line++;
	}
	TransPat<<","<<wftname<<",stop";
	for(unsigned i=0;i<PatSignals.size();i++){
		TransPat<<","<<"X";
	}
	
	TransPat<<endl;
	cout<<"750 "<<orign<<" transform to "<<trans<<" complete"<<endl;
	OringnPat.close();
	TransPat.close();
	return 1;
}


void Transform_CV4001(string orign,string trans)
{
	ifstream OringnPat(orign,ios::in);
	ofstream TransPat(trans,ios::out);
	
	if(!OringnPat.is_open()){
		cout<<"cannot open"<<endl;
	}
	TransPat<<"Label,WFT,Sequence,HSYNC,REFCLK,SCL,SDA,ADDRSEL,DTEST,VSYNC,RESET"<<endl;
	string linestrings;
//	unsigned int commenterstarter = 0;
	unsigned int wfcstarter = 41;
	string sequence = "nop";
	string wftname = "TS1_OTP";
	unsigned int line = 1;
	while(getline(OringnPat,linestrings)){
		if(line>24){

			if(linestrings[0]=='s'||linestrings[0]=='c'||linestrings[0]=='e'||linestrings[0]=='h'){
				continue;
			}
			if(linestrings[0]!='/'&&
				linestrings[0]!='g'&&
				linestrings[0]!='}'&&
				linestrings[0]!='h')
			{
				if(linestrings[26]==' '){
					TransPat<<","<<"TTT";
				}
				else{
					TransPat<<","<<"TTT_1";
				}
//				TransPat<<","<<linestrings[24]<<linestrings[25]<<linestrings[26]
				TransPat<<","<<sequence<<","
				<<linestrings[wfcstarter]<<","
				<<linestrings[wfcstarter+2]<<","
				<<linestrings[wfcstarter+4]<<","
				<<linestrings[wfcstarter+6]<<","
				<<linestrings[wfcstarter+8]<<","
				<<linestrings[wfcstarter+10]<<","
				<<linestrings[wfcstarter+12]<<","
				<<linestrings[wfcstarter+14]<<",//";
				TransPat<<endl;
				sequence = "nop";
			}
//			if(linestrings[0]=='g'){
//				linestrings = linestrings.erase(0,7);
//				linestrings.erase(remove(linestrings.begin(),linestrings.end(),':'),linestrings.end());
//				TransPat<<linestrings;
//			}
		}  
		line++;
	}
	TransPat<<","<<"TTT"<<",stop,X,X,X,X,X,X,X,X"<<endl;
	OringnPat.close();
	TransPat.close();
}
void Transform_EAI80(string orign,string trans)
{
	ifstream OringnPat(orign,ios::in);
	ofstream TransPat(trans,ios::out);
	
	if(!OringnPat.is_open()){
		cout<<"cannot open"<<endl;
	}
	TransPat<<"Label,WFT,Sequence,XPF14,XPE5,XPC9,XPE6,XRSTJ,XPH13,XPC10,XPC11,XPE3,XPE4,XPB9,XPB10,XPB14,XPB15,XPH11,XPH12,XPH14,XPH15,XPI0,XPI1,XPF12,XPF13,XPF15,XPG0,XPG1,XPC0,XPC1,XPC8"<<endl;
	string linestrings;

	unsigned int wfcstarter = 7;
	string sequence = "nop";
	string wftname = "TS1_SCAN";
	unsigned int line = 1;
	while(getline(OringnPat,linestrings)){
		if(line>12){
//			cout<<linestrings<<endl;
			if(linestrings[0]=='s'||linestrings[0]=='c'||linestrings[0]=='e'||linestrings[0]=='h'){
				continue;
			}
			if(linestrings[0]!='/'&&
				linestrings[0]!='g'&&
				linestrings[0]!='}'&&
				linestrings[0]!='h')
			{
				TransPat<<","<<wftname;
				TransPat<<","<<sequence<<",";
				for(int i=0;i<=52;i+=2){
					TransPat<<linestrings[wfcstarter+i]<<",";
				}
				TransPat<<linestrings[wfcstarter+54]<<",//";
				TransPat<<endl;
//				sequence = "nop";
			}
		}  
		line++;
	}
	TransPat<<","<<wftname<<",stop,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X"<<endl;
	OringnPat.close();
	TransPat.close();
}

bool Transform_Multi_SWD(string orign,vector<string> PatSignals,unsigned int patstartline = 1,\
	unsigned int wfcstarterline = 1)
{
	string trans = orign + ".csv";
	orign = orign + ".atp";
	cout<<"750 "<<orign<<" transform to "<<trans<<" start"<<endl;
	ifstream OringnPat(orign,ios::in);
	
	ofstream TransPat(trans,ios::out);
	if(!OringnPat.is_open()){
		cout<<"cannot open"<<endl;
		return 0;
	}
	TransPat<<"Label,WFT,Sequence";//固定的header
	for(vector<string>::iterator iter=PatSignals.begin();iter!=PatSignals.end();iter++){
		TransPat<<","<<*iter;
	}
	TransPat<<endl;
	string linestrings;
	unsigned int line = 1;
	unsigned wfcstarter = 0;
	unsigned wftstarter = 0;
	//	unsigned int commenterstarter = 0;
	
	string sequence = "nop";
	string wftname = "TS1_FUNC";
	
	while(getline(OringnPat,linestrings)){
		if(line==wfcstarterline){
			wfcstarter = linestrings.find('X',0);
			wftstarter = linestrings.find('>',0);
			//			commenterstarter = linestrings.find('/',0);
		}
		if(line>patstartline){
			if(linestrings[0]=='s'||linestrings[0]=='c'||linestrings[0]=='e'||linestrings[0]=='h'){
				continue;
			}
			if(linestrings[0]!='/'&&
				linestrings[0]!='g'&&
				linestrings[0]!='}'&&
				linestrings[0]!='h')
			{
				if(linestrings[0]=='r'){
					sequence = linestrings; 
					continue;
				}
				TransPat<<",";//for label
				TransPat<<wftname;
				TransPat<<","<<sequence;
				for(unsigned i=0;i<PatSignals.size();i++){
					TransPat<<","<<linestrings[wfcstarter+2*i];
				}
				//for repeat sequence
				//				if(commenterstarter!=0){
				//					for(int i=0;i<19;i++){
				//						TransPat<<linestrings[commenterstarter+i];
				//					}
				//				}
				TransPat<<endl;
				sequence = "nop";
			}
			//for gloabl label
			//			if(linestrings[0]=='g'){
			//				linestrings = linestrings.erase(0,7);
			//				linestrings.erase(remove(linestrings.begin(),linestrings.end(),':'),linestrings.end());
			//				TransPat<<linestrings;
			//			}
		}
		
		line++;
	}
	TransPat<<","<<wftname<<",stop";
	for(unsigned i=0;i<PatSignals.size();i++){
		TransPat<<","<<"x";
	}
	
	TransPat<<endl;
	cout<<"750 "<<orign<<" transform to "<<trans<<" complete"<<endl;
	OringnPat.close();
	TransPat.close();
	return 1;
}
vector<string> Find_ATPFile()
{
	vector<string> FileName;
	FileName.clear();
	_finddata_t fileinfo;
	string strfind ="*.atp";
	intptr_t filehandle = _findfirst(strfind.c_str(),&fileinfo);
	if(filehandle==-1){
		cout<<"no match in the path to find atp file"<<endl;
		FileName.push_back("ERROR");
		return FileName;
	}
	
	do{
		//cout<<fileinfo.name<<endl;
		FileName.push_back(fileinfo.name);
		
	}while(_findnext(filehandle,&fileinfo)==0);
	
	return FileName;
}
int main()
{
//	vector<string> pins{"HSYNC","REFCLK","SCL","SDA","ADDRESEL","DTEST","VSYNC","RESET"};
//	Transform_Multi("CNBIST_1",pins,24,25);
//	Transform_Multi("CNBIST_2",pins,24,25);
//	Transform_Multi("CNBIST_3",pins,24,25);
//	Transform_Multi("CNBIST_4",pins,24,25);
//	Transform_Multi("CNBIST_5",pins,24,25);
//	Transform_Multi("PLLBIST_24M_PCT1",pins,24,25);
//	Transform_Multi("PLLBIST_24M_PCT3",pins,24,25);
//	Transform_Multi("PLLBIST_24M_PCT5",pins,24,25);
//	Transform_Multi("PLLBIST_27M_756M_PCT1",pins,24,25);
//	Transform_Multi("PLLBIST_27M_756M_PCT3",pins,24,25);
//	Transform_Multi("PLLBIST_27M_756M_PCT5",pins,24,25);
//	Transform_Multi("PLLBIST_27M_1320M_PCT1",pins,24,25);
//	Transform_Multi("PLLBIST_27M_1320M_PCT3",pins,24,25);
//	Transform_Multi("PLLBIST_27M_1320M_PCT5",pins,24,25);
//	vector<string> pins1{"XPB10","XPB9"};
//	Transform_Multi_SWD("usb_host_without_int_dut",pins1,4,5);
//	Transform_Multi_SWD("usb_device_without_int_dut",pins1,4,5);
//	vector<string> pins2{"XPB10_GS","XPB9_GS"};
//	Transform_Multi_SWD("usb_host_without_int_gs",pins2,4,5);
//	Transform_Multi_SWD("usb_device_without_int_gs",pins2,4,5);
//	vector<string> pins3{"XPB10","XPB9","XPB10_GS","XPB9_GS"};
//	Transform_Multi_SWD("usb_check_result",pins3,4,5);
	vector<string> filename = Find_ATPFile();
	vector<string> pins{"HSYNC","REFCLK","SCL","SDA","ADDRSEL","DTEST","VSYNC","RESET"};
	for(auto iter  = filename.begin();iter!=filename.end();iter++){
		Transform_Multi((*iter),pins,24,25);
	}

}
