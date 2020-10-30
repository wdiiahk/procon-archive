//デバッグ用オプション：-fsanitize=undefined,address

//コンパイラ最適化
// #pragma GCC optimize("Ofast")

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
 * 高橋くんの住む国には N 個の街があります。
 * それぞれ 1 から N の整数で番号付けされています。 しかし、これらの街の間を移動する手段がまだありません。 
 * そこで国が補助金を出して、異なる 2 つの街を結ぶ道路を、いくつか敷設することになりました。
 * 各道路は個別の長さを持っています。 
 * 敷設される道路は結んだ 2つの国のどちらからでも、もう一方の国に移動することが出来ます。
 * つまり双方向に移動できる道路です。ところで、高橋くんは偶数が大好きです。 
 * 高橋くんは道路を使って、たとえそれが遠回りになろうとも、同じ道を何度通ろうとも、
 * 移動距離の合計が偶数メートルになるように移動しようとします。 
 * また、高橋くんは中途半端なことが嫌いなので、道の途中で来た道を引き返すことはしません。
 * 高橋君はときどき、2 つの街を指定して、その間を偶数メートルで移動できるかどうかあなたに質問します。 
 * 先述の通り、今は道路を増やしている最中なので、質問のタイミングによっては新しく敷設された道路の影響で、
 * 偶数メートルで移動できるかどうかが変わり得るに注意してください。
 * なお、街の中での移動は移動距離の合計に含まないものとします。
 * 
 * 道路の敷設と、高橋くんの質問の情報を時系列順に与えるので、高橋くんの質問に答えるプログラムを作成してください。
 */
struct UnionFind
{
  vll par, siz;
  UnionFind() {}
  void init(ll n)
  {
    par.resize(n, -1);
    siz.resize(n, 1);
  }

  ll root(ll x)
  {
    if (par.at(x) < 0)
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
    siz.at(rx) += siz.at(ry);
    par.at(ry) = rx;
    return true;
  }

  ll size(ll x)
  {
    return siz.at(root(x));
  }
};

struct Args
{
  ll N, Q;
  vll w, x, y, z;
  Args()
  {
    cin >> N >> Q;
    w.resize(Q);
    x.resize(Q);
    y.resize(Q);
    z.resize(Q);
    REP(i, Q)
    {
      ll tmpx, tmpy, tmpz;
      cin >> w.at(i) >> tmpx >> tmpy >> tmpz;
      x.at(i) = tmpx - 1;
      y.at(i) = tmpy - 1;
      z.at(i) = tmpz % 2;
    }
  }
};

class Solver
{
private:
  /* data */
  Args &args;
  vbool ans;
  UnionFind uf;

public:
  Solver(Args &args) : args(args), ans()
  {
    uf.init(2 * args.N);
  }
  void unite(ll x, ll y, ll z)
  {
    if (z == 0)
    {
      uf.unite(x, y);
      uf.unite(x + args.N, y + args.N);
    }
    else
    {
      uf.unite(x, y + args.N);
      uf.unite(y, x + args.N);
    }
  }

  bool get_ans(ll x, ll y)
  {
    return uf.issame(x, y);
  }

  void solve()
  {
    REP(i, args.Q)
    {
      if (args.w.at(i) == 1)
      {
        unite(args.x.at(i), args.y.at(i), args.z.at(i));
      }
      else if (args.w.at(i) == 2)
      {
        bool res = get_ans(args.x.at(i), args.y.at(i));
        ans.push_back(res);
      }
    }
  }
  void output()
  {
    FORA(a, ans)
    {
      pr((a) ? "YES" : "NO");
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
