#include <bits/stdc++.h>
using namespace std;

const int MAXN=5e5+5;
typedef pair<int,int>par;
struct azulejos
{
    int p,h,id;
    azulejos()
    {
        p=0,h=0,id=0;
    }
    bool operator < (const azulejos &a)const
    {
        return p < a.p;
    }
};
azulejos A1[MAXN],A2[MAXN];
multiset<par>MS1,MS2;
multiset<par>::iterator it1,it2;
vector<int>sol1,sol2;
bool Impossible=false;;

void proccess()
{
    if(MS1.size()<=MS2.size())
    {
        it1=MS1.begin();
        it2=MS2.lower_bound(par(it1->first,0));
        if(it2==MS2.begin())
        {
            Impossible=true;
            return;
        }
        it2--;
        sol1.push_back(it1->second);
        sol2.push_back(it2->second);
        MS1.erase(it1);
        MS2.erase(it2);
    }
    else
    {
        it2=MS2.begin();
        it1=MS1.upper_bound(par(it2->first,1<<30));
        if(it1==MS1.end())
        {
            Impossible=true;
            return;
        }
        sol1.push_back(it1->second);
        sol2.push_back(it2->second);
        MS1.erase(it1);
        MS2.erase(it2);
    }
}

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    int N;
    cin >> N;

    for(int i=1; i<=N; i++)
        cin >> A1[i].p;
    for(int i=1; i<=N; i++)
        cin >> A1[i].h,A1[i].id=i;

    for(int i=1; i<=N; i++)
        cin >> A2[i].p;
    for(int i=1; i<=N; i++)
        cin >> A2[i].h,A2[i].id=i;

    sort(A1+1,A1+N+1);
    sort(A2+1,A2+N+1);

    int p1=1,p2=1;

    while(p1<=N || p2<=N)
    {
        if(MS1.empty())
        {
            int paux=p1;
            while(p1<=N && A1[paux].p==A1[p1].p)
                MS1.insert(par(A1[p1].h,A1[p1].id)),p1++;
        }
        if(MS2.empty())
        {
            int paux=p2;
            while(p2<=N && A2[paux].p==A2[p2].p)
                MS2.insert(par(A2[p2].h,A2[p2].id)),p2++;
        }

        proccess();
        if(Impossible)
        {
            cout << "impossible\n";
            return 0;
        }

    }

    while(!MS1.empty() && !MS2.empty())
    {
        proccess();
        if(Impossible)
        {
            cout << "impossible\n";
            return 0;
        }
    }
    cout << sol1[0];
    for(int i=1; i<N; i++)
        cout << ' ' << sol1[i];
    cout << '\n' << sol2[0];
    for(int i=1; i<N; i++)
        cout << ' ' << sol2[i];
    cout << '\n';

    return 0;
}
