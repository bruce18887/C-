#include<iostream>
#include<filesystem>
#include<fstream>
#include<bitset>
#include<math.h>
#include<algorithm>
using namespace std;

int GetChipID(int SITE_NUM = 0)
{
	ifstream ChipIDFile;
	ChipIDFile.open("CHIP_ID.log", ios::in);
	string linestring;
	string savestring[8]={" "};
	uint32_t num[8] = {0};
	int line =0;
	while(getline(ChipIDFile,linestring))
	{
//		cout<<linestring<<endl;
		savestring[line] = linestring;
		cout<<savestring[line]<<endl;
		num[line] = atoi(linestring.erase(0, 6).c_str());
				cout<<num[line]<<endl;
		line++;
	}
	ChipIDFile.close();

	ofstream ChipIDFileWrite;
	ChipIDFileWrite.open("CHIP_ID.log", ios::out);
	for(line=0;line<=7;line++){
		if(line==SITE_NUM){
			if(num[SITE_NUM]>=0xffffffff){
				ChipIDFileWrite<<"SITE"<<SITE_NUM<<":"<<(num[SITE_NUM]= 0)<<endl;
			}
			else{
				ChipIDFileWrite<<"SITE"<<SITE_NUM<<":"<<(num[SITE_NUM]+=1)<<endl;
			}
		}
		else{
			ChipIDFileWrite<<savestring[line]<<endl;
		}
	}
	ChipIDFileWrite.close();
	return num[SITE_NUM];
}
int main()
{
		cout<<GetChipID(3);
	
}
