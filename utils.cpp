#include <sstream>
#include <vector>
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