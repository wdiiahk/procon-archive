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
  ll N, L;
  Constants()
  {
    cin >> N >> L;
  }
} C;

struct Args
{
  vector<P> lr;
  vll c;
  vll sorted;

  Args() : lr(C.N), c(C.N), sorted(C.N)
  {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    REP(i, C.N)
    {
      cin >> lr.at(i).first >> lr.at(i).second >> c.at(i);
      sorted.at(i) = i;
    }
    sort(ALL(sorted), [&](ll l, ll r) {
      return lr.at(l).second > lr.at(r).second;
    });
  }
} args;

struct BIT
{
  int _n;
  vll data;
  BIT(ll n) : _n(n), data(n, INF)
  {
  }

  void set(int p, ll x)
  {
    p++;
    while (p <= _n)
    {
      chmin(data.at(p - 1), x);
      p += p & -p;
    }
  }

  ll query(int r)
  {
    ll res = INF;
    while (r > 0)
    {
      chmin(res, data.at(r - 1));
      r -= r & -r;
    }
    return res;
  }
};

struct Solver
{
  ll ans;
  vll dp;
  BIT bit;
  Solver() : ans(0), dp(C.L + 1, INF), bit(2 * C.L)
  {
    dp.at(C.L) = 0;
    bit.set(C.L, 0);
  }
  //
  void solve()
  {
    REP(i, C.N)
    {
      ll ni = args.sorted.at(i);
      ll l = args.lr.at(ni).first;
      ll r = args.lr.at(ni).second;
      ll c = args.c.at(ni);
      /*
      REPD(j, C.L + 1)
      {
      if (l <= j && j <= r)
      {
      */
      /*
      ll tmpmin = INF;
      REP(k, r + 1)
      {
        chmin(tmpmin, dp.at(k));
      }
      */
      ll tmpmin = bit.query(r + 1);
      bit.set(l, tmpmin + c);
      /*
      }
      }
      */
    }
    ans = bit.query(0 + 1);
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
