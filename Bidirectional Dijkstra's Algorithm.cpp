#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> ii;
typedef pair<string,ll> si;
typedef pair<ii,ll> iii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;
#define sort(a) sort(a.begin(),a.end());
#define pb push_back
#define pf push_front
#define popb pop_back
#define popf pop_front
#define mp make_pair
#define F first
#define S second
#define ios ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define nl "\n"
const ld PI = 3.1415926535898;
const ll LLMAX = LLONG_MAX;
const ll MOD=1000000007;
#define N (int)1e6+5

int n,m,x,y,u,v;
ll maximum=1000000000000000;
ll z;
vector<pair<int,int> >edge[N];

vector<pair<int,int> >edge_rev[N];

int heap[N];
ll distances[N];
int pos[N];

int heap_rev[N];
ll distances_rev[N];
int pos_rev[N];

vector<int>processed_nodes;
int processed[N]={0};
int processed_rev[N]={0};

void shift_up(int heap[],int pos[],ll distances[],int i)
{
	if(i<=0)return;
	int par=(i-1)/2;
	if(distances[heap[par]]>distances[heap[i]])
	{
		swap(pos[heap[i]],pos[heap[par]]);
		swap(heap[i],heap[par]);
		return shift_up(heap,pos,distances,par);
	}
	return;
}

void shift_down(int heap[],int pos[],ll distances[],int i,int size)
{
	int ch1=2*i+1,ch2=2*i+2,ch;
	if(ch1>=size)return;
	else if(ch2==size)
	{
		if(distances[heap[ch1]]<distances[heap[i]])
		{
			swap(pos[heap[ch1]],pos[heap[i]]);
			swap(heap[ch1],heap[i]);
			return shift_down(heap,pos,distances,ch1,size);
		}
		return;
	}
	ll v1=distances[heap[ch1]],v2=distances[heap[ch2]];
	if(v1<v2)ch=ch1;
	else ch=ch2;
	if(distances[heap[ch]]<distances[heap[i]])
	{
		swap(pos[heap[ch]],pos[heap[i]]);
		swap(heap[ch],heap[i]);
		return shift_down(heap,pos,distances,ch,size);
	}
	return;
}

void find_min_distance()
{
	ll ans=maximum;
	for(int i=0;i<processed_nodes.size();i++)
	{
		processed_rev[processed_nodes[i]]=0;
		processed[processed_nodes[i]]=0;
		ans=min(ans,distances[processed_nodes[i]]+distances_rev[processed_nodes[i]]);
	}
	if(ans==maximum)cout<<"There is no path between given nodes."<<nl;
	else cout<<"Minimum distance between given nodes is "<<ans<<nl;
}

void solve(int u,int v)
{
	processed_nodes.clear();
	int size=n;
	for(int i=1;i<=n;i++)
	{
		heap[i-1]=i;
		pos[i]=i-1;
		distances[i]=maximum;
		heap_rev[i-1]=i;
		pos_rev[i]=i-1;
		distances_rev[i]=maximum;
	}
	distances[u]=0;
	distances_rev[v]=0;
	shift_up(heap,pos,distances,pos[u]);
	shift_up(heap_rev,pos_rev,distances_rev,pos_rev[v]);
	for(size;size>0;size--)
	{
		int node=heap[0];
		swap(pos[heap[0]],pos[heap[size-1]]);
		swap(heap[0],heap[size-1]);
		shift_down(heap,pos,distances,0,size-1);
		if(distances[node]==maximum)break;
		for(int i=0;i<edge[node].size();i++)
		{
			if(distances[edge[node][i].F]>distances[node]+edge[node][i].S)
			{
				distances[edge[node][i].F]=distances[node]+edge[node][i].S;
				int temp=pos[edge[node][i].F];
				while(temp>0 && distances[heap[(temp-1)/2]]>distances[heap[temp]])
				{
					swap(pos[heap[temp]],pos[heap[(temp-1)/2]]);
					swap(heap[temp],heap[(temp-1)/2]);
					temp=(temp-1)/2;
				}
			}
		}
		processed_nodes.pb(node);
		processed[node]=1;
		if(processed_rev[node])return find_min_distance();

		node=heap_rev[0];
		swap(pos_rev[heap_rev[0]],pos_rev[heap_rev[size-1]]);
		swap(heap_rev[0],heap_rev[size-1]);
		shift_down(heap_rev,pos_rev,distances_rev,0,size-1);
		if(distances_rev[node]==maximum)break;
		for(int i=0;i<edge_rev[node].size();i++)
		{
			if(distances_rev[edge_rev[node][i].F]>distances_rev[node]+edge_rev[node][i].S)
			{
				distances_rev[edge_rev[node][i].F]=distances_rev[node]+edge_rev[node][i].S;
				int temp=pos_rev[edge_rev[node][i].F];
				while(temp>0 && distances_rev[heap_rev[(temp-1)/2]]>distances_rev[heap_rev[temp]])
				{
					swap(pos_rev[heap_rev[temp]],pos_rev[heap_rev[(temp-1)/2]]);
					swap(heap_rev[temp],heap_rev[(temp-1)/2]);
					temp=(temp-1)/2;
				}
			}
		}
		processed_nodes.pb(node);
		processed_rev[node]=1;
		if(processed[node])return find_min_distance();
	}
	for(int i=0;i<processed_nodes.size();i++)
	{
		processed_rev[processed_nodes[i]]=0;
		processed[processed_nodes[i]]=0;
	}
	cout<<"There is no path between given nodes."<<nl;
}

int main()
{
	cout<<"Enter the number of nodes: ";
	cin>>n;
	cout<<"Enter the number of edges: ";
	cin>>m;
	cout<<"Enter two nodes joined with an edge and weight of the edge:\n";
	for(int i=0;i<m;i++)
	{
		cin>>x>>y>>z;
		edge[x].pb(mp(y,z));
		edge_rev[y].pb(mp(x,z));
	}
	while(true)
	{
		cout<<"Enter the source node: ";
		cin>>u;
		cout<<"Enter the destination node: ";
		cin>>v;
		if(u==v)cout<<"Shortest distance between nodes is 0"<<nl;
		else solve(u,v);
		int k;
		cout<<"Enter 1 if you have further queries else enter 0: ";
		cin>>k;
		if(k==0)break;
	}
}
