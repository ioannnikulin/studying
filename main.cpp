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
    Matrix x1(Matrix::constr_modes::mode_conseq, 3, 3);
    x1.set_item(2, 2, 10);
    cout << x1 << endl << x1.determinant() << endl;
    return 0;
}
