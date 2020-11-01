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
 * 無限に広い 2 次元平面の上に N 個の点があります
 * i 番目の点は (xi,yi) にあります。
 * N 個の点の中の相異なる 3 点であって、同一直線上にあるものは存在するでしょうか？
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
  bool get_ans()
  {
    REP(i, args.N - 2)
    {
      FOR(j, i + 1, args.N - 1)
      {
        FOR(k, j + 1, args.N)
        {
          if (args.x.at(i) == args.x.at(j))
          {
            if (args.x.at(i) == args.x.at(k))
            {
              return true;
            }
          }
          else
          {
            ll x21 = args.x.at(j) - args.x.at(i);
            ll x31 = args.x.at(k) - args.x.at(i);
            ll y21 = args.y.at(j) - args.y.at(i);
            ll y31 = args.y.at(k) - args.y.at(i);
            if (x21 * y31 == y21 * x31)
            {
              return true;
            }
          }
        }
      }
    }
    return false;
  }

  void solve()
  {
    ans = get_ans();
  }
  void output()
  {
    pr((ans) ? "Yes" : "No");
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
