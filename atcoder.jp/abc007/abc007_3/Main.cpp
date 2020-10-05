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
  int R; // i <= R <= 50
  int C; // 1 <= C <= 50
  pair<ll, ll> s;
  pair<ll, ll> g;
  vector<string> lines;
  vector<vector<ll>> dist;
  vector<ll> dx;
  vector<ll> dy;

  Solver() : dx({-1, 0, 1, 0}), dy({0, -1, 0, 1}) {}
  void input()
  {
    init_RC();
    init_start();
    init_goal();
    init_lines();
    init_dist();
  }

  void init_RC()
  {
    cin >> R >> C;
  }
  void init_start()
  {
    ll x, y;
    cin >> y >> x;
    s = make_pair(y - 1, x - 1);
  }
  void init_goal()
  {
    ll x, y;
    cin >> y >> x;
    g = make_pair(y - 1, x - 1);
  }
  void init_lines()
  {
    REP(i, R)
    {
      string line;
      cin >> line;
      lines.push_back(line);
    }
  }
  void init_dist()
  {
    dist = vector<vector<ll>>(R, vector<ll>(C, INF));
  }
  //
  ll bfs()
  {
    ll sy, sx;
    tie(sy, sx) = s;
    dist.at(sy).at(sx) = 0;
    ll gy, gx;
    tie(gy, gx) = g;
    queue<pair<ll, ll>> q;
    q.push(s);
    while (!q.empty())
    {
      ll y, x;
      tie(y, x) = q.front();
      ll d = dist.at(y).at(x);
      if (y == gy & x == gx)
      {
        return d;
      }
      REP(i, 4)
      {
        ll ny = y + dy.at(i);
        ll nx = x + dx.at(i);
        if (ny < 0 || R <= ny)
        {
          continue;
        }
        if (nx < 0 || C <= nx)
        {
          continue;
        }
        if (lines.at(ny).at(nx) == '#')
        {
          continue;
        }
        if (dist.at(ny).at(nx) < INF)
        {
          continue;
        }
        //
        dist.at(ny).at(nx) = d + 1;
        q.push(make_pair(ny, nx));
      }
      q.pop();
    }
    return INF;
  }
  //
  ll solve()
  {
    return bfs();
  }
  void output(ll res)
  {
    cout << res << endl;
  }
};

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  Solver s;
  s.input();
  ll res = s.solve();
  s.output(res);
}
