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

template <typename... Args>
std::string to_str_by(const std::string &fmt, Args... args)
{
  size_t len = std::snprintf(nullptr, 0, fmt.c_str(), args...);
  std::vector<char> buf(len + 1);
  std::snprintf(&buf[0], len + 1, fmt.c_str(), args...);
  return std::string(&buf[0], &buf[0] + len);
}

template <class T>
int popcount(T &a)
{
  int c = 0;
  REP(i, 8 * (int)sizeof(a))
  {
    if ((a >> i) & 1)
      c++;
  }
  return c;
}

template <class T>
void pl(T x) { cout << x << " "; }

template <class T>
void pr(T x) { cout << x << endl; }

template <class T>
void prvec(vector<T> &a)
{
  REP(i, a.size() - 1)
  {
    cout << a[i] << " ";
  }
  pr(a[a.size() - 1]);
}

template <class T>
void prarr(arr<T> &a)
{
  REP(i, a.size())
  if (a[i].empty())
    pr("");
  else
    prvec(a[i]);
}

using P = pair<ll, ll>;
void prp(P &p) { cout << p.first << " " << p.second << endl; }

/**
 * N 個の品物があります。 品物には 1,2,…,N と番号が振られています。 
 * 各 i (1≤i≤N) について、品物 i の重さは wi で、価値は viです。
 * 太郎君は、N 個の品物のうちいくつかを選び、ナップサックに入れて持ち帰ることにしました。 
 * ナップサックの容量は W であり、持ち帰る品物の重さの総和は W 以下でなければなりません。
 * 
 * 太郎君が持ち帰る品物の価値の総和の最大値を求めてください。
 */

struct Args
{
  ll N, W;
  vll w, v;
  Args()
  {
    cin >> N >> W;
    w.resize(N);
    v.resize(N);
    REP(i, N)
    {
      cin >> w.at(i) >> v.at(i);
    }
  }
};

class Solver
{
private:
  /* data */
  Args &args;
  ll ans;
  /**
   * i: pos, j: residual
   */
  arr<ll> dp;

public:
  Solver(Args &args) : args(args), ans(0), dp(args.N + 1, vll(args.W + 1, 0))
  {
  }
  void calc_dp()
  {
    REP(i, args.N)
    {
      ll w = args.w.at(i);
      ll v = args.v.at(i);
      REP(j, args.W + 1)
      {
        dp.at(i + 1).at(j) = dp.at(i).at(j);
        if (0 <= j - w)
        {
          chmax(dp.at(i + 1).at(j), dp.at(i).at(j - w) + v);
        }
      }
    }
  }
  void solve()
  {
    calc_dp();
  }
  void output()
  {
    REP(j, args.W + 1)
    {
      chmax(ans, dp.at(args.N).at(j));
    }
    pr(ans);
  }
};

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  Args args;
  Solver s(args);
  s.solve();
  s.output();
}
