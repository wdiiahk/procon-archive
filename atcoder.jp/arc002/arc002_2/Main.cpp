//デバッグ用オプション：-fsanitize=undefined,address

//コンパイラ最適化
#pragma GCC optimize("Ofast")

//インクルードなど
#include <bits/stdc++.h>
#include <atcoder/all>

using namespace std;
using namespace atcoder;

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

struct Constants
{
  ll Y, M, D;
  Constants()
  {
    string s;
    cin >> s;
    //
    Y = s.at(0) - '0';
    FOR(i, 1, 4)
    {
      Y *= 10;
      Y += (s.at(i) - '0');
    }
    //
    M = (s.at(5) - '0') * 10 + (s.at(6) - '0');
    D = (s.at(8) - '0') * 10 + (s.at(9) - '0');
  }
} C;

struct Args
{
  Args()
  {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
  }
} args;

struct Solver
{
  vll ans;
  vll days;
  Solver() : ans(3, 0), days(13, 0)
  {
  }
  //
  bool uruu(ll y)
  {
    if ((y % 400) == 0)
    {
      return true;
    }
    if ((y % 100) == 0)
    {
      return false;
    }
    if ((y % 4) == 0)
    {
      return true;
    }
    return false;
  }

  //
  void solve()
  {
    FOR(n, 1, 12 + 1)
    {
      if (n == 2)
      {
        days.at(n) = (uruu(C.Y)) ? 29 : 28;
      }
      else if (n == 4 || n == 6 || n == 9 || n == 11)
      {
        days.at(n) = 30;
      }
      else
      {
        days.at(n) = 31;
      }
    }
    //
    ll y = C.Y;
    ll m = C.M;
    ll d = C.D;
    while (y == C.Y)
    {
      if (y % (m * d) == 0)
      {
        break;
      }
      d++;
      if (d != days.at(m) + 1)
      {
        continue;
      }
      d = 1;
      m++;
      if (m != 13)
      {
        continue;
      }
      m = 1;
      y++;
    }

    /*
    */
    ans.at(0) = y;
    ans.at(1) = m;
    ans.at(2) = d;
  }
  //
  void output()
  {
    cout << ans.at(0) << "/";
    if (ans.at(1) < 10)
    {
      cout << "0";
    }
    cout << ans.at(1) << "/";
    if (ans.at(2) < 10)
    {
      cout << "0";
    }
    cout << ans.at(2) << endl;
  }
} s;

int main()
{
  s.solve();
  s.output();
  return 0;
}
