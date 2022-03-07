#include <bits/stdc++.h>

using namespace std;

// Define the structs Workshops and Available_Workshops.
// Implement the functions initialize and CalculateMaxWorkshops

struct Workshop
{
    int start_time;
    int end_time;
    int duration;

    Workshop(int _start_time, int _duration)
    {
        start_time = _start_time;
        duration = _duration;
        end_time = start_time + duration;
    }
};

struct Available_Workshops
{
    vector<Workshop> workshops;
};

Available_Workshops *initialize(int start_time[], int duration[], int n)
{
    Available_Workshops *aw = new Available_Workshops();
    for (int i = 0; i < n; i++)
    {
        aw->workshops.push_back(Workshop(start_time[i], duration[i]));
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

template <typename DataType, typename ReturnType>
ReturnType reduce(function<ReturnType(const ReturnType &, const DataType &)> func, const vector<DataType> &v, const ReturnType &initial)
{
    ReturnType result = initial;
    for (const DataType &d : v)
    {
        result = func(result, d);
    }
    return result;
}

struct Candidate
{
    int start_time;
    int count;

    Candidate(int _start_time, int _count)
    {
        start_time = _start_time;
        count = _count;
    }
};

bool later(Workshop &a, Workshop &b)
{
    return a.start_time > b.start_time;
}

function<bool(const Candidate &)> after(int end_time)
{
    return [end_time](const Candidate &c) -> bool
    {
        return c.start_time >= end_time;
    };
}

template <typename DataType>
function<bool(const DataType &)> inv(function<bool(const DataType &)> func)
{
    return [func](const DataType &d) -> bool
    {
        return !func(d);
    };
}

int reducer(const int &count, const Candidate &c)
{
    return max(c.count, count);
}

int CalculateMaxWorkshops(Available_Workshops *ptr)
{
    sort(ptr->workshops.begin(), ptr->workshops.end(), later);
    vector<Candidate> candidates;
    for (const Workshop workshop : ptr->workshops)
    {
        auto not_conflict = after(workshop.end_time);
        if (!any_of(candidates.begin(), candidates.end(), not_conflict))
        {
            candidates.push_back(Candidate(workshop.start_time, 1));
        }
        const int size = candidates.size();
        for (int index = 0; index < size; index++)
        {
            if (not_conflict(candidates[index]))
            {
                candidates[index].start_time = workshop.start_time;
                candidates[index].count++;
            }
        }
    }
    return reduce<Candidate, int>(reducer, candidates, 0);
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
