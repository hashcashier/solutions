//11405 - Can U Win?
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

typedef pair<int, int> ii;
typedef pair<int, ii > state;

int dist[1<<8][8][8];
bool blocked[8][8], enem[8][8];
int enemy[8][8];

int dx[] = {-1, 1, 2, 2, 1, -1, -2, -2};
int dy[] = {-2, -2, -1, 1, 2, 2, 1, -1};

bool valid(int X, int Y) {
    return 0 <= X && X < 8 && 0 <= Y && Y < 8 && !blocked[X][Y];
}

int main() {
//    freopen("11405 - Can U Win.in", "r", stdin);
    int T;
    cin >> T;
    while(T--) {
        memset(blocked, false, sizeof blocked);
        memset(enem, false, sizeof enem);
        memset(dist, -1, sizeof dist);

        int X, Y, e = 0, n;
        cin >> n;
        for(int i = 0; i < 8; i++) {
            string lne;
            cin >> lne;
            for(int j = 0; j < 8; j++) {
                if(lne[j] == 'k')
                    X = i, Y = j;
                else if(lne[j] != '.' && lne[j] != 'P')
                    blocked[i][j] = true;
                if(lne[j] == 'P')
                    enem[i][j] = true,
                    enemy[i][j] = e++;
            }
        }

        bool res = false;
        queue<state> Q;
        Q.push(state(0, ii(X,Y)));
        dist[0][X][Y] = 0;
        while(!Q.empty() && !res) {
            state u = Q.front(); Q.pop();
            int x = u.second.first, y = u.second.second, z = u.first;

            if(dist[z][x][y] > n)
                continue;
            else if(z == (1<<e)-1) {
                res = true;
            } else for(int i = 0; i < 8; i++) {
                int xx = x + dx[i], yy = y + dy[i], zz = z;
                if(!valid(xx, yy) || blocked[xx][yy])
                    continue;
                if(enem[xx][yy])
                    zz |= (1<<enemy[xx][yy]);
                if(dist[zz][xx][yy] == -1 || dist[zz][xx][yy] > dist[z][x][y] + 1)
                    dist[zz][xx][yy] = dist[z][x][y] + 1, Q.push(state(zz, ii(xx, yy)));
            }
        }

        cout << (res ? "Yes" : "No") << endl;
    }
    return 0;
}
