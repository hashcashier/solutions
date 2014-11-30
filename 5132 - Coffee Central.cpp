//5132 - Coffee Central
// N x M: ( i , j ) -> ( i + j, ( i - j ) + M - 1)

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

int dx, dy, n, m, q, lim;

int f[2010][2010];

int zi(int i, int j) {
    int res = i + j;
    return max(min(res, lim), 0);
}

int zj(int i, int j) {
    int res = i - j + dx - 1;
    return max(min(res, lim), 0);
}

int G(int i, int j) {
    int rai = i - m, raj = j,
        rbi = i, rbj = j - m,
        rci = i, rcj = j + m,
        rdi = i + m, rdj = j;

    int ai = zi(rai, raj), aj = zj(rai, raj),
        bi = zi(rbi, rbj), bj = zj(rbi, rbj) + 1,
        ci = zi(rci, rcj) + 1, cj = zj(rci, rcj),
        di = zi(rdi, rdj) + 1, dj = zj(rdi, rdj) + 1;

    int res = f[ai][aj] - f[bi][bj] - f[ci][cj] + f[di][dj];
    return res;
}

int main() {
//    freopen("5132 - Coffee Central.in", "r", stdin);
    int cse = 1;
    while(cin >> dx >> dy >> n >> q && (dx || dy || n || q)) {
        lim = dx + dy + 5;

        cout << "Case " << cse++ << ':' << endl;
        memset(f, 0, sizeof f);

        for(int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;
            x--, y--;
            f[ zi(y, x) ][ zj(y, x) ] = 1;
        }

        for(int i = lim; i >= 0; i--)
            for(int j = lim; j >= 0; j--)
                f[i][j] += f[i+1][j] + f[i][j+1] - f[i+1][j+1];

        for(int k = 0; k < q; k++) {
            cin >> m;

            int ri = 0, rj = 0, res = 0;
            for(int i = 0; i < dy; i++)
                for(int j = 0; j < dx; j++)
                    if(G(i, j) > res)
                        res = G(i, j), ri = i, rj = j;

            cout << res << " (" << rj+1 << ',' << ri+1 << ')' << endl;
        }
    }
}
