//ASC31B
#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

typedef pair<int, int> ii;
vector<string> grid;

void printUnq(int i, int j, int h) {
    grid[i][j] = grid[i+h-1][j] = '+';
    for(int k = 1; k < h-1; k++)
        grid[i+k][j] = '|';
}

int main() {
    freopen("chip.in", "r", stdin);
    freopen("chip.out", "w", stdout);
    int m, n, h;
    cin >> m >> n >> h;
    int a[m], b[n];
    for(int i = 0; i < m; i++)
        cin >> a[i], a[i] = n - a[i];
    for(int i = 0; i < n; i++)
        cin >> b[i];


    bool ok = true;
    for(int i = 0; i < m && ok; i++)
        if(a[i])
            for(int j = 1; j < h && ok; j++)
                if(i+j >= m || (a[i+j] -= a[i]) < 0)
                    ok = false;

    priority_queue< pair<int, ii> > PQ;
    for(int i = 0; i < n; i++)
        if(b[i])
            PQ.push(make_pair(0, ii(b[i], i)));

    grid.assign(m, string(n, '*'));
    for(int i = 0; i < m && ok; i++) {
        priority_queue<ii> PQQ;
        while(!PQ.empty() && -PQ.top().first <= i)
            PQQ.push(PQ.top().second), PQ.pop();

        for(int j = 0; j < a[i]; j++) {
            if(PQQ.empty()) {
                ok = false;
                break;
            }
            ii front = PQQ.top(); PQQ.pop();
            printUnq(i, front.second, h);
            if(--front.first)
                PQ.push(make_pair(-(i+h), front));
        }
        while(!PQQ.empty())
            PQ.push(make_pair(-i, PQQ.top())), PQQ.pop();
    }

    if(ok && PQ.empty())
        for(int i = 0; i < m; i++)
            cout << grid[i] << endl;
    else
        cout << "inconsistent" << endl;
    return 0;
}
