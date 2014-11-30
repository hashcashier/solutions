#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

#define INF 1000000000

using namespace std;

typedef pair<int, int> ii;

vector< vector<int> > res;
vector< vector<ii> > adjList;
vector<int> p, dist;

bool negativeCyclePresent;
int V, E;

bool bellman(int source, int target) {
	dist.assign(V, INF);
	p.assign(V, -1);
	negativeCyclePresent = false;

	dist[source] = 0;
	for(int i = 0; i < V; i++)
		for(int u = 0; u < V; u++)
			for(int j = 0; j < (int) adjList[u].size(); j++) {
				int v = adjList[u][j].first, w = adjList[u][j].second;
				if(res[u][v] > 0 && dist[u] + w < dist[v]) {
					if(i == V-1)
						negativeCyclePresent = true;
					else
						p[v] = u, dist[v] = dist[u] + w;
				}
			}
    p[source] = -1;
	return p[target] != -1;
}

bool dijkstra(int source, int target) {
    dist.assign(V, INF);
    p.assign(V, -1);

    dist[source] = 0;
    priority_queue< ii > Q;
    Q.push( ii(0, source) );
    while(!Q.empty()) {
        int u = Q.top().second, D = -Q.top().first;
        Q.pop();

        if(D != dist[u]) continue;
        for(int j = 0; j < adjList[u].size(); j++) {
            int v = adjList[u][j].first, w = adjList[u][j].second;
            if(res[u][v] && dist[u] + w < dist[v]) {
                p[v] = u, dist[v] = dist[u] + w;
                Q.push( ii(-dist[v], v) );
            }
        }
    }

    p[source] = -1;
    return p[target] != -1;
}

int FFK(int s, int t) {
    int mf = 0;
    while(true) {
        if(!dijkstra(s,t))
            break;
        p[s] = -1;
		int cost = 0;

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

void block(int w, int g) {
    for(int i = 0; i < adjList[w].size(); i++) {
        int v = adjList[w][i].first;
        if(v == g)
            adjList[w][i].second = -1;
    }
    for(int i = 0; i < adjList[g].size(); i++) {
        int v = adjList[g][i].first;
        if(v == w)
            adjList[g][i].second = 1;
    }

    res[0][w] = res[w][g] = res[g][V - 1] = 0;
    res[w][0] = res[g][w] = res[V - 1][g] = 1;
}

int main() {
    freopen("keeper.in", "r", stdin);
    int m, n;
    cin >> m >> n;
    V = m + n + 2;
    adjList.assign(V, vector<ii>());
    res.assign(V, vector<int>(V, 0));
    for(int i = 1; i <= m; i++) {
        cin >> E;
        adjList[0].push_back(ii(i, 0));
        adjList[i].push_back(ii(0, 0));
        res[0][i] = 1;

        for(int j = 0; j < E; j++) {
            int k;
            cin >> k;
            adjList[i].push_back(ii(k + m, 0));
            adjList[k + m].push_back(ii(i, 0));
            res[i][k + m] = 1;
        }
    }
    for(int i = 0; i < n; i++) {
        int a = m + i + 1, b = V - 1;
        adjList[a].push_back(ii(b, 0));
        adjList[b].push_back(ii(a, 0));
        res[a][b] = 1;
    }
    int initial = 0;
    for(int i = 1; i <= m; i++) {
        int k;
        cin >> k;
        if(!k) continue;
        initial++;
        block(i, m + k);
    }

//    for(int i = 0; i < V; i++) {
//        cout << i << ": ";
//        for(int j = 0; j < adjList[i].size(); j++)
//            cout << adjList[i][j].first << ',' << adjList[i][j].second << ',' << res[i][ adjList[i][j].first ] << ' ';
//        cout << endl;
//    }

    int rez = FFK(0, V - 1);

//    for(int i = 0; i < V; i++) {
//        cout << i << ": ";
//        for(int j = 0; j < adjList[i].size(); j++)
//            cout << adjList[i][j].first << ',' << adjList[i][j].second << ',' << res[i][ adjList[i][j].first ] << ' ';
//        cout << endl;
//    }

    int rp = 0;
    for(int i = m + 1; i <= m + n; i++) {
        for(int j = 0; j < adjList[i].size(); j++) {
            int v = adjList[i][j].first, w = adjList[i][j].second;
            if(res[v][i] && w) {
                rp++;
                break;
            }
        }
    }

    cout << rez + initial << ' ' << rp << endl;

    for(int i = 1; i <= m; i++) {
        if(i > 1) cout << ' ';
        bool ok = false;
        for(int j = 0; j < adjList[i].size(); j++) {
            int v = adjList[i][j].first;
            if(v > m && res[v][i]) {
                cout << v - m;
                ok = true;
                break;
            }
        }
        if(!ok) cout << 0;
    }
    cout << endl;
    return 0;
}
