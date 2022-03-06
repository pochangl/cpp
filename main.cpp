#include <sstream>
#include <vector>
#include <iostream>
using namespace std;

vector<int> parseInts(string str)
{
    stringstream ss(str);
    string num_str;
    vector<int> result;
    while (getline(ss, num_str, ','))
    {
        result.push_back(stoi(num_str));
    }
    return result;
}

int main()
{
    string str;
    cin >> str;
    vector<int> integers = parseInts(str);
    for (int i = 0; i < integers.size(); i++)
    {
        cout << integers[i] << "\n";
    }

    return 0;
}