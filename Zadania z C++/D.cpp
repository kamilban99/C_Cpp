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
#define INF (int)1e9
#define EPS 1e-9
#define PI 3.1415926535897932384626433832795
#define MOD 1000000007
#define read(type) readInt<type>()
#define MAX 1000002
#define MAX1 2
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





int n,k, tab[MAX];

void medianfive(int b, int e, int pos){ 
	sort(tab + b, tab + e + 1); //sortowanie <= 5 liczb
	//cout<<"piątka to: "<<tab[b]<<" "<<tab[b+1]<<" "<<tab[b+2]<<" "<<tab[b+3]<<" "<<tab[b+4]<<"\n";
	swap(tab[(b + e) / 2], tab[pos]);
}

int magicalfives(int b, int e){
	int len = e - b + 1;
	if(len <= 20){
		sort(tab + b, tab + e + 1); //sortowanie <= 20 liczb
	//	cout<<"mediana to "<<tab[(b + e) / 2]<<"\n";
		return (b + e) / 2; 
	}
	int cunt = b;
	int belp = b;
	int fives = ceil(len / 5);
	int fives1 = fives;
	//szukanie pivota
	while(fives1--){
		if(belp + 4 > e) medianfive(belp, e, cunt);
		else medianfive(belp, belp + 4, cunt);
		//cout<<tab[cunt]<<"\n";
		cunt++;
		belp = belp + 5;
	//	cout<<fives<<endl;
	}
	return magicalfives(b, b + fives);
}

int find_kth(int b, int e, int k){
	int len = e - b + 1;
	if(len <= 20){
		sort(tab + b, tab + e + 1); //sortowanie <= 20 liczb
		//cout<<"wypisujemy wynik"<<" "<<k<<" "<<tab[k]<<"\n";
		return tab[k];
	}
	int pivot = magicalfives(b, e);
	swap(tab[pivot], tab[e]);
	pivot = tab[e];
	//cout<<"pivot: "<<pivot<<"\n";
	int b1 = b, e1 = e, h = b;
	while(h <= e1){
		if(tab[h] < pivot)
			swap(tab[b1++], tab[h++]);
		else if(tab[h] == pivot) 
			h++;
		else if(tab[h] > pivot)
			swap(tab[h], tab[e1--]);
	}
	b1--;
	cout<< "b1 i h to "<<b1<<" "<<h<<"\n";
	/*
	cout<<"wypisanie tablicy \n";
	for (int i = b; i <= e; i++) {
		cout <<i<<" "<<tab[i]<<"\n";
	}*/
	if(k <= b1) pivot =  find_kth(b, b1, k);
	if(k >= h) pivot =  find_kth(h, e, k);
	return pivot;
}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin>> n >> k;
	REP(i, n){
		cin >> tab[i];
	}
	cout<<find_kth(0, n - 1, k - 1);
	//cout<<tab[magicalfives(0, n-1)];

return 0;
}

