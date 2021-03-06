#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<queue>

using namespace std;

const int N=400400;

struct pos{
	int l,r,s;
};

struct data{
	pos u[2],v[2],w[2],s;
};

struct seg{
	int l,r;
	bool f;
	pos p;
};

pos operator + (pos x,pos y){
	pos z;
	z.s=x.s+y.s;
	z.l=x.l;
	z.r=y.r;
	return z;
}

data operator + (data x,data y){
	data z;
	z.s=x.s+y.s;
	if(x.w[0].s<y.w[0].s)z.w[0]=x.w[0];
	else z.w[0]=y.w[0];
	if(z.w[0].s>x.v[0].s+y.u[0].s)z.w[0]=x.v[0]+y.u[0];
	z.u[0]=x.u[0];
	if(z.u[0].s>x.s.s+y.u[0].s)z.u[0]=x.s+y.u[0];
	z.v[0]=y.v[0];
	if(z.v[0].s>y.s.s+x.v[0].s)z.v[0]=x.v[0]+y.s;
	if(x.w[1].s>y.w[1].s)z.w[1]=x.w[1];
	else z.w[1]=y.w[1];
	if(z.w[1].s<x.v[1].s+y.u[1].s)z.w[1]=x.v[1]+y.u[1];
	z.u[1]=x.u[1];
	if(z.u[1].s<x.s.s+y.u[1].s)z.u[1]=x.s+y.u[1];
	z.v[1]=y.v[1];
	if(z.v[1].s<y.s.s+x.v[1].s)z.v[1]=x.v[1]+y.s;
	return z;
}

bool operator < (seg x,seg y){
	return (x.f?x.p.s:-x.p.s)<(y.f?y.p.s:-y.p.s);
}

priority_queue<seg> h;
data a[N];
int t[N];
seg x,y,z,f;
int n,m,i,j,k,u,v,w,ans;

void build(int cur,int l,int r){
	int mid;
	if(l==r){
		a[cur].s=a[cur].u[0]=a[cur].v[0]=a[cur].u[1]=a[cur].v[1]=(pos){l,l,t[l]};
		a[cur].w[0]=a[cur].w[1]=(pos){l,l,0};
		a[cur].w[0].s=min(a[cur].w[0].s,t[l]);
		a[cur].w[1].s=max(a[cur].w[1].s,t[l]);
		return;
	}
	mid=(l+r)>>1;
	build(cur<<1,l,mid);
	build(cur<<1|1,mid+1,r);
	a[cur]=a[cur<<1]+a[cur<<1|1];
}

data ask(int cur,int l,int r,int u,int v){
	int mid;
	if(l>=u && r<=v)return a[cur];
	mid=(l+r)>>1;
	if(v<=mid)return ask(cur<<1,l,mid,u,v);
	if(u>mid)return ask(cur<<1|1,mid+1,r,u,v);
	return ask(cur<<1,l,mid,u,v)+ask(cur<<1|1,mid+1,r,u,v);
}

void modify(int cur,int l,int r,int tar){
	int mid;
	if(l==r){
		a[cur].s=a[cur].u[0]=a[cur].v[0]=a[cur].u[1]=a[cur].v[1]=(pos){l,l,t[l]};
		a[cur].w[0]=a[cur].w[1]=(pos){l,l,0};
		a[cur].w[0].s=min(a[cur].w[0].s,t[l]);
		a[cur].w[1].s=max(a[cur].w[1].s,t[l]);
		return;
	}
	mid=(l+r)>>1;
	if(tar<=mid)modify(cur<<1,l,mid,tar);
	else modify(cur<<1|1,mid+1,r,tar);
	a[cur]=a[cur<<1]+a[cur<<1|1];
}

int main(){
	scanf("%d",&n);
	for(i=1;i<=n;i++)scanf("%d",&t[i]);
	build(1,1,n);
	scanf("%d",&m);
	for(i=1;i<=m;i++){
		scanf("%d",&k);
		if(!k){
			scanf("%d%d",&u,&v);
			t[u]=v;
			modify(1,1,n,u);
		}else{
			scanf("%d%d%d",&u,&v,&w);
			while(!h.empty())h.pop();
			h.push((seg){u,v,1,ask(1,1,n,u,v).w[1]});
			ans=0;
			for(j=1;j<=w;j++){
				f=h.top();
				h.pop();
				if(f.f){
					if(f.p.s<=0)break;
					ans+=f.p.s;
					if(f.l<f.p.l)h.push((seg){f.l,f.p.l-1,1,ask(1,1,n,f.l,f.p.l-1).w[1]});
					h.push((seg){f.p.l,f.p.r,0,ask(1,1,n,f.p.l,f.p.r).w[0]});
					if(f.p.r<f.r)h.push((seg){f.p.r+1,f.r,1,ask(1,1,n,f.p.r+1,f.r).w[1]});
				}else{
					if(f.p.s>=0)break;
					ans-=f.p.s;
					if(f.l<f.p.l)h.push((seg){f.l,f.p.l-1,0,ask(1,1,n,f.l,f.p.l-1).w[0]});
					h.push((seg){f.p.l,f.p.r,1,ask(1,1,n,f.p.l,f.p.r).w[1]});
					if(f.p.r<f.r)h.push((seg){f.p.r+1,f.r,0,ask(1,1,n,f.p.r+1,f.r).w[0]});
				}
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}
