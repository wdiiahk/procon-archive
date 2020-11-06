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
 * N 個のブロックがあります。 ブロックには 1,2,…,N と番号が振られています。 
 * 各 i (1≤i≤N) について、ブロック i の重さは wi で、丈夫さは si で、価値は viです。
 * 太郎君は、N 個のブロックのうち何個かを選び、それらを任意の順序で一列に積み重ね、
 * 塔を作ることにしました。 このとき、塔は次の条件を満たさなければなりません。
 * 塔に含まれる各ブロック i について、ブロック i より上に積まれたブロックの重さの総和は si 以下である。
 * 塔に含まれるブロックの価値の総和の最大値を求めてください。
 */
ll N(1000);
// i番目まで見た時、重さの和がjとなるタワーの価値の最大値
// dp[i][j] = max(dp[i-1][j], dp[i-1][j-w[i]] + v[i])
//
arr<ll> dp(1100, vll(22000, 0));
vll w(1100, 0), s(1100, 0), v(1100, 0);
int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  REP(i, N)
  {
    cin >> w.at(i) >> s.at(i) >> v.at(i);
  }
  vll blocks;
  REP(i, N)
  {
    blocks.push_back(i);
  }
  sort(ALL(blocks), [&](ll x, ll y) {
    return s.at(x) + w.at(x) < s.at(y) + w.at(y);
  });
  //  A + w1 < s2
  //      s1 < A + w2
  //   w1 + s1 < s2 + w2
  //
  FOR(i, 1, N + 1)
  {
    ll ind = blocks.at(i - 1);
    REP(j, 22000)
    {
      dp.at(i).at(j) = dp.at(i - 1).at(j);
      if (0 <= j - w.at(ind) && j - w.at(ind) <= s.at(ind))
      {
        chmax(dp.at(i).at(j), dp.at(i - 1).at(j - w.at(ind)) + v.at(ind));
      }
    }
  }
  //
  ll ans(0);
  REP(j, 22000)
  {
    chmax(ans, dp.at(N).at(j));
  }
  pr(ans);
}
