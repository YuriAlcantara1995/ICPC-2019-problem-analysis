#include <bits/stdc++.h>
using namespace std;

const int MAXN=5e5+5;
vector<int>Prv[MAXN];
int MaxLevel;
int L[MAXN];
int Stack[MAXN],s;
int sol[MAXN],TA[MAXN];
int F[MAXN],Nxt[MAXN];
int N,K;

void dfs(int nod,int pad,int lv)
{
    L[lv]++;
    Stack[++s]=nod;
    MaxLevel=max(MaxLevel,lv);
    if(s-K>=1)
        F[Stack[s-K]]++;
    for(auto nn:Prv[nod])
    {
        if(nn==pad)continue;
        dfs(nn,nod,lv+1);
    }
    s--;
}

void g(int nod,int pad)
{
    sol[nod]=1;
    for(auto nn:Prv[nod])
    {
        if(nn==pad)continue;
        g(nn,nod);
        sol[nod]+=sol[nn]-F[nn];
    }
}
int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    cin >> N >> K;

    for(int i=1; i<=N; i++)
    {
        cin >> Nxt[i];
        Prv[Nxt[i]].push_back(i);
    }
    memset(sol,-1,sizeof sol);
    for(int nod=1; nod<=N; nod++)
    {
        if(sol[nod]!=-1)continue;

        int u,t;
        for (u = nod, t = Nxt[nod]; u != t && u != Nxt[t]; u = Nxt[u], t = Nxt[Nxt[t]]);
        vector<int> cycle;
        cycle.push_back(u);
        for (int i = Nxt[u]; i != u; i = Nxt[i])
            cycle.push_back(i);

        for(auto i: cycle)
            sol[i]=min(K+1,(int)cycle.size());

        int sz=cycle.size();
        for(int i=0; i<sz; i++)
        {
            for(auto j:Prv[cycle[i]])
            {
                if(i==0 && j==cycle[sz-1])continue;
                if(i>0 && j==cycle[i-1])continue;
                for(int k=1; k<=MaxLevel; k++)
                    L[k]=0;
                MaxLevel=0,s=0;

                dfs(j,cycle[i],1);
                g(j,cycle[i]);

                for(int k=1; k<=MaxLevel; k++)
                {
                    if(K<k)continue;

                    if(K>=sz-1+k)
                        TA[0]+=L[k];
                    else
                    {
                        int r=i+K-k;
                        TA[i]+=L[k];
                        if(r>=sz)
                        {
                            r=r%sz;
                            TA[0]+=L[k];
                            TA[r+1]-=L[k];
                        }
                        else if(r+1!=sz) TA[r+1]-=L[k];
                    }
                }
            }
        }
        for(int k=0; k<sz; k++)
        {
            TA[k]+=TA[k-1];
            sol[cycle[k]]+=TA[k];
        }
        for(int k=0; k<sz; k++)
            TA[k]=0;
    }

    for(int i=1; i<=N; i++)
        cout << sol[i] << '\n';

    return 0;
}
