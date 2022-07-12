#include <iostream>
#include "cormen.h"
#include "Matrix.h"

using namespace std;

int main()
{
    Matrix x1(Matrix::constr_modes::mode_conseq, 8, 8);
    Matrix x2(x1);
    x2 *= 2;
    cout << x1 << endl << x2 << endl;
    Matrix x3 = x1 * x2;
    cout << x3;
    return 0;
}
