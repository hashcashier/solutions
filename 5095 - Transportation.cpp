//5095 - Transportation
#include <iostream>
#include <cstdio>
#include <cstdio>
#include <queue>
#include <vector>
#include <cassert>

#define INF 1e9

using namespace std;

typedef pair<int, int> ii;

struct graph {
    int V;
    vector< vector< vector<int> > > costMat, costMatOld, res, X;
    vector< vector< pair<int, ii> > > adjList;
    vector<int> dist, p, pEdge, pBackEdge;

    graph(int V) {
        this->V = V;
        adjList.assign(V, vector< pair<int, ii> >());
        costMat.assign(V, vector< vector<int> >(V, vector<int>()));
        res.assign(V, vector< vector<int> >(V, vector<int>()));
        X.assign(V, vector< vector<int> >(V, vector<int>()));
    }

    void connect(int a, int b, int f, int c, int k) {
        for(int i = 1; i <= k; i++) {
//            cout << a << ' ' << b << ' ' << f << ' ' << c << ' ' << i << endl;
            costMat[a][b].push_back(c*(2*i - 1));
            costMat[b][a].push_back(0);

            res[a][b].push_back(f);
            res[b][a].push_back(0);

            X[a][b].push_back(0);
            X[b][a].push_back(0);

            int n = adjList[a].size(), m = adjList[b].size();

            adjList[a].push_back(make_pair(m, ii(b, costMat[a][b].size()-1)));
            adjList[b].push_back(make_pair(n, ii(a, costMat[b][a].size()-1)));
        }
    }


//    bool BellmanFord(int source, int target) {
//        dist.assign(V, INF);
//        p.assign(V, -1);
////        negativeCyclePresent = false;
//
//        dist[source] = 0;
//        for(int i = 0; i < V; i++)
//            for(int u = 0; u < V; u++)
//                for(int j = 0; j < (int) adjList[u].size(); j++) {
//                    int v = adjList[u][j], w = costMat[u][v];
//                    if(res[u][v] > 0 && dist[u] + w < dist[v]) {
//                        if(i == V-1);
////                            negativeCyclePresent = true;
//                        else
//                            p[v] = u, dist[v] = dist[u] + w;
//                    }
//                }
//        p[source] = -1;
//        return p[target] != -1;
//    }

//    int Pot(int u, int v) {
//        return dist[u] + pi[u] - pi[v];
//    }

    bool Dijkstra(int source, int target) {
//        cout << "# " << source << ' ' << target << endl;
        dist.assign(V, INF);
        p.assign(V, -1);
        pEdge.assign(V, -1);
        pBackEdge.assign(V, -1);

        dist[source] = 0;
        priority_queue< ii > Q;
        Q.push( ii(0, source) );
        int cnt = 0;
        while(!Q.empty()) {
            int u = Q.top().second, D = -Q.top().first;
            Q.pop();
//            assert((cnt++) < V*V*V);
//            cout << u << endl;
            if(D != dist[u]) continue;
            for(int j = 0; j < adjList[u].size(); j++) {
                int v = adjList[u][j].second.first,
                    pos = adjList[u][j].second.second,
                    revEdgeNum = adjList[u][j].first,
                    w = costMat[u][v][pos];

                if(res[u][v][pos] && dist[u] + w < dist[v]) {
                    p[v] = u,
                    pEdge[v] = j,
                    pBackEdge[v] = revEdgeNum,
                    dist[v] = dist[u] + w;

                    Q.push( ii(-dist[v], v) );
                }
            }
        }

        p[source] = -1;
        return p[target] != -1;
    }

    void setPotentials() {
        for(int u = 0; u < V; u++)
            for(int j = 0; j < adjList[u].size(); j++) {
                int v = adjList[u][j].second.first, pos = adjList[u][j].second.second;
                if(res[u][v][pos])
                    costMat[u][v][pos] += dist[u] - dist[v],
                    costMat[v][u][pos] = 0;
            }
    }

    int getInnerEdge(int u, int e) {
        return adjList[u][e].second.second;
    }

    int maxFlow(int s, int t) {
        int mf = 0;

        Dijkstra(s, t);
        setPotentials();

//        cout << s << "->" << t << endl;
        while(true) {
            if(!Dijkstra(s, t))
                break;
            setPotentials();

            int z = p[t],
                zEdge = pEdge[t],
                zBackEdge = pBackEdge[t],
                bot = res[z][t][ getInnerEdge(z, zEdge) ];

//            cout << "############" << endl;
//            printf("(t:%d, z:%d, zEdge:%d, zBackEdge:%d, bot:%d, f():%d)\n", t, z, zEdge, zBackEdge, bot, getInnerEdge(z, zEdge));
            for(int v = z, u = p[v], uEdge = pEdge[v], uBackEdge = pBackEdge[v]; u >= 0; v = u, u = p[v], uEdge = pEdge[v], uBackEdge = pBackEdge[v])
                bot = min(bot, res[u][v][ getInnerEdge(u, uEdge)]);
//                printf("(v:%d, u:%d, uEdge:%d, uBackEdge:%d, bot:%d, f():%d)\n", v, u, uEdge, uBackEdge, bot, getInnerEdge(u, uEdge));
//            cout << endl;
            if(!bot) return mf;

            res[z][t][ getInnerEdge(z, zEdge) ] -= bot;
            res[t][z][ getInnerEdge(t, zBackEdge) ] += bot;

            X[z][t][ getInnerEdge(z, zEdge) ] += bot;
            X[t][z][ getInnerEdge(t, zBackEdge) ] = max(0, X[t][z][ getInnerEdge(t, zBackEdge) ]-bot);

            for(int v = z, u = p[v], uEdge = pEdge[v], uBackEdge = pBackEdge[v]; u >= 0; v = u, u = p[v], uEdge = pEdge[v], uBackEdge = pBackEdge[v])
                res[u][v][ getInnerEdge(u, uEdge) ] -= bot,
                res[v][u][ getInnerEdge(v, uBackEdge) ] += bot,
                X[u][v][ getInnerEdge(u, uEdge) ] += bot,
                X[v][u][ getInnerEdge(v, uBackEdge) ] = max(0, X[v][u][ getInnerEdge(v, uBackEdge) ] - bot);

            mf += bot;
        }
        return mf;
    }

    long long maxFlowCost() {
        long long res = 0;
        for(int u = 0; u < V; u++) {
            for(int j = 0; j < adjList[u].size(); j++) {
                int v = adjList[u][j].second.first,
                    pos = adjList[u][j].second.second,
                    revEdgeNum = adjList[u][j].first,
                    w = costMatOld[u][v][pos];
                res += X[u][v][pos]*w;
            }
        }
        return res;
    }

    void saveCosts() {
        costMatOld = costMat;
    }

};

int main() {
//    freopen("5095 - Transportation.in", "r", stdin);
    int N, M, K;
    while(cin >> N >> M >> K) {
        graph G(N+2);

        for(int i = 0; i < M; i++) {
            int u,v,a,c;
            cin >> u >> v >> a >> c;
            G.connect(u, v, 1, a, c);
        }
        G.connect(0, 1, K, 0, 1);
        G.connect(N, N+1, K, 0, 1);
        G.saveCosts();
//        cout << "OK" << endl;
//        for(int u = 0; u <= N+1; u++) {
//            for(int j = 0; j < G.adjList[u].size(); j++) {
//                int v = G.adjList[u][j].second.first,
//                    pos = G.adjList[u][j].second.second,
//                    revEdgeNum = G.adjList[u][j].first,
//                    w = G.costMat[u][v][pos];
//                printf("(v:%d, p:%d, r:%d, w:%d) ", v, pos, revEdgeNum, w);
//            }
//            cout << endl;
//        }

        if(G.maxFlow(0, N+1) == K) {
            cout << G.maxFlowCost() << endl;
        } else {
            cout << -1 << endl;
        }
    }
}
