#include <iostream>
#include <deque>
#include <algorithm>
#include <map>
using namespace std;

#define DEBUG 0
auto removeSpaces = [](std::string &str)
{
    str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
};

class fomulacalculate
{
    private:
        deque<double> dq_num;
        deque<char> dq_op;
        int calc_index = 0;
        // Operator priority hash table
        map<char, int> priority = {
            {'+', 1},
            {'-', 1},
            {'*', 2},
            {'/', 2},
            {'(', 10},
            {')', 10}
        };
        
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
        // 根据进程内运算符优先级进行调整
        void adjust()
        {
            // 确保运算符数量大于1
            if(dq_op.size() > 1)
            {
                auto iter = dq_op.rbegin();
                char op1 = *iter;
                char op2 = *(iter + 1);
                // 如果当前运算符的优先级大于前一个运算符的优先级，那么就进行运算
                if(priority[op1] > priority[op2])
                {
                    double num1 = dq_num.back();
                    dq_num.pop_back();
                    double num2 = dq_num.back();
                    dq_num.pop_back();
                    char op = dq_op.back();
                    dq_op.pop_back();
                    dq_num.push_back(calculate(num2, num1, op));
                }
            }
        }

    public:
        fomulacalculate(int num)
        {
            dq_num.clear();
            dq_op.clear();

            calc_index = num;
        }
        // 添加数字
        void addnum(double num)
        {
            dq_num.push_back(num);
            adjust();
        }
        // 添加运算符
        void addop(char op)
        {
            dq_op.push_back(op);
            
        }
        // 计算当前进程最终结果
        double getresult()
        {
            for(auto op:dq_op)
            {
                auto iter_num = dq_num.begin();
                double num1 = *iter_num;
                dq_num.pop_front();
                double num2 = *(iter_num + 1);
                dq_num.pop_front();
                double result = calculate(num1, num2, op);
                #if DEBUG
                cout << "step result is :" << result << endl;
                #endif
                dq_num.push_front(result);
            }
            return dq_num.back();
        }

};
// 将字符串转换为数字,切片取值
double slicetransform(string str, int start, int length)
{
    #if DEBUG
    cout << "start:" << start << " length:" << length << endl;
    cout << "Slice " << str.substr(start, length) << endl;
    #endif
    return stod(str.substr(start, length));
}

void Calculator(string fomula)
{
    // 计算的主体
    deque<fomulacalculate> dq_calculate;
    int num_len = 0;
    int calc_count = 0;
    // 初始计算进程 0
    fomulacalculate maincalculate(calc_count);
    dq_calculate.push_back(maincalculate);
    for (int index = 0; index < fomula.size() + 1; index++)
    {
            // 如果遇到是数字，记录数字的长度
            if (fomula[index] >= '0' && fomula[index] <= '9' || fomula[index] == '.')
            {
                num_len++;
            }
            else if (fomula[index] == '+' || fomula[index] == '-' || fomula[index] == '*' || fomula[index] == '/')
            {
                if (fomula[index - 1] != ')') // 如果不是右括号
                {
                    // 将数字添加到当前进程
                    dq_calculate.back().addnum(slicetransform(fomula, index - num_len, num_len));
                    // 将运算符添加到当前进程
                    dq_calculate.back().addop(fomula[index]);
                    // 重置数字长度
                    num_len = 0;
                }
                else
                {
                    dq_calculate.back().addop(fomula[index]);
                }
            }
            else if (fomula[index] == '(' || fomula[index] == ')')
            {
                if (fomula[index] == '(') // 如果是左括号，创建一个新的计算进程
                {
                    calc_count++;
                    fomulacalculate subcalculate(calc_count);
                    dq_calculate.push_back(subcalculate);
                }
                else // 如果是右括号，计算当前进程的结果，然后将结果传递给上一个进程
                {
                    if (fomula[index - 1] != ')') // 如果不是右括号
                    {
                        dq_calculate.back().addnum(slicetransform(fomula, index - num_len, num_len));
                        num_len = 0;
                    }
                    double lastresult = dq_calculate.back().getresult();
                    dq_calculate.pop_back();                // 删除当前进程
                    dq_calculate.back().addnum(lastresult); // 将结果传递给上一个进程
                }
            }
            else if (index == fomula.size()) // 如果达到边界
            {
                if (fomula[index - 1] != ')') // 如果不是右括号
                {
                    dq_calculate.back().addnum(slicetransform(fomula, index - num_len, num_len));
                    num_len = 0;
                }
            }
    }

    cout << "Result of fomula:"<<fomula<<" = "<< dq_calculate.back().getresult() << endl;
}


int main()
{
    string eg_fomula = "2.0*(4.0+(3.0+(1.0*2.0)))*(2.0+2.0)/2.0";
    removeSpaces(eg_fomula);
    Calculator(eg_fomula);
    
    cout << "Please input fomula:";
    cin>>eg_fomula;
    removeSpaces(eg_fomula);
    Calculator(eg_fomula);
    system("pause");
}