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
    Matrix a(Matrix::constr_modes::mode_conseq, 2, 2);
    Matrix b(Matrix::constr_modes::mode_conseq, 2, 3);
    cout << a << endl << b << endl;
    a = a * b;
    cout << a << endl;
    return 0;
}
