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
 * N 個の都市があり、K 本の道路と L 本の鉄道が都市の間に伸びています。 
 * i 番目の道路は pi 番目と qi 番目の都市を双方向に結び、 
 * i 番目の鉄道は ri 番目と si 番目の都市を双方向に結びます。 
 * 異なる道路が同じ 2 つの都市を結ぶことはありません。
 * 同様に、異なる鉄道が同じ 2 つの都市を結ぶことはありません。
 * 
 * ある都市から別の都市に何本かの道路を通って到達できるとき、それらの都市は道路で連結しているとします。
 * また、すべての都市はそれ自身と道路で連結しているとみなします。
 * 鉄道についても同様に定めます。
 * 
 * 全ての都市について、その都市と道路・鉄道のどちらでも連結している都市の数を求めてください。
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
    ll root_x = root(x);
    ll root_y = root(y);
    if (root_x == root_y)
    {
      return false;
    }
    if (siz.at(x) < siz.at(y))
    {
      swap(root_x, root_y);
    }
    par.at(root_y) = root_x;
    siz.at(root_x) += siz.at(root_y);
    return true;
  }

  ll size(ll x)
  {
    return siz.at(root(x));
  }
};

struct Args
{
  ll N, K, L;
  UnionFind u1, u2;
  Args() : u1(0), u2(0)
  {
    cin >> N >> K >> L;
    u1 = UnionFind(N);
    REP(i, K)
    {
      ll p, q;
      cin >> p >> q;
      u1.unite(p - 1, q - 1);
    }
    u2 = UnionFind(N);
    REP(i, L)
    {
      ll r, s;
      cin >> r >> s;
      u2.unite(r - 1, s - 1);
    }
  }
};

class Solver
{
private:
  /* data */
  Args &args;
  vll ans;
  unordered_map<ll, ll> cnt;

public:
  Solver(Args &args) : args(args), ans(0)
  {
  }
  void calc_cnt()
  {
    REP(i, args.N)
    {
      ll key = args.u1.root(i) * args.N + args.u2.root(i);
      cnt[key]++;
    }
  }
  vll get_ans()
  {
    vll ret(args.N);
    REP(i, args.N)
    {
      ll key = args.u1.root(i) * args.N + args.u2.root(i);
      ret.at(i) = cnt.at(key);
    }
    return ret;
  }
  void solve()
  {
    calc_cnt();
    ans = get_ans();
  }
  void output()
  {
    prvec(ans);
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
