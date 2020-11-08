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
 * 2K 人が参加するトーナメントがある。このトーナメントでは以下の形式で試合を行う。
 * 
 * - 第 1 ラウンドでは、1 と 2、3 と 4、…　が試合を行う。
 * - 第 2 ラウンドでは、(1 と 2 の勝者) と (3 と 4 の勝者), (5 と 6 の勝者) と (7 と 8 の勝者), …　が試合を行う。
 * - 第 3 ラウンドでは、((1 と 2 の勝者) と (3 と 4 の勝者) の勝者) と ((5 と 6 の勝者) と (7 と 8 の勝者) の勝者), ((9 と 10 の勝者) と (11 と 12 の勝者) の勝者) と ((13 と 14 の勝者) と (15 と 16 の勝者) の勝者), …　が試合を行う。
 * - 以下同様に第 K ラウンドまで行う。
 * 
 * 第 K ラウンドの終了後に優勝者が決定する。人 i の Elo Rating が Ri であるとき、人 i の優勝確率を求めよ。
 * ただし、Elo Rating RP の人 P と Elo Rating RQ の人 Q が対戦した場合、
 * 人 P が勝つ確率は 1/(1+10^(RQ−RP)/400) であり、異なる試合の勝敗は独立であるとする。 
 * 
 * Constraints
 * - 1≤K≤10
 * - 0≤Ri≤4000
 */

ll K, N;
vll R;
// 人jが、i勝する確率
arr<double> dp, p;

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> K;
  N = pow(2, K);
  R.resize(N, 0);
  REP(i, N)
  {
    cin >> R.at(i);
  }
  p.resize(N, vector<double>(N, 0));
  REP(i, N)
  {
    REP(j, N)
    {
      if (i == j)
      {
        continue;
      }
      p.at(i).at(j) = 1.0 / (1 + pow(10.0, (R.at(j) - R.at(i)) / 400.0));
    }
  }

  dp.resize(K + 1, vector<double>(N, 0.0));
  REP(j, N)
  {
    dp.at(0).at(j) = 1.0;
  }

  FOR(i, 1, K + 1)
  {
    ll len = pow(2, i - 1);
    REP(j, N)
    {
      ll group_A = j / len;
      ll target = (group_A % 2 == 0) ? group_A + 1 : group_A - 1;
      REP(k, N)
      {
        if (k / len == target)
        {
          dp.at(i).at(j) += p.at(j).at(k) * dp.at(i - 1).at(k) * dp.at(i - 1).at(j);
        }
      }
    }
  }
  //
  REP(j, N)
  {
    pd(dp.at(K).at(j));
  }
}
