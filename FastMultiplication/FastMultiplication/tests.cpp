#include <iostream>
#include "BadischeEntwicklung.h"
#include "FundamentaleAlgorithmen.h"
#include "SchnelleMultiplikation.h"

int main()
{
    static const int B = 10;

    // original:
//    vector<int> x = { 2,3,1,4,1,7,7,8,9,1};
//	  vector<int> y = { 8,5,2,1,7,1};

    vector<int> x = {2, 3, 1, 4, 1};
    int x_s = 1;
    vector<int> y = {8, 5, 2, 1};
    int y_s = 0;

    BadicRepresentation<B> x_b(x);
    x_b.sgn = x_s;
    BadicRepresentation<B> y_b(y);
    y_b.sgn = y_s;
    BadicRepresentation<B> z_b = FundamentalMultiply<B>(x_b, y_b);

    cout << "X in B-adischer Darstellung: " << x_b << endl;
    cout << "Y in B-adischer Darstellung: " << y_b << endl;
    cout << "X*Y in B-adischer Darstellung (FundamentalMultiply): " << z_b << endl;
    cout << endl;

    BadicRepresentation<2> x_new = ChangeBase(x_b);
    x_new.sgn = x_s;
    BadicRepresentation<2> y_new = ChangeBase(y_b);
    y_new.sgn = y_s;
    cout << "X in 2-adischer Darstellung: " << x_new << endl;
    cout << "Y in 2-adischer Darstellung: " << y_new << endl;
    cout << "X*Y in 2-adischer Darstellung (FundamentalMultiply): " << FundamentalMultiply<2>(x_new, y_new) << endl;
    cout << endl;

    int max_x = std::ceil(log(x_new.data.size())/log(2));
    int max_y = std::ceil(log(y_new.data.size())/log(2));
    int max = std::max(max_x, max_y);

    BadicRepresentation<2> z_new = FastMultiply<B>(x_b, y_b, max);
    cout << "X*Y in 2-adischer Darstellung (FastMultiply): " << z_new << endl;

    std::cout << "done" << std::endl;
}
