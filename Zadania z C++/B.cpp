#include<bits/stdc++.h>
using namespace std;
#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (int i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i, j) FOR(i, 1, j + 1, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define all(cont) cont.begin(), cont.end()
#define rall(cont) cont.end(), cont.begin()
#define FOREACH(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define FOREACH1(it, it1, it2) for (auto it = it1; it != it2; it++)
#define IN(A, B, C) assert( B <= A && A <= C)
#define MP make_pair
#define PB push_back
#define ST first
#define ND second
#define INF (int)1e9
#define EPS 1e-9
#define PI 3.1415926535897932384626433832795
#define MOD 1000000007
#define read(type) readInt<type>()
#define MAX 1e18 + 1e4
#define MAX1 500005
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#define time__(d) for(long blockTime = 0; (blockTime == 0 ? (blockTime=clock()) != 0 : false); de    bug("%s time : %.4fs", d, (double)(clock() - blockTime) / CLOCKS_PER_SEC))
const double pi=acos(-1.0);
typedef long long int ll;
typedef pair<int, int> PII;
typedef pair<ll, ll> PLL;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<PII> VII;
typedef vector<PLL> VLL;
typedef vector<VI> VVI;
typedef map<int,int> MPII;
typedef set<int> SETI;
typedef multiset<int> MSETI;
typedef long int int32;
typedef unsigned long int uint32;
typedef unsigned long long int  ull; 
typedef queue<int> QI;

PII tab[MAX1];

long double dist(PLL a, PLL b){
	return sqrt(double((a.first - b.first) * (a.first - b.ST) + (a.ND - b.ND) * (a.ND - b.ND)));
}

long double peri(PLL a, PLL b, PLL c){
	return dist(a, b) + dist(a, c) + dist(b, c);
}

ll closest (VLL p){
	int siz = p.size();
	sort (p.begin(), p.end());
	set<PLL> s;
	long double rez = MAX;
	ll j = 0, smol = 0;
	REP(i, siz){
		smol = ceil(sqrt(rez));
		while(p[i].first - p[j].first >= rez){
			s.erase({p[j].second, p[j].first});
			++ j;
		}
		
		auto it1 = s.lower_bound(PLL(p[i].ND - smol, p[i].ST));
		auto it2 = s.upper_bound(PLL(p[i].ND + smol, p[i].ST));
		
		FOREACH1(it, it1, it2){
			PLL s1 = {it -> first, it -> second};
			//PLL sx = {it1 -> first, it;
			//sy = p[i].ND - it -> ST;
			FOREACH1(itt, it, it2){
				PLL s2 = {itt -> first, itt -> second}; 
				rez = min(rez, peri(p[i], s1, s2)); 
			}
		}
		s.insert({p[i].ND, p[i].ST});
	}
	return rez;
}
		
ll n, pa, pb;
VLL p;
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin>>n;
	REP(i, n){
		cin>>pa>>pb;
		p.PB({pa,pb});
	}
	cout << closest(p);
	return 0;
}
