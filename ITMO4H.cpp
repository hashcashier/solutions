#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;
int B, M, R[500], N[500], V[500][500], voted[100], voters[100][500];
string dfs(100, '?');

bool DFS(int i) {
    if(i == B)
        return true;

    bool possible = false;
    for(int j = 0; j < 2; j++) {
        if(possible) {
            bool maybe = true;
            for(int k = 0; k < voted[i] && maybe; k++) {
                int voter = voters[i][k];
                if(V[voter][i] != j && R[voter] <= 2*N[voter] + 2)
                    maybe = false;
            }

            if(maybe) dfs[i] = '?';
        } else {
            bool maybe = true;
            for(int k = 0; k < voted[i] && maybe; k++) {
                int voter = voters[i][k];
                if(V[voter][i] != j && R[voter] <= 2*N[voter] + 2)
                    maybe = false;
            }

            for(int k = 0; k < voted[i] && maybe; k++) {
                int voter = voters[i][k];
                if(V[voter][i] != j)
                    N[voter]++;
            }

            if(DFS(i+1))
                possible = true, dfs[i] = j == 0 ? 'n' : 'y';
            else
                for(int k = 0; k < voted[i] && maybe; k++) {
                    int voter = voters[i][k];
                    if(V[voter][i] != j)
                        N[voter]--;
                }
        }
    }
    return possible;
}

int main() {
    freopen("major.in", "r", stdin);
    int cse = 1;
    while(cin >> B >> M && (B || M)) {
        cout << "Case " << cse++ << ": ";
        memset(voted, 0, sizeof voted);
        memset(N, 0, sizeof N);
        for(int i = 0; i < M; i++) {
            cin >> R[i];
            for(int j = 0; j < R[i]; j++) {
                int x, y = 0;
                char v;
                cin >> x >> v;
                if(v == 'y')
                    y = 1;
                x--;
                V[i][x] = y;

                voters[x][ voted[x]++ ] = i;
            }
        }

        if(DFS(0)) {
            cout << dfs.substr(0, B) << endl;
        } else {
            cout << "impossible" << endl;
        }

    }
}
