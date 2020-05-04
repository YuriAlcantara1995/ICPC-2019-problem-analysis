#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int>par;
const int MAXN=1e6+5;

int getMarker(string in)
{
    int ret=0;
    for(int i=1; i<in.size(); i++)
    {
        ret*=10;
        ret+=(in[i]-'0');
    }
    return ret;
}

set<int>M;
vector<par>V[MAXN];
int C[MAXN];
int TA[MAXN];


int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    int N;
    cin >> N;

    string in;
    for(int i=1; i<=N; i++)
    {
        cin >> in;
        char c=in[0];
        int marker=getMarker(in);
        if(c=='s')
            V[marker].push_back(par(1,i)),C[marker]++;
        else
            V[marker].push_back(par(-1,i)),C[marker]--;

        M.insert(marker);
    }

    multiset<par>I;

    for(auto i:M)
    {
        if(C[i])continue;
        int c=0;
        int minc=1<<30;
        for(auto p:V[i])
        {
            c+=p.first;
            minc=min(minc,c);
        }
        c=0;
        for(int j=0; j<V[i].size(); j++)
        {
            c+=V[i][j].first;
            if(c==minc && j+1<V[i].size())
                I.insert(par(V[i][j].second+1,V[i][j+1].second));
            else if(c==minc)
            {
                if(V[i][j].second+1<=N)
                    I.insert(par(V[i][j].second+1,N));
                I.insert(par(1,V[i][0].second));
            }
        }
    }

    for(auto p:I)
    {
        TA[p.first]++;
        TA[p.second+1]--;
    }

    int solV=0,solP=1;
    for(int i=1; i<=N; i++)
    {
        TA[i]+=TA[i-1];
        if(TA[i]>solV)
        {
            solV=TA[i];
            solP=i;
        }
    }

    cout << solP << ' ' << solV << '\n';

    return 0;
}
