#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;

// judge the priority of operator
int priority(char op)
{
    if (op == '*' || op == '/')
    {
        return 2;
    }
    else if (op == '+' || op == '-')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

template <typename T>
T calculate(T num1, T num2, char op)
{
    switch (op)
    {
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

auto removeSpaces = [](std::string &str)
{
    str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
};
int main(int, char **)
{
    // string fomula = "1+3+(4-2)*5/5";
    // string fomula = "10.0*2.0/2.0+1.0";
    string fomula = "2.0*(2.0*3.0-3.0)-4.0";
    deque<double> dq_num;
    deque<char> dq_op;

    removeSpaces(fomula);
    int num_len = 0;
    int high_priority_calculate = 0;
    int create_new_num = 0;
    int end_flag = 0;
    for (int i = 0; i < fomula.size() + 1; i++)
    {
        // 如果遇到是数字，记录数字的长度
        if (fomula[i] >= '0' && fomula[i] <= '9' || fomula[i] == '.')
        {
            num_len++;
        }
        else if (fomula[i] == '+' || fomula[i] == '-' || 
                fomula[i] == '*' || fomula[i] == '/' || 
                i == fomula.size()|| 
                fomula[i] == '(' || fomula[i] == ')')
        {
            if (fomula[i] == '(')
            {
                // 将左括号存入deque中
                dq_op.push_back(fomula[i]);
                continue;
            }
            else if (fomula[i] == ')')
            {
                cout << "address:" << i - num_len << "  " << i << endl;
                cout << "Slice " << fomula.substr(i - num_len, num_len) << endl;
                // 将字符串的数字部分进行切片，转换成double类型，存入deque中
                dq_num.push_back(stod(fomula.substr(i - num_len, num_len)));
                num_len = 0;
                auto iter_op = dq_op.rbegin();
                while(*iter_op != '(')
                {
                    char op = *iter_op;
                    auto iter_num = dq_num.rbegin();
                    double num1 = *iter_num;
                    double num2 = *(iter_num + 1);
                    dq_num.pop_back();
                    dq_num.pop_back();
                    double result = calculate(num2, num1, op);
                    cout << "calculate result:" << result << endl;
                    dq_num.push_back(result);
                    dq_op.erase(dq_op.end() - 1);
                    iter_op = dq_op.rbegin();
                }
                dq_op.erase(dq_op.end() - 1);
                end_flag  = 1;
                high_priority_calculate = 0;
                continue;
            }

            if (i != fomula.size())
            { 
                // 将运算符存入deque中
                dq_op.push_back(fomula[i]);
                if (end_flag == 1)
                {
                    end_flag = 0;
                    continue;
                }
            }
            cout << "address:" << i - num_len << "  " << i << endl;
            cout << "Slice " << fomula.substr(i - num_len, num_len) << endl;
            // 将字符串的数字部分进行切片，转换成double类型，存入deque中
            dq_num.push_back(stod(fomula.substr(i - num_len, num_len)));
            num_len = 0;
            if (dq_op.size() > 1)
            {
                auto iter_op = dq_op.rbegin();
                char op1 = *iter_op;
                char op2 = *(iter_op + 1);
                cout << "op1:" << op1 << " op2:" << op2 << endl;
                auto num_size = 0;
                /*如果当前运算符的优先级大于前一个运算符的优先级，那么标志位自增1,
                需要将队列尾的数字与下一个即将到来的数字进行优先运算*/
                if (op2 == '(')
                {
                    continue;
                }
                if (priority(op1) > priority(op2))
                {
                    high_priority_calculate += 1;
                    // 如果当前运算符是最后一个高优先级运算符，那么标志位自增1
                    create_new_num = i == fomula.size() ? 1 : 0;
                }
                else
                {
                    create_new_num += 1;
                }
                // 当标志位大于1时，说明有高优先级的运算符，进行高优先级的运算
                if (high_priority_calculate > 0 && create_new_num > 0)
                {
                    auto iter_num = dq_num.rbegin();
                    double num1 = *iter_num;
                    double num2 = *(iter_num + 1);
                    dq_num.pop_back();
                    dq_num.pop_back();
                    double result = calculate(num2, num1, i == fomula.size() ? op1 : op2);
                    cout << "high priority calculate result:" << result << endl;
                    dq_num.push_back(result);
                    dq_op.erase(dq_op.end() - (i == fomula.size() ? 1 : 2));
                    high_priority_calculate = 0;
                    create_new_num = 0;
                }
            }
        }
        
    }
    cout << "dq_num:";
    for (auto i : dq_num)
    {
        cout << i << " ";
    }
    cout << endl;

    for (auto iter = dq_op.begin(); iter != dq_op.end(); iter++)
    {
        cout << *iter << endl;
        auto iter_num = dq_num.begin();
        double num1 = *iter_num;
        double num2 = *(iter_num + 1);
        dq_num.pop_front();
        dq_num.pop_front();
        double result = calculate(num1, num2, *iter);
        cout << "result" << result << endl;
        dq_num.push_front(result);
    }
}
