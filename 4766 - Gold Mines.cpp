//4766 - Gold Mines
#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>

#define INF 1e9

using namespace std;

typedef pair<int, int> ii;

struct graph {
    int V;
    long long MFC;
    vector< vector<int> > adjList, costMat, res;
    vector<int> dist, p, pi;

    graph(int V) {
        this->V = V;
        adjList.assign(V, vector<int>());
        costMat.assign(V, vector<int>(V, 0));
        res.assign(V, vector<int>(V, 0));
    }

    void connect(int a, int b, int f, int c) {
        adjList[a].push_back(b);
        adjList[b].push_back(a);
        costMat[b][a] = -(costMat[a][b] = c);
        res[a][b] = f;
    }

    int Pot(int u, int v) {
        return dist[u] + pi[u] - pi[v];
    }

    bool Dijkstra(int source, int target) {
        dist.assign(V, INF);
        p.assign(V, -1);

        dist[source] = 0;
        priority_queue< ii > Q;
        Q.push( ii(0, source) );
        while(!Q.empty()) {
            int u = Q.top().second, D = -Q.top().first;
            Q.pop();
//            cout << u << endl;
            if(D != dist[u]) continue;
            for(int j = 0; j < adjList[u].size(); j++) {
                int v = adjList[u][j], w = costMat[u][v];
//                cout << '#' << v << ' ' << w << ' ' << dist[v] << ' ' << p[v] << endl;
                if(res[u][v] && dist[u] + w < dist[v]) {
//                if(res[u][v] && Pot(u,v) + costMat[u][v] < dist[v]) {
                    p[v] = u, dist[v] = dist[u] + w;
//                    p[v] = u, dist[v] = Pot( u, v ) + costMat[u][v];
                    Q.push( ii(-dist[v], v) );
                }
            }
        }

        for(int i = 0; i < V; i++)
            if(dist[i] < INF)
                pi[i] += dist[i];

        p[source] = -1;
        return p[target] != -1;
    }

    bool BellmanFord(int source, int target) {
        dist.assign(V, INF);
        p.assign(V, -1);
//        negativeCyclePresent = false;

        dist[source] = 0;
        for(int i = 0; i < V; i++)
            for(int u = 0; u < V; u++)
                for(int j = 0; j < (int) adjList[u].size(); j++) {
                    int v = adjList[u][j], w = costMat[u][v];
                    if(res[u][v] > 0 && dist[u] + w < dist[v]) {
                        if(i == V-1);
//                            negativeCyclePresent = true;
                        else
                            p[v] = u, dist[v] = dist[u] + w;
                    }
                }
        p[source] = -1;
        return p[target] != -1;
    }

    int maxFlow(int s, int t) {
        int mf = 0;
        MFC = 0;
//        cout << s << "->" << t << endl;
        pi.assign(V, 0);
        while(true) {
            if(!Dijkstra(s, t))
                break;

            int z = p[t], bot = res[z][t];
            for(int v = z, u = p[v]; u >= 0; v = u, u = p[v])
                bot = min(bot, res[u][v]);

            res[z][t] -= bot;
            res[t][z] += bot;
            MFC += bot*costMat[z][t];
            for(int v = z, u = p[v]; u >= 0; v = u, u = p[v])
                res[u][v] -= bot, res[v][u] += bot, MFC += bot*costMat[u][v];

            mf += bot;
        }
        return mf;
    }

    long long maxFlowCost() {
        return MFC;
        long long result = 0;
        for(int u = 0; u < V; u++) {
            for(int j = 0; j < adjList[u].size(); j++) {
                int v = adjList[u][j];
                if(res[u][v] == 0 && costMat[u][v])
                    result += costMat[u][v];//, cout << '@' << u << ' ' << v << endl;
            }
        }
        return result;
    }
};

int oneCount(int i) {
    int res = 0;
    while(i)
        res += i%2,
        i /= 2;
    return res;
}

int main() {
//    freopen("4766 - Gold Mines.in", "r", stdin);
    if(true) {
        graph G(8);
        G.connect(0, 1, 5, 0);
        G.connect(1, 2, 7, 1);
        G.connect(1, 3, 7, 5);
        G.connect(2, 4, 3, 8);
        G.connect(3, 4, 3, -3);
        G.connect(3, 5, 2, 4);
        G.connect(4, 6, 3, 0);
        G.connect(5, 6, 2, 0);
        cout << G.maxFlow(0, 6) << endl;
        for(int i = 0; i < 7; i++) {
            for(int j = 0; j < 7; j++)
                cout << G.costMat[i][j] << ' ';
            cout << endl;
        }
        cout << endl;
        for(int i = 0; i < 7; i++) {
            for(int j = 0; j < 7; j++)
                cout << G.res[i][j] << ' ';
            cout << endl;
        }
        cout << G.maxFlowCost() << endl;
        return 0;
    }




    int T;
    cin >> T;
    while(T--) {
        int V, E;
        cin >> V >> E;
        graph G(2*V+2);
        for(int i = 0; i < E; i++) {
            int a,b;
            cin >> a >> b;
            G.connect(2*a+1, 2*b, 1, 0);
            G.connect(2*b+1, 2*a, 1, 0);
        }

        int N;
        cin >> N;
        N *= 2;
        int lands[N];
        for(int i =0; i < N; i++)
            cin >> lands[i];
        long long sum = 0;
        for(int i = 0; i < V; i++) {
            int c;
            cin >> c;
            sum += c;
            G.connect(2*i, 2*i+1, 1, c);
        }

        long long res = -1;
        for(int msk = 0; msk < (1<<N); msk++) {
            if(oneCount(msk) != N/2) continue;
            graph GG = G;
            for(int i = 0; i < N; i++) {
                int submsk = (1<<i);
                if(submsk & msk)
                    GG.connect(2*V+1, 2*i, 1, 0);
                else
                    GG.connect(2*i+1, 2*V, 1, 0);
            }
            int flow = GG.maxFlow(2*V+1, 2*V);
            if(flow == N/2) {
                int cost = GG.maxFlowCost();
//                cout << '#' << sum << ' ' << flow << ' ' << cost << endl;
                res = max(res, sum-cost);
            }
        }


        cout << res << endl;
    }
}
