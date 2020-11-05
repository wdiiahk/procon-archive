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

/**
 * 問題文
 * 
 * N頂点の木があります。 頂点には 1,2,…,N と番号が振られています。 
 * 各 i (1≤i≤N−1) について、i 番目の辺は頂点 xi と yi を結んでいます。
 * 
 * 太郎君は、各頂点を白または黒で塗ることにしました。 
 * このとき、どの黒い頂点からどの黒い頂点へも、黒い頂点のみを辿って到達できるようにします。
 * 正整数 Mが与えられます。 各 v (1≤v≤N) について、次の質問に答えてください。
 * 
 * 頂点 v が黒であるような頂点の色の組合せは何通りか？ Mで割った余りを求めよ。
 * 
 * 制約
 * 
 * 入力はすべて整数である。
 * 1≤N≤10^5
 * 2≤M≤10^9
 * 1≤xi,yi≤N
 * 与えられるグラフは木である。
 */
ll N, M;
arr<ll> edges;
vll dp1, dp2;

void dfs1(ll x, ll p = -1)
{
  ll prod = 1;
  FORA(to, edges.at(x))
  {
    if (to == p)
    {
      continue;
    }
    dfs1(to, x);
    prod *= dp1.at(to);
    prod %= M;
  }
  dp1.at(x) = (prod + 1) % M;
}

void dfs2(ll x, ll last = -1)
{
  if (last == -1)
  {
    dp2.at(x) = 1;
  }
  vll lprod = vll(edges.at(x).size() + 1, 1);
  REP(i, edges.at(x).size())
  {
    ll to = edges.at(x).at(i);
    lprod.at(i + 1) = lprod.at(i);
    if (to == last)
    {
      continue;
    }
    lprod.at(i + 1) *= dp1.at(to);
    lprod.at(i + 1) %= M;
  }
  //
  vll rprod = vll(edges.at(x).size() + 1, 1);
  REPD(i, edges.at(x).size())
  {
    if (i == 0)
    {
      continue;
    }
    ll to = edges.at(x).at(i);
    rprod.at(i - 1) = rprod.at(i);
    if (to == last)
    {
      continue;
    }
    rprod.at(i - 1) *= dp1.at(to);
    rprod.at(i - 1) %= M;
  }
  //
  REP(i, edges.at(x).size())
  {
    ll to = edges.at(x).at(i);
    if (to == last)
    {
      continue;
    }
    ll rest_prod = 1;
    rest_prod *= lprod.at(i);
    rest_prod %= M;
    rest_prod *= rprod.at(i);
    rest_prod %= M;
    dp2.at(to) = (rest_prod * dp2.at(x) + 1) % M;
    dfs2(to, x);
  }
}

vll ans;
void dfs3(ll x, ll last = -1)
{
  ll res(dp2.at(x));
  FORA(to, edges.at(x))
  {
    if (to == last)
    {
      //      res *= dp2.at(x);
      continue;
    }
    res *= dp1.at(to);
    res %= M;
    dfs3(to, x);
  }
  ans.at(x) = (res % M);
}

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> M;
  //
  edges.assign(N, vll());
  REP(i, N - 1)
  {
    ll x, y;
    cin >> x >> y;
    edges.at(x - 1).push_back(y - 1);
    edges.at(y - 1).push_back(x - 1);
  }

  dp1.assign(N, 0);
  dfs1(0);
  dp2.assign(N, 0);
  dfs2(0);
  ans.assign(N, 0);
  dfs3(0);
  REP(i, N)
  {
    pr(ans.at(i));
  }
  return 0;
}
