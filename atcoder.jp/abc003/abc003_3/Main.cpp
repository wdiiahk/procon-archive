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
 * 高橋くんのレートが C の時に、レート R の競技プログラマーの講座動画を見ると、
 * 高橋くんのレートは (C+R)/2 に変化します。
 * 高橋くんは、講座動画を合計で K 個まで好きな順番で見ることができますが、
 * 同じ競技プログラマーの講座動画は一度までしか見ることができません。
 * 講座動画を配信している N 人のレートが与えられた時、高橋くんが講座動画を
 * 見ることによって達成できるレートの最大値を求めるプログラムを書いてください。
 * ただし、高橋くんの初期レートは 0 です。
 */
struct Args
{
  /**
   * 1 行目には、講座動画の数を表す整数 N (1≦N≦100) と高橋くんが見ることのできる動画の数を表す整数 K (1≦K≦N)
   * がスペース区切りで与えられる。
   */
  ll N, K;
  /**
   * 2 行目には、講座動画を配信している競技プログラマーのレートを表す整数 Ri (1≦Ri≦4,000) がスペース区切りで与えられる
   */
  vll R;
  Args()
  {
    cin >> N >> K;
    R = vll(N);
    REP(i, N)
    {
      cin >> R.at(i);
    }
    sort(ALL(R));
  }
};

class Solver
{
private:
  /* data */
  Args &args;
  double ans;

public:
  Solver(Args &args) : args(args), ans(0)
  {
  }
  void solve()
  {
    ans = 0.0;
    REPD(i, args.K)
    {
      ans = (ans + args.R.at(args.N - 1 - i)) / 2.0;
    }
  }
  void output()
  {
    cout << fixed << setprecision(9) << ans << endl;
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
