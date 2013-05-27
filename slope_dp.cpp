#pragma warning(disable:4996)
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
#include <string.h>
#include <ctime>
#include <limits.h>
using namespace std;

typedef long long ll;
const double pi=acos(-1.0);
const double eps=1e-11;
//const ll INF=(_I64_MAX)/2;
//#pragma comment(linker, "/STACK:102400000,102400000")
const int inf=0x3f3f3f3f;
#define maxx(a) memset(a, 0x3f, sizeof(a))
#define zero(a) memset(a, 0, sizeof(a))
template<class T>void show(T a, int n){for(int i=0; i<n; ++i) cout<<a[i]<<' '; cout<<endl;}
template<class T>void show(T a, int r, int l){for(int i=0; i<r; ++i)show(a[i],l);cout<<endl;}
#define REP(i,a,b) for(i=a;i<b;i++)
#define rep(i,n) REP(i,0,n)
#define srep(i,n) for(i = 1;i <= n;i ++)
#define snuke(c,itr) for(__typeof((c).begin()) itr=(c).begin();itr!=(c).end();itr++)
#define MP make_pair
typedef pair<int,int> PII;

const int N = 1e5+ 111;
ll dd[N];
ll sy[N];
ll sum[N];
ll dp[101][N];

//const int N = 1e6+ 111;
ll num[N];
struct point{
	ll x,y;
	point(ll x=0,ll y=0):x(x),y(y){}
	point operator -(const point B) const {
		return point(x - B.x, y - B.y);
	}
}q[N];
inline ll cross(point O, point A, point B) {
	point OA = A - O;
	point OB = B - O;
	return OA.x * OB.y - OB.x * OA.y;
}

ll getx(int i){
	return i;
}
ll gety(int _p,int i){
	return dp[_p-1][i] + sum[i];
}
ll getk(int i){
	return sy[i];
}
ll getg(int l,int i){
	return q[l].y - getk(i) * q[l].x;
}

void slope(int _p,int m){//G = dp[p][x] + sum[x] - a[x]*x      k = a[x]    x = x     y = dp[p-1][k] + sum[k]
	int l,r;
	l = r = 1;
	dp[_p-1][0] = 0;
	q[1] = point(getx(0),gety(0,0));
	int i,j;
	srep(i,m){
		point tmp(getx(i),gety(_p,i));
		for(j = r;j > l;j --){
			if(cross(q[j-1],q[j],tmp) >= 0) break;
			else r--;
		}
		q[++r] = tmp;

		for(j = l;j < r;j ++){
			if( (q[j+1].y - q[j].y) < getk(i) * (q[j+1].x - q[j].x) ) l++;
			else break;
		}
		dp[_p][i] = getg(l,i) - sum[i] + sy[i] * i;
	}
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin); 
	// freopen("out.txt","w",stdout);
#endif
	int n,m,p,i,j,a,b,t;
	scanf("%d%d%d",&n,&m,&p);
	maxx(dp);
	REP(i,2,n+1) {
		scanf("%d",&a);
		dd[i] = dd[i-1] + a;
	}
	srep(i,m){
		scanf("%d%d",&a,&b);
		sy[i] = b - dd[a];
	}
	sort(sy+1,sy+1+m);
	srep(i,m){
		sum[i] = sum[i-1] + sy[i];
	}

	srep(i,p) slope(i,m);

	printf("%I64d",dp[min(m,p)][m]);

	return 0;
}
