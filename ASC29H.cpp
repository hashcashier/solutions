//ASC29H
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>

#define MAXN 100100

using namespace std;

int f[MAXN], g[MAXN][2], m;
bool exist[MAXN];

int circ(int index) {
    return index < 0 ? m + index: index%m;
}

int main() {
    freopen("truth.in", "r", stdin);
    freopen("truth.out", "w", stdout);
    cin >> m;
//    while(cin >> m) {
//        memset(f, 0, sizeof f);
//        memset(g, 0, sizeof g);
//        memset(exist, false, sizeof exist);

        bool consistent = true, cycle = true;
        for(int i = 0; i < m; i++) {
            char c;
            cin >> c;
            if(c == '$') {
                cin >> f[i];
                exist[ f[i] ] = true;
                cycle = false;
            } else {
                f[i] = c == '+' ? -1 : -2;
            }
        }

        for(int i = 0; i < m; i++)
            if(f[i] >= 0)
                for(int k = 0; k < 2; k++) {
                    bool truth = k;
                    g[ f[i] ][k] += truth;
                    for(int j = circ(i-1); f[j] < 0; j = circ(j-1)) {
                        truth = !(truth^(f[j] == -1));
                        g[ f[i] ][k] += truth;
                    }
                }

        int allFalse = 0;
        for(int i = 0; i <= m; i++)
            allFalse += g[i][0];

        int truthfulN = 0;
        for(int i = 1; i <= m; i++)
            if(exist[i])
                if(allFalse - g[i][0] + g[i][1] == i) {
                    truthfulN = i;
                    break;
                }

        if(!truthfulN && !cycle) {
            if(exist[0] && !allFalse) {
                consistent = false;
            } else if(exist[allFalse]) {
                consistent = false;
            } else {
                truthfulN = -3;
            }
        } else if(cycle)
            truthfulN = -3;

//        cout << allFalse << ' ' << truthfulN << endl;
//        for(int i = 0; i <= m; i++)
//            if(exist[i])
//                cout << i << ' ' << g[i][0] << ' ' << g[i][1] << endl;

        string res = string(m, '?');
        if(cycle) {
            int i = 0;
            res[i] = 't';
            bool truth = true;
            for(int j = m-1; j >= 0; j--) {
                truth = !(truth^(f[j] == -1));
                res[j] = truth ? 't' : 'f';
            }
            consistent = res[0] == 't';
        }

        if(consistent) {
            cout << "consistent" << endl;
            for(int i = 0; i < m; i++)
                if(f[i] >= 0) {
                    res[i] = f[i] == truthfulN ? 't' : 'f';
                    bool truth = res[i] == 't';
                    for(int j = circ(i-1); f[j] < 0; j = circ(j-1)) {
                        truth = !(truth^(f[j] == -1));
                        res[j] = truth ? 't' : 'f';
                    }
                }
            assert(res.find('?') == string::npos);
            cout << res << endl;
        } else
            cout << "inconsistent" << endl;
//    }
    return 0;
}
