#include <bits/stdc++.h>

using namespace std;

//Define the structs Workshops and Available_Workshops.
//Implement the functions initialize and CalculateMaxWorkshops

struct Workshops
{
    int start_time;
    int end_time;
    int duration;
};

struct Available_Workshops
{
    vector<Workshops> workshops;
};

Available_Workshops *initialize(int start_time[], int duration[], int n)
{
    Available_Workshops *aw = new Available_Workshops();
    for (int i = 0; i < n; i++)
    {
        aw->workshops.push_back(Workshops());
        Workshops &w = aw->workshops[i];
        w.start_time = start_time[i];
        w.duration = duration[i];
        w.end_time = w.start_time + w.duration;
    }
    return aw;
};

int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

bool earlier(Workshops &a, Workshops &b)
{
    return a.start_time < b.start_time;
}

int search(vector<Workshops> &workshops, int start_index, int start_time)
{
    int result = 0;
    for (; start_index < workshops.size(); start_index++)
    {
        Workshops &ws = workshops[start_index];
        if (ws.start_time >= start_time)
        {
            int count = search(workshops, start_index + 1, ws.end_time);
            result = max(count + 1, result);
        }
    }
    return result;
}

int CalculateMaxWorkshops(Available_Workshops *ptr)
{
    sort(ptr->workshops.begin(), ptr->workshops.end(), earlier);
    return search(ptr->workshops, 0, 0);
};

int main(int argc, char *argv[])
{
    int n; // number of workshops
    cin >> n;
    // create arrays of unknown size n
    int *start_time = new int[n];
    int *duration = new int[n];

    for (int i = 0; i < n; i++)
    {
        cin >> start_time[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> duration[i];
    }

    Available_Workshops *ptr;
    ptr = initialize(start_time, duration, n);
    cout << CalculateMaxWorkshops(ptr) << endl;
    return 0;
}
