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
 * Problem Statement
 * ある路線には駅 1 から駅 N までの N 個の駅がある。すぬけ君は、この路線に準急を走らせることにした。
 *     - 準急は、駅 1 に止まり、{駅 2, ..., 駅 N-1} の部分集合に止まり、駅 Nに止まる。
 *     - 連続する K 個以上の駅に止まると、客が飽きてしまうので、そのようなことはしない。
 * 準急の停車駅の組み合わせとして何通り考えられるか、mod 1,000,000,007 で求めよ。 
 */
ll N, K;
vll dp;
bool flip(false);
//
// dp.at(i).at(0) = sum_i sum_j^i-2 dp.at(i-1).at(j)
// dp.at(i).at(j) = dp.at(i-1).at(j-1);

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> K;
  dp.assign(2 * K, 0);
  //
  ll zeroj = 0;
  dp.at(0) = 1;
  //
  zeroj += (2 * K - 1);
  zeroj %= 2 * K;
  dp.at(zeroj) = 0;
  //
  zeroj += (2 * K - 1);
  zeroj %= 2 * K;
  dp.at(zeroj) = 1;

  ll last = dp.at((zeroj + K + 1) % (2 * K));
  FOR(i, 3, N + 1)
  {
    /*
    REP(j, K)
    {
      dp.at(i).at(0) += dp.at(i - 1).at(j);
    }
    */
    zeroj += (2 * K - 1);
    zeroj %= 2 * K;
    last = dp.at((zeroj + K + 1) % (2 * K));
    dp.at(zeroj) = 2 * dp.at((zeroj + 1) % (2 * K)) - last + MOD;
    dp.at(zeroj) %= MOD;
    /*
    FOR(j, 1, K)
    {
      dp.at(curi).at(j) = dp.at(prei).at(j - 1);
    }
    */
  }
  ll ans(0);
  FOR(j, 1, K)
  {
    ll curj = (zeroj + j) % (2 * K);
    ans += dp.at(curj);
    ans %= MOD;
  }
  pr(ans);
  return 0;
}
