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
 * N 頂点 M 辺の単純無向グラフが与えられます。 i 番目の辺は頂点 ci と頂点 di を結んでいます。
 * 
 * はじめ、頂点 i には値 ai が書かれています。あなたは次の操作を 0 回以上行うことで、
 * 操作後の各頂点の値をそれぞれ b1,⋯,bN にしたいと思っています。
 * 
 * 辺を 1 つ選ぶ。選んだ辺が頂点 x と頂点 y を結んでいるとしたとき、次のいずれかを選んで行う。
 * - 値 ax を −1 し、値 ay を +1 する 
 * - 値 ax を +1 し、値 ay を −1 する
 * 
 * 適切に操作を行うことで目的を達成することが可能かどうかを判定してください。
 */
struct Args
{
  ll N, M;
  vll a, b;
  arr<ll> c;
  Args()
  {
    cin >> N >> M;
    a.resize(N);
    REP(i, N)
    {
      cin >> a.at(i);
    }
    b.resize(N);
    REP(i, N)
    {
      cin >> b.at(i);
    }
    c.resize(N);
    REP(i, M)
    {
      ll a, b;
      cin >> a >> b;
      c.at(a - 1).push_back(b - 1);
      c.at(b - 1).push_back(a - 1);
    }
  }
};

class Solver
{
private:
  /* data */
  Args &args;
  bool ans;
  vbool flag;
  vll dp;

public:
  Solver(Args &args) : args(args), ans(false)
  {
    dp.resize(args.N, 0);
    REP(i, args.N)
    {
      dp.at(i) = args.b.at(i) - args.a.at(i);
    }
    flag = vbool(args.N, false);
  }

  void dfs(ll i, ll parent)
  {
    if (flag.at(i))
    {
      return;
    }
    flag.at(i) = true;
    FORA(x, args.c.at(i))
    {
      if (x == parent)
      {
        continue;
      }
      dfs(x, i);
    }
    if (0 <= parent)
    {
      dp.at(parent) += dp.at(i);
      dp.at(i) = 0;
    }
  }
  bool get_ans()
  {
    FORA(x, dp)
    {
      if (x != 0)
      {
        return false;
      }
    }
    return true;
  }

  void solve()
  {
    REP(i, args.N)
    {
      if (!flag.at(i))
      {
        dfs(i, -1);
      }
    }
    ans = get_ans();
  }
  void output()
  {
    pr((ans) ? "Yes" : "No");
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
