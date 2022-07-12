#include <iostream>
#include "cormen.h"
#include "Matrix.h"

using namespace std;

int main()
{
    /*Matrix m(Matrix::constr_modes::mode_copy, 2, 3, 4);
    m.set_item(1, 0, 5);
    cout << m << endl;
    cin >> m;
    cout << endl << m << endl;
    */
    Matrix x1(Matrix::constr_modes::mode_copy, 3, 1);
    Matrix x2(Matrix::constr_modes::mode_copy, 3, 1);
    Matrix x3(Matrix::constr_modes::mode_copy, 3, 1);
    x1.set_item(0, 0, 1);
    x1.set_item(1, 0, 2);
    x1.set_item(2, 0, 3);
    x2.set_item(0, 0, 2);
    x2.set_item(1, 0, 6);
    x2.set_item(2, 0, 4);
    x3.set_item(0, 0, 4);
    x3.set_item(1, 0, 11);
    x3.set_item(2, 0, 9);
    Matrix res(x1);
    res = x1;
    cout << res << endl;
    return 0;
}
