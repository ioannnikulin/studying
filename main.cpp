#include <iostream>
#include "cormen.h"
#include "Matrix.h"

using namespace std;

int main()
{
    Matrix x1(Matrix::constr_modes::mode_conseq, 8, 8);
    Submatrix sbm;
    sbm[sbm_row][sbm_from] = 1;
    sbm[sbm_row][sbm_to] = 3;
    sbm[sbm_col][sbm_from] = 2;
    sbm[sbm_col][sbm_to] = 5;
    Matrix x2(x1.submatrix(sbm));
    cout << x1 << endl << x2 << endl;
    /*Matrix x2(x1);
    x2 *= 2;
    Matrix x3 = x1 * x2;
    cout << x3;*/
    return 0;
}
