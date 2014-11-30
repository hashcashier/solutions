#include <iostream>
#include <cstdio>
#include <vector>

#define INF 2000000000

using namespace std;

int N;
long long f[100010][2];
bool v[100010][2];
vector< vector<int> > children, cost;

long long F(int i, bool canTake) {
//    cout << i << ' ' << canTake << endl;

    if(children[i].size() == 0 && canTake)
        return INF;
    else if(v[i][canTake])
        return f[i][canTake];
    v[i][canTake] = true;

    if(!canTake)
        return f[i][canTake] = 0;
//    cout << "PROC" << endl;


    long long res = 0;
    for(int j = 0; j < children[i].size(); j++)
        res += min((long long) cost[i][j], F(children[i][j], true));

    return f[i][canTake] = res;
}

int main() {
    freopen("army.in", "r", stdin);

    cin >> N;
    children.assign(N, vector<int>());
    cost.assign(N, vector<int>());

    for(int i = 0; i < N-1; i++) {
        int K, C;
        cin >> K >> C;
        children[K-1].push_back(i+1);
        cost[K-1].push_back(C);
    }

    cout << F(0, true) << ".00" << endl;
}
