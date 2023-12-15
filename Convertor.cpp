#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <cmath>

using std::cout, std::endl, std::setw, std::setfill;

char intToChar(int val)
{
    char output;
    if(val < 10)
        output = char(val + 48); // digit characters --- 0 - 9
    else if(val < 36)
        output = char(val + 87); // lowercase letters --- 10 - 35
    else if(val < 62)
        output = char(val + 29); // uppercase letters --- 36 - 61 
    else if(val == 62)
        output = '+'; // '+' character --- 62
    else if(val == 63)
        output = '/'; // '/' character --- 63
    else
    {
        cout << "non-recognized input passed: " << val << endl;
        output = '\0';
    }
    return output;
}
int charToInt(char &val, int &inBase)
{
    int output, intVal = int(val);
    if(val == '/') // '/' character
        output = 63;
    else if(val == '+') // '+' character
        output = 62;
    else if(isalpha(val)) 
        if(intVal > 96) // lowercase letters --- 97 - 122
            output = int(val) - 87;
        else
            output = int(val) - 29; // uppercase letters --- 65 - 90
    else if(isdigit(val)) // digits --- 48 - 57
        output = intVal - 48;
    else
    {
        cout << "Input Value Contains Invalid Digit For This Input Base: \'" << val << "\' in base " << inBase << "\n";
        return -1;
    }
    if(output >= inBase && inBase != 1)
    {
        cout << "Input Value Contains Invalid Digit For This Input Base: \'" << val << "\' in base " << inBase << "\n";
        return -1;
    }
    return output;
}

void printOutput(int &inBase, int &outBase, char* inVal, char* outVal)
{
    cout << setw(80) << setfill('-') << "\n";
    cout << "Input Value: " << inVal;
    cout << ", Input Base: " << inBase;
    cout << ", Output Base: " << outBase << "\n";
    cout << "Output Value: " << outVal << "\n";
    cout << setw(80) << setfill('-') << "\n";
}

char* convert(char* &inVal, int &inBase, int &outBase)
{
    size_t sum = 0, newSize = 0, size = 0, digitMultiple = 1;
    char* output;
    while(inVal[size] != '\0')
        size++;
    while(size > 0)
    {
        size--;
        int c = charToInt(inVal[size], inBase);
        if(c == -1)
        {
            output = new char[1];
            output[0] = '\0';
            return output;
        }
        sum += digitMultiple * c;
        digitMultiple *= inBase;
    }
    size = sum;
    while(size > 0)
    {
        size /= outBase;
        newSize++;
    }
    newSize = newSize == 0 ? 1 : newSize;
    size = newSize;
    output = new char[newSize];
    while(sum > 0)
    {
        output[--size] = intToChar(sum % outBase);
        sum /= outBase;
    }
    output[newSize] = '\0';
    return output;
}

int main (int argc, char** argv)
{
    if(argc != 4)
    {
        cout << "Incompatible Number Of Arguments: " << argc - 1 << " (should be 3)\n";
        cout << "Program call should conform to \"./nsc (input value) (input base) (output base)\"\n"; 
        return 1;
    }
    char* inVal = argv[1];
    int inBase = atoi(argv[2]);
    int outBase = atoi(argv[3]);
    char* outVal = convert(inVal, inBase, outBase);
    if(outVal[0] == '\0')
        return -1;
    printOutput(inBase, outBase, inVal, outVal);
    return 0;
}

