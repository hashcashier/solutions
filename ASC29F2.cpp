//ASC29F
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <string>
#include <set>
#include <map>

using namespace std;

typedef long long LL;
typedef pair<int, int> ii;

string T, P;
vector<int> res;
ii f[200010], g[200010];
int last[500], first[500], b[200010];

bool ok2(int i, int j) {
    return (f[i].first == f[j].first || f[i].first == -1) && (f[i].second == f[j].second || f[j].second == -1);
}

void kmpPreprocess() {
    b[0] = -1;
    int i = 0, j = -1;
    while (i < P.length()) {
        while (j >= 0 && !ok2(i, j)){
//            cout << "FAIL: " << i << ' ' << j << " -> " << b[j] << endl;
            j = b[j];
        }
        i++;
        j++;
        b[i] = j;
    }

//    for(int i = 0; i < P.length(); i++)
//        cout << P.substr(0,i+1) << "\t\t=>\t" << P.substr(0, b[i]+1) << endl;
}

bool ok(int i, int j) {
    int rem = P.length() - j - 1;
    int RA = f[j].first, LA = f[j].second,
        RB = g[i].first > rem ? -1 : g[i].first,
        LB = g[i].second > j ? -1 : g[i].second;

//    cout << i << ' ' << j << endl;
//    cout << LA << ' ' << RA << ' ' << LB << ' ' << RB << endl;

    return LA == LB && RA == RB;
}

void match() {
    int i = 0, j = 0;
    for(int i = 0; i < T.length(); i++) {
        while(j >= 0 && !ok(i, j)) j = b[j];
        j++;
        if(j == P.length()) {
            res.push_back(i-j+1);
            j = b[j];
        }
    }
}

void mutate() {

    memset(last, -1, sizeof last);
    memset(first, -1, sizeof first);
    for(int i = P.length() - 1; i >= 0; i--) {
        int ni = P.length() - i - 1;
        f[ i ].first = last[ P[i] ] == -1 ? -1 : last[ P[i] ] - i;
        f[ ni ].second = first[ P[ni] ] == -1 ? -1 : ni - first[ P[ni] ];

        last[ P[i] ] = i;
        first[ P[ni] ] = ni;
    }

    memset(last, -1, sizeof last);
    memset(first, -1, sizeof first);
    for(int i = T.length() - 1; i >= 0; i--) {
        int ni = T.length() - i - 1;
        g[ i ].first = last[ T[i] ] == -1 ? -1 : last[ T[i] ] - i;
        g[ ni ].second = first[ T[ni] ] == -1 ? -1 : ni - first[ T[ni] ];

        last[ T[i] ] = i;
        first[ T[ni] ] = ni;
    }
}

int main() {
    freopen("substring.in", "r", stdin);
    freopen("substring.out", "w", stdout);
    cin >> T >> P;
    mutate();
    kmpPreprocess();
    match();
    cout << res.size() << endl;
    if(res.size()) {
        for(int i = 0; i < res.size(); i++) {
            if(i) cout << ' ';
            cout << res[i] + 1;
        }
        cout << endl;
//        for(int i = 0; i < res.size(); i++) {
//            cout << P << endl << T.substr(res[i], P.length()) << endl << endl;
//        }
    }
    return 0;
}
