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
 * 問題
 * 
 * JOI君は小学 1 年生である．JOI君は教わったばかりの足し算，引き算がとても好きで，数字が並んでいるのを見ると
 * 最後の 2 つの数字の間に = を入れ，残りの数字の間に必ず + または - を入れて等式を作って遊んでいる．
 * 例えば 8 3 2 4 8 7 2 4 0 8 8 から，等式 8+3-2-4+8-7-2-4-0+8=8 を作ることができる． 
 * JOI君は等式を作った後，それが正しい等式になっているかを計算して確かめる． 
 * ただし，JOI君はまだ負の数は知らないし， 20を超える数の計算はできない．
 * したがって，正しい等式のうち左辺を左から計算したとき計算の途中で現れる 
 * 数が全て 0 以上 20以下の等式だけがJOI君が確かめられる 
 * 正しい等式である．例えば， 8+3-2-4-8-7+2+4+0+8=8 は 
 * 正しい等式だが，途中に現れる 8+3-2-4-8 が負の数なのでJOI君は
 * この等式が正しいかどうか確かめることができない．
 * 入力として数字の列が与えられたとき，JOI君が作り，
 * 確かめることができる正し い等式の個数を求めるプログラムを作成せよ．
 */
ll N, M(20);
vll a;
arr<ll> dp;

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  a.assign(N, 0);
  REP(i, N)
  {
    cin >> a.at(i);
  }
  bool flag(true);
  dp.assign(N + 1, vll(M + 1, 0));
  dp.at(0).at(0) = 1;
  REP(i, N - 1)
  {
    ll next = a.at(i);
    if (flag && next == 0)
    {
      dp.at(i+1).at(0) = 1;
      continue;
    }
    flag = false;
    REP(j, M + 1)
    {
      if (0 <= j - next)
      {
        dp.at(i + 1).at(j) += dp.at(i).at(j - next);
      }
      if (j + next <= M)
      {
        dp.at(i + 1).at(j) += dp.at(i).at(j + next);
      }
    }
  }
  //
  ll last = a.at(N - 1);
  ll ans = dp.at(N - 1).at(last);
  pr(ans);

  return 0;
}
