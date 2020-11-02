//デバッグ用オプション：-fsanitize=undefined,address

//コンパイラ最適化
//#pragma GCC optimize("Ofast")

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
 * x 軸上に N 人の人が立っています。 
 * 人 i の位置を xi とします。 
 * 任意の i に対して、xi は 0 以上 109 以下の整数です。 
 * 同じ位置に複数の人が立っていることもありえます。
 * 
 * これらの人の位置に関する情報が M 個与えられます。 
 * このうち i 個めの情報は (Li,Ri,Di) という形をしています。 
 * この情報は、人 Ri は人 Li よりも距離 Di だけ右にいること、 すなわち、xRi−xLi=Diが成り立つことを表します。
 * 
 * これら M 個の情報のうちのいくつかに誤りがある可能性があることがわかりました。 
 * 与えられる M 個すべての情報と矛盾しないような値の組 (x1,x2,...,xN) が存在するか
 * どうか判定してください。
 */
struct Args
{
  ll N, M;
  vll L, R, D;
  Args()
  {
    cin >> N >> M;
    L.resize(M);
    R.resize(M);
    D.resize(M);
    REP(i, M)
    {
      ll tmpl, tmpr;
      cin >> tmpl >> tmpr >> D.at(i);
      L.at(i) = tmpl - 1;
      R.at(i) = tmpr - 1;
    }
  }
};

/**
 * 併合時の工夫: union by size
 * par[x]: x が根のときは x を含むグループのサイズ (の -1 倍)、そうでないときは親ノード
 */
template <class Abel>
struct UnionFind
{
  const Abel UNITY_SUM = 0; // to be set
  vector<int> par;
  vector<Abel> diff_weight;

  UnionFind(int n) : par(n, -1), diff_weight(n, UNITY_SUM) {}

  void init(int n)
  {
    par.assign(n, -1);
    diff_weight.assign(n, UNITY_SUM);
  }

  int root(int x)
  {
    if (par[x] < 0)
    {
      return x;
    }
    int r = root(par[x]);
    diff_weight[x] += diff_weight[par[x]];
    return par[x] = r;
  }

  Abel calc_weight(int x)
  {
    root(x);
    return diff_weight[x];
  }

  bool issame(int x, int y)
  {
    return root(x) == root(y);
  }

  bool merge(int x, int y, Abel w = 0)
  {
    w += calc_weight(x);
    w -= calc_weight(y);
    x = root(x);
    y = root(y);
    if (x == y)
    {
      return false;
    }
    if (par[x] > par[y])
    {
      swap(x, y);
      w = -w;
    }
    par[x] += par[y];
    par[y] = x;
    diff_weight[y] = w;
    return true;
  }

  Abel diff(int x, int y)
  {
    return calc_weight(y) - calc_weight(x);
  }

  int size(int x)
  {
    return -par[root(x)];
  }
};

class Solver
{
private:
  /* data */
  Args &args;
  bool ans;

public:
  Solver(Args &args) : args(args), ans(true)
  {
  }
  void solve()
  {
    UnionFind<ll> uf(args.N);
    REP(i, args.M)
    {
      ll l = args.L.at(i);
      ll r = args.R.at(i);
      ll d = args.D.at(i);
      if (uf.issame(l, r))
      {
        if (uf.diff(l, r) != d)
        {
          ans = false;
          return;
        }
      }
      uf.merge(l, r, d);
    }
  }
  void output()
  {
    pr(ans ? "Yes" : "No");
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
