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

struct Solver
{
  int N; // 2 <= N <= 100
  int M; // 1 <= M <+ N (N + 1) / 2
  vector<vector<ll>> paths;
  vector<bool> checker;

  void input()
  {
    init();
    init_paths();
    init_checker();
  }
  void init()
  {
    cin >> N >> M;
  }
  void init_paths()
  {
    paths = vector<vector<ll>>(N, vector<ll>());
    REP(i, M)
    {
      ll u, v;
      cin >> u >> v;
      paths.at(u - 1).push_back(v - 1);
      paths.at(v - 1).push_back(u - 1);
    }
  }
  void init_checker()
  {
    checker = vector<bool>(N, false);
  }

  bool dfs(int x, int from)
  {
    if (checker.at(x))
    {
      return false;
    }
    checker.at(x) = true;
    FORA(i, paths.at(x))
    {
      if (i == from)
      {
        continue;
      }
      if (!dfs(i, x))
      {
        return false;
      }
    }
    return true;
  }

  ll solve()
  {
    ll res = 0;
    REP(i, N)
    {
      if (checker.at(i))
      {
        continue;
      }
      if (!dfs(i, -1))
      {
        continue;
      }
      ++res;
    }
    return res;
  }

  void output(ll res)
  {
    cout << res << endl;
  }
};

int main()
{
  //入力の高速化用のコード
  //ios::sync_with_stdio(false);
  //cin.tie(nullptr);
  Solver s;
  s.input();
  ll res = s.solve();
  s.output(res);
}
