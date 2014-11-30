//ASC21A
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

class bigraph {
    public:
        int U, V;
        vector<int> match, dist;
        vector< vector<int> > adjList;
        bigraph(int u, int v) {
            U = u, V = v;
            adjList.assign(U+V, vector<int>());
        }
        void connect(int u, int v) {
            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }

        bool AUG(int u) {
            for(int j = 0; j < adjList[u].size(); j++) {
                int v = adjList[u][j];
                if((match[v] == -1) || (dist[match[v]] == dist[u]+1 && AUG(match[v]))) {
                    match[u] = v, match[v] = u;
                    return true;
                }
            }
            dist[u] = -1;
            return false;
        }

        bool BFS(int a = 0, int b = 0, int c = 1) {
            queue<int> bfs;
            if(c)
                dist.assign(U+V, -1);
            bool res = false;
            for(int u = 0 + a; u < U + b; u++)
                if(match[u] == -1)
                    bfs.push(u), dist[u] = 0;
            while(!bfs.empty()) {
                int u = bfs.front(); bfs.pop();
                for(int j = 0; j < adjList[u].size(); j++) {
                    int v = adjList[u][j];
                    if(match[v] == -1)
                        res = true;
                    else if(dist[match[v]] == -1) {
                        dist[match[v]] = dist[u] + 1;
                        bfs.push(match[v]);
                    }
                }
            }

            return res;
        }

        int MCBM() {
            match.assign(U+V, -1);
            int res = 0;
            while(BFS())
                for(int u = 0; u < U; u++)
                    if(match[u] == -1)
                        res += AUG(u);
            return res;
        }
};

int main() {
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    int U, V, M;
    cin >> U >> V >> M;
    bigraph G(U, V);
    for(int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        G.connect(a, U+b);
    }
    int CONN = G.MCBM();
    vector<bool> pos(U+V, false);
    G.BFS();
    G.BFS(U, V, 0);
    for(int i = 0; i < U+V; i++) {
//        cout << i%U+1 << ' ' << G.match[i]%U+1 << ' ' << G.dist[i] << endl;
        if(G.match[i] != -1)
            pos[i] = G.dist[i] == -1;
//        cout << pos[i] << endl;
    }

    for(int u = 0; u < U; u++)
        cout << (pos[u] ? 'N' : 'P');
    cout << endl;
    for(int u = U; u < U+V; u++)
        cout << (pos[u] ? 'N' : 'P');
    cout << endl;
    return 0;
}
