#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN=1e4+5;
ll DP[MAXN];
ll X[MAXN],Y[MAXN];
int MINI[MAXN],MAXD[MAXN];

bool check(double xc, double yc, double r, double xp,double yp)
{
    double D=-2*xc;
    double E=-2*yc;
    double F=xc*xc+yc*yc-r*r;

    double a=1.,b=E,c=xp*xp+D*xp+F;
    double SqrtDisc = sqrt(b*b - 4*a*c);
    double y=max((-b+SqrtDisc)/2*a,(-b-SqrtDisc)/2*a);

    return yp>y;
}

bool ArcoValido(int i,int j)
{
    if(i>j)
        swap(i,j);
    return MAXD[i]>=j && MINI[j]<=i;
}

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    int N,H,A,B;
    cin >> N >> H >> A >> B;

    for(int i=1; i<=N; i++)
        cin >> X[i] >> Y[i];

    for(int i=1; i<=N; i++)
    {
        MAXD[i]=N;
        for(int j=i; j<=MAXD[i]; j++)
        {
            double Xc = (X[i]+X[MAXD[i]])/2.;
            double Yc = H-(X[MAXD[i]]-X[i])/2.;
            double r  = (X[MAXD[i]]-X[i])/2.;
            while(MAXD[i]>j && X[j]<Xc && check(Xc,Yc,r,X[j],Y[j]))
            {

                MAXD[i]--;
                Xc = (X[i]+X[MAXD[i]])/2.;
                Yc = H-(X[MAXD[i]]-X[i])/2.;
                r  = (X[MAXD[i]]-X[i])/2.;
            }
            if(X[j]>=Xc)
                break;
        }
        MINI[i]=1;
        for(int j=i; j>=MINI[i]; j--)
        {
            double Xc = (X[i]+X[MINI[i]])/2.;
            double Yc = H-(X[i]-X[MINI[i]])/2.;
            double r  = (X[i]-X[MINI[i]])/2.;
            while(MINI[i]<j && X[j]>Xc && check(Xc,Yc,r,X[j],Y[j]))
            {
                MINI[i]++;
                Xc = (X[i]+X[MINI[i]])/2.;
                Yc = H-(X[i]-X[MINI[i]])/2.;
                r  = (X[i]-X[MINI[i]])/2.;
            }
            if(X[j]<=Xc)
                break;
        }
    }

    DP[1] = A*(H-Y[1]);
    for(int i=2; i<=N; i++)
        DP[i]=1ll<<60;
    for(int i=2; i<=N; i++)
        for(int j=1; j<i; j++)
            if(ArcoValido(j,i))
                DP[i]=min(DP[i],DP[j]+ A*(H-Y[i]) + B*(X[j]-X[i])*(X[j]-X[i]));

    if(DP[N]==1ll<<60)
        cout << "impossible\n";
    else
        cout << DP[N] << '\n';

    return 0;
}
