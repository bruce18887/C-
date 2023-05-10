#include <chrono>
#include <iostream>
#include<sstream>
using namespace std;
using namespace std::chrono;

void print_epoch_time()
{
	// 新纪元1970.1.1时间
	system_clock::time_point epoch;
	time_t tm2 = system_clock::to_time_t(epoch);
	cout << "新纪元时间:      " << ctime(&tm2);
	
	duration<int, ratio<60*60*24>> day(1);
	// 新纪元1970.1.1时间 + 1天
	system_clock::time_point ppt(day);
	
	using dday = duration<int, ratio<60 * 60 * 24>>;
	// 新纪元1970.1.1时间 + 10天
	time_point<system_clock, dday> t(dday(10));
	
	time_t tm3 = system_clock::to_time_t(ppt);
	cout << "新纪元时间+1天:  " << ctime(&tm3);
	
	time_t tm4 = system_clock::to_time_t(t);
	cout << "新纪元时间+10天: " << ctime(&tm4);
}


void show_now()
{
//	duration<int, ratio<60*60*24>> day(1);
//	// 系统当前时间
//	system_clock::time_point today = system_clock::now();
//	
//	// 转换为time_t时间类型
//	time_t tm = system_clock::to_time_t(today);
//	cout<<"TM "<<tm<<endl;
//	cout << "今天的日期是:    " << ctime(&tm);
//	
//	time_t tm1 = system_clock::to_time_t(today+day);
//	cout << "明天的日期是:    " << ctime(&tm1);
system_clock::time_point today1 = system_clock::now();
time_t timenow = system_clock::to_time_t(today1);
struct tm *p;
p = localtime(&timenow);
cout<<asctime(p)<<endl;
cout<<ctime(&timenow);
cout<<1900+p->tm_year<<"年"<<endl;
cout<<1+p->tm_mon<<"月"<<endl;
cout<<p->tm_mday<<"日"<<endl;
cout<<p->tm_hour<<"时"<<endl;
cout<<p->tm_min<<"分"<<endl;
cout<<p->tm_sec<<"秒"<<endl;
cout<<"星期"<<p->tm_wday<<endl;
cout<<"今年已经过去了"<<p->tm_yday<<"天"<<endl;
cout<<"目前进行的是"<<(p->tm_isdst==1?"夏令时":"冬令时")<<endl;
/*
  Wed Dec 07 14:26:14 2022
  
  Wed Dec 07 14:26:14 2022
  2022年
  12月
  7日
  14时
  26分
  14秒
  星期3
  今年已经过去了340天
  目前进行的是冬令时
 */
}
void costtime()
{
		// 获取开始时间点
		steady_clock::time_point start = steady_clock::now();
		// 执行业务流程
		cout << "print 1000 stars ...." << endl;
		for (int i = 0; i < 1000; ++i)
		{
			cout << "*";
		}
		cout << endl;
		// 获取结束时间点
		steady_clock::time_point last = steady_clock::now();
		// 计算差值
		auto dt = last - start;
		cout << "总共耗时: " << dt.count()/1000 << "纳秒" << endl;
}

//string GetCurrentTimeStamp(int time_stamp_type = 0)
//{
//	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
//	
//	std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
//	std::tm* now_tm = std::localtime(&now_time_t);
//	
//	char buffer[128];
//	strftime(buffer, sizeof(buffer), "%F %T", now_tm);
//	
//	std::ostringstream ss;
//	ss.fill('0');
//	
//	std::chrono::milliseconds ms;
//	std::chrono::microseconds cs;
//	std::chrono::nanoseconds ns;
//	
//	switch (time_stamp_type)
//	{
//	case 0:
//		ss << buffer;
//		break;
//	case 1:
//		ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
//		ss << buffer << ":" << ms.count();
//		break;
//	case 2:
//		ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
//		cs = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()) % 1000000;
//		ss << buffer << ":" << ms.count() << ":" << cs.count() % 1000;
//		break;
//	case 3:
//		ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
//		cs = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()) % 1000000;
//		ns = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()) % 1000000000;
//		ss << buffer << ":" << ms.count() << ":" << cs.count() % 1000 << ":" << ns.count() % 1000;
//		break;
//	default:
//		ss << buffer;
//		break;
//	}
//	
//	return ss.str();
//}

int main()
{
time_t  time_mico= system_clock::now().time_since_epoch().count();
	cout<<ctime(&time_mico)<<endl;
}
