//デバッグ用オプション：-fsanitize=undefined,address

//コンパイラ最適化
#pragma GCC optimize("Ofast")

//インクルードなど
#include <bits/stdc++.h>
using namespace std;
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

using Edge = pair<ll, P>;

struct UnionFind
{
  vll par, siz;
  UnionFind() {}
  void init(ll n)
  {
    par.assign(n, -1);
    siz.assign(n, 0);
  }

  ll root(ll x)
  {
    if (par.at(x) < 0)
    {
      return x;
    }
    return par.at(x) = root(par.at(x));
  }

  bool same(ll x, ll y)
  {
    ll rx = root(x);
    ll ry = root(y);
    return rx == ry;
  }

  bool unite(ll x, ll y)
  {
    ll rx = root(x);
    ll ry = root(y);
    if (rx == ry)
    {
      return false;
    }
    if (siz.at(rx) < siz.at(ry))
    {
      swap(rx, ry);
    }
    par.at(ry) = rx;
    siz.at(rx) += siz.at(ry);
    return true;
  }

  ll size(ll x)
  {
    ll rx = root(x);
    return siz.at(rx);
  }
};

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll N;
  cin >> N;
  vll x(N), y(N);
  REP(i, N)
  {
    cin >> x.at(i) >> y.at(i);
  }
  //
  vll xidx(N, 0);
  iota(ALL(xidx), 0);
  sort(ALL(xidx), [&](ll l, ll r) {
    return x.at(l) < x.at(r);
  });
  vll yidx(N, 0);
  iota(ALL(yidx), 0);
  sort(ALL(yidx), [&](ll l, ll r) {
    return y.at(l) < y.at(r);
  });
  vector<Edge> edges(4 * N);
  REP(i, N - 1)
  {
    ll lx = xidx.at(i);
    ll rx = xidx.at(i + 1);
    edges.at(4 * i) = {x.at(rx) - x.at(lx), {lx, rx}};
    edges.at(4 * i + 1) = {x.at(rx) - x.at(lx), {rx, lx}};
    ll ly = yidx.at(i);
    ll ry = yidx.at(i + 1);
    edges.at(4 * i + 2) = {y.at(ry) - y.at(ly), {ly, ry}};
    edges.at(4 * i + 3) = {y.at(ry) - y.at(ly), {ry, ly}};
  }

  //
  sort(ALL(edges));
  ll res(0);
  UnionFind uf;
  uf.init(N);
  FORA(e, edges)
  {
    ll w = e.first;
    ll u = e.second.first;
    ll v = e.second.second;
    if (uf.same(u, v))
    {
      continue;
    }
    res += w;
    uf.unite(u, v);
  }

  pr(res);
}
