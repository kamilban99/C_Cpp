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
#define INF (int)1e9
#define EPS 1e-9
#define PI 3.1415926535897932384626433832795
#define MOD 1000000007
#define read(type) readInt<type>()
#define MAX 1000002
#define MAX1 10e12
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#define time__(d) for(long blockTime = 0; (blockTime == 0 ? (blockTime=clock()) != 0 : false); debug("%s time : %.4fs", d, (double)(clock() - blockTime) / CLOCKS_PER_SEC))
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
typedef long long int ll;
typedef unsigned long long int  ull; 
typedef queue<int> QI;

ll dpmax[1000002], dpmin[1000002];
int lastmax[1000002], lastmin[1000002];
int tw[102], tp[102], rezmin[102], rezmax[102];
int F, C;

void minmaxDP(){
	REP(j, C){
		if(dpmax[tw[j]] < tp[j]){
			dpmax[tw[j]] = tp[j];
			lastmax[tw[j]] = j;
		}
		if(!dpmin[tw[j]]) dpmin[tw[j]] = 100001; 
		if(dpmin[tw[j]] > tp[j]){
			dpmin[tw[j]] = tp[j];
			lastmin[tw[j]] = j;
		}
	}
	REP1(i, F){
		if(!dpmin[i])dpmin[i] = 10e17;
		REP(j, C){
			if(tw[j] <=  i){
				if(dpmax[i-tw[j]] + tp[j] > dpmax[i] && dpmax[i - tw[j]]){
					dpmax[i] = dpmax[i - tw[j]] + tp[j];
					lastmax[i] = j;
				}
				/*if(dpmin[i] == 0){
					if(dpmin[i-tw[j]]){
						dpmin[i] = dpmin[i - tw[j]] + tp[j];
						lastmin[i] = j;
					}
				}
				else{*/
					if(dpmin[i-tw[j]] + tp[j] < dpmin[i] && dpmin[i - tw[j]]){
						dpmin[i] = dpmin[i - tw[j]] + tp[j];
						lastmin[i] = j;
					}
			}
		}
		if(dpmin[i] == 10e17)dpmin[i] = 0;
	}
}
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	//time__("zad"){
	cin>>F>>C;
	REP(i, C){
		cin>>tp[i]>>tw[i];
	}
	minmaxDP();
	if(!dpmax[F]){
		cout<<"NIE";
		return 0;
	}
	cout<<"TAK\n";
	cout<<dpmin[F]<<"\n";
	int rez = F;
	while(rez){
		rezmax[lastmax[rez]]++;
		rez -= tw[lastmax[rez]];
	}
	rez = F;
	while(rez){
		rezmin[lastmin[rez]]++;
		//cout<<lastmin[rez]<<" "<<tp[lastmin[rez]]<<endl;
		rez -= tw[lastmin[rez]];
	}
	REP(i, C){
		//cout<<i<<" "<<rezmin[i]<<"\n";
		cout<<rezmin[i]<<" ";
	}
	cout<<"\n"<<dpmax[F]<<"\n";
	REP(i, C){
		//cout<<i<<" "<<rezmax[i]<<"\n";
		cout<<rezmax[i]<<" ";	
	}
	//}
	return 0;
}
