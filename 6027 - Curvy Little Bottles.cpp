//6027 - Curvy Little Bottles
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <vector>

#define EPS 1e-9

using namespace std;
int n, inc;
long double eqn[300], square[300], integral[300], xlow, xhigh;

void clrVars() {
    for(int i = 0; i < 40; i++)
        eqn[i] = square[i] = integral[i] = 0;
}

double F(double x) {
    double res = 0;
    for(int i = 0; i < 30; i++)
        res += integral[i]*pow(x, i);
    return res;
}

double evalInteg(double x1, double x0) {
    return M_PI*(F(x1) - F(x0));
}

void print() {
cout << endl;
    for(int i = 0; i < 30; i++)
        cout << eqn[i] << ' ';
    cout << endl;
    for(int i = 0; i < 30; i++)
        cout << square[i] << ' ';
    cout << endl;
    for(int i = 0; i < 30; i++)
        cout << integral[i] << ' ';
    cout << endl;
    cout << endl;
}

int main() {
//    freopen("6027 - Curvy Little Bottles.in", "r", stdin);
    int cse = 1;
    while(cin >> n) {
        clrVars();
        cout << "Case " << cse++ << ":";
        for(int i = 0; i <= n; i++)
            cin >> eqn[i];
        cin >> xlow >> xhigh >> inc;
        // A = pi * r(x)^2
        // r(x) = a0 + a1x + a2x^2 + ...
        for(int i = 0; i <= n; i++)
            for(int j = 0; j <= n; j++)
                square[i+j] += eqn[i]*eqn[j];
        // v(x1)-v(x0) = integ(pi*r(x)^2)|x1,x0 -> pi*integ(r(x)^2)|x1,x0
        for(int i = 0; i < 29; i++)
            integral[i+1] = square[i]/(i+1);

        cout << setprecision(2) << fixed << ' ' << evalInteg(xhigh, xlow) << endl;// << F(xhigh) << ' ' << xlow << endl;;
//        print();
        // binary search
        int target = inc;
        bool found = false;

        for(int i = 0; i < 8; i++) {
            double low = xlow, high = xhigh, vol;

            while(high-low > EPS) {
                double x = (high+low)/2;
                vol = evalInteg(x, xlow);

                if(vol > target)
                    high = x;
                else
                    low = x;
            }

            if(fabs(low - xhigh) < 1e-2 || low > xhigh)
                break;

            if(found)
                cout << ' ';

            found = true;
            target += inc;
            cout << setprecision(2) << fixed << low-xlow;
        }

        if(!found) cout << "insufficient volume";
        cout << endl;
    }
}
