//ASC28G
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define INF 1000000000

typedef pair<int, int> ii;

vector< vector<int> > res;
vector< vector<ii> > adjList;
vector<int> p;

bool negativeCyclePresent;
int V, E;

// initialize p to -1 before calling
bool DFS(int u, int t) {
    if(u == t)
        return true;
    for(int j = 0; j < adjList[u].size(); j++) {
        int v = adjList[u][j].first;
        if(p[v] == -1 && res[u][v] > 0) {
            p[v] = u;
            if(DFS(v,t))
                return true;
        }
    }

    return false;
}

int MaxFlow(int s, int t) {
    int mf = 0;
    while(true) {
        p.assign(V, -1);
        if(!DFS(s, t))
            break;
        p[s] = -1;
        int z = p[t], bot = res[z][t];
        for(int v = z, u = p[v]; u >= 0; v = u, u = p[v])
            bot = min(bot, res[u][v]);

        res[z][t] -= bot;
        res[t][z] += bot;
        for(int v = z, u = p[v]; u >= 0; v = u, u = p[v])
            res[u][v] -= bot, res[v][u] += bot;

        mf += bot;
    }
    return mf;
}

void connect(int a, int b, int resid) {
    adjList[a].push_back(ii(b,0));
    adjList[b].push_back(ii(a,0));
    res[a][b] = resid;
}

int main() {
    freopen("show.in", "r", stdin);
    int n, m;
    cin >> n;
    int num[n];
    for(int i = 0; i < n; i++)
        cin >> num[i];
    cin >> m;
    V = n + m + 2;
    adjList.assign(V, vector<ii>());
    res.assign(V, vector<int>(V, 0));

    for(int i = 0; i < n; i++)
        connect(0, i+1, 1);
    for(int i = 0; i < m; i++)
        connect(n+i+1, V-1, 1);
    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++) {
            int x;
            cin >> x;
            if(x == num[j])
                connect(j+1, n+i+1, 1);
        }

    if(MaxFlow(0, V-1) == n) {
        cout << "YES" << endl;
        for(int i = 0; i < n; i++) {
            if(i) cout << ' ';
            for(int j = 0; j < m; j++)
                if(res[n+j+1][i+1]) {
                    cout << j+1;
                    break;
                }
        }
        cout << endl;
    } else {
        cout << "NO" << endl;
    }

}
