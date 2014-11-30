//CF255
#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

typedef pair<int, int> ii;

long long n, m, K, p, g[1000100];
bool vis[1000110];
priority_queue<long long> rPQ, cPQ;

long long G(long long k) {
    if(vis[k]) return g[k];
    else if(k == 0) return 0;
    vis[k] = true;
    long long take = cPQ.top(); cPQ.pop();
    cPQ.push(take - p*n);
    return g[k] = take + G(k-1);
}

long long F(long long k) {
    if(k == 0) return 0;
    long long take = rPQ.top(); rPQ.pop();
    rPQ.push(take - p*m);
    long long res = F(k-1);
    return max(take + res, G(k) - p*(K-k)*(k));
}

int main() {
    cin >> n >> m >> K >> p;

    long long mat[n][m], rowDec = 0, colDec = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            cin >> mat[i][j];
    for(int i = 0; i < n; i++) {
        long long rs = 0;
        for(int j = 0; j < m; j++)
            rs += mat[i][j];
        rPQ.push(rs);
    }
    for(int j = 0; j < m; j++) {
        long long cs = 0;
        for(int i = 0; i < n; i++)
            cs += mat[i][j];
        cPQ.push(cs);
    }

    long long res = F(K);
    res = max(res, G(K));

    cout << res << endl;

    return 0;
}
