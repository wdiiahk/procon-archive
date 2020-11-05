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
 * 1 以上 K 以下の整数のうち、十進表記における各桁の数字の総和が D の倍数であるようなものは何個でしょうか？ 
 * 10^9+7 で割った余りを求めてください。
 */
string K;
ll D, N;

// dp; 左からi番目、j: 各数字の総和%D の総数, c: 既に小さいかどうか,
vector<arr<ll>> dp;

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> K;
  cin >> D;
  N = K.length();
  dp.assign(N + 1, arr<ll>(D, vll(2, 0)));
  dp.at(0).at(0).at(1) = 1;
  FOR(i, 1, N + 1)
  {
    ll digit = K.at(i - 1) - '0';
    REP(j, D)
    {
      REP(k, 10)
      {
        dp.at(i).at(j).at(0) += dp.at(i - 1).at(((j - k) % D + D) % D).at(0);
        if (k < digit)
        {
          dp.at(i).at(j).at(0) += dp.at(i - 1).at(((j - k) % D + D) % D).at(1);
        }
        dp.at(i).at(j).at(0) %= MOD;
      }
      dp.at(i).at(j).at(1) = dp.at(i - 1).at(((j - digit) % D + D) % D).at(1);
    }
  }
  ll ans = dp.at(N).at(0).at(0) + dp.at(N).at(0).at(1) + MOD - 1;
  ans %= MOD;
  pr(ans);
  return 0;
}
