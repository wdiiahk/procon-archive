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

void pd(double x) { cout << fixed << setprecision(10) << x << endl; }

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
 * N を正の奇数とします。
 * N 枚のコインがあります。 
 * コインには 1,2,…,N と番号が振られています。 
 * 各 i (1≤i≤N) について、コイン i を投げると、確率 pi で表が出て、確率 1−pi で裏が出ます。
 * 太郎君は N 枚のコインをすべて投げました。 
 * このとき、表の個数が裏の個数を上回る確率を求めてください。
 */
ll N;
vector<double> p;
// dp[i][j] : i番目まで投げて、j回表がでる確率
// dp[i][j] = dp[i-1][j-1] * p[i-1] + dp[i-1][j] * (1 - p[i-1])
arr<double> dp;

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  p.assign(N, 0);
  REP(i, N)
  {
    cin >> p.at(i);
  }
  //
  dp.assign(N + 1, vector<double>(N + 1, 0));
  dp.at(0).at(0) = 1;
  FOR(i, 1, N + 1)
  {
    REP(j, N + 1)
    {
      if (0 <= j - 1)
      {
        dp.at(i).at(j) += dp.at(i - 1).at(j - 1) * p.at(i - 1);
      }
      dp.at(i).at(j) += dp.at(i - 1).at(j) * (1.0 - p.at(i - 1));
    }
  }
  //
  double ans(0);
  FOR(j, N / 2 + 1, N + 1)
  {
    ans += dp.at(N).at(j);
  }
  pd(ans);
}
