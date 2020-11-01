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
 * N 人の児童がおり、 i 番目の児童の身長は Hi です。 N は奇数です。
 * 今から、先生であるあなたを含めた N+1 人で 2 人 1 組を (N+1)/2 ペア組みます。
 * あなたの目標は、それぞれのペアの身長の差の合計を最小化することです。 
 * すなわち、 i 番目のペアの身長の組を (xi,yi) としたとき、 ∑|xi−yi| を最小化したいです。
 * あなたには M 個の変身形態があり、 i 番目の変身形態での身長は Wiです。
 * あなたの変身形態とペアの組み方を工夫することで、それぞれのペアの身長の差の合計が
 * 最小でいくつにできるか求めてください。
 */

struct Args
{
  ll N, M;
  vll H, W;
  Args()
  {
    cin >> N >> M;
    H.resize(N);
    REP(i, N)
    {
      cin >> H.at(i);
    }
    sort(ALL(H));
    W.resize(M);
    REP(i, M)
    {
      cin >> W.at(i);
    }
  }
};

class Solver
{
private:
  /* data */
  Args &args;
  ll ans;
  vll cum1, cum2;

public:
  Solver(Args &args) : args(args), ans(0), cum1((args.N + 1) / 2 + 2, 0), cum2((args.N + 1) / 2 + 2, 0)
  {
    cum1.at(0) = 0;
    cum2.at(0) = 0;
    FOR(i, 1, (args.N + 1) / 2)
    {
      ll a = abs(args.H.at(2 * (i - 1) + 1) - args.H.at(2 * (i - 1)));
      cum1.at(i) = cum1.at(i - 1) + a;
      ll b = abs(args.H.at(args.N - 2 * i + 1) - args.H.at(args.N - 2 * i));
      cum2.at(i) = cum2.at(i - 1) + b;
    }
  }
  ll get_ans()
  {
    ll res(INF);
    FORA(w, args.W)
    {
      auto idx = lower_bound(ALL(args.H), w);
      if (idx == args.H.end())
      {
        ll tmp = cum1.at((args.N + 1) / 2 - 1);
        tmp += abs(w - args.H.at(args.N - 1));
        chmin(res, tmp);
        continue;
      }
      /*
      */
      ll i = idx - args.H.begin();
      ll t = i / 2;
      ll tmp = cum1.at(t);
      tmp += cum2.at((args.N + 1) / 2 - 1 - t);
      if (i % 2 == 0)
      {
        tmp += abs(w - args.H.at(i));
      }
      else
      {
        tmp += abs(w - args.H.at(i - 1));
      }
      chmin(res, tmp);
    }
    return res;
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
