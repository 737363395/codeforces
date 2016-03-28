#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cstring>

using namespace std;

#define ll long long
#define N 131072
#define M 266144

struct matrix{
	ll s[2][2];
	void make(ll a,ll b,ll c,ll d){
		s[0][0]=a;
		s[0][1]=b;
		s[1][0]=c;
		s[1][1]=d;
	}
	void clear(){
		s[0][0]=s[1][1]=1;
		s[0][1]=s[1][0]=0;
	}
};


struct data{
	int l,r;
	matrix s;
};

struct query{
	ll p,q;
};

struct inter{
	matrix s;
	ll p;
};

data a[M];
ll s[N];
matrix t,ans;
inter f[N];
query q[N];
int n,m,i,j,c;
ll k,p,d;

matrix operator * (matrix u,matrix v){
	matrix w;
	int i,j,k;
	memset(w.s,0,sizeof(w.s));
	for(i=0;i<2;i++)
		for(j=0;j<2;j++)
			for(k=0;k<2;k++){
				w.s[i][j]+=u.s[i][k]*v.s[k][j]%p;
				w.s[i][j]%=p;
			}
				
	return w;
}

int pre(int x){
	return x==0?n-1:x-1;
}

void build(int cur,int l,int r){
	int mid;
	a[cur].l=l;
	a[cur].r=r;
	if(l==r){
		a[cur].s.make(s[pre(l)],1,s[pre(pre(l))],0);
		return;
	}
	mid=(l+r)>>1;
	build(cur<<1,l,mid);
	build(cur<<1|1,mid+1,r);
	a[cur].s=a[cur<<1].s*a[cur<<1|1].s;
}

matrix ask(int cur,int l,int r){
	int mid;
	if(l<=a[cur].l && r>=a[cur].r)return a[cur].s;
	mid=(a[cur].l+a[cur].r)>>1;
	if(r<=mid)return ask(cur<<1,l,r);
	if(l>mid)return ask(cur<<1|1,l,r);
	return ask(cur<<1,l,r)*ask(cur<<1|1,l,r);
}

matrix power(matrix x,ll y){
	matrix z;
	if(!y)return t;
	z=power(x,y>>1);
	if(y&1)return z*z*x;
	else return z*z;
}

matrix sum(ll l,ll r){
	ll u,v;
	if(l>r)return t;
	u=l/n+1;
	v=r/n;
	if(u<=v)return ask(1,l%n,n-1)*power(ask(1,0,n-1),v-u)*ask(1,0,r%n);
	else return ask(1,l%n,r%n);
}

int comp(query u,query v){
	return u.p<v.p;
}

int main(){
	scanf("%I64d%I64d",&k,&p);
	if(!k){
		printf("0\n");
		return 0;
	}
	scanf("%d",&n);
	for(i=0;i<n;i++){
		scanf("%I64d",&s[i]);
		s[i]%=p;
	}
	build(1,0,n-1);
	scanf("%d",&m);
	for(i=1;i<=m;i++){
		scanf("%I64d%I64d",&q[i].p,&q[i].q);
		q[i].q%=p;
	}
	t.clear();
	ans.clear();
	sort(q+1,q+m+1,comp);
	for(i=1;i<=m;i++){
		if(f[c].p==q[i].p+1)f[c].s.s[0][0]=q[i].q;
		else{
			c++;
			f[c].s.make(q[i].q,1,s[pre(q[i].p%n)],0);
			f[c].p=q[i].p+1;
		}
		c++;
		f[c].s.make(s[(q[i].p+1)%n],1,q[i].q,0);
		f[c].p=q[i].p+2;
	}
	d=1;
	for(i=1;i<=c;i++){
		if(f[i].p>k)break;
		ans=ans*sum(d+1,f[i].p-1)*f[i].s;
		d=f[i].p;
	}
	ans=ans*sum(d+1,k);
	printf("%I64d\n",ans.s[0][0]);
	return 0;
}
