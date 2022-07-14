#include <iostream>
#include "cormen.h"
#include "Matrix.h"

using namespace std;

int main()
{
    /*Matrix x1(Matrix::constr_modes::mode_conseq, 8, 8);
    Matrix x2(x1);
    x2 *= 2;
    cout << x1 << endl << x2 << endl;
    Matrix x3 = x1 * x2;
    cout << x3;*/
    Matrix x1(Matrix::constr_modes::mode_conseq, 5, 6);
    Matrix x2(Matrix::constr_modes::mode_copy, 6, 13, 1);
    cout << x1 << endl << x2 << endl;
    Submatrix sbm;
    sbm[sbm_row][sbm_from] = 1;
    sbm[sbm_row][sbm_to] = 3;
    sbm[sbm_col][sbm_from] = 2;
    sbm[sbm_col][sbm_to] = 5;
    Submatrix sbm1;
    sbm1[sbm_row][sbm_from] = 2;
    sbm1[sbm_row][sbm_to] = 4;
    sbm1[sbm_col][sbm_from] = 4;
    sbm1[sbm_col][sbm_to] = 7;
    Matrix x3(x1.subtract(sbm, x2, sbm1));
    cout << x3 << endl;
    return 0;
}
