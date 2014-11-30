//ASC22C
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cassert>

#define INF 100000000000LL

using namespace std;

typedef pair<long long, long long> ii;
typedef pair<long long, ii> iii;

class graph {
    public:
    vector< vector< iii > > adjList;
    vector<long long> dist, dfs_num, dfs_low, dfs_par;
    vector<bool> important, veryImportant;
    long long E, dfs_ctr;

    graph(int V) {
        adjList.assign(V, vector<iii>());
        E = 0;
    }

    void connect(int a, int b, long long c) {
        adjList[a].push_back(iii(E, ii(b, c)));
        adjList[b].push_back(iii(E, ii(a, c)));
        E += 1;
    }

    void dijkstra(int s) {
        dist.assign(adjList.size(), INF);
        dist[s] = 0;
        priority_queue<ii> Q;
        Q.push(ii(0, s));
        while(!Q.empty()) {
            ii elem = Q.top(); Q.pop();
            long long u = elem.second, d = -elem.first;
            if(d != dist[u]) continue;

            for(int j = 0; j < adjList[u].size(); j++) {
                ii elem = adjList[u][j].second;
                long long v = elem.first, w = elem.second;

                if(dist[v] > d + w) {
                    dist[v] = d + w;
                    Q.push(ii(-dist[v], v));
                }
            }
        }
    }

    void markBridges(int u) {
        dfs_low[u] = dfs_num[u] = ++dfs_ctr;
//        cout << "Visit " << u+1 << ' ' << dfs_ctr << endl;

        for(int j = 0; j < adjList[u].size(); j++) {
            ii elem = adjList[u][j].second;
            long long e = adjList[u][j].first, v = elem.first, w = elem.second;

            if(!important[e])
                continue;
            else if(!dfs_num[v]) {
                dfs_par[v] = e;
                markBridges(v);

                if(dfs_low[v] > dfs_num[u])
                    veryImportant[e] = true;//, cout << "Add " << u+1 << ' ' << v+1 << ' ' << e << endl;

                dfs_low[u] = min(dfs_low[u], dfs_low[v]);
            } else if(e != dfs_par[u]) {
                dfs_low[u] = min(dfs_low[u], dfs_num[v]);
            }

        }

//        cout << "Exit " << u+1 << ' ' << dfs_low[u] << endl;
    }

    void markImportant() {
        important.assign(E, false);

        vector<bool> vis(adjList.size(), false);
        queue<int> Q;
        Q.push(0);
        vis[0] = true;

        while(!Q.empty()) {
            int u = Q.front(); Q.pop();
            for(int j = 0; j < adjList[u].size(); j++) {
                ii elem = adjList[u][j].second;
                long long e = adjList[u][j].first, v = elem.first, w = elem.second;

                if(dist[u] == dist[v] + w) {
                    important[e] = true;
//                    cout << "Add " << u+1 << ' ' << v+1 << " (" << e << ')' << endl;
                    if(!vis[v])
                        vis[v] = true, Q.push(v);
                }
            }
        }

        dfs_num.assign(adjList.size(), 0);
        dfs_low.assign(adjList.size(), 0);
        dfs_par.assign(adjList.size(), -1);
        dfs_ctr = 0;
        dfs_par[0] = -1;
        veryImportant.assign(E, false);
        markBridges(0);

        assert(dfs_num[adjList.size()-1]);
    }
};

int main() {
    freopen("important.in", "r", stdin);
    freopen("important.out", "w", stdout);
    int n, m;
//    while(cin >> n >> m) {
        cin >> n >> m;
        graph G(n);
        for(int i = 0; i < m; i++) {
            int a,b,c;
            cin >> a >> b >> c;
            G.connect(a-1, b-1, c);
        }

        G.dijkstra(n-1);
        G.markImportant();

//        for(int i = 0; i < G.E; i++)
//            cout << G.important[i] << ' ';
//        cout << endl;
//        for(int i = 0; i < G.E; i++)
//            cout << G.veryImportant[i] << ' ';
//        cout << endl;

        vector<int> res;
        for(int i = 0; i < G.E; i++)
            if(G.veryImportant[i])
                res.push_back(i+1);

        cout << res.size() << endl;
        for(int i = 0; i < res.size(); i++) {
            if(i) cout << ' ';
            cout << res[i];
        }
//        cout << endl << endl;
//    }
    return 0;
}
