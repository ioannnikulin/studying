#include "cormen.h"

#include <vector>
#include <iostream>
#include <conio.h>

using namespace std;

int go_arr(vector<int> data, int from_incl, int to_excl)
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

    int left = go_arr(data, from_incl, mid);
    int right = go_arr(data, mid, to_excl);

    return max(max(left, right), here);
}

void find_max_subarray_recursive()
{
    //cormen edition 3, ch 4.1
    vector<int> data = {100, 113, 110, 85, 105, 102, 86, 63, 81, 101, 94, 106, 101, 79, 94, 90, 97};
    vector<int> deltas(data.size() - 1);
    for (int i = 0; i < data.size() - 1; i++)
    {
        deltas[i] = data[i + 1] - data[i];
    }
    cout << go_arr(deltas, 0, deltas.size()) << endl;
}
