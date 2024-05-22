#include<bits/stdc++.h>
using namespace std;
#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (int i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define all(cont) cont.begin(), cont.end()
#define rall(cont) cont.end(), cont.begin()
#define FOREACH(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define IN(A, B, C) assert( B <= A && A <= C)
#define MP make_pair
#define PB push_back
#define INF (int)1e9
#define EPS 1e-9
#define PI 3.1415926535897932384626433832795
#define MOD 1000000007
#define read(type) readInt<type>()
#define MAX 10001
#define MAX1 200001
const double pi=acos(-1.0);
typedef pair<int, int> PII;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<PII> VII;
typedef vector<VI> VVI;
typedef map<int,int> MPII;
typedef set<int> SETI;
typedef multiset<int> MSETI;
typedef long int int32;
typedef unsigned long int uint32;
typedef long long int int64;
typedef unsigned long long int  uint64;
typedef queue<int> QI;
int n,l,r,m,tab[2][MAX], count[MAX];
bool odw[MAX];
VII E[MAX];
QI Q;
void BFS(){
	while(!Q.empty()){
		int x = Q.front();
		Q.pop();
		FOREACH(y, E[x]){
			if(!odw[y->first]){
				odw[y->first] = true;
				tab[0][y->first] = y->second;
				tab[1][y->first] = x;
				count[y->first] = count[x] + 1;
				Q.push(y->first);
			}
		}
	}
}

void DFS(int x){
	FOREACH(y,E[x]){
		if(!odw[y->first]){
			odw[y->first] = true;
			tab[0][y->first] = y->second;
			tab[1][y->first] = x;
			count[y->first] = count[x] + 1;
			DFS(y->first);
		}
	}
}

void DFS0(){
	FOREACH(y,E[0]){
		if(!odw[y->first]){
			odw[y->first] = true;
			tab[0][y->first] = y->second;
			tab[1][y->first] = 0;
			count[y->first] = 1;
			DFS(y->first);
		}
	}
}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin>>n;
	REP(i, n){
		cin>>l>>m>>r;
		E[r].push_back({l,m});
		
	}
	 FOREACH(y, E[0]){
		 if(!odw[y->first]){
                odw[y->first] = true;
			 	tab[0][y->first] = y->second;
                tab[1][y->first] = 0;
                count[y->first] = 1;
				Q.push(y->first);
		 }
	 }
	 BFS();
	 //DFS0();

	 if(!odw[0]){
		 cout<<"BRAK";
		 return 0;
	 }
	 cout<<cunt[0]<<"\n";
	 cout<<"0"<<" "<<tab[0][0]<<" "<<tab[1][0]<<"\n";
	 n = tab[1][0];
	 while(n){
		 cout<<n<<" "<<tab[0][n]<<" "<<tab[1][n]<<"\n";
		 n = tab[1][n];
	 }
	 return 0;
}

