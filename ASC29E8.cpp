//ASC29E
#include <iostream>
#include <cstdio>

using namespace std;

typedef unsigned long long LL;
LL f[30][30][30], n;
bool v[30][30][30];

LL F(int T, int B, int C) {
    bool &vis = v[T][B][C];
    LL &res = f[T][B][C];
    if(vis)
        return res;
    vis = true;

    if(B == 0 && T == n-1) {
        return res = 1<<C;
    }

    if(T < n - 1)
        for(int j = T + 1; j < n; j++)
            res += F(j, B, C + j - T - 1);
    else if(C)
        res += F(T, B, C - 1);

    if(B)
        for(int j = B - 1; j >= 0; j--)
            res += F(T, j, C + B - j - 1);
    else if(C)
        res += F(T, B, C - 1);

    return res;
}

int main() {
    freopen("permutominoes.in", "r", stdin);
    freopen("permutominoes.out", "w", stdout);
    cin >> n;
    LL res = 0;
    for(int B = 0; B < n; B++)
        for(int T = B + 1; T < n; T++)
            res += F(T, B, T - B - 1);
    cout << res << endl;
    return 0;
}
