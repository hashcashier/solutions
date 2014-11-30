//11825 - Hackers' Crackdown
#include <isotream>
#include <cstdio>

using namespace std;

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
        if(w[findSet(a)] > w[findSet(b)]) {
            w[findSet(a)] += w[findSet(b)];
            p[findSet(b)] = findSet(a);
        } else {
            w[findSet(b)] += w[findSet(a)];
            p[findSet(a)] = findSet(b);
        }
    }
};

int main() {
    int N, cse = 1;
    while(cin >> N && N) {
        cout << "Case " << cse++ << ": ";
        ujset S(N);
        for(int i = 0; i < N; i++) {
            int m;
            cin >> m;
            for(int j = 0; j < m; j++) {
                int k;
                cin >> k;
                S.unionSet(i, k);
            }
        }
        int res = 0;
        for(int i = 0; i < N; i++)
            res = max(res, S.w[i]);
        cout << res << endl;
    }
    return 0;
}
