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
 * りんごさんは N 頂点 の連結な無向グラフを持っています。 
 * このグラフにはすでに M 本の辺があり、i 本目の辺は頂点 Ai と頂点 Bi を繋いでいます。
 * りんごさんは以下の操作を行うことで、辺を追加しようと思っています
 * 
 * 操作：頂点 u から辺をちょうど 3 本辿ることによって頂点 v に辿り着けるような u,v(u≠v) をとり、
 * 頂点 u と頂点 v の間に辺を追加する。
 * ただし、すでに頂点 u と頂点 vの間に辺が存在する場合は辺を追加することはできない。
 * 
 * りんごさんが追加できる辺の本数の最大値を求めて下さい。
 */
struct Args
{
  ll N, M;
  arr<ll> edges;

  Args()
  {
    cin >> N >> M;
    edges.resize(N);
    REP(i, M)
    {
      ll A, B;
      cin >> A >> B;
      edges.at(A - 1).push_back(B - 1);
      edges.at(B - 1).push_back(A - 1);
    }
  }
};

class Solver
{
private:
  /* data */
  Args &args;
  ll ans;
  vll colors;

public:
  Solver(Args &args) : args(args), ans(0)
  {
    colors.assign(args.N, 0);
  }
  bool dfs(ll i, ll c)
  {
    if (0 < colors.at(i))
    {
      return true;
    }
    colors.at(i) = c;
    ll nc = (c == 1) ? 2 : 1;
    FORA(to, args.edges.at(i))
    {
      if (0 < colors.at(to))
      {
        if (colors.at(to) != nc)
        {
          return false;
        }
      }
      if (!dfs(to, nc))
      {
        return false;
      }
    }
    return true;
  }

  ll get_ans()
  {
    if (!dfs(0, 1))
    {
      return args.N * (args.N - 1) / 2 - args.M;
    }
    //
    ll cnt1 = 0;
    ll cnt2 = 0;
    FORA(c, colors)
    {
      if (c == 1)
      {
        ++cnt1;
      }
      else if (c == 2)
      {
        ++cnt2;
      }
    }
    return cnt1 * cnt2 - args.M;
  }

  void solve()
  {
    ans = get_ans();
  }
  void output()
  {
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
