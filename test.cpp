//
// Created by zlq on 2023/1/5.
//
#include <iostream>

using namespace std;

int main(){
//    try {
////        throw 1;
//        throw "error";
//    }
//    catch (int& Input) {
//        cout<<Input<<endl;
//    }
//    catch (char const* Input) {
//        cout<<Input<<endl;
//    }
//    catch (...) {
//        cerr<<"Unhandle Exception"<<endl;
//    }
//    throw invalid_argument("Size has to be bigger than 0!!!");
//    throw logic_error("This is horrible logic_error");
    auto Calculate = [&](double num1,double num2)->double{
        double ret = 0;
        try {
            if (num2==0)
            {
                throw logic_error("You must not devide a num equals to zero!!! ");
            }
            ret = num1/num2;
        }
        catch (const char* Input)
        {
            cout<<Input<<endl;
        }
        catch (logic_error&) {
            cout<<"You cause a logic_error return with 0"<<endl;
            return 0;
        }
        return ret;
    };
    cout<<Calculate(1.2,0)<<endl;
}