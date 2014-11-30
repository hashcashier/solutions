//5128 - To Add or to Multiply
#include <cstdio>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

long long inf = 1000000000LL;

string solStr(vector<int> solution) {
    ostringstream res;
    int n = solution.size(), mrun = 0;
    for(int i = 0; i < n; i++) {
        if(solution[i]) {
            if(mrun) {
                res << ' ' << mrun << 'M';
                mrun = 0;
            }
            res << ' ' << solution[i] << 'A';
        }
        if(i == n - 1 && mrun)
            res << ' ' << mrun << 'M';
        mrun++;
    }
    return res.str();
}

bool sollLexi(vector<int> A, vector<int> B) {
//    cout << solStr(A) << " VS" << solStr(B) << endl;

    int n = A.size(), m = B.size();

    for(int i = 0; i < min(n, m); i++)
        if(A[i] < B[i])
            return false;
        else if(A[i] > B[i])
            return true;

    return 1010100101;
}

int main() {
//    freopen("5128 - To Add or to Multiply.in", "r", stdin);

    long long cse = 1, a, m, p, q, r, s;
    while(cin >> a >> m >> p >> q >> r >> s && a) {
        cout << "Case " << cse++ << ": ";
        int solSize = -1;
        vector<int> solution;
        for(long long muls = 0; muls < 32; muls++) {
            long long u = ( r - p*pow(m, muls) ), v = ( s - q*pow(m, muls) );

            if( v < 0 || u > inf || v > inf )
                break;

//            cout << endl << muls << ": " << u << ' ' << v << '(';

            long long curr = 0, tempSolSize = muls;
            vector<int> tempSol(muls+1, 0);

            for(int i = 0; curr < u && i <= muls; i++) {
                long long mpow = pow(m, muls-i);

                tempSol[i] = (u-curr)/(a*mpow);
                curr += a*tempSol[i]*mpow;

                if((u-curr)%(a*mpow) != 0 && curr + a*mpow <= v)
                    tempSol[i]++, curr += a*mpow;

                tempSolSize += tempSol[i];
//                cout << tempSol[i] << "(" << curr << "), ";
            }

//            cout << ")----" << solStr(tempSol) << endl;

//            cout << '(' << (v-curr)/pow(m, muls) << ", " << q - p << ')' << endl;

            if(curr < u || curr > v)
                continue;

//            cout << endl << solStr(tempSol) << ':' << solStr(solution) << "->" << sollLexi(tempSol, solution) << endl;

            if(solSize == -1 || tempSolSize < solSize)
                solution = tempSol, solSize = tempSolSize;
            else if(tempSolSize == solSize && sollLexi(tempSol, solution))
                solution = tempSol, solSize = tempSolSize;
        }

        if(solSize == -1)
            cout << "impossible" << endl;
        else if(!solSize)
            cout << "empty" << endl;
        else {
            cout << solStr(solution).substr(1) << endl;
        }
    }
}
