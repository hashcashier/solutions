//6752 Sweeping Robot
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
bool ok[600][600][2], marked[600][600], visa[600][600][2], visb[600][600][2];
int wall[200][2], path[200][2];
int n, k;

void g(int x, int y, int d) {
    if(visb[x][y][d] || !ok[x][y][1]) return;
    visb[x][y][d] = true;
    marked[x][y] = true;
    if(d) g(x, y-1, d);
    else  g(x, y+1, d);
}

void f(int x, int y, int d) {
//    cout << x << ' ' << y << ' ' << d << endl;
    if(visa[x][y][d] || !ok[x][y][0]) return;
    visa[x][y][d] = true;
    marked[x][y] = true;
    if(d) f(x-1, y, d);
    else  f(x+1, y, d);
}

void walk(int x0, int y0, int x1, int y1) {
    if(x0 != x1) { // x walk
        for(int x = x0; x < x1; x++)
            g(x, y0, 0), g(x, y0, 1);
    } else {
        for(int y = y0; y < y1; y++)
            f(x0, y, 0), f(x0, y, 1);
    }
}

void okz(int x0, int y0, int x1, int y1) {
    if(x0 != x1) { // x walk
        for(int x = x0; x < x1; x++)
            ok[x][y0][1] = false;//, cout << '-' << x << ' ' << y0 << endl;
    } else {
        for(int y = y0; y < y1; y++)
            ok[x0][y][0] = false;//, cout << '|' << x0 << ' ' << y << endl;
    }
}

int main() {
    freopen("6752 Sweeping Robot.in", "r", stdin);
    while(cin >> n >> k && (n || k)) {
        memset(ok, true, sizeof ok);
        memset(marked, false, sizeof marked);
        memset(visa, false, sizeof visa);
        memset(visb, false, sizeof visb);

        for(int i = 0; i < n; i++)
            cin >> wall[i][0] >> wall[i][1];
        wall[n][0] = wall[0][0], wall[n][1] = wall[0][1];

        for(int i = 0; i < k; i++)
            cin >> path[i][0] >> path[i][1];

        for(int i = 0; i < n; i++)
            okz(wall[i][0], wall[i][1], wall[i+1][0], wall[i+1][1]);

        for(int i = 0; i < k-1; i++)
            walk(path[i][0], path[i][1], path[i+1][0], path[i+1][1]);

        int res = 0;
        for(int i = 0; i < 600; i++)
            for(int j = 0; j < 600; j++)
                res += marked[i][j];
        cout << res << endl;
    }
}
