#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<queue>

using namespace std;

#define pa pair<double,int>
#define mp make_pair
#define A first
#define B second
#define N 128
#define M 300000

priority_queue<pa> h;
double a[N],b[N],p[N];
int n,m,i,j,k;
double ans,sum;

double f(int i){
	return p[i]*a[i]/(1-p[i]);
}

int main(){
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		scanf("%d",&k);
		a[i]=k/100.0;
		b[i]=1-a[i];
	}
	sum=1;
	ans=n;
	for(i=1;i<=n;i++){
		p[i]=b[i];
		sum*=1-p[i];
		h.push(mp(f(i),i));
		ans*=a[i];
	}
	for(i=n+1;i<=M;i++){
		k=h.top().B;
		h.pop();
		ans+=f(k)*sum*i;
		sum*=(1-p[k]*b[k])/(1-p[k]);
		p[k]*=b[k];
		h.push(mp(f(k),k));
	}
	printf("%.10lf\n",ans);
	return 0;
}
