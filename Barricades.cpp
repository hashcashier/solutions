//Barricades
#include <iostream>
#include <cstdio>
#include <vector>
#include <set>

#define INF 1000000000

using namespace std;

typedef pair<int, int> ii;

class graph {
    public:
    int N, dfs_num;
    vector< vector<int> > adjList, dp;
    vector<int> zoneCutNum, weight, right, parent, visNum;

    graph(int n) {
        N = n;
        adjList.assign(N, vector<int>());
        zoneCutNum.assign(N+1, -1);
        zoneCutNum[0] = 0;
        weight.assign(N, 0);
        right.assign(N, -1);
        parent.assign(N, -1);
    }

    void connect(int a, int b) {
        adjList[a].push_back(b);
        adjList[b].push_back(a);
    }

    int calcWeight(int u) {
        visNum[dfs_num++] = u;
        int res = 1;
        for(int i = 0; i < adjList[u].size(); i++) {
            int v = adjList[u][i];
            if(v == parent[u])
                continue;

            if(i)
                right[adjList[u][i-1]] = dfs_num+1;

            parent[v] = u;
            res += calcWeight(v);
        }
        return weight[u] = res;
    }

    void compute() {
        dfs_num = 0;
        calcWeight(0);
        dp.assign(N+10, vector<int>(N+10, INF));
        dp[0][ weight[0] ] = 0;
        for(int i = 1; i < N; i++) {
            int u = visNum[i], ni = right[u] == -1 ? i + 1 : right[u];
            dp[ni][weight[u]] = 1;
            for(int j = weight[u]; j <= N; j++) {
                int nj = j-weight[u];
                dp[ni][nj] = min(dp[ni][nj], dp[i][j] + 1);
            }
        }
    }

    int fetch(int k) {
        return zoneCutNum[k];
    }
};

int main() {
    freopen("Barricades.in", "r", stdin);
    int n;
    cin >> n;
    graph G(n);
    for(int i = 1; i < n; i++) {
        int a,b;
        cin >> a >> b;
        G.connect(a-1, b-1);
    }
    G.compute();
    int m;
    cin >> m;
    for(int i = 0; i < m; i++) {
        int k;
        cin >> k;
        cout << G.fetch(k) << endl;
    }

    return 0;
}
