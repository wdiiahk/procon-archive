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
 * 以下のように直角三角形上に並んだ数列が与えられる．
 * 頂点から初めて一段下の直下か右下を選び，底辺まで下ったときの経路中の数値の合計の最大値を求めよ．
 */
struct Args
{
  ll N;
  arr<ll> a;
  Args()
  {
    cin >> N;
    a = arr<ll>(N, vll(N));
    REP(i, N)
    {
      REP(j, i + 1)
      {
        cin >> a.at(i).at(j);
      }
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
  ll do_solve()
  {
    arr<ll> dp(args.N, vll(args.N, 0));
    // dp.at(0).at(0) = args.a.at(0).at(0);
    REP(i, args.N)
    {
      REP(j, i + 1)
      {
        REP(k, 2)
        {
          if ((i - 1 < 0) || (j - k < 0))
          {
            continue;
          }
          chmax(dp.at(i).at(j), dp.at(i - 1).at(j - k));
        }
        dp.at(i).at(j) += args.a.at(i).at(j);
      }
    }
    //
    ll res(0);
    REP(j, args.N)
    {
      chmax(res, dp.at(args.N - 1).at(j));
    }
    return res;
  }

  void solve()
  {
    ans = do_solve();
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
