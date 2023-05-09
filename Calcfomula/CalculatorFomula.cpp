#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;

// judge the priority of operator
int priority(char op) {
    if (op == '*' || op == '/') {
        return 2;
    } else if (op == '+' || op == '-') {
        return 1;
    } else {
        return 0;
    }
}

template <typename T>
T calculate(T num1, T num2, char op) {
    switch (op) {
        case '+':
            return num1 + num2;
        case '-':
            return num1 - num2;
        case '*':
            return num1 * num2;
        default:
            return num1 / num2;
    }
}

auto removeSpaces = [](std::string& str) {
    str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
};
int main(int, char**) {
    // string fomula = "1+3+(4-2)*5/5";
    string fomula = "11.3+3.2-10.0+0.2";
    deque<double> dq_num;
    deque<char> dq_op;

    removeSpaces(fomula);
    int num_len = 0;
    for(int i=0;i<fomula.size()+1;i++){
        // 如果遇到是数字，记录数字的长度
        if(fomula[i]>='0'&&fomula[i]<='9'||fomula[i]=='.'){
            num_len++;
        }        
        else if (fomula[i]=='+'||fomula[i]=='-'||fomula[i]=='*'||fomula[i]=='/'||i==fomula.size())
        {
            if (i!=fomula.size())
            {
               // 将运算符存入deque中
                dq_op.push_back(fomula[i]);
            }
            cout << "address:" << i-num_len<<"  "<<i<< endl;
            cout<<"Slice "<<fomula.substr(i-num_len,num_len)<<endl;
            // 将字符串的数字部分进行切片，转换成double类型，存入deque中
            dq_num.push_back(stod(fomula.substr(i-num_len,num_len)));
            num_len=0;
        }

    }
    cout << "dq_num:";
    for(auto i:dq_num){
        cout<<i<<" ";
    }
    cout<<endl;

    for (auto iter = dq_op.begin(); iter != dq_op.end(); iter++)
    {
        cout << *iter << endl;
        auto iter_num = dq_num.begin();
        double num1 = *iter_num;
        double num2 = *(iter_num+1);
        dq_num.pop_front();
        dq_num.pop_front();
        double result = calculate(num1, num2, *iter);
        cout << "result" << result << endl;
        dq_num.push_front(result);
    }
    
}
