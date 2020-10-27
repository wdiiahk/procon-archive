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
 * N 頂点の木が与えられます。
 * 木とはグラフの一種であり、頂点の数を N とすると、辺の数が N−1 本である閉路のない連結グラフです。
 * i(1≦i≦N−1) 番目の辺は 頂点 ai と 頂点 bi を距離 ci で結びます。
 * 
 * また、Q 個の質問クエリと整数 K が与えられます。
 * j(1≦j≦Q) 番目の質問クエリでは、頂点 xj から 頂点 K を経由しつつ、頂点 yj まで移動する場合の最短経路の距離を求めてください。
 */
struct Edge
{
  ll to;
  ll cost;
};

struct Args
{
  ll N;
  arr<Edge> edges;
  ll Q, K;
  vll x, y;
  Args()
  {
    cin >> N;
    edges.resize(N);
    REP(i, N - 1)
    {
      ll a, b, c;
      cin >> a >> b >> c;
      edges.at(a - 1).push_back({b - 1, c});
      edges.at(b - 1).push_back({a - 1, c});
    }
    cin >> Q >> K;
    x.resize(Q);
    y.resize(Q);
    REP(i, Q)
    {
      cin >> x.at(i) >> y.at(i);
    }
  }
};

class Solver
{
private:
  /* data */
  Args &args;
  vll ans;
  vll dp;
  vll pred;

public:
  Solver(Args &args) : args(args), ans()
  {
    dp.resize(args.N + 1, -1);
    pred.resize(args.N, -1);
  }
  //
  void dfs(ll v, ll p = -1, ll d = 0)
  {
    dp.at(v) = d;
    FORA(c, args.edges.at(v))
    {
      if (c.to == p)
      {
        continue;
      }
      dfs(c.to, v, d + c.cost);
    }
  }

  void bfs(ll root)
  {
    queue<ll> q;
    q.push(root);
    dp.at(root) = 0;
    while (!q.empty())
    {
      ll v = q.front();
      q.pop();
      ll d = dp.at(v);
      ll p = pred.at(v);
      FORA(c, args.edges.at(v))
      {
        if (c.to == p)
        {
          continue;
        }
        pred.at(c.to) = v;
        dp.at(c.to) = d + c.cost;
        q.push(c.to);
      }
    }
  }

  void solve()
  {
    // dfs(args.K - 1);
    bfs(args.K - 1);
    REP(i, args.Q)
    {
      ll x = args.x.at(i);
      ll y = args.y.at(i);
      ans.push_back(dp.at(x - 1) + dp.at(y - 1));
    }
  }
  void output()
  {
    FORA(a, ans)
    {
      pr(a);
    }
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
