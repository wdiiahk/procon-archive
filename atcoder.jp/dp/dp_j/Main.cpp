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
void prp(const P &p) { cout << p.first << " " << p.second << endl; }

/**
 * N 枚の皿があります。 皿には 1,2,…,N と番号が振られています。 
 * 最初、各 i (1≤i≤N) について、皿 i には ai (1≤ai≤3)個の寿司が置かれています。
 * すべての寿司が無くなるまで、太郎君は次の操作を繰り返し行います。
 * - 1,2,…,Nの目が等確率で出るサイコロを振り、出目を i とする。 
 * - 皿 i に寿司がある場合、皿 i の寿司を 1 個食べる。 
 * - 皿 iに寿司が無い場合、何も行わない。
 * 
 * すべての寿司が無くなるまでの操作回数の期待値を求めてください。
 */
struct Args
{
  ll N;
  vll a;
  Args()
  {
    cin >> N;
    a.resize(N + 1);
    FOR(i, 1, N + 1)
    {
      cin >> a.at(i);
    }
  }
};

class Solver
{
private:
  /* data */
  Args &args;
  double ans;
  /**
   * i: 1個, j 2個, k 3個
   */
  vector<arr<double>> memo;
  ll ones, twos, threes;
  double prob;

public:
  Solver(Args &args) : args(args), ans(0)
  {
    ones = twos = threes = 0;
    FORA(a, args.a)
    {
      switch (a)
      {
      case 1:
        ++ones;
        break;
      case 2:
        ++twos;
        break;
      case 3:
        ++threes;
        break;
      default:
        break;
      }
    }
    memo = vector<arr<double>>(
        args.N + 1,
        arr<double>(
            args.N + 1,
            vector<double>(
                args.N + 1, 0.0)));
    prob = 1.0 / args.N;
  }
  double dfs(ll i, ll j, ll k)
  {
    if (0 < memo.at(i).at(j).at(k))
    {
      return memo.at(i).at(j).at(k);
    }
    ll zeros = args.N - i - j - k;
    if (zeros == args.N)
    {
      return 0.0;
    }
    double ret(1.0);
    if (0 < i)
    {
      ret += dfs(i - 1, j, k) * prob * i;
    }
    if (0 < j)
    {
      ret += dfs(i + 1, j - 1, k) * prob * j;
    }
    if (0 < k)
    {
      ret += dfs(i, j + 1, k - 1) * prob * k;
    }
    double fact = 1. / (1. - prob * zeros);
    ret *= fact;
    return memo.at(i).at(j).at(k) = ret;
  }

  void calc_memo()
  {
    dfs(ones, twos, threes);
  }

  double get_ans()
  {
    return dfs(ones, twos, threes);
  }

  void solve()
  {
    calc_memo();
    ans = get_ans();
  }
  void output()
  {
    cout << fixed << setprecision(10) << ans << endl;
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
