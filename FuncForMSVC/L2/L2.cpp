#include <iostream>
#include <Windows.h>
#include <string>
#include <sstream>
using namespace std;


string DecToHex(int decimal, int fixlength = 0, bool prefix = false) {
    string hex = "";
    if (decimal == 0)hex = "0";
    else {
        while (decimal > 0) {
            int remainder = decimal % 16;
            char hexDigit = (remainder < 10) ? (remainder + '0') : (remainder - 10 + 'A');
            hex += hexDigit;
            decimal /= 16;
        }
        reverse(hex.begin(), hex.end());
    }
    if (fixlength > hex.length())hex = string(fixlength - hex.length(), '0') + hex;
    if (prefix) hex = "0x" + hex;
    return hex;
}

//C 语言 风格
void DebugPrint(const char* format, ...) {
    char buffer[1024];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    OutputDebugStringA(buffer);
}
// C++ cout 风格 不支持 endl
class DebugPrintC {
public:
    template <typename T>
    DebugPrintC& operator<<(const T& value) {
        std::ostringstream oss;
        oss << value;
        OutputDebugStringA(oss.str().c_str());
        return *this;
    }
};

DebugPrintC dcout;



int main()
{
    cout << DecToHex(0x0,4,false) << endl;
    DebugPrint("Site:%d test result is %f %s \n", 1, 3.145, "OK");
    
    dcout << "Hello, " << "World! " << 42 << "value is " << 3.1255656 << "\n";
    system("pause");
    return 0;
}
