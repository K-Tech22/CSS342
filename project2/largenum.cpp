#include "largenum.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

using namespace std;

ostream &operator<<(ostream &out, const LargeNum &no)
{
    string s = no.number;
    int neg = s.length() - 3;
    while (neg > 0)
    {
        s.insert(neg, ",");
        neg = neg - 3;
    }
    out << s;
    return out;
}

LargeNum::LargeNum(const string &str) : number{str} {}

LargeNum::LargeNum(int anInteger) { number = to_string(anInteger); }

bool LargeNum::isZero() const
{
    if (number == "0")
    {
        return true;
    }
    return false;
}
LargeNum &LargeNum::negate()
{
    string x = "";
    if (isZero())
    {
        return *this;
    }
    else if (LargeNum(number) > LargeNum(0))
    {
        x = "-" + number;
    }
    else
    {
        for (int i = 0; i < number.length(); i++)
        {
            number += number[i];
        }
    }
    return *this;
}

LargeNum LargeNum::operator+(const LargeNum &rhs) const
{
    string a = rhs.number;
    string b = number;
    if (a.size() < b.size())
        swap(a, b);

    int sZ = a.size() - 1;

    for (int i = b.size() - 1; i >= 0; i--, sZ--)
        a[sZ] += (b[i] - '0');

    for (int i = a.size() - 1; i > 0; i--)
    {
        if (a[i] > '9')

        {
            int d = a[i] - '0';
            a[i - 1] = ((a[i - 1] - '0') + d / 10) + '0';
            a[i] = (d % 10) + '0';
        }
    }
    if (a[0] > '9')
    {
        string answer;
        answer += a[0];
        a[0] = ((a[0] - '0') % 10) + '0';
        answer[0] = ((answer[0] - '0') / 10) + '0';
        a = answer + a;
    }

    LargeNum result(a);
    return result;
}
LargeNum LargeNum::operator-(const LargeNum &rhs) const
{
    string num2 = rhs.number;
    string num1 = number;
    int n1 = stoi(num1);
    int n2 = stoi(num2);
    LargeNum result(n1 - n2);
    return result;
}

LargeNum LargeNum::operator*(const LargeNum &rhs) const
{
    string num1 = rhs.number;
    string num2 = number;
    string s = "";
    int n = max(num1.size(), num2.size());
    if (n < 5)
    {
        int n1 = stoi(num1);
        int n2 = stoi(num2);
        LargeNum result(n1 * n2);
        return result;
    }
    if ((num1 == "0") || (num2 == "0"))
    {
        LargeNum alpha(0);
        return alpha;
    }
    int size1 = num1.size();
    int size2 = num2.size();

    vector<int> result(size1 + size2, 0);

    int index1 = 0;
    int index2 = 0;

    for (int i = size1 - 1; i >= 0; i--)
    {

        int carry = 0;
        int ar = num1[i] - '0';

        index2 = 0;

        for (int j = size2 - 1; j >= 0; j--)
        {
            int br = num2[j] - '0';
            int sum = ar * br + result[index1 + index2] + carry;
            carry = sum / 10;
            result[index1 + index2] = sum % 10;
            index2++;
        }
        if (carry > 0)
            result[index1 + index2] += carry;

        index1++;
    }

    int i = result.size() - 1;
    while (i >= 0 && result[i] == 0)
        i--;

    while (i >= 0)
        s += to_string(result[i--]);

    LargeNum answer(s);
    return answer;
}
LargeNum LargeNum::operator/(const LargeNum &rhs) const
{
    string num2 = rhs.number;
    string num1 = number;
    int n1 = stoi(num1);
    int n2 = stoi(num2);
    LargeNum result(n1 / n2);
    return result;
}
bool LargeNum::operator==(const LargeNum &rhs) const
{
    string a = rhs.number;
    string b = number;
    int n = max(a.size(), b.size());
    for (int i = 0; i < n; i++)
    {
        if (a[i] == b[i])
        {
            return true;
        }
    }
    return false;
}
bool LargeNum::operator!=(const LargeNum &rhs) const
{
    string a = rhs.number;
    string b = number;
    int n = max(a.size(), b.size());
    for (int i = 0; i < n; i++)
    {
        if (a[i] != b[i])
        {
            return true;
        }
    }
    return false;
}
bool LargeNum::operator<(const LargeNum &rhs) const
{
    string a = rhs.number;
    string b = number;
    int answer = a.compare(b);
    if (answer > 0)
    {
        return true;
    }
    return false;
}
bool LargeNum::operator>(const LargeNum &rhs) const
{
    string a = rhs.number;
    string b = number;
    int answer = a.compare(b);
    if (answer < 0)
    {
        return true;
    }
    return false;
}
bool LargeNum::operator<=(const LargeNum &rhs) const
{
    string a = rhs.number;
    string b = number;
    int answer = a.compare(b);
    if (answer >= 0)
    {
        return true;
    }
    return false;
}
bool LargeNum::operator>=(const LargeNum &rhs) const
{
    string a = rhs.number;
    string b = number;
    int answer = a.compare(b);
    if (answer < 0)
    {
        return true;
    }
    return false;
}
LargeNum &LargeNum::operator++()
{
    LargeNum plus1 = LargeNum("1");
    *this = this->operator+(plus1);
    return *this;
}
LargeNum LargeNum::operator++(int)
{
    LargeNum thisCopy = *this;
    LargeNum plus1 = LargeNum("1");
    *this = thisCopy.operator+(plus1);
    return thisCopy;
}
LargeNum &LargeNum::operator--()
{
    LargeNum minus1 = LargeNum("1");
    *this = this->operator-(minus1);
    return *this;
}
LargeNum LargeNum::operator--(int)
{
    LargeNum thisCopy = *this;
    LargeNum minus1 = LargeNum("1");
    *this = thisCopy.operator-(minus1);
    return thisCopy;
}
