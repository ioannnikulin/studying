#include "cormen.h"

#include <vector>
#include <map>
#include <iostream>
#include <conio.h>

using namespace std;

int find_max_subarray_recursive(vector<int> data, int from_incl, int to_excl)
{
    if (from_incl == to_excl - 1) return data[from_incl];
    int mid = (from_incl + to_excl) / 2;

    int best_left = 0, best_right = 0;
    int cur_left = 0, cur_right = 0;
    for (int i = mid - 1; i >= from_incl; i--)
    {
        cur_left += data[i];
        best_left = max(best_left, cur_left);
    }
    for (int i = mid; i < to_excl; i++)
    {
        cur_right += data[i];
        best_right = max(best_right, cur_right);
    }
    int here = best_left + best_right;
    //cout << from_incl << " " << to_excl << " : " << here << endl;
    //getch();

    int left = find_max_subarray_recursive(data, from_incl, mid);
    int right = find_max_subarray_recursive(data, mid, to_excl);

    return max(max(left, right), here);
}

int find_max_subarray_dynamic(vector<int> data)
{
    for (auto &i: data) cout << i << " ";
    cout << endl;
    int lowest = data[0];
    int cur_sum = 0;
    int best_sum = 0;
    for (int i = 1; i < data.size(); i++)
    {
        if (data[i] < lowest)
        {
            cur_sum = 0;
            lowest = data[i];
        }
        else
        {
            cur_sum += data[i] - data[i - 1];
            best_sum = max(best_sum, cur_sum);
        }
        cout << i << " " << data[i] << " " << cur_sum << endl;
    }
    return best_sum;
}

void find_max_subarray()
{
    //cormen edition 3, ch 4.1
    vector<int> data = {100, 113, 110, 85, 105, 102, 86, 63, 81, 101, 94, 106, 101, 79, 94, 90, 97};
    vector<int> deltas(data.size() - 1);
    for (int i = 0; i < data.size() - 1; i++)
    {
        deltas[i] = data[i + 1] - data[i];
    }
    const int mode_recursive = 0;
    const int mode_dynamic = 1;
    const int mode = mode_dynamic;
    if (mode == mode_recursive)
    {
        cout << find_max_subarray_recursive(deltas, 0, deltas.size()) << endl;
    }
    else
    {
        cout << find_max_subarray_dynamic(data) << endl;
    }
}
