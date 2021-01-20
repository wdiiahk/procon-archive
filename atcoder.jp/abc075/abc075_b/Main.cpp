//デバッグ用オプション：-fsanitize=undefined,address

//コンパイラ最適化
#pragma GCC optimize("Ofast")

//インクルードなど
#include <bits/stdc++.h>
//#include <atcoder/all>

using namespace std;
//using namespace atcoder;

typedef long long ll;
using vint = vector<int>;
using vll = vector<ll>;
using vbool = vector<bool>;
using vs = vector<string>;
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
  ll H, W;
  Constants()
  {
    cin >> H >> W;
  }
} C;

struct Args
{
  vs a;
  Args() : a(C.H)
  {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    REP(i, C.H)
    {
      cin >> a.at(i);
    }
  }
} args;

struct Solver
{
  vs ans;
  Solver() : ans(C.H)
  {
    REP(i, C.H)
    {
      ans.at(i) = regex_replace(args.a.at(i), regex("[^#]"), "0");
    }
  }
  //
  void solve()
  {
    vector<P> dv = {
        {-1, -1},
        {-1, 0},
        {-1, 1},
        {0, -1},
        {0, 1},
        {1, -1},
        {1, 0},
        {1, 1},
    };
    REP(i, C.H)
    {
      REP(j, C.W)
      {
        if (ans.at(i).at(j) != '#')
        {
          continue;
        }
        FORA(v, dv)
        {
          ll ni = i + v.first;
          ll nj = j + v.second;
          if (ni < 0 || C.H <= ni)
          {
            continue;
          }
          if (nj < 0 || C.W <= nj)
          {
            continue;
          }
          if (ans.at(ni).at(nj) == '#')
          {
            continue;
          }
          char c = ans.at(ni).at(nj) + 1;
          ans.at(ni).at(nj) = c;
        }
      }
    }
  }
  //
  void output()
  {
    FORA(a, ans)
    pr(a);
  }
} s;

int main()
{
  s.solve();
  s.output();
  return 0;
}
