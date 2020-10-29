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
 * 1 から N までの整数を並び替えた順列 p1, p2, .., pN があります。 
 * また、 1 以上 N 以下の整数のペアが M 個与えられます。 
 * これらは (x1,y1), (x2,y2), .., (xM,yM) で表されます。 
 * シカの AtCoDeer くんは順列 p に次の操作を好きなだけ行って、 
 * pi=i となる i (1 ≤ i ≤ N) の数を最大にしようと考えています。
 * 
 * 1 ≤ j ≤ M なる j を選び、 pxj と pyj をスワップする
 * 
 * 操作後の pi=i となる i の数として考えうる最大値を求めてください。
 */
struct UnionFind
{
  vll par, siz;
  UnionFind(ll n) : par(n, -1), siz(n, 1) {}

  ll root(ll x)
  {
    if (par.at(x) == -1)
    {
      return x;
    }
    return par.at(x) = root(par.at(x));
  }

  bool issame(ll x, ll y)
  {
    return root(x) == root(y);
  }

  bool unite(ll x, ll y)
  {
    x = root(x);
    y = root(y);
    if (x == y)
    {
      return false;
    }
    if (siz.at(x) < siz.at(y))
    {
      swap(x, y);
    }
    par.at(y) = x;
    siz.at(x) += siz.at(y);
    return true;
  }

  ll size(ll x)
  {
    return siz.at(root(x));
  }
};

struct Args
{
  ll N, M;
  vll p;
  UnionFind u1;
  Args() : u1(0)
  {
    cin >> N >> M;
    p.resize(N);
    REP(i, N)
    {
      cin >> p.at(i);
    }

    u1 = UnionFind(N);
    REP(i, M)
    {
      ll x, y;
      cin >> x >> y;
      u1.unite(x - 1, y - 1);
    }
  }
};

class Solver
{
private:
  /* data */
  Args &args;
  ll ans;

public:
  Solver(Args &args) : args(args), ans(0)
  {
  }
  ll get_ans()
  {
    ll ret(0);
    REP(i, args.N)
    {
      if (args.u1.issame(args.p.at(i) - 1, i))
      {
        ret++;
      }
    }
    return ret;
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
