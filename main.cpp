#undef CATCH_CONFIG_MAIN
#ifdef CATCH_CONFIG_MAIN
#include <catch.hpp>
#endif
#include <iostream>
#include "cormen.h"
#include "Matrix.h"
#include <conio.h>

using namespace std;

#ifdef CATCH_CONFIG_MAIN
TEST_CASE("testing schtrassen multiplication", "[schtrassen multiply]")
{
    /*SECTION("cormen 4.2.1")
    {
        Matrix x1(2, 2, {{1, 3}, {7, 5}});
        Matrix x2(2, 2, {{6, 8}, {4, 2}});
        Matrix x3 = x1 * x2;
        Matrix xres(2, 2, {{18, 14}, {62, 66}});
        REQUIRE(x3 == xres);
    }
    SECTION("consequtive numbers 4x4")
    {
        Matrix x1(Matrix::constr_modes::mode_conseq, 4, 4);
        Matrix x2(x1);
        x2 *= 2;
        Matrix x3 = x1 * x2;
        Matrix xres(4, 4, {{112, 124, 136, 148}, {304, 348, 392, 436}, {496, 572, 648, 724}, {688, 796, 904, 1012}});
        REQUIRE(x3 == xres);
    }*/
    SECTION("consequtive numbers 3x3")
    {
        Matrix x1(Matrix::constr_modes::mode_conseq, 3, 3);
        Matrix x2(x1);
        x2 *= 2;
        cout << x1 << endl << x2 << endl;
        Matrix x3 = x1 * x2;
        Matrix xres(3, 3, {{30, 36, 42}, {84, 108, 132}, {138, 180, 222}});
        REQUIRE(x3 == xres);
    }
    /*SECTION("consequtive numbers 5x5")
    {
        Matrix x1(Matrix::constr_modes::mode_conseq, 5, 5);
        Matrix x2(x1);
        x2 *= 2;
        cout << x1 << endl << x2 << endl;
        Matrix x3 = x1 * x2;
        Matrix xres(5, 5, {{300, 320, 340, 360, 380}, {800, 870, 940, 1010, 1080}, {1300, 1420, 1540, 1660, 1780}, {1800, 1970, 2140, 2310, 2480}, {2300, 2520, 2740, 2960, 3180}});
        REQUIRE(x3 == xres);
    }*/
}

#else

int main()
{
    Matrix x1(Matrix::constr_modes::mode_conseq, 3, 3);
    Matrix x2(x1);
    x2 *= 2;
    cout << x1 << endl << x2 << endl << endl;
    Matrix x3 = x1 * x2;
    Matrix xres(3, 3, {{30, 36, 42}, {84, 108, 132}, {138, 180, 222}});
    cout << x3 << endl << xres << endl;
}
#endif // CATCH_CONFIG_MAIN
