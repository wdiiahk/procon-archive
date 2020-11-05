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
 * N 頂点の木があります。 頂点には 1,2,…,N と番号が振られています。 
 * 各 i (1≤i≤N−1) について、i 番目の辺は頂点 xi と yi を結んでいます。
 * 太郎君は、各頂点を白または黒で塗ることにしました。 
 * ただし、隣り合う頂点どうしをともに黒で塗ってはいけません。
 * 頂点の色の組合せは何通りでしょうか？ 10^9+7で割った余りを求めてください。
 */
ll N;
arr<ll> edges;
// dp: i番目の頂点で、j(0:白, 1:黒)番目の色の場合の数
arr<ll> dp;
vbool used;

void dfs(ll x, ll p = -1)
{
  /*
  if (used.at(x))
  {
    return;
  }
  used.at(x) = true;
  */
  dp.at(x).at(0) = dp.at(x).at(1) = 1;
  FORA(to, edges.at(x))
  {
    if (to == p)
    {
      continue;
    }
    dfs(to, x);
    dp.at(x).at(0) *= (dp.at(to).at(0) + dp.at(to).at(1)) % MOD;
    dp.at(x).at(0) %= MOD;
    dp.at(x).at(1) *= dp.at(to).at(0);
    dp.at(x).at(1) %= MOD;
  }
}

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  edges.assign(N, vll());
  REP(i, N - 1)
  {
    ll x, y;
    cin >> x >> y;
    edges.at(x - 1).push_back(y - 1);
    edges.at(y - 1).push_back(x - 1);
  }
  //
  dp.assign(N, vll(2, 0));
  used.assign(N, false);
  dfs(0);
  ll ans = dp.at(0).at(0) + dp.at(0).at(1);
  ans %= MOD;
  pr(ans);
}
