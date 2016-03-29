#include<cstdlib>
#include<cstdio>
#include<algorithm>

using namespace std;

const int N=2048;
const int M=8192;

struct data{
	int s[N];
	int p[N];
	int l,r;
	void clear(){
		l=1;
		r=0;
	}
	void insert(int d,int k){
		while(l<=r && s[r]>d)r--;
		r++;
		s[r]=d;
		p[r]=k;
	}
	int pos(){
		return p[l];
	}
	int height(){
		return s[l];
	}
	int pop(){
		l++;
	}
};

bool a[N][N];
int p[M][N],q[M][N];
data x,y;
int ans[M];
char ch[N];
int n,m,i,j,k,t,u,v,w;

int solve(int cur,int l,int r){
	int mid,i,j,k,ans,last;
	mid=(l+r)>>1;
	x.clear();
	y.clear();
	last=ans=0;
	for(i=1;i<=m;i++){
		if(a[mid][i]){
			x.clear();
			y.clear();
			last=i;
			continue;
		}
		x.insert(p[cur][i],i);
		y.insert(q[cur][i],i);
		while(x.height()+y.height()-1<i-last){
			last=min(x.pos(),y.pos());
			if(x.pos()==y.pos()){
				x.pop();
				y.pop();
			}else if(x.pos()<y.pos())x.pop();
			else y.pop();
		}
		ans=max(ans,min(x.height()+y.height()-1,i-last));
	}
	return ans;
}

void up(int cur){
	ans[cur]=max(ans[cur],ans[cur<<1]);
	ans[cur]=max(ans[cur],ans[cur<<1|1]);	
}

void build(int cur,int l,int r){
	int mid,i;
	mid=(l+r)>>1;
	for(i=1;i<=m;i++){
		for(p[cur][i]=0;mid-p[cur][i]>=l && !a[mid-p[cur][i]][i];p[cur][i]++);
		for(q[cur][i]=0;mid+q[cur][i]<=r && !a[mid+q[cur][i]][i];q[cur][i]++);
	}
	ans[cur]=solve(cur,l,r);
	if(l==r)return;
	build(cur<<1,l,mid);
	build(cur<<1|1,mid+1,r);
	up(cur);
}

void update(int cur,int l,int r,int u,int v){
	int mid;
	mid=(l+r)>>1;
	for(p[cur][v]=0;mid-p[cur][v]>=l && !a[mid-p[cur][v]][v];p[cur][v]++);
	for(q[cur][v]=0;mid+q[cur][v]<=r && !a[mid+q[cur][v]][v];q[cur][v]++);
	ans[cur]=solve(cur,l,r);
	if(l==r)return;
	if(u<=mid)update(cur<<1,l,mid,u,v);
	else update(cur<<1|1,mid+1,r,u,v);
	up(cur);
}

int main(){
	scanf("%d%d%d",&n,&m,&t);
	for(i=1;i<=n;i++){
		scanf("%s",ch+1);
		for(j=1;j<=m;j++)a[i][j]=ch[j]=='X';
	}
	build(1,1,n);
	for(i=1;i<=t;i++){
		scanf("%d%d",&u,&v);
		a[u][v]=true;
		update(1,1,n,u,v);
		printf("%d\n",ans[1]);
	}
	return 0;
}
