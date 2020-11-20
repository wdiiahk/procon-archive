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

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll N, M;
  cin >> N >> M;
  vector<string> grid(N);
  REP(i, N)
  {
    cin >> grid.at(i);
  }
  // generate (s -> even grid -> odd grid -> t) graph
  // grid(i, j) correspond to vertex (i * M + j)
  mf_graph<ll> g(N * M + 2);
  ll s = N * M;
  ll t = N * M + 1;
  // s -> even / odd -> t
  REP(i, N)
  {
    REP(j, M)
    {
      if (grid[i][j] == '#')
      {
        continue;
      }
      ll v = i * M + j;
      if ((i + j) % 2 == 0)
      {
        g.add_edge(s, v, 1);
      }
      else
      {
        g.add_edge(v, t, 1);
      }
    }
  }
  // even -> odd
  REP(i, N)
  {
    REP(j, M)
    {
      if ((i + j) % 2 == 1 || grid.at(i).at(j) == '#')
      {
        continue;
      }
      ll v0 = i * M + j;
      if (i && grid.at(i - 1).at(j) == '.')
      {
        ll v1 = (i - 1) * M + j;
        g.add_edge(v0, v1, 1);
      }
      if (j && grid.at(i).at(j - 1) == '.')
      {
        ll v1 = i * M + (j - 1);
        g.add_edge(v0, v1, 1);
      }
      if (i + 1 < N && grid.at(i + 1).at(j) == '.')
      {
        ll v1 = (i + 1) * M + j;
        g.add_edge(v0, v1, 1);
      }
      if (j + 1 < M && grid.at(i).at(j + 1) == '.')
      {
        ll v1 = i * M + (j + 1);
        g.add_edge(v0, v1, 1);
      }
    }
  }
  //
  ll ans(g.flow(s, t));
  FORA(e, g.edges())
  {
    if (e.from == s || e.to == t || e.flow == 0)
    {
      continue;
    }
    ll i0 = e.from / M;
    ll j0 = e.from % M;
    ll i1 = e.to / M;
    ll j1 = e.to % M;
    if (i1 < i0)
    {
      swap(i1, i0);
    }
    if (j1 < j0)
    {
      swap(j1, j0);
    }
    if (i0 != i1)
    {
      grid.at(i0).at(j0) = 'v';
      grid.at(i1).at(j1) = '^';
    }
    else
    {
      grid.at(i0).at(j0) = '>';
      grid.at(i1).at(j1) = '<';
    }
  }
  //
  pr(ans);
  FORA(line, grid)
  {
    pr(line);
  }
  return 0;
}
