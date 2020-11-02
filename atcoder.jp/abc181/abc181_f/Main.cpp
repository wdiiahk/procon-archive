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
 * xy 平面上に 2 直線 y=−100, y=100 で囲まれた通路があります。
 * この通路の中の −100<x<100 の部分に N 本の大きさの無視できる釘が打たれており、 i 本目の釘の座標は (xi,yi)です。
 * 高橋くんは実数 r (0<r≤100) を 1 つ選び、半径 r の円を中心が (−109,0) に位置するように置きます。 
 * その後、円を (−10^9,0) から (10^9,0) まで移動させます。
 * このとき、円は通路の境界や釘が円の内部に入らないような範囲で連続的に動かすことができるものとします。
 * 円を (109,0)まで動かせるような最大の r を求めてください。
 */
struct Args
{
  ll N;
  vll x, y;
  Args()
  {
    cin >> N;
    x.resize(N);
    y.resize(N);
    REP(i, N)
    {
      cin >> x.at(i) >> y.at(i);
    }
  }
};

struct UnionFind
{
  vll par, siz;
  UnionFind() {}
  void init(ll n)
  {
    par.resize(n, -1);
    siz.resize(n, 0);
  }
  ll root(ll x)
  {
    if (par.at(x) < 0)
    {
      return x;
    }
    par.at(x) = root(par.at(x));
    return par.at(x);
  }
  bool same(ll x, ll y)
  {
    return root(x) == root(y);
  }
  bool unite(ll x, ll y)
  {
    ll rx = root(x);
    ll ry = root(y);
    if (rx == ry)
    {
      return false;
    }
    if (siz.at(rx) < siz.at(ry))
    {
      swap(rx, ry);
    }
    par.at(ry) = rx;
    siz.at(rx) += siz.at(ry);
    return true;
  }
};

using Edge = tuple<ll, ll, ll>;

class Solver
{
private:
  /* data */
  Args &args;
  double ans;
  vector<Edge> edges;
  ll S;
  ll T;

public:
  Solver(Args &args) : args(args), ans(0)
  {
    S = args.N;
    T = args.N + 1;
    REP(i, args.N)
    {
      ll x0 = args.x.at(i);
      ll y0 = args.y.at(i);
      ll dS = dist2(x0, y0, x0, 100);
      edges.push_back({dS, i, S});
      ll dT = dist2(x0, y0, x0, -100);
      edges.push_back({dT, i, T});
      FOR(j, i + 1, args.N)
      {
        ll x1 = args.x.at(j);
        ll y1 = args.y.at(j);
        ll d = dist2(x0, y0, x1, y1);
        edges.push_back({d, i, j});
      }
    }
    sort(ALL(edges));
  }

  ll dist2(ll x0, ll y0, ll x1, ll y1)
  {
    return pow(x0 - x1, 2) + pow(y0 - y1, 2);
  }

  double get_ans()
  {
    UnionFind uf;
    uf.init(args.N + 2);
    ll res(INF);
    FORA(e, edges)
    {
      ll d, i, j;
      tie(d, i, j) = e;
      uf.unite(i, j);
      if (uf.same(S, T))
      {
        return sqrt(d) / 2;
      }
    }
    return 0;
  }

  void solve()
  {
    ans = get_ans();
  }
  void output()
  {
    cout << fixed << setprecision(15) << ans << endl;
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
