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
  ll X, Y, N;
  Constants()
  {
    cin >> X >> Y;
    cin >> N;
  }
} C;

struct Args
{
  vector<P> t;
  Args() : t(C.N)
  {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    REP(i, C.N)
    {
      cin >> t.at(i).first >> t.at(i).second;
    }
    //sort(ALL(t));
  }
} args;

struct Solver
{
  ll ans;
  arr<ll> dp;
  Solver() : ans(0), dp(C.X + 1, vll(C.X + C.Y + 1, 0))
  {
  }
  //
  void solve()
  {
    REP(i, C.N)
    {
      auto &t = args.t.at(i);
      REPD(j, C.X + 1)
      {
        REPD(k, C.X + C.Y + 1)
        {
          chmax(dp.at(j).at(k), dp.at(j).at(k));
          if (j + 1 <= C.X && k + t.first <= C.X + C.Y)
          {
            chmax(dp.at(j + 1).at(k + t.first), dp.at(j).at(k) + t.second);
          }
          /*
          FOR(l, 1, t.first + 1)
          {
            if (C.X < j + l)
            {
              continue;
            }
            if (C.Y < k + t.first - l)
            {
              continue;
            }
            chmax(dp.at(i + 1).at(j + l).at(k + t.first - l), dp.at(i).at(j).at(k) + t.second);
          }
          */
        }
      }
    }
    REP(i, C.X + 1)
    {
      REP(j, C.X + C.Y + 1)
      {
        chmax(ans, dp.at(i).at(j));
      }
    }
  }
  //
  void output()
  {
    pr(ans);
  }
} s;

int main()
{
  s.solve();
  s.output();
  return 0;
}
