//11876 - N + NOD (N)
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>


using namespace std;

const int MXPRIMES = 1000010;
bool notprime[MXPRIMES];
long long prime[1000010], numprimes, mem[1000010], mem2[1000010];

void sieve() {
    notprime[0] = notprime[1] = true;
    numprimes = 0;
    long long i, j;
    for(i = 2; i < MXPRIMES; i++)
        if(!notprime[i])
            for(j = i*i, prime[numprimes++] = i; j < MXPRIMES; j += i)
                notprime[j] = true;
}

long long NOD(long long N) {
    if(mem2[N])
        return mem2[N];
    long long PF_idx = 0, PF = prime[PF_idx], ans = 1;
    while(PF*PF <= N) {
        long long power = 1;
        while(N%PF == 0)
            N /= PF, power++;
        ans *= power;
        PF = prime[++PF_idx];
    }
    ans += (N != 1)*ans;
    return mem2[N] = ans;
}

int main() {
    sieve();
    int i;
    mem[0] = 1;
    for(i = 1; mem[i-1] < 1000010; i++)
        mem[i] = mem[i-1] + NOD(mem[i-1]);
    vector<int> N(mem, mem+i);

//    freopen("11876 - N + NOD (N).in", "r", stdin);
    int T;
    cin >> T;
    for(int cse = 1; cse <= T; cse++) {
        cout << "Case " << cse << ": ";
        int a, b;
        cin >> a >> b;

        std::vector<int>::iterator lo = lower_bound(N.begin(), N.end(), a), hi = lower_bound(N.begin(), N.end(), b);
        int down = (lo-N.begin()), up = (hi-N.begin()), res = (up - (N[up] > b)) - (down + (N[down] < a)) + (up >= down);

        cout << res << endl;
    }
    return 0;
}
