#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <cstring>
#include <string>

using namespace std;

#define PB push_back
#define MP make_pair
#define IT(c) typeof((c).end())
#define ALL(c) c.begin(),c.end()
#define TRV(c,i) for(IT(c) i=(c).begin();i!=(c).end();i++)
#define FOR(i,j,k) for(int i=j;i<k;i++)
#define REP(v, n) FOR(v,0,n)
#define CTR(v, n) FOR(v,1,n+1)
#define MST(a, b) memset(a, b, sizeof a)
#define SZ(x) ((int)x.size())

typedef vector<int> VI;
typedef vector<string> VS;
typedef pair<int, int> ii;
typedef long long LL;

const double eps = 1e-9;

int deg[51];

list<int> cyc;
vector< VI > adjList;

void EulerTour(list<int>::iterator i, int u) {
    REP(j, adjList[u].size()) {
        int &v = adjList[u][j];
        if(v > 0) {
//            cout << u << ' ' << v << endl;
            int tmp = v;
            v = 0;
            REP(k, adjList[tmp].size()) {
                int &uu = adjList[tmp][k];
                if(uu == u) {
                    uu = 0;
                    k = 1000;
                }
            }
            EulerTour(cyc.insert(i, u), tmp);
        }
    }
}


int main() {
	int T;
	cin >> T;
	CTR(cse, T) {
	    MST(deg, 0);
	    adjList.assign(51, VI());
	    cyc.clear();
	    int n, a, b;
	    cin >> n;
	    REP(i, n) {
	        cin >> a >> b;
	        deg[a]++, deg[b]++;
	        adjList[a].PB(b);
	        adjList[b].PB(a);
	    }
	    bool pos = true;
        CTR(i, 50) {
            pos = pos && (deg[i]%2) == 0;
        }

        if(cse > 1) cout << endl;
        cout << "Case #" << cse << endl;
        if(pos) {
            EulerTour(cyc.begin(), a);
            TRV(cyc, it) {
                cout << a << ' ' << *it << endl;
                a = *it;
            }
        } else {
            cout << "some beads may be lost" << endl;
        }
	}
	return 0;
}
