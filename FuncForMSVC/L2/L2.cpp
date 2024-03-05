#include <iostream>

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


int main()
{
    cout << DecToHex(0x0,4,false) << endl;
    system("pause");
    return 0;
}
