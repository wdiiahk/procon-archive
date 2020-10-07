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

class Solver
{
private:
  /* data */
  ll H;
  ll W;
  vector<string> lines;
  pair<ll, ll> s;
  pair<ll, ll> g;
  vector<vector<ll>> dist;
  vector<vector<pair<ll, ll>>> pred;
  vector<ll> dx, dy;
  //
  void init_HW();
  void init_lines();
  void init_dist();
  ll bfs01();

public:
  Solver(/* args */);
  ~Solver();
  void input();
  bool solve();
  void output(bool res);
};

Solver::Solver(/* args */) : dx({-1, 1, 0, 0}), dy({0, 0, -1, 1})
{
}

Solver::~Solver()
{
}

void Solver::input()
{
  init_HW();
  init_lines();
  init_dist();
}
bool Solver::solve()
{
  ll res = bfs01();
  return (res <= 2);
}

void Solver::output(bool res)
{
  cout << ((res) ? "YES" : "NO") << endl;
}

ll Solver::bfs01()
{
  deque<pair<ll, ll>> q;
  q.push_front(s);
  ll sy, sx;
  tie(sy, sx) = s;
  dist.at(sy).at(sx) = 0;
  ll gy, gx;
  tie(gy, gx) = g;

  while (!q.empty())
  {
    pair<ll, ll> cur = q.front();
    q.pop_front();
    ll y, x;
    tie(y, x) = cur;
    ll d = dist.at(y).at(x);
    if (y == gy && x == gx)
    {
      return d;
    }
    REP(i, 4)
    {
      ll ny = y + dy.at(i);
      ll nx = x + dx.at(i);
      if (ny < 0 || H <= ny || nx < 0 || W <= nx)
      {
        continue;
      }
      bool wall = (lines.at(ny).at(nx) == '#');
      ll tmp = d + ((wall) ? 1 : 0);
      if (2 < tmp)
      {
        continue;
      }
      if (!chmin(dist.at(ny).at(nx), tmp))
      {
        continue;
      }
      pred.at(ny).at(nx) = cur;
      if (wall)
      {
        q.push_back(make_pair(ny, nx));
      }
      else
      {
        q.push_front(make_pair(ny, nx));
      }
    }
  }
  return INF;
}

void Solver::init_HW()
{
  cin >> H >> W;
}
void Solver::init_lines()
{
  REP(i, H)
  {
    string line;
    cin >> line;
    lines.push_back(line);
    size_t sj = line.find('s');
    if (sj != string::npos)
    {
      s = make_pair(i, sj);
    }
    size_t gj = line.find('g');
    if (gj != string::npos)
    {
      g = make_pair(i, gj);
    }
  }
}
//
void Solver::init_dist()
{
  dist = vector<vector<ll>>(H, vector<ll>(W, INF));
  pred = vector<vector<pair<ll, ll>>>(H, vector<pair<ll, ll>>(W));
}

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  Solver s;
  s.input();
  bool res = s.solve();
  s.output(res);
}
