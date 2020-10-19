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
 * このプログラムの出力する答えは 1≦a1≦a2≦…≦ak≦n であるような
 * 整数の組 (a1,a2,…,ak) の個数に等しいということに気づきました。 
 */

struct Args
{
  /**
   * 1 行目には、整数 n(1≦n≦10^5)が与えられる。
   * 2行目には、整数 k(1≦k≦10^5) が与えられる。
   */
  ll n, k;
  Args()
  {
    cin >> n >> k;
  }
};

class Solver
{
private:
  /* data */
  Args &args;
  ll ans;
  vll fact, finv, inv;

public:
  Solver(Args &args) : args(args), ans(0)
  {
    COMinit(1000000);
  }

  void COMinit(ll N)
  {
    fact.resize(N);
    finv.resize(N);
    inv.resize(N);
    fact[0] = fact[1] = 1;
    finv[0] = finv[1] = 1;
    inv[1] = 1;
    for (int i = 2; i < N; i++)
    {
      fact[i] = fact[i - 1] * i % MOD;
      inv[i] = MOD - inv[MOD % i] * (MOD / i) % MOD;
      finv[i] = finv[i - 1] * inv[i] % MOD;
    }
  }

  ll COM(ll n, ll k)
  {
    if (n < k)
    {
      return 0;
    }
    if (n < 0 || k < 0)
    {
      return 0;
    }
    return fact[n] * (finv[k] * finv[n - k] % MOD) % MOD;
  }

  vector<P> prime_factorize(ll n)
  {
    vector<P> res;
    for (ll a = 2; a * a <= n; ++a)
    {
      if (n % a != 0)
      {
        continue;
      }
      ll ex = 0;
      while (n % a == 0)
      {
        ++ex;
        n /= a;
      }
      res.push_back({a, ex});
    }
    //
    if (n != 1)
    {
      res.push_back({n, 1});
    }
    return res;
  }

  ll H(ll n, ll k)
  {
    return COM(n - 1 + k, n - 1);
  }

  void solve()
  {
    ans = H(args.n, args.k);
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
