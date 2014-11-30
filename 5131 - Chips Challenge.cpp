//5131 - Chips Challenge
#include <iostream>
#include <cstring>

using namespace std;

int N, A, B, rowComponents[40], colComponents[40], rowBlocks[40], colBlocks[40], rowIn[40], colOut[40];
bool blocked[40][40], f[50][50], allowed[50][50];
string grid[40];
vector< vector<int> > adjList;

int DFS() {

}

int FFK() {
    int mf = 0
}

int main() {
    int cse = 1;
    while(cin >> N >> A >> B && N) {
        cout << "Case " << cse++ << ": ";

        adjList.assign(vector<int>(), 2*N + 2);
        memset(f, 0, sizeof f);
        memset(rowComponents, 0, sizeof rowComponents);
        memset(colComponents, 0, sizeof colComponents);
        memset(allowed, 0, sizeof allowed);
        memset(blocked, 0, sizeof blocked);

        for(int i = 0; i < N; i++)
            cin >> grid[i];

        int res = -1, intial = 0;

        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                blocked[i][j] = grid[i][j] != '.',
                rowComponents[i] += grid[i][j] == 'C',
                colComponents[j] += grid[i][j] == 'C',
                rowBlocks[i] += grid[i][j] == '/',
                colBlocks[j] += grid[i][j] == '/',
                intial += grid[i][j] == 'C';

        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                if(!blocked[i][j] && i != j)
                    adjList[i].push_back(N + j),
                    adjList[N + j].push_back(i),
                    f[i][N + j] = 1;

        for(int i = 0; i < N*N; i++) {
            int temp = initial + i, maxallowed = (A*temp)/B;

            for(int j = 0; j < N; j++)
                if(rowIn[j] + rowBlocks[j] + rowComponents[j] < maxallowed) {
                    int addition = maxallowed - rowBlocks[j] - rowComponents[j] - rowIn[j];
                    f[2*N-1][j] += addition, rowIn[j] += addition;
                }

            for(int j= 0; j < N; j++)
                if(colOut[j] + colBlocks[j] + colComponents[j] < maxallowed) {
                    int addition = maxallowed - colBlocks[j] - colComponents[j] - colOut[j];
                    f[N + j][2*N] += addition, colOut[j] += addition;
                }

            int mflow = FFK();
            if(mflow == temp)
                res = temp;
        }

        if(res == -1)
            cout << "impossible";
        else
            cout << res;
        cout << endl;
    }
}
