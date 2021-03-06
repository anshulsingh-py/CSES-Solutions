#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()

const int MOD = 1000000007;


template<int SZ> struct Combo {
    ll fac[SZ+1], ifac[SZ+1];
    
    Combo() {
        fac[0] = ifac[0] = 1;
        FOR(i,1,SZ+1) {
            fac[i] = i*fac[i-1] % MOD;
            ifac[i] = inv(fac[i]);
        }
    }
    
    ll po (ll b, ll p) {
        return !p?1:po(b*b%MOD,p/2)*(p&1?b:1)%MOD;
    }
    
    ll inv (ll b) { return po(b,MOD-2); }
    
    ll comb(ll a, ll b) {
        if (a < b) return 0;
        ll tmp = fac[a]*ifac[b] % MOD;
        tmp = tmp*ifac[a-b] % MOD;
        return tmp;
    }
};

string s;
int dp[501][501];
Combo<500> C;

void solve(int l, int r) {
    if ((r-l+1) % 2 == 1) return;
    for (int i = l+1; i <= r; i += 2) if (s[l] == s[i]) {
        ll t = (ll)dp[l+1][i-1]*dp[i+1][r] % MOD;
        t = t*C.comb((r-l+1)/2,(i-l+1)/2) % MOD;
        dp[l][r] += t;
        dp[l][r] %= MOD;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> s;
    FOR(i,1,sz(s)+1) dp[i][i-1] = 1;
    F0Rd(i,sz(s)) FOR(j,i,sz(s)) solve(i,j);
    cout << dp[0][sz(s)-1];
}
