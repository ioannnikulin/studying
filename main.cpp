#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <iostream>
#include "cormen.h"
#include "Matrix.h"
#include <conio.h>

using namespace std;

int mult_conseq(int sz)
{
    Matrix x1(Matrix::constr_modes::mode_conseq, sz, sz);
    Matrix x2(x1);
    x2 *= 2;
    cout << x1 << endl << x2 << endl;
    Matrix x3 = x1 * x2;
    cout << x3;
}

TEST_CASE("testing identity matrix", "[identity matrix]")
{
    Matrix x1(Matrix::constr_modes::mode_identity, 4);
    Matrix x2(4, 4, {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}});
    REQUIRE(x1 == x2);
}
