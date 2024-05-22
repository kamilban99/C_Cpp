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
#define IN(A, B, C) assert( B <= A && A <= C)
#define MP make_pair
#define PB push_back
#define ST first
#define ND second
#define CI const int
#define INF (int)1e9
#define EPS 1e-9
#define PI 3.1415926535897932384626433832795
#define MOD 1000000007
#define read(type) readInt<type>()
#define MAX 10001
#define MAX1 200001
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#define time__(d) for(long blockTime = 0; (blockTime == 0 ? (blockTime=clock()) != 0 : false); debug("%s time : %.4fs", d, (double)(clock() - blockTime) / CLOCKS_PER_SEC))
const double pi=acos(-1.0);
typedef pair<int, int> PII;
typedef long long int ll;
typedef pair<ll, int> PLI;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<PII> VII;
typedef vector<VI> VVI;
typedef map<int,int> MPII;
typedef map<int, ll> MPIL;
typedef map<int, PLI>MIPLI;
typedef set<int> SETI;
typedef multiset<int> MSETI;
typedef long int int32;
typedef unsigned long int uint32;
typedef unsigned long long int  ull; 
typedef queue<int> QI;

int n, m, k;
ll now;
MIPLI s;
CI MK = 1000005;

int rev[MK];

struct Catalan{
	int a, b, c;
}Cat[MK];

VI E;

bool sort_tuple(Catalan x, Catalan y){
	if(x.a != y.a)
		return x.a < y.a;
	return x.b < y.b;
}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m >> k;
	REP(i, k){
		cin >> Cat[i].a >> Cat[i].b >> Cat[i].c;
		//E.PB({Cat[i].a, Cat[i].b});	
	}
	s.emplace(0,PLI{0,-1});
	sort(Cat, Cat + k, sort_tuple);
	REP(i,k){
		/*cout<<"size "<<s.size()<<endl;
		FOREACH(itt, s)
			cout<<itt->ST<<" "<<itt->ND<<"\n";
		cout<<"koniec mapy\n";*/
		auto it = s.upper_bound(Cat[i].b);
		--it;
		rev[i]= it->ND.ND;
		now = it->ND.ST + Cat[i].c;
		++it;
		while(it != s.end() && it->ND.ST < now){
			it = s.erase(it);
		}
		//cout<<"s[cat[i].b] i now: " <<s[Cat[i].b] <<" "<<now<<"\n";
		s[Cat[i].b] = max(s[Cat[i].b], {now,i});
	/*	if(s[Cat[i].b] == now){
			
			F.PB({E[Cat[i].in].ST,E[Cat[i].in].ND});
		}*/
	//rezz[i] = (--s.end())->ND;
	}
	cout<<(--s.end())->ND.ST<<"\n";
	int p = (--s.end())->ND.ND;
	while(p != -1){
		E.push_back(p);
		p = rev[p];
	}
	cout<<E.size()<<"\n";
	for(int i = E.size() - 1; 0 <= i; i--)
		cout<<Cat[E[i]].a<<" "<<Cat[E[i]].b<<"\n";

	/*cout<<"kolejne wyniki \n";
	REP(i,k)
		cout<<Cat[i].a<<" "<<Cat[i].b<<" "<<Cat[i].c<<" "<<<"\n";*/
	/*int siz = F.size();
	cout<<siz<<"\n";
	REP(i, siz){
		cout<<F[i].ST<<" "<<F[i].ND<<"\n";
	}*/
	return 0;
}
