#include <iostream>
#include <cstdio>

using namespace std;

#define MAXN 135

long long BIT[MAXN][MAXN][MAXN], norm[MAXN][MAXN][MAXN];
int N;

void put(int i, int j, int k, long long v){
    for(int x = i + 1; x <= N; x += (x & -x)){
        for(int y = j + 1; y <= N; y += (y & -y)){
            for(int z = k + 1; z <= N; z += (z & -z)){
                BIT[x][y][z] += v;
            }
        }
    }
}

long long get(int i, int j, int k){
    long long res = 0;
    for(int x = i + 1; x > 0; x -= (x & -x)){
        for(int y = j + 1; y > 0; y -= (y & -y)){
            for(int z = k + 1; z > 0; z -= (z & -z)){
                res += BIT[x][y][z];
            }
        }
    }
    return res;
}

long long getRange(int x1, int y1, int z1, int x2, int y2, int z2) {
//    long long total = get(x2, y2, z2),
//                A = get(x2, y2, z1-1),
//                B = get(x1-1, y2, z2),
//                C = get(x1-1, y1, z1-1),
//                D = get(x2, y2-1, z2);
    long long x[2] = {x1-1, x2}, y[2] = {y1-1, y2}, z[2] = {z1-1, z2}, res = 0;

    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 2; j++)
            for(int k = 0; k < 2; k++)
                if((i + j + k)%2 == 1) {
                    res += get(x[i], y[j], z[k]);
                } else {
                    res -= get(x[i], y[j], z[k]);
                }

    return res;
}

int main() {
    freopen("stars.in", "r", stdin);
//    while(cin >> N) {
    cin >> N;
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                for(int k = 0; k < N; k++)
                    norm[i][j][k] = BIT[i][j][k] = 0;

        int M;
        while(cin >> M) {
            if(M == 1) {
                int x, y, z, k;
                cin >> x >> y >> z >> k;

                if(norm[x][y][z] + k < 0)
                    k = -norm[x][y][z];

                norm[x][y][z] += k;

                put(x, y, z, k);
            } else if(M == 2) {
                int x1, y1, z1, x2, y2, z2;
                cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
                cout << getRange(x1, y1, z1, x2, y2, z2) << endl;
            } else if(M == 3) {
                break;
            }
        }
//    }
    return 0;
}
