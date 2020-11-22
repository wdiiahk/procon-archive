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

arr<ll> edges;
vbool h;

// i: nodeの部分木に宝石を含んでいるか
vbool dp;
void dfs(ll x, ll last = -1)
{
  dp.at(x) = h.at(x);
  FORA(to, edges.at(x))
  {
    if (to == last)
    {
      continue;
    }
    dfs(to, x);
    dp.at(x) = dp.at(x) || dp.at(to);
  }
}

vll dp2;
void dfs2(ll x, ll last = -1)
{
  FORA(to, edges.at(x))
  {
    if (to == last)
    {
      continue;
    }
    if (!dp.at(to))
    {
      continue;
    }
    dp2.at(x)++;
    dfs2(to, x);
    dp2.at(x) += dp2.at(to);
    dp2.at(x)++;
  }
}

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll N, X;
  cin >> N >> X;
  X--;
  h.assign(N, false);
  REP(i, N)
  {
    ll a;
    cin >> a;
    h.at(i) = (a == 1);
  }
  edges.assign(N, vll());
  REP(i, N - 1)
  {
    ll a, b;
    cin >> a >> b;
    a--;
    b--;
    edges.at(a).push_back(b);
    edges.at(b).push_back(a);
  }
  //
  dp.assign(N, false);
  dfs(X);
  dp2.assign(N, 0);
  dfs2(X);
  ll ans(dp2.at(X));
  pr(ans);
  return 0;
}
