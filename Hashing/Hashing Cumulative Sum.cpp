#include<bits/stdc++.h>

#define fi first
#define endl '\n'
#define se second
#define LL long long
#define pb push_back
#define vi vector<int>
#define pl pair<LL , LL>
#define EPS (double)1e-8
#define pii pair<int , int>
#define sz(x) (int) x.size()
#define sl(x) scanf("%lld",&x)
#define sii(x, y) si(x) , si(y)
#define all(x) (x).begin() , (x).end()
#define lg2(X) (31 - __builtin_clz(X))
#define llg2(X) (63 - __builtin_clzll(X))
#define rall(x) (x).rbegin() , (x).rend()
#define siii(x, y, z) si(x) , si(y) , si(z)
#define mem(a , b) memset((a), (b), sizeof(a))
#define FOR(i , n) for(int i = 0 ; i < n ; i++)
#define FOR1(i , n) for(int i = 1 ; i <= n ; i++)
#define _ceil(n, a) ((n)%(a)==0?((n)/(a)):((n)/(a)+1))
#define mlr int mid = (lo + hi) / 2 , l = node << 1 , r = l | 1 // 1 based
#define itr(it, X) for (__typeof((X).begin()) it = (X).begin(); it != (X).end(); it++)
template <typename T> T si(T &n){n = 0;bool neg = false;char c = getchar();while( c < '0' || c > '9'){if(c == '-') neg = true;c = getchar();}while(c >= '0' && c <= '9'){n = n*10 + c-48;c = getchar();}if(neg) n = ~(n-1);return n;}
// Don't Use this I/O in EOF 
using namespace std;
//Edges Can Be Zero (Specially in Tree)
const int MAXN = 1000003;
//const int MOD  = 100000000;
const LL inf  = 1 << 30; 
/*
int fx[] = {1 , 0 , -1 , 0}; //, 1 , 1 , -1 , -1};
int fy[] = {0 , 1 , 0 , -1}; //, 1 , -1 , 1 , -1};
*/
const int M[] = {2078526727, 2117566807};
const int P[] = {1572872831, 1971536491};

/*
-----------------------------------------------------------------------------------------
Dont Use It When ML is 32/64 MB. High Possibility of getting MLE when len <= 1000000
-----------------------------------------------------------------------------------------
*/

LL inv[3][MAXN];
LL B[3][MAXN];
LL H[3][MAXN];
int lent , lenp;
char text[MAXN], pat[MAXN];

LL bigmod(LL a , LL b , LL mod) {
    a %= mod;
    LL res = 1;
    while(b) {
        if(b & 1) res = (res * a) % mod;
        b /= 2;
        a = (a * a) % mod;
    }
    return res % mod;
}

LL modinv(LL a , LL mod) {
    return bigmod(a , mod - 2 , mod) % mod;
}

void inverse() {
    LL power1 = 1;
    LL power2 = 1;

    for(int i = 0 ; i < MAXN ; i++) {
        inv[0][i] = modinv(power1 , M[0]) % M[0];
        inv[1][i] = modinv(power2 , M[1]) % M[1];
        power1 = (power1 * P[0]) % M[0];
        power2 = (power2 * P[1]) % M[1];
    }
}

void setB() {
    B[0][0] = B[1][0] = 1;

    for(int i = 1 ; i < MAXN ; i++) {
        B[0][i] = (B[0][i - 1] * P[0]) % M[0];
        B[1][i] = (B[1][i - 1] * P[1]) % M[1]; // Str[0] * B^1
    }
}

void ForHash(char *text , int lent) { // OKAY

    H[0][0] = H[1][0] = 0;

    for(int i = 1 ; i <= lent ; i++) {
        H[0][i] = (H[0][i - 1] + (text[i - 1] * B[0][i]) % M[0] ) % M[0];
        H[1][i] = (H[1][i - 1] + (text[i - 1] * B[1][i]) % M[1] ) % M[1];  // text[0] * B^1 
    }

}

// LL RH[2][MAXN];

// void RevHash(char *text , int lent) { // OKAY

//     RH[0][0] = RH[1][0] = 0;

//     for(int i = 1; i <= lent ; i++) {
//         RH[0][i] = (RH[0][i - 1] + (text[i - 1] * B[0][lent - i + 1]) % M[0] ) % M[0];
//         RH[1][i] = (RH[1][i - 1] + (text[i - 1] * B[1][lent - i + 1]) % M[1] ) % M[1];  // text[0] * B^len
//     }

// }

pl i2jFor(int i , int j) { //Verified
    LL value1 = (H[0][j + 1] - H[0][i] + M[0])% M[0];
    LL value2 = (H[1][j + 1] - H[1][i] + M[1])% M[1];
    value1 = (value1 * inv[0][i] + M[0]) % M[0];
    value2 = (value2 * inv[1][i] + M[1]) % M[1];
    return make_pair(value1, value2);    
}

// pl i2jRev(int i , int j) { //OKAY
//     LL value1 = (RH[0][j + 1] - RH[0][i] + M[0])% M[0];
//     LL value2 = (RH[1][j + 1] - RH[1][i] + M[1])% M[1];
//     value1 = (value1 * inv[0][lent - j - 1] + M[0]) % M[0];
//     value2 = (value2 * inv[1][lent - j - 1] + M[1]) % M[1];
//     return make_pair(value1, value2); 
// }

pl PatternHash(char *pat , int lenp) {

    LL p1 = 0, p2 = 0;
    for(int i = 1 ; i <= lenp ; i++) {
        p1 = ( p1 + (pat[i - 1] * B[0][i]) % M[0] ) % M[0];
        p2 = ( p2 + (pat[i - 1] * B[1][i]) % M[1] ) % M[1];
    }
    return make_pair(p1 , p2);
}


void solve(char *text , int lent , char *pat , int lenp) {
    ForHash(text , lent);
    //RevHash(text , lent);
    pl pH = PatternHash(pat , lenp);
    int cnt = 0;
    for(int i = 0 ; i + lenp - 1 < lent; i++) {
    	pl X = i2jFor(i , i + lenp - 1);
    	if(X.fi == pH.fi && X.se == pH.se) cnt++;
    }

    printf("%d\n", cnt);
    
}

int main() {	

#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
#endif
	inverse();
    setB();
	int test;
	si(test);
	while(test--) {
		scanf("%s",pat);
		scanf("%s",text);
		lent = strlen(text);
		lenp = strlen(pat);
		solve(text , lent , pat , lenp);
	}
}
