//デバッグ用オプション：-fsanitize=undefined,address

//コンパイラ最適化
#pragma GCC optimize("Ofast")

//インクルードなど
#include <bits/stdc++.h>
#include <atcoder/all>

using namespace std;
using namespace atcoder;

typedef long long ll;
using vint = vector<int>;
using vll = vector<ll>;
using vbool = vector<bool>;
template <class T>
using arr = vector<vector<T>>;

//マクロ
//forループ
//引数は、(ループ内変数,動く範囲)か(ループ内変数,始めの数,終わりの数)、のどちらか
//Dがついてないものはループ変数は1ずつインクリメントされ、Dがついてるものはループ変数は1ずつデクリメントされる
//FORAは範囲for文(使いにくかったら消す)
#define REP(i, n) for (ll i = 0; i < ll(n); i++)
#define REPD(i, n) for (ll i = n - 1; i >= 0; i--)
#define FOR(i, a, b) for (ll i = a; i < ll(b); i++)
#define FORD(i, a, b) for (ll i = a; i >= ll(b); i--)
#define FORA(i, I) for (const auto &i : I)
//xにはvectorなどのコンテナ
#define ALL(x) x.begin(), x.end()
#define SIZE(x) ll(x.size())
//定数
#define INF 1000000000000 //10^12:∞
#define MOD 1000000007    //10^9+7:合同式の法
#define MAXR 100000       //10^5:配列の最大のrange

// aよりもbが大きいならばaをbで更新する
// (更新されたならばtrueを返す)
template <typename T>
bool chmax(T &a, const T &b)
{
  if (a < b)
  {
    a = b; // aをbで更新
    return true;
  }
  return false;
}
// aよりもbが小さいならばaをbで更新する
// (更新されたならばtrueを返す)
template <typename T>
bool chmin(T &a, const T &b)
{
  if (a > b)
  {
    a = b; // aをbで更新
    return true;
  }
  return false;
}

template <class T>
void pl(T x) { cout << x << " "; }

template <class T>
void pr(T x) { cout << x << endl; }

template <class T>
void prvec(const vector<T> &a)
{
  REP(i, a.size() - 1)
  {
    cout << a[i] << " ";
  }
  pr(a[a.size() - 1]);
}

template <class T>
void prarr(const arr<T> &a)
{
  REP(i, a.size())
  if (a[i].empty())
    pr("");
  else
    prvec(a[i]);
}

using P = pair<ll, ll>;
void prp(const P &p) { cout << p.first << " " << p.second << endl; }

struct Constants
{
  ll N, K;
  Constants()
  {
    cin >> N >> K;
  }
} C;

struct Args
{
  string s;
  Args()
  {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> s;
  }
} args;

struct Solver
{
  char ans;
  Solver() : ans('P')
  {
  }

  ll win(ll a, ll b)
  {
    char c1 = args.s.at(a % C.N);
    char c2 = args.s.at(b % C.N);
    if (c1 == c2)
    {
      return a;
    }
    if (c1 == 'R')
    {
      if (c2 == 'S')
      {
        return a;
      }
      if (c2 == 'P')
      {
        return b;
      }
    }
    if (c1 == 'S')
    {
      if (c2 == 'P')
      {
        return a;
      }
      if (c2 == 'R')
      {
        return b;
      }
    }
    if (c1 == 'P')
    {
      if (c2 == 'R')
      {
        return a;
      }
      if (c2 == 'S')
      {
        return b;
      }
    }
    return a;
  }

  char win_c(char c1, char c2)
  {
    if (c1 == c2)
    {
      return c1;
    }
    if (c1 == 'R')
    {
      if (c2 == 'S')
      {
        return c1;
      }
      if (c2 == 'P')
      {
        return c2;
      }
    }
    if (c1 == 'S')
    {
      if (c2 == 'P')
      {
        return c1;
      }
      if (c2 == 'R')
      {
        return c2;
      }
    }
    if (c1 == 'P')
    {
      if (c2 == 'R')
      {
        return c1;
      }
      if (c2 == 'S')
      {
        return c2;
      }
    }
    return c1;
  }

  ll loop(ll l, ll r)
  {
    if (r - l == 1)
    {
      return l;
    }
    ll m = (l + r) / 2;
    ll a = loop(l, m);
    ll b = loop(m, r);
    ll res = win(a, b);
    return res;
  }

  ll modpow(ll a, ll n, ll mod)
  {
    long long res = 1;
    while (n > 0)
    {
      if (n & 1)
        res = res * a % mod;
      a = a * a % mod;
      n >>= 1;
    }
    return res;
  }

  void solve()
  {
    //
    arr<char> dp(C.K + 1, vector<char>(2 * C.N));
    REP(j, C.N)
    {
      ll k = loop(j, j + 2);
      dp.at(1).at(j) = args.s.at(k % C.N);
    }
    // i = 2;
    FOR(i, 1, C.K)
    {
      REP(j, C.N)
      {

        dp.at(i + 1).at(j) = win_c(dp.at(i).at(j), dp.at(i).at((j + modpow(2, i, C.N)) % C.N));
      }
    }
    ans = dp.at(C.K).at(0);

    /*
    ll res = loop(0, pow(ll(2), C.K));
    ans = args.s.at(res % C.N);
    */
  }
  //
  void output()
  {
    pr(ans);
  }
} s;

int main()
{
  s.solve();
  s.output();
  return 0;
}
