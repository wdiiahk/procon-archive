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

struct Args
{
  ll W;    // 1 <= W <= 10000
  ll N, K; // 1 <= N <= 50, 1 <= K <= N
  vector<ll> a;
  vector<ll> b;
  Args()
  {
    cin >> W;
    cin >> N >> K;
    a = vector<ll>(N);
    b = vector<ll>(N);
    REP(i, N)
    {
      cin >> a.at(i) >> b.at(i);
    }
  }
};

class Solver
{
private:
  /* data */
  Args &args;
  ll ans;
  vector<vector<unordered_map<ll, ll>>> dp;

public:
  Solver(Args &args_) : args(args_), ans(0), dp(args.N + 1, vector<unordered_map<ll, ll>>(args.K + 1))
  {
  }

  ll dfs(ll i, ll j, ll k)
  {
    auto &memo = dp.at(i).at(j);
    if (memo.count(k))
    {
      return memo.at(k);
    }
    int res(0.);
    if (i == args.N)
    {
      memo[k] = res;
      return res;
    }
    //
    ll w = args.a.at(i);
    if (j == 0 || k < w)
    {
      res = dfs(i + 1, j, k);
      memo[k] = res;
      return res;
    }
    //
    res = max(dfs(i + 1, j, k), dfs(i + 1, j - 1, k - w) + args.b.at(i));
    memo[k] = res;
    return res;
  }

  void solve()
  {
    ans = dfs(0, args.K, args.W);
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
