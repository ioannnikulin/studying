#include "Matrix.h"
#include <iomanip>
#include <cmath>
#include <conio.h>

using namespace std;


void schtrassen_mult_rec(const Matrix & p_a, const Matrix & p_b, Matrix & p_res, array<Submatrix, 3> p_subm)
{
    int sz = p_subm[0][sbm_row][sbm_to] - p_subm[0][sbm_row][sbm_from];
    if (sz < 1)
    {
        cerr << "Error: request to multiply empty matrices" << endl;
    }
    if (sz == 1)
    {
        p_res.set_item(p_subm[2][sbm_row][sbm_from],
                       p_subm[2][sbm_col][sbm_from],
                       p_a.get_item(p_subm[0][sbm_row][sbm_from], p_subm[0][sbm_col][sbm_from]) * p_b.get_item(p_subm[1][sbm_row][sbm_from], p_subm[1][sbm_col][sbm_from]));
        return;
    }

    array<int, 3> row_mid, col_mid;
    for (int i = 0; i < 3; i++)
    {
        row_mid[i] = (p_subm[i][sbm_row][sbm_to] + p_subm[i][sbm_row][sbm_from]) / 2;
        col_mid[i] = (p_subm[i][sbm_col][sbm_to] + p_subm[i][sbm_col][sbm_from]) / 2;
    }

    array<array<Submatrix, 4>, 3> subm;
    const int a = 0, b = 1, c = 2;
    const int i11 = 0, i12 = 1, i21 = 2, i22 = 3;

    for (int i = 0; i < 3; i ++)
    {
        subm[i][i11][sbm_row][sbm_from] = p_subm[i][sbm_row][sbm_from];
        subm[i][i11][sbm_row][sbm_to] = row_mid[i];
        subm[i][i11][sbm_col][sbm_from] = p_subm[i][sbm_row][sbm_from];
        subm[i][i11][sbm_col][sbm_to] = col_mid[i];

        subm[i][i12][sbm_row][sbm_from] = p_subm[i][sbm_row][sbm_from];
        subm[i][i12][sbm_row][sbm_to] = row_mid[i];
        subm[i][i12][sbm_col][sbm_from] = col_mid[i];
        subm[i][i12][sbm_col][sbm_to] = p_subm[i][sbm_row][sbm_to];

        subm[i][i21][sbm_row][sbm_from] = row_mid[i];
        subm[i][i21][sbm_row][sbm_to] = p_subm[i][sbm_row][sbm_to];
        subm[i][i21][sbm_col][sbm_from] = p_subm[i][sbm_row][sbm_from];
        subm[i][i21][sbm_col][sbm_to] = col_mid[i];

        subm[i][i22][sbm_row][sbm_from] = row_mid[i];
        subm[i][i22][sbm_row][sbm_to] = p_subm[i][sbm_row][sbm_to];
        subm[i][i22][sbm_col][sbm_from] = col_mid[i];
        subm[i][i22][sbm_col][sbm_to] = p_subm[i][sbm_row][sbm_to];
    }

    vector<Matrix> s(11, Matrix(Matrix::constr_modes::mode_copy, ceil(sz / 2.0), ceil(sz / 2.0), 0));//11 though we need 10 - to match book numbering for clarity
    //possible error above in sz / 2

    cout << p_b.submatrix(subm[b][i12]) << endl << p_b.submatrix(subm[b][i22]) << endl;//TODO what should we do if the matrix size is not power of 2?

    s[1] = p_b.subtract(subm[b][i12], p_b, subm[b][i22]).submatrix(subm[b][i12]);
    s[2] = p_a.add(subm[a][i11], p_a, subm[a][i12]).submatrix(subm[a][i11]);
    s[3] = p_a.add(subm[a][i21], p_a, subm[a][i22]).submatrix(subm[a][i21]);
    s[4] = p_b.subtract(subm[b][i21], p_b, subm[b][i11]).submatrix(subm[b][i21]);
    s[5] = p_a.add(subm[a][i11], p_a, subm[a][i22]).submatrix(subm[a][i11]);
    s[6] = p_b.add(subm[b][i11], p_b, subm[b][i22]).submatrix(subm[b][i11]);
    s[7] = p_a.subtract(subm[a][i12], p_a, subm[a][i22]).submatrix(subm[a][i12]);
    s[8] = p_b.add(subm[b][i21], p_b, subm[b][i22]).submatrix(subm[b][i21]);
    s[9] = p_a.subtract(subm[a][i11], p_a, subm[a][i21]).submatrix(subm[a][i11]);
    s[10] = p_b.add(subm[b][i11], p_b, subm[b][i12]).submatrix(subm[b][i11]);

    Submatrix whole;
    whole[sbm_row][sbm_from] = 0;
    whole[sbm_row][sbm_to] = ceil(sz / 2.0);
    whole[sbm_col][sbm_from] = 0;
    whole[sbm_col][sbm_to] = ceil(sz / 2.0);

    vector<Matrix> p(8, Matrix(Matrix::constr_modes::mode_copy, ceil(sz / 2.0), ceil(sz / 2.0), 0));//8 though we need 7 - to match book numbering for clarity

    schtrassen_mult_rec(p_a, s[1], p[1], {subm[a][i11], whole, whole});
    schtrassen_mult_rec(s[2], p_b, p[2], {whole, subm[b][i22], whole});
    schtrassen_mult_rec(s[3], p_b, p[3], {whole, subm[b][i11], whole});
    schtrassen_mult_rec(p_a, s[4], p[4], {subm[a][i22], whole, whole});
    schtrassen_mult_rec(s[5], s[6], p[5], {whole, whole, whole});
    schtrassen_mult_rec(s[7], s[8], p[6], {whole, whole, whole});
    schtrassen_mult_rec(s[9], s[10], p[7], {whole, whole, whole});

    p_res.add_here(subm[c][i11], p[5] + p[4] - p[2] + p[6], whole);
    p_res.add_here(subm[c][i12], p[1] + p[2], whole);
    p_res.add_here(subm[c][i21], p[3] + p[4], whole);
    p_res.add_here(subm[c][i22], p[5] + p[1] - p[3] - p[7], whole);
}


Matrix Matrix::schtrassen_multiply(const Matrix & p_a) const
{
    int n = this->rows();
    if (n != this->cols() or n != p_a.rows() or n != p_a.cols())
    {
        cerr << "cannot use schtrassen matrix multiplication method on nonsquare matrices" << endl;
        Matrix e(err);
        return e;
    }
    Matrix res(constr_modes::mode_copy, n, n);
    array<Submatrix, 3> sbm;
    for (int i = 0; i < 3; i ++)
    {
        sbm[i][sbm_row][sbm_from] = 0;
        sbm[i][sbm_row][sbm_to] = n;
        sbm[i][sbm_col][sbm_from] = 0;
        sbm[i][sbm_col][sbm_to] = n;
    }
    schtrassen_mult_rec(*this, p_a, res, sbm);
    return res;
}
