#include <iostream>
#include "cormen.h"
#include "Matrix.h"

using namespace std;

int main()
{
    Matrix m(2, 3, 4);
    m.set_item(1, 0, 5);
    cout << m << endl;
    cin >> m;
    cout << endl << m << endl;
    return 0;
}
