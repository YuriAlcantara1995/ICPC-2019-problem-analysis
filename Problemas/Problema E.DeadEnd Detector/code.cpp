#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int>par;
const int MAXN=5e5+5;
vector<int>ady[MAXN];
typedef pair<int,int>par;


int CC[MAXN];
int CN[MAXN];
bool notTree[MAXN];
int cc;
par E[MAXN];
int G[MAXN];
bool Eliminado[MAXN];


void dfs(int nod,int parent=-1)
{
    CC[nod]=cc;
    CN[cc]++;
    for(auto nn:ady[nod])
    {
        if(CC[nn])
        {
            if(nn!=parent)
                notTree[cc]=true;
            continue;
        }
        dfs(nn,nod);
    }
}

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    int N,M;
    cin >> N >> M;

    int a,b;
    for(int i=1; i<=M; i++)
    {
        cin >> a >> b;
        ady[a].push_back(b);
        ady[b].push_back(a);
        E[i]=par(a,b);
        G[a]++,G[b]++;
    }

    for(int i=1; i<=N; i++)
    {
        if(CC[i])continue;
        cc++;
        dfs(i);
    }

    queue<int>cola;
    vector<par>sol;

    for(int i=1; i<=M; i++)
    {
        int a=E[i].first;
        int b=E[i].second;
        if(notTree[CC[a]])
        {
            if(G[a]==1)
                cola.push(a);
            if(G[b]==1)
                cola.push(b);
        }
        else
        {
            if(G[a]==1)
                sol.push_back(par(a,b));
            if(G[b]==1)
                sol.push_back(par(b,a));
        }
    }

    while(!cola.empty())
    {
        int nod=cola.front();
        Eliminado[nod]=true;
        cola.pop();

        for(auto nn:ady[nod])
        {
            if(Eliminado[nn])continue;
            G[nn]--;
            if(G[nn]==1)
                cola.push(nn);
        }
    }

    for(int i=1; i<=M; i++)
    {
        int a=E[i].first;
        int b=E[i].second;
        if(Eliminado[a] && !Eliminado[b])
            sol.push_back(par(b,a));
        if(Eliminado[b] && !Eliminado[a])
            sol.push_back(par(a,b));
    }

    sort(sol.begin(),sol.end());
    cout << sol.size() << '\n';
    for(auto i:sol)
        cout << i.first << ' ' << i.second << '\n';




    return 0;
}
