#include <bits/stdc++.h>
using namespace std;

const int MAXN=2e6+5;

struct T
{
    int nr[2],p;
} L[MAXN];

bool com(const T &s,const T &p)
{
    if(s.nr[0]!=p.nr[0])
        return s.nr[0]<p.nr[0];

    return s.nr[1]<p.nr[1];
}

int N,K,stp,delta;
char S[MAXN];
int P[25][MAXN];
int Pos[MAXN];
int Nxt[MAXN][25];
int Len[MAXN];

bool MayorIgual(int p,string &aux)
{
    p=Pos[p];
    int p1=0;
    int sz=aux.size();

    while(p!=-1 && p1<sz && S[p]==aux[p1])
    {
        p1++;
        p=Nxt[p][0];
    }
    if(p==-1 && p1<sz)
        return false;

    if(p1<sz && S[p]<aux[p1])
        return false;

    return true;
}

bool MenorIgual(int p,string &aux)
{
    p=Pos[p];
    int p1=0;
    int sz=aux.size();

    while(p!=-1 && p1<sz && S[p]==aux[p1])
    {
        p1++;
        p=Nxt[p][0];
    }

    if(p!=-1 && p1<sz && S[p]>aux[p1])
        return false;

    return true;
}

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    int N,Q;
    cin >> N >> Q;

    memset(Nxt,-1,sizeof Nxt);

    for(int i=0; i<N; i++)
    {
        cin >> S[i] >> Nxt[i][0];
        Nxt[i][0]--;
    }

    for(int stp=1; (1<<stp)<=N; stp++)
    {
        for(int i=0; i<N; i++)
            Nxt[i][stp]=Nxt[Nxt[i][stp-1]][stp-1];
    }
    Len[0]=1;
    for(int i=1; i<N; i++)
    {
        int stp=0;
        while(Nxt[i][stp]!=-1)
            Len[i]=1<<stp,stp++;
    }

    for(int i=0; i<N; i++)
        P[0][i]=S[i]-'A';

    for(stp=1,delta=1; (delta>>1) < N; stp++,delta<<=1)
    {
        for(int i=0; i<N; i++)
        {
            L[i].nr[0]=P[stp - 1][i];
            L[i].p = i;
            if(Nxt[i][stp-1]!=-1)
                L[i].nr[1]=P[stp-1][Nxt[i][stp-1]];
            else
                L[i].nr[1]=-(i+1);
        }
        sort(L,L+N,com);

        for(int i=0; i<N; i++)
        {
            if(i>0 && L[i].nr[0] == L[i - 1].nr[0] && L[i].nr[1] == L[i - 1].nr[1] )
                P[stp][L[i].p]=P[stp][L[i - 1].p];
            else
                P[stp][L[i].p]=i;
        }
    }

    for(int i=0; i<N; i++)
        Pos[P[stp-1][L[i].p]]=L[i].p;

    string aux;
    for(int i=0; i<Q; i++)
    {
        cin >> aux;

        //Lower Bound
        int lb=N-1;
        int I=0,F=N-1;
        while(I<=F)
        {
            int piv=(I+F)/2;
            if(MayorIgual(piv,aux))
                lb=piv,F=piv-1;
            else
                I=piv+1;
        }
        if(!MayorIgual(lb,aux))
            lb++;
        //Upper Bound
        int ub=lb-1;
        I=lb,F=N-1;
        while(I<=F)
        {
            int piv=(I+F)/2;
            if(MenorIgual(piv,aux))
                ub=piv,I=piv+1;
            else
                F=piv-1;
        }
        ub++;

        cout << ub-lb << '\n';
    }
    return 0;
}
