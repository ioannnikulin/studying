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
    Matrix a(Matrix::constr_modes::mode_conseq, 2, 3);
    Matrix b(Matrix::constr_modes::mode_copy, 2, 3, 1);
    cout << b << endl;
    b += a;
    cout << b << endl;
    b = a + a;
    cout << b << endl;
    return 0;
}
