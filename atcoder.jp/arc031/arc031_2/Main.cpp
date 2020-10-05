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
  ll W, H;
  vector<string> lines;
  vector<vector<bool>> checker;
  pair<ll, ll> s;
  ll N;
  vector<ll> dx, dy;

  Solver() : W(10), H(10), N(0), dx({-1, 0, 1, 0}), dy({0, -1, 0, 1})
  {
  }
  void input()
  {
    init_lines();
    init_checker();
    init_start();
  }
  void init_lines()
  {
    REP(i, H)
    {
      string line;
      cin >> line;
      lines.push_back(line);
      FORA(c, line)
      {
        if (c == 'o')
          ++N;
      }
    }
    //
  }
  void init_checker()
  {
    checker = vector<vector<bool>>(H, vector<bool>(W, false));
  }

  void init_start()
  {
    REP(i, H)
    {
      REP(j, W)
      {
        if (lines.at(i).at(j) == 'o')
        {
          s = make_pair(i, j);
          return;
        }
      }
    }
  }
  //
  ll dfs(ll i, ll j)
  {
    if (checker.at(i).at(j))
    {
      return 0;
    }
    checker.at(i).at(j) = true;

    ll ret = 0;
    REP(idx, 4)
    {
      ll y = i + dy.at(idx);
      ll x = j + dx.at(idx);
      if (x < 0 || W <= x || y < 0 || H <= y)
      {
        continue;
      }
      if (lines.at(y).at(x) != 'o')
      {
        continue;
      }
      ret += dfs(y, x);
    }
    ret += 1;
    return ret;
  }

  bool solve()
  {
    REP(y, H)
    {
      REP(x, W)
      {
        if (lines.at(y).at(x) == 'o')
        {
          continue;
        }
        lines.at(y).at(x) = 'o';
        init_checker();
        if (N < dfs(s.first, s.second))
        {
          return true;
        }
        lines.at(y).at(x) = 'x';
      }
    }
    return false;
  }
  void output(bool res)
  {
    cout << ((res) ? "YES" : "NO") << endl;
  }
};

int main()
{
  //入力の高速化用のコード
  //ios::sync_with_stdio(false);
  //cin.tie(nullptr);
  Solver s;
  s.input();
  bool res = s.solve();
  s.output(res);
}
