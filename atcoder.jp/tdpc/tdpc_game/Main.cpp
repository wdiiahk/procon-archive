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
#define INF 10000000000 //10^12:∞
#define MOD 1000000007  //10^9+7:合同式の法
#define MAXR 100000     //10^5:配列の最大のrange

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
 * 
 * すぬけ君とすめけ君がゲームをしている。
 * 最初に、二つの山がある。左の山には A 個の物が積まれており、上から i 番目のものの価値は ai である。
 * 左の山には B 個の物が積まれており、上から i 番目のものの価値は bi である。
 * すぬけ君とすめけ君は、すぬけ君からはじめて交互に次の操作を繰り返す。
 * 
 * - 両方の山が空であれば、ゲームを終了する。
 * - 片方の山が空であれば、空でないほうの山の一番上のものをとる。
 * - 両方の山が空でなければ、好きなほうの山を選び、一番上のものをとる。
 * 
 * 両者が最善を尽くしたとき、すぬけ君の取るものの価値の合計を求めよ。
 * Constraints
 * 
 * - 1≤A,B≤1000
 * - 1≤ai,bi≤1000
 */
ll A(1000), B(1000);
vll a(1100, 0), b(1100, 0);
ll total(0);

// Aの山がi個、Bの山がj個の時の価値の最大
//arr<ll> dp(1100, vll(1100, 0));
arr<ll> dp;

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> A >> B;
  REP(i, A)
  {
    cin >> a.at(i);
    total += a.at(i);
  }
  REP(i, B)
  {
    cin >> b.at(i);
    total += b.at(i);
  }
  //
  dp.assign(A + 1, vll(B + 1, 0));
  dp.at(0).at(0) = 0;
  REP(i, A + 1)
  {
    REP(j, B + 1)
    {
      if (i == 0 && j == 0)
      {
        dp.at(0).at(0) = 0;
        continue;
      }
      if ((i + j) % 2 == (A + B) % 2)
      {
        if (0 <= A - i && 0 <= i - 1)
        {
          chmax(dp.at(i).at(j), dp.at(i - 1).at(j) + a.at(A - i));
        }
        if (0 <= B - j && 0 <= j - 1)
        {
          chmax(dp.at(i).at(j), dp.at(i).at(j - 1) + b.at(B - j));
        }
      }
      else
      {
        if (dp.at(i).at(j) == 0)
        {
          dp.at(i).at(j) = INF;
        }
        if (0 <= A - i && 0 <= i - 1)
        {
          chmin(dp.at(i).at(j), dp.at(i - 1).at(j));
        }
        if (0 <= B - j && 0 <= j - 1)
        {
          chmin(dp.at(i).at(j), dp.at(i).at(j - 1));
        }
      }
    }
  }
  //
  //pr((total + dp.at(A).at(B)) / 2);
  pr(dp.at(A).at(B));
  return 0;
}
