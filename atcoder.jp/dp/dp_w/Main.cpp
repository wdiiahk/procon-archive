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
 * 長さ N の 0 と 1 からなる文字列を考えます。 この文字列のスコアを次のように計算します。
 * 各 i (1≤i≤M) について、li 文字目から ri 文字目までに 1 がひとつ以上含まれるならば、スコアに ai を加算する。
 * 文字列のスコアの最大値を求めてください。
 * 
 * 制約
 * 
 * 入力はすべて整数である。
 * 1≤N≤2×10^5
 * 1≤M≤2×10^5
 * 1≤li≤ri≤N
 * |ai|≤10^9
 */
ll N, M;
// dp 左からi番目まで見た時、最も右の1がj番目であるような文字列に対して確定しているスコアの最大値
// dp[i][j] = dp[i-1][j] + (r = iでありjを含む区間のスコア)
// dp[i][i] = max(dp[i-1][j]) + (r = iである区間のスコア)

arr<ll> dp;

struct Seg
{
  vll sum;
  vll mx;
  Seg() : sum(1 << 19, 0), mx(1 << 19, 0) {}

  void add_val(ll l, ll r, ll val, ll bottom = 0, ll top = 1 << 18, ll pos = 1)
  {
    if (l <= bottom && top <= r)
    {
      sum.at(pos) += val;
      return;
    }
    if (r <= bottom || top <= l)
    {
      return;
    }
    ll mid = (bottom + top) / 2;
    add_val(l, r, val, bottom, mid, pos * 2);
    add_val(l, r, val, mid, top, pos * 2 + 1);
    mx.at(pos) = max(
        mx.at(pos * 2) + sum.at(pos * 2),
        mx.at(pos * 2 + 1) + sum.at(pos * 2 + 1));
  }

  ll max_val(ll l, ll r, ll bottom = 0, ll top = 1 << 18, ll pos = 1)
  {
    if (l <= bottom && top <= r)
    {
      return sum.at(pos) + mx.at(pos);
    }
    if (r <= bottom || top <= l)
    {
      return -INF;
    }
    ll mid = (bottom + top) / 2;
    return max(
               max_val(l, r, bottom, mid, pos * 2),
               max_val(l, r, mid, top, pos * 2 + 1)) +
           sum.at(pos);
  }
};

arr<P> intervals;

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> M;
  //
  intervals.resize(N + 1);
  REP(i, M)
  {
    ll l, r, a;
    cin >> l >> r >> a;
    intervals.at(r).push_back({l, a});
  }

  Seg seg;
  FOR(i, 1, N + 1)
  {
    ll mx = seg.max_val(0, i);
    seg.add_val(i, i + 1, mx);
    FORA(p, intervals.at(i))
    {
      ll l = p.first;
      ll a = p.second;
      seg.add_val(l, i + 1, a);
    }
  }
  ll ans = seg.max_val(0, N + 1);
  pr(ans);
}
