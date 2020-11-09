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
 * Problem Statement
 * サイコロを N 回振ったとき、出た目の積が D の倍数となる確率を求めよ。
 * 
 * Constraints
 * - 1≤N≤100
 * - 1≤D≤10^18
 */
ll N, D, D2(0), D3(0), D5(0);
arr<arr<double>> dp;

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> D;
  //
  ll cur = D;
  while (cur % 2 == 0)
  {
    cur /= 2;
    D2++;
  }
  while (cur % 3 == 0)
  {
    cur /= 3;
    D3++;
  }
  while (cur % 5 == 0)
  {
    cur /= 5;
    D5++;
  }
  if (1 < cur)
  {
    pd(0.0);
    return 0;
  }

  //
  double prob(1. / 6);
  dp.resize(N + 1, vector<arr<double>>(D2 + 1, arr<double>(D3 + 1, vector<double>(D5 + 1, 0))));
  dp.at(0).at(0).at(0).at(0) = 1;
  FOR(i, 1, N + 1)
  {
    REP(j, D2 + 1)
    {
      REP(k, D3 + 1)
      {
        REP(l, D5 + 1)
        {

          // 1
          dp.at(i).at(j).at(k).at(l) += dp.at(i - 1).at(j).at(k).at(l);
          // 2
          if (j == D2)
          {
            dp.at(i).at(j).at(k).at(l) += dp.at(i - 1).at(j).at(k).at(l);
          }
          if (0 <= j - 1)
          {
            dp.at(i).at(j).at(k).at(l) += dp.at(i - 1).at(j - 1).at(k).at(l);
          }
          // 3
          if (k == D3)
          {
            dp.at(i).at(j).at(k).at(l) += dp.at(i - 1).at(j).at(k).at(l);
          }
          if (0 <= k - 1)
          {
            dp.at(i).at(j).at(k).at(l) += dp.at(i - 1).at(j).at(k - 1).at(l);
          }
          // 4
          if (j == D2)
          {
            dp.at(i).at(j).at(k).at(l) += dp.at(i - 1).at(j).at(k).at(l);
            if (0 <= j - 1)
            {
              dp.at(i).at(j).at(k).at(l) += dp.at(i - 1).at(j - 1).at(k).at(l);
            }
          }
          if (0 <= j - 2)
          {
            dp.at(i).at(j).at(k).at(l) += dp.at(i - 1).at(j - 2).at(k).at(l);
          }
          // 5
          if (l == D5)
          {
            dp.at(i).at(j).at(k).at(l) += dp.at(i - 1).at(j).at(k).at(l);
          }
          if (0 <= l - 1)
          {
            dp.at(i).at(j).at(k).at(l) += dp.at(i - 1).at(j).at(k).at(l - 1);
          }
          // 6
          if (j == D2 && k == D3)
          {
            dp.at(i).at(j).at(k).at(l) += dp.at(i - 1).at(j).at(k).at(l);
          }
          if (j == D2 && 0 <= k - 1)
          {
            dp.at(i).at(j).at(k).at(l) += dp.at(i - 1).at(j).at(k - 1).at(l);
          }
          if (0 <= j - 1 && k == D3)
          {
            dp.at(i).at(j).at(k).at(l) += dp.at(i - 1).at(j - 1).at(k).at(l);
          }
          if (0 <= j - 1 && 0 <= k - 1)
          {
            dp.at(i).at(j).at(k).at(l) += dp.at(i - 1).at(j - 1).at(k - 1).at(l);
          }
          dp.at(i).at(j).at(k).at(l) *= prob;
        }
      }
    }
  }
  //
  pd(dp.at(N).at(D2).at(D3).at(D5));
  return 0;
}
