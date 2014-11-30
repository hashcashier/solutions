//11825 - Hackers' Crackdown
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;
int N;

class ujset {
    public:
    vector<int> p, w;

    ujset(int N) {
        p.assign(N, 0);
        w.assign(N, 1);
        for(int i = 0; i < N; i++)
            p[i] = i;
    }

    int findSet(int a) {
        return p[a] == a ? a : p[a] = findSet(p[a]);
    }

    void unionSet(int a, int b) {
        if(findSet(a) == findSet(b))
            return;
        if(w[findSet(a)] > w[findSet(b)]) {
            w[findSet(a)] += w[findSet(b)];
            p[findSet(b)] = findSet(a);
        } else {
            w[findSet(b)] += w[findSet(a)];
            p[findSet(a)] = findSet(b);
        }
    }
};

class graph {
    public:
    vector< int > adjList;
    graph(int V) {
        adjList.assign(V, 0);
    }

    void connect(int a, int b) {
        adjList[a] |= (1<<b);
    }
};

graph G(0);
int f[1<<16], prec[1<<16];

int oneCount(int i) {
    int res = 0;
    while(i)
        res++,
        i /= 2;
    return res;
}

int F(int msk) {
    if(msk == (1<<N)-1)
        return 0;

    int &res = f[msk];
    if(res != -1)
        return res;
    int remaining(N-oneCount(msk));
    res = 0;
    vector<int> av;
    for(int i = 0; i < N; i++)
        if(((1<<i)&msk) == 0)
            av.push_back(i);

    int M = av.size();
    for(int i = (1<<M)-1; i > 0; i--) {
        int marked = 0, nmsk = msk;
        for(int j = 0; j < M; j++) {
            if((1<<j)&i) {
                int jj = av[j];
                marked |= (1<<jj) | G.adjList[jj];
                nmsk |= (1<<jj);
            }
        }

        if(marked == (1<<N)-1)
            res = max(res, 1 + F(nmsk));
        else if(i == (1<<M)-1 || res == 1 + remaining)
            break;
    }
    return res;
}

int main() {
//    freopen("11825 - Hackers' Crackdown.in", "r", stdin);
    int cse = 1;
    while(cin >> N && N) {
        cout << "Case " << cse++ << ": ";
//        ujset S(N);
        G = graph(N);
        for(int i = 0; i < N; i++) {
            int m;
            cin >> m;
            for(int j = 0; j < m; j++) {
                int k;
                cin >> k;
//                S.unionSet(i, k);
                G.connect(i, k);
            }
        }

//        int res = N;
//        for(int i = 0; i < N; i++)
//            res = min(res, S.w[S.findSet(i)]);
        memset(f, -1, sizeof f);
        memset(prec, 0, sizeof prec);
//        for(int i = 0; i < (1<<N); i++) {
//            for(int j = 0; j < N; j++) {
//                if((1<<j)&i) {
//                    prec[i] |= G.adjList[j];
//                }
//            }
//        }

        cout << F(0) << endl;
    }
    return 0;
}
