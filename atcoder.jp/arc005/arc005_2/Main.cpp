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
using vchar = vector<char>;
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
  ll x, y;
  string W;
  Constants()
  {
    cin >> x >> y;
    x--;
    y--;
    cin >> W;
  }
} C;

struct Args
{
  arr<char> c;
  Args() : c(9, vchar(9))
  {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    REP(i, 9)
    {
      string line;
      cin >> line;
      REP(j, 9)
      {
        c.at(i).at(j) = line.at(j);
      }
    }
  }
} args;

struct Solver
{
  vector<char> ans;
  ll lr, ud;
  Solver() : ans(), lr(0), ud(0)
  {
    FORA(c, C.W)
    {
      if (c == 'L')
      {
        lr = -1;
      }
      else if (c == 'R')
      {
        lr = 1;
      }
      else if (c == 'U')
      {
        ud = -1;
      }
      else if (c == 'D')
      {
        ud = 1;
      }
    }
  }
  //
  void solve()
  {
    P p({C.y, C.x});
    char c = args.c.at(p.first).at(p.second);
    ans.push_back(c);
    REP(n, 3)
    {
      p.first += ud;
      p.second += lr;
      if (p.first == -1 || p.first == 9)
      {
        ud = -ud;
        p.first += 2 * ud;
      }
      if (p.second == -1 || p.second == 9)
      {
        lr = -lr;
        p.second += 2. * lr;
      }
      c = args.c.at(p.first).at(p.second);
      ans.push_back(c);
    }
  }
  //
  void output()
  {
    string a(ALL(ans));
    pr(a);
  }
} s;

int main()
{
  s.solve();
  s.output();
  return 0;
}
