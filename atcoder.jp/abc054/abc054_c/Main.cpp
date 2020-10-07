//デバッグ用オプション：-fsanitize=undefined,address

//コンパイラ最適化
#pragma GCC optimize("Ofast")

//インクルードなど
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

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

struct Args
{
  ll N; // node_num: 2<= N <= 8
  ll M; // edge_num: 0 <= M <= N (N + 1) /2
  vector<pair<ll, ll>> ab;
  //
  Args()
  {
    cin >> N >> M;
    REP(i, M)
    {
      ll a, b;
      cin >> a >> b;
      --a;
      --b;
      ab.push_back({a, b});
    }
  }
};

struct Edge
{
  ll to;
  ll cost;
};

class Solver
{
private:
  ll N;
  unordered_map<ll, vector<Edge>> adj_list;
  ll start_point;
  vector<ll> pred;
  vector<ll> costs;
  //
  ll dfs(ll pos, ll x);

public:
  Solver(const Args &args);
  ~Solver();
  ll solve();
  void output(ll res);
};

Solver::Solver(const Args &args)
    : N(args.N), start_point(0), pred(args.N), costs(args.N, INF)
{
  FORA(el, args.ab)
  {
    if (adj_list.count(el.first) == 0)
    {
      adj_list[el.first] = vector<Edge>();
    }
    adj_list.at(el.first).push_back({el.second, 1});
    if (adj_list.count(el.second) == 0)
    {
      adj_list[el.second] = vector<Edge>();
    }
    adj_list.at(el.second).push_back({el.first, 1});
  }
}

Solver::~Solver()
{
}

ll Solver::dfs(ll pos, ll x)
{
  if (x == N)
  {
    return 1;
  }
  ll res(0);
  ll cost = costs.at(pos);
  FORA(e, adj_list.at(pos))
  {
    if (!chmin(costs.at(e.to), cost + e.cost))
    {
      continue;
    }
    res += dfs(e.to, x + 1);
    costs.at(e.to) = INF;
  }
  return res;
}

ll Solver::solve()
{
  costs.at(start_point) = 0;
  return dfs(start_point, 1);
}

void Solver::output(ll res)
{
  cout << res << endl;
}

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  Args args;
  Solver s(args);
  ll res = s.solve();
  s.output(res);
}
