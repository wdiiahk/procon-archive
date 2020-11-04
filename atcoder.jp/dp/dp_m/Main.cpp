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
 * N 人の子供たちがいます。 子供たちには 1,2,…,N と番号が振られています。
 * 
 * 子供たちは K個の飴を分け合うことにしました。 
 * このとき、各 i (1≤i≤N) について、子供 i が受け取る飴の個数は 
 * 0 以上 ai 以下でなければなりません。 また、飴が余ってはいけません。
 * 子供たちが飴を分け合う方法は何通りでしょうか？ 
 * 10^9+7で割った余りを求めてください。 ただし、2 通りの方法が異なるとは、
 * ある子供が存在し、その子供が受け取る飴の個数が異なることを言います。
 */
ll N, K;
vll a;
// i番目の人まで、j個の飴を配る場合の数
// dp[0][0] = 1;
// dp[i][j] = dp[i-1][j] + dp[i-1][j-1] + ... + dp[i-1][j-a_i];
arr<ll> dp;

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> K;
  a.assign(N, 0);
  REP(i, N)
  {
    cin >> a.at(i);
  }
  //
  dp.assign(N + 1, vll(K + 1, 0));
  dp.at(0).at(0) = 1;
  FOR(i, 1, N + 1)
  {
    vll acc(K + 2, 0);
    REP(j, K + 1)
    {
      acc.at(j + 1) = acc.at(j) + dp.at(i - 1).at(j);
      acc.at(j + 1) %= MOD;
    }
    REP(j, K + 1)
    {
      ll to = max(j - a.at(i - 1), ll(0));
      dp.at(i).at(j) = acc.at(j + 1) - acc.at(to) + MOD;
      dp.at(i).at(j) %= MOD;
    }
  }
  pr(dp.at(N).at(K));
  return 0;
}
