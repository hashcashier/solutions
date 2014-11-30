//ASC28G2
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
//#include <cassert>

using namespace std;

typedef pair<int, int> ii;

vector< vector<int> > viable;
int n, m, heiro[500][500], nums[500], matched[500], colliding[500];
bool collide[500][500], cantBe[500];

int viableSize(int row) {
    if(viable[row].size() == 0)
        return 0;
    else if(viable[row].size() == 1)
        return !cantBe[ viable[row][0] ];
//    assert(viable[row].size() == 2);
    return (!cantBe[ viable[row][0] ]) + (!cantBe[ viable[row][1] ]);
}

int onlyViable(int row) {
//    assert(viableSize(row) == 1);
    if(!cantBe[ viable[row][0] ])
        return viable[row][0];
//    assert(viable[row].size() == 2);
    return viable[row][1];
}

bool canTake(int word) {
    return !cantBe[word];
}

void take(int row, int word) {
//    assert(!matched[row]);
    matched[row] = word+1;

    cantBe[word] = true;
    for(int i = 0; i < m; i++)
        if(collide[word][i]) {
            colliding[i]++;
            cantBe[i] = true;
        }
}

void remove(int row, int word) {
//    assert(matched[row]);
    matched[row] = 0;

    cantBe[word] = false;
    for(int i = 0; i < m; i++)
        if(collide[word][i]) {
            colliding[i]--;
            if(!colliding[i]) cantBe[i] = false;
        }
}

bool search() {
    bool ok = true;
    queue<ii> oneVia, backtrack;
    int trial = 0;
    for(int i = 0; i < n; i++)
        if(!matched[i]) {
            if(viableSize(i) == 0) return false;
            else if(viableSize(i) == 1) oneVia.push(ii(i, onlyViable(i)));
            trial = i;
            ok = false;
        }
    if(ok) return true;

    if(oneVia.size()) {
        while(!oneVia.empty()) {
            int u = oneVia.front().first, v = oneVia.front().second;
            if(!canTake(v)) break;
            oneVia.pop();
            take(u, v);
            backtrack.push(ii(u, v));
        }

        if(oneVia.size()) {
            while(!backtrack.empty()) {
                int u = backtrack.front().first, v = backtrack.front().second;
                remove(u, v);
                backtrack.pop();
            }
        } else if(search())
            return true;
        else {
            while(!backtrack.empty()) {
                int u = backtrack.front().first, v = backtrack.front().second;
                remove(u, v);
                backtrack.pop();
            }
        }
    } else {
        for(int i = 0; i < viable[trial].size(); i++) {
            int u = viable[trial][i];
            if(canTake(u)) {
                take(trial, u);
                if(search()) return true;
                remove(trial, u);
            }
        }
    }
    return false;
}

int main() {
    freopen("show.in", "r", stdin);
    freopen("show.out", "w", stdout);

    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> nums[i];
    viable.assign(n, vector<int>());

    cin >> m;
    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++) {
            cin >> heiro[i][j];
            if(heiro[i][j] == nums[j])
                viable[j].push_back(i);

            for(int k = 0; k < i; k++)
                if(heiro[k][j] == heiro[i][j])
                    collide[i][k] = collide[k][i] = true;
        }

    if(search()) {
        cout << "YES" << endl;
        for(int i = 0; i < n; i++) {
            if(i) cout << ' ';
            cout << matched[i];
        }
        cout << endl;
    } else {
        cout << "NO" << endl;
    }
}
