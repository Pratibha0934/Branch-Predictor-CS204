#include <bits/stdc++.h>

using namespace std;

vector<string> split(string s)
{
    vector<string> output;
    string token;

    istringstream iss(s);

    while (iss >> token)
    {
        output.push_back(token);
    }

    return output;
}

string decToHex(long long dec)
{
    string hex = "";

    int rem;
    char ch;

    while (dec != 0)
    {
        rem = dec % 16;

        if (rem < 10)
        {
            ch = rem + 48;
        }
        else
        {
            ch = rem + 55;
        }

        hex += ch;
        dec = dec / 16;
    }

    if (hex == "")
    {
        hex += '0';
    }

    reverse(hex.begin(), hex.end());

    return ("0x" + hex);
}