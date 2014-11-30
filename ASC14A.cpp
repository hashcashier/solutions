//ASC14A
#include <iostream>
#include <cstdio>

#define DEATH 17000

using namespace std;

int f[20000][3], id[20000], revId[20000], num, numT;
bool exist[20000], terminal[20000];

int toState(int row, int filled) {
    return (filled<<4)|row;
}

int main() {
    freopen("automata.in", "r", stdin);
    freopen("automata.out", "w", stdout);
    // inputs
    int m;
    cin >> m;
    // Life & Death
    exist[DEATH] = true;
    f[DEATH][0] = f[DEATH][1] = f[DEATH][2] = DEATH;
    exist[0] = terminal[0] = true;
    f[0][0] = m == 1 ? toState(0, 1) : toState(1, 1);
    f[0][1] = m == 1 ? DEATH : toState(1, 2);
    f[0][2] = DEATH;
    // stuffs
    for(int state = 1; state <= (1<<m)<<4; state++) {
        int row = state&15, filled = state>>4;
        if(row >= m || filled >= (1<<m)) continue;
        exist[state] = true;
        if((1<<row)&filled)
            f[state][0] = f[state][1] = DEATH,
            f[state][2] = toState((row+1)%m, filled-(1<<row));
        else if(row == m-1)
            f[state][0] = toState(0, filled|(1<<row)),
            f[state][1] = f[state][2] = DEATH;
        else
            f[state][0] = toState(row+1, filled|(1<<row)),
            f[state][1] = (1<<(row+1)&filled) ? DEATH : toState(row+1, filled|(1<<(row+1))),
            f[state][2] = DEATH;
    }
    // Output
    for(int i = 0; i < 20000; i++)
        if(exist[i])
            revId[num] = i, id[i] = num, num += 1;

    cout << num << " 1" << endl << "1 1" << endl;
    for(int i = 0; i < num; i++) {
        int ID = revId[i];
        cout << id[ f[ID][0] ]+1 << ' ' << id[ f[ID][1] ]+1 << ' ' << id[ f[ID][2] ]+1 << endl;
    }

    return 0;
}
