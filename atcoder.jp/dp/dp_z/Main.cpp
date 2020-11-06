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
#define INF 1000000000 //10^12:∞
#define MOD 1000000007 //10^9+7:合同式の法
#define MAXR 100000    //10^5:配列の最大のrange

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
 * N個の足場があります。 足場には 1,2,…,N と番号が振られています。 
 * 各 i (1≤i≤N) について、足場 i の高さは hi です。 ここで、h1<h2<⋯<hNです。
 * 最初、足場 1 にカエルがいます。 カエルは次の行動を何回か繰り返し、足場 Nまで辿り着こうとしています。
 * 
 * 足場 iにいるとき、足場 i+1,i+2,…,N のどれかへジャンプする。 
 * このとき、ジャンプ先の足場を j とすると、コスト (hj−hi)2+C を支払う。
 * 
 * カエルが足場 N に辿り着くまでに支払うコストの総和の最小値を求めてください。
 * 
 * 制約
 * 入力はすべて整数である
 * 2≤N≤2×10^5
 * 1≤C≤10^12
 * 1≤h1<h2<⋯<hN≤10^6
 */
ll N, C;
vll h;

ll calc(P &f, ll x)
{
  return f.first * x + f.second;
}

struct CHTrick
{
  vll to;
  vector<P> f;
  CHTrick() {}

  void add_line(ll a, ll b)
  {
    P new_f = P(a, b);
    if (f.empty())
    {
      f.push_back(new_f);
      return;
    }
    if (calc(f.back(), INF) <= calc(new_f, INF))
    {
      return;
    }
    if (calc(new_f, 0) <= calc(f.front(), 0))
    {
      f.clear();
      to.clear();
      f.push_back(new_f);
      return;
    }
    //
    while (!to.empty())
    {
      ll lastl = to.back() + 1;
      if (calc(new_f, lastl) <= calc(f.back(), lastl))
      {
        f.pop_back();
        to.pop_back();
      }
      else
      {
        break;
      }
    }
    ll bottom = (!to.empty()) ? to.back() + 1 : -INF;
    ll top = INF;
    while (1 < top - bottom)
    {
      ll mid = (top + bottom) / 2;
      if (calc(new_f, mid) <= calc(f.back(), mid))
      {
        top = mid;
      }
      else
      {
        bottom = mid;
      }
    }
    to.push_back(bottom);
    f.push_back(new_f);
  }

  ll get_min(ll x)
  {
    ll ind = lower_bound(ALL(to), x) - to.begin();
    return calc(f.at(ind), x);
  }
};

vll dp;

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> C;
  h.resize(N);
  REP(i, N)
  {
    cin >> h.at(i);
  }
  //
  //chmin(dp.at(i), dp.at(j) + pow(h.at(j) - h.at(i), 2) + C);
  //chmin(dp.at(i), dp.at(j) + pow(h.at(j), 2) - 2 * h.at(j) * h.at(i));
  // dp.at(i) += dp.at(i) * dp.at(i) + C;
  CHTrick ch;
  dp.resize(N, 0);
  dp.at(0) = 0;
  ch.add_line(-2 * h.at(0), dp.at(0) + h.at(0) * h.at(0));

  FOR(i, 1, N)
  {
    dp.at(i) = ch.get_min(h.at(i)) + h.at(i) * h.at(i) + C;
    ch.add_line(-2 * h.at(i), dp.at(i) + h.at(i) * h.at(i));
  }
  pr(dp.at(N - 1));
}
