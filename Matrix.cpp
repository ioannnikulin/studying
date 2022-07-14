#include "Matrix.h"
#include <ios>
#include <cmath>

using namespace std;

Matrix::Matrix(const constr_modes constr_mode, const int p_rows, const int p_cols, const int p_val)
{
    switch(constr_mode)
    {
        case mode_copy:
            m_items = vector<vector<int>>(p_rows, vector<int>(p_cols, p_val));
            break;
        case mode_identity:
            m_items = vector<vector<int>>(p_rows, vector<int>(p_rows, 0));
            for (int i = 0; i < p_rows; i++)
            {
                m_items[i][i] = 1;
            }
            break;
        case mode_conseq:
            m_items = vector<vector<int>>(p_rows, vector<int>(p_cols, 0));
            {
                int val = 0;
                for (int r = 0; r < p_rows; r ++)
                {
                    for (int c = 0; c < p_cols; c ++)
                    {
                        m_items[r][c] = val ++;
                    }
                }
            }
            break;
        default:
            cerr << "Error: unrecognized matrix creation mode" << endl;
            m_items = vector<vector<int>>(1, vector<int>(1, 0));
    }
}

Matrix::~Matrix()
{

}

int Matrix::get_item(const int p_row, const int p_col) const
{
    return m_items[p_row][p_col];
}

void Matrix::set_item(const int p_row, const int p_col, const int p_val)
{
    if (p_row >= this->rows())
    {
        cerr << "cannot assign value: no such row" << endl;
        return;
    }
    if (p_col >= this->cols())
    {
        cerr << "cannot assign value: no such column" << endl;
        return;
    }
    m_items[p_row][p_col] = p_val;
}

ostream & operator<<(ostream & p_os, const Matrix & p_m)
{
    int rows = p_m.rows();
    int cols = p_m.cols();
    if (rows <= 0)
    {
        p_os << "empty matrix: no rows" << endl;
    }
    if (cols <= 0)
    {
        p_os << "empty matrix: no columns" << endl;
    }
    for (int r = 0; r < rows; r ++)
    {
        for (int c = 0; c < cols; c ++)
        {
            p_os << p_m.get_item(r, c) << " ";
        }
        p_os << endl;
    }
    return p_os;
}

istream & operator>>(istream & p_is, Matrix & p_m)
{
    int rows = p_m.rows();
    int cols = p_m.cols();
    int val = 0;
    for (int r = 0; r < rows; r ++)
    {
        for (int c = 0; c < cols; c ++)
        {
            if (not (p_is >> val))
            {
                val = 0;
            }
            p_m.set_item(r, c, val);
        }
    }
    return p_is;
}
int Matrix::rows() const
{
    return m_items.size();
}
int Matrix::cols() const
{
    if (m_items.size() == 0)
    {
        return 0;
    }
    return m_items[0].size();
}

Matrix Matrix::add(const Submatrix & sbm_this, const Matrix & p_a, const Submatrix & sbm_a) const
{
    int trf = sbm_this.m_idxs[sbm_row][sbm_from];
    int trt = sbm_this.m_idxs[sbm_row][sbm_to];
    int rows = trt - trf;

    int tcf = sbm_this.m_idxs[sbm_col][sbm_from];
    int tct = sbm_this.m_idxs[sbm_col][sbm_to];
    int cols = tct - tcf;

    int arf = sbm_a.m_idxs[sbm_row][sbm_from];
    int art = sbm_a.m_idxs[sbm_row][sbm_to];

    int acf = sbm_a.m_idxs[sbm_col][sbm_from];
    int act = sbm_a.m_idxs[sbm_col][sbm_to];

    Matrix res(*this);

    if (trt >= this->rows() or trf < 0 or trt < 0)
    {
        cerr << "Error: not enough rows in minuend matrix" << endl;
        return res;
    }

    if (tct >= this->cols() or tcf < 0 or tct < 0)
    {
        cerr << "Error: not enough columns in minuend matrix" << endl;
        return res;
    }

    if (art >= p_a.rows() or arf < 0 or art < 0)
    {
        cerr << "Error: not enough rows in subtrahend matrix" << endl;
        return res;
    }

    if (act >= p_a.cols() or acf < 0 or act < 0)
    {
        cerr << "Error: not enough columns in subtrahend matrix" << endl;
        return res;
    }


    if (rows != art - arf
        or cols != act - acf)
    {
        cerr << "Error: cannot add matrices of different sizes" << endl;
        return res;
    }

    for (int r = trf; r < trt; r ++)
    {
        for (int c = tcf; c < tct; c ++)
        {
            res.set_item(r, c, this->get_item(r, c) + p_a.get_item(r - trf + arf, c - tcf + acf));
        }
    }
    return res;
}

Matrix Matrix::subtract(const Submatrix & sbm_this, const Matrix & p_a, const Submatrix & sbm_a) const
{
    return this->add(sbm_this, p_a * -1, sbm_a);
}

Matrix Matrix::multiply(const Submatrix & sbm_this, const Matrix & p_a, const Submatrix & sbm_a) const
{
    Matrix e(err);
    return e;
}//TODO

Matrix & Matrix::operator+=(const Matrix & p_a)
{
    Submatrix t_whole;
    t_whole[sbm_row][sbm_from] = 0;
    t_whole[sbm_row][sbm_to] = this->rows();
    t_whole[sbm_col][sbm_from] = 0;
    t_whole[sbm_col][sbm_to] = this->cols();

    Submatrix a_whole;
    a_whole[sbm_row][sbm_from] = 0;
    a_whole[sbm_row][sbm_to] = p_a.rows();
    a_whole[sbm_col][sbm_from] = 0;
    a_whole[sbm_col][sbm_to] = p_a.cols();

    this->add(t_whole, p_a, a_whole);
}

Matrix & Matrix::operator*=(const Matrix & p_a)
{
    int rows = this->rows();
    int connect = this->cols();
    int cols = p_a.cols();
    if (connect != p_a.rows())
    {
        cerr << "Error: cannot multiply incompatible matrices" << endl;
        return *this;
    }
    if (rows == connect and connect == cols)
    {
        return schtrassen_multiply(p_a);
    }
    Matrix res(constr_modes::mode_copy, rows, cols);
    for (int r = 0; r < rows; r ++)
    {
        for (int c = 0; c < cols; c ++)
        {
            int val = 0;
            for (int i = 0; i < connect; i ++)
            {
                val += this->get_item(r, i) * p_a.get_item(i, c);
            }
            res.set_item(r, c, val);
        }
    }
    this->copy_items(res);
    return * this;
}

Matrix & Matrix::operator-=(const Matrix & p_a)
{
    (*this) += p_a * -1;
    return * this;
}

Matrix & Matrix::operator*=(const int p_a)
{
    int rows = this->rows();
    int cols = this->cols();
    for (int r = 0; r < rows; r ++)
    {
        for (int c = 0; c < cols; c ++)
        {
            this->set_item(r, c, this->get_item(r, c) * p_a);
        }
    }
    return * this;
}

Matrix Matrix::operator~() const
{
    int rows = this->cols();
    int cols = this->rows();
    Matrix res(constr_modes::mode_copy, rows, cols);
    for (int r = 0; r < rows; r ++)
    {
        for (int c = 0; c < cols; c ++)
        {
            res.set_item(r, c, this->get_item(c, r));
        }
    }
    return res;
}

int Matrix::copy_items(const Matrix & p_a)
{
    int rows = p_a.rows();
    int cols = p_a.cols();
    this->m_items = vector<vector<int>>(rows, vector<int>(cols, 0));
    for (int r = 0; r < rows; r ++)
    {
        for (int c = 0; c < cols; c ++)
        {
            this->set_item(r, c, p_a.get_item(r, c));
        }
    }
    return 0;
}

Matrix operator+(Matrix p_a, const Matrix & p_b)
{
    p_a += p_b;
    return p_a;
}

Matrix operator*(Matrix p_a, const Matrix & p_b)
{
    p_a *= p_b;
    return p_a;
}

Matrix operator-(Matrix p_a, const Matrix & p_b)
{
    p_a -= p_b;
    return p_a;
}

Matrix operator*(Matrix p_a, const int p_b)
{
    p_a *= p_b;
    return p_a;
}

Matrix operator*(const int p_a, Matrix p_b)
{
    p_b *= p_a;
    return p_b;
}

Matrix & Matrix::operator=(const Matrix & p_a)
{
    this->copy_items(p_a);
    return * this;
}

Matrix::Matrix(const Matrix & p_a)
{
    this->copy_items(p_a);
}
/*
int & Row::operator[](int p_idx)
{
    return m_parent.m_items[m_row_idx][p_idx];
}

Row Matrix::operator[](int p_idx)
{
    return Row(*this, p_idx);
}
*/
double Matrix::determinant() const
{
    int rows = this->rows();
    if (rows != this->cols())
    {
        cerr << "cannot find a determinant for a nonsquare matrix" << endl;
        return nan("");
    }
    if (rows == 1)
    {
        return this->get_item(0, 0);
    }
    double res = 0;
    for (int i = 0; i < rows; i ++)
    {
        res += pow(-1, i) * get_item(0, i) * (this->minor(0, i).determinant());
    }
    return res;
}

Matrix Matrix::minor(int p_row, int p_col) const
{
    if (p_row > this->rows())
    {
        cerr << "cannot create a minor: no such row" << endl;
        return err;
    }
    if (p_col > this->cols())
    {
        cerr << "cannot create a minor: no such column" << endl;
        return err;
    }
    Matrix res(*this);
    res.m_items.erase(res.m_items.begin() + p_row);
    int rows = this->rows() - 1;
    int cols = this->cols() - 1;
    for (int r = 0; r < rows; r ++)
    {
        for (int c = p_col; c < cols; c ++)
        {
            res.m_items[r][c] = res.m_items[r][c + 1];
        }
        res.m_items[r].pop_back();
    }
    return res;
}

bool Matrix::operator==(const Matrix & p_a) const
{
    int rows = this->rows();
    int cols = this->cols();
    if (rows != p_a.rows() or cols != p_a.cols())
    {
        return false;
    }

    for (int r = 0; r < rows; r ++)
    {
        for (int c = 0; c < cols; c ++)
        {
            if (this->get_item(r, c) != p_a.get_item(r, c))
            {
                return false;
            }
        }
    }
    return true;
}

Matrix Matrix::submatrix(Submatrix p_subm) const
{
    Matrix res(constr_modes::mode_copy, p_subm[sbm_row][sbm_to] - p_subm[sbm_row][sbm_from], p_subm[sbm_col][sbm_to] - p_subm[sbm_col][sbm_from]);
    for (int r = p_subm[sbm_row][sbm_from]; r < p_subm[sbm_row][sbm_to]; r ++)
    {
        for (int c = p_subm[sbm_col][sbm_from]; c < p_subm[sbm_col][sbm_to]; c ++)
        {
            res.set_item(r - p_subm[sbm_row][sbm_from], c - p_subm[sbm_col][sbm_from], this->get_item(r, c));
        }
    }
    return res;
}

void schtrassen_mult_rec(const Matrix & p_a, const Matrix & p_b, Matrix & p_res, array<Submatrix, 3> p_subm)
{
    if (p_subm[0][sbm_row][sbm_to] - p_subm[0][sbm_row][sbm_from] == 1)
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

    //cout << p_a.submatrix(subm[a][i22]) << endl;
    Matrix s1 = p_b.subtract(subm[b][i12], p_b, subm[b][i22]);
    Matrix s2 = p_a.add(subm[a][i11], p_a, subm[a][i12]);
    Matrix s3 = p_a.add(subm[a][i21], p_a, subm[a][i22]);
    Matrix s4 = p_b.subtract(subm[b][i21], p_b, subm[b][i11]);
    Matrix s5 = p_a.add(subm[a][i11], p_a, subm[a][i22]);
    Matrix s6 = p_b.add(subm[b][i11], p_b, subm[b][i22]);
    Matrix s7 = p_a.subtract(subm[a][i12], p_a, subm[a][i22]);
    Matrix s8 = p_b.add(subm[b][i21], p_b, subm[b][i22]);
    Matrix s9 = p_a.subtract(subm[a][i11], p_a, subm[a][i21]);
    Matrix s10 = p_b.add(subm[b][i11], p_b, subm[b][i12]);

    Submatrix whole;
    whole[sbm_row][sbm_from] = 0;
    whole[sbm_row][sbm_to] = s1.rows();
    whole[sbm_col][sbm_from] = 0;
    whole[sbm_col][sbm_to] = s1.cols();

    Matrix p1 = p_a.multiply(subm[a][i11], s1, whole);
    Matrix p2 = s2.multiply(whole, p_b, subm[b][i22]);
    Matrix p3 = s3.multiply(whole, p_b, subm[b][i11]);
    Matrix p4 = p_a.multiply(subm[a][i22], s4, whole);
    Matrix p5 = s5.multiply(whole, s6, whole);
    Matrix p6 = s7.multiply(whole, s8, whole);
    Matrix p7 = s9.multiply(whole, s10, whole);

    p_res.add(subm[c][i11], p5 + p4 - p2 + p6, whole);
    p_res.add(subm[c][i12], p1 + p2, whole);
    p_res.add(subm[c][i21], p3 + p4, whole);
    p_res.add(subm[c][i22], p5 + p1 - p3 - p7, whole);
}


Matrix & Matrix::schtrassen_multiply(const Matrix & p_a)
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
    this->copy_items(res);
    return * this;
}
