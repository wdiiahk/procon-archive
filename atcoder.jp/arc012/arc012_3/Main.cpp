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
  ll N;
  Constants()
  {
    N = 19;
  }
} C;

struct Args
{
  arr<ll> grid;
  ll n_black, n_white;
  Args() : grid(C.N, vll(C.N, -1)), n_black(0), n_white(0)
  {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    REP(i, C.N)
    {
      string line;
      cin >> line;
      REP(j, C.N)
      {
        if (line.at(j) == 'o')
        {
          grid.at(i).at(j) = 0;
          n_black++;
        }
        else if (line.at(j) == 'x')
        {
          grid.at(i).at(j) = 1;
          n_white++;
        }
      }
    }
  }
} args;

struct Solver
{
  bool ans;
  vector<P> dps;

  Solver() : ans(false)
  {
    dps = {
        {0, 1},
        {1, 1},
        {1, 0},
        {1, -1}};
  }
  //
  bool
  is_win(P p, ll c)
  {
    if (args.grid.at(p.first).at(p.second) != c)
    {
      return false;
    }
    FORA(dp, dps)
    {
      ll ni = p.first;
      ll nj = p.second;
      bool flag(true);
      REP(i, 4)
      {
        ni += dp.first;
        nj += dp.second;
        if (ni < 0 || C.N <= ni)
        {
          flag = false;
          break;
        }
        if (nj < 0 || C.N <= nj)
        {
          flag = false;
          break;
        }
        if (args.grid.at(ni).at(nj) != c)
        {
          flag = false;
          break;
        }
      }
      if (flag)
      {
        return true;
      }
    }
    return false;
  }

  //
  void solve()
  {
    if (args.n_black < args.n_white)
    {
      ans = false;
      return;
    }
    if (1 < args.n_black - args.n_white)
    {
      ans = false;
      return;
    }

    //
    vbool win(2, false);
    REP(c, 2)
    {
      REP(i, C.N)
      {
        REP(j, C.N)
        {
          if (is_win({i, j}, c))
          {
            win.at(c) = true;
          }
        }
      }
    }
    //
    if (!win.at(0) && !win.at(1))
    {
      ans = true;
      return;
    }
    if (win.at(0) && win.at(1))
    {
      ans = false;
      return;
    }

    //
    if (win.at(0) && args.n_black != args.n_white + 1)
    {
      ans = false;
      return;
    }
    if (win.at(1) && args.n_black != args.n_white)
    {
      ans = false;
      return;
    }
    //
    REP(c, 2)
    {
      if (!win.at(c))
      {
        continue;
      }
      REP(i, C.N)
      {
        REP(j, C.N)
        {
          if (args.grid.at(i).at(j) != c)
          {
            continue;
          }
          args.grid.at(i).at(j) = -1;
          //
          bool flag(true);
          REP(k, C.N)
          {
            REP(l, C.N)
            {
              if (is_win({k, l}, c))
              {
                flag = false;
                break;
              }
            }
            if (!flag)
            {
              break;
            }
          }
          if (flag)
          {
            ans = true;
            return;
          }
          //
          args.grid.at(i).at(j) = c;
        }
      }
    }
  }
  //
  void output()
  {
    pr(ans ? "YES" : "NO");
  }
} s;

int main()
{
  s.solve();
  s.output();
  return 0;
}
