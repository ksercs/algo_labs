#include <iostream>
#include <fstream>
#include <utility>
#include <algorithm>

#define PII pair <int, int>
#define SS second
#define FF first
#define MP make_pair
#define LL long long

using namespace std;

const double EPS = 1e-6;
const int MAXN = (int)1e6 + 15;


int S, n, MaxS, MaxT;
double ans;
int t[MAXN], v[MAXN];
LL s[MAXN];

float getS(float tm)
{
		float ss = 0;
		int i = 0;
		while(tm >= t[i])
		{
			ss += t[i]*v[i];
			tm -= t[i];
			i++;
		}
		ss += tm*v[i];
		return ss;
}

/*int getInd(double tm)
{
	int L = 0, R = n;
	while(R-L > 1)
	{
	    int M = (L+R)/2;
		if(t[M] < tm)
			L = M;
		else
			R = M;
	}
	return R;
}

double getS(double tm)
{
	double path = 0;
	int i = getInd(tm);
	path = s[i] + (tm-t[i-1])*v[i];
	return path;
}

double Count(double M)
{
	double res = 1e10;

	for(int i = 0; i < n; i++){
		if(1.0*t[i] < M-EPS)
			continue;
		double there = t[i] - M;
		double high = getS(t[i]);
		double low = getS(there);
		cout << i << " " << M << " " << t[i] << " " << there << " " << low << " " <<high << "\n";
		res = min(res, high-low);
	}

	for(int i = 0; i < n; i++){
		if(t[i] > t[n-1]-M)
			continue;
		double there = t[i]+M;
		double low = getS(t[i]);
		double high = getS(there);
		res = min(res, high-low);
	}
	return res;
}*/
bool check(float t, float dt)
{
    float s1, s2;
    s1 = getS(t);
    s2 = getS(t - dt);
	return  (s1 - s2) < S;
}

bool check2(float t, float dt)
{
    float s1, s2;
    s1 = getS(t);
    s2 = getS(t + dt);
	return  (s2 - s1) < S;
}

bool Count(float M)
{
	float fl = 0;
    float tmp = 0;
	for(int i = 0; i < n; i++){
        if(tmp > M)
            fl+=check(tmp, M);
        tmp += t[i];
		if(fl > 0)
			return 1;
	}
    tmp = 0;
	for(int i = 0; i < n; i++){
        if(tmp < MaxT - M)
            fl+=check2(tmp, M);
        tmp += t[i];
		if(fl > 0)
			return 1;
	}
	return 0;
}

double bin()
{
    double L = 0, R = MaxT, M = 0;
    while (R-L > EPS){
        M = (R+L)/2.0;
        //cout << "BIN : " << L << " " << R << " " << M << " " << Count(M)  << "\n";
        if (Count(M) /*<= S*/)
            L = M;
        else
            R = M;
    }
    return (L+R)/2;
}

void in()
{
    ifstream cin("trains.in");
    cin >> S >> n;
    for (int i = 0; i < n; ++i){
        cin >> t[i] >> v[i];
        MaxT += t[i];
        MaxS += t[i]*v[i];
        //if (i)
        //    t[i] += t[i-1];
    }
}

void solution()
{
    LL cnt = t[0]*v[0];
    s[1] = cnt;

    for(int i = 1; i < n; i++){
        cnt += (t[i]-t[i-1])*v[i];
		s[i+1] = cnt;
	}

	ans = bin();
}

void out()
{
    ofstream cout("trains.out");
    cout.precision(4);
    cout << fixed << ans << "\n";
}

int main()
{
    in();
    solution();
    out();
    return 0;
}
