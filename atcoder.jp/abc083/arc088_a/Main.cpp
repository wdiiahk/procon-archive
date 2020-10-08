//デバッグ用オプション：-fsanitize=undefined,address

//コンパイラ最適化
#pragma GCC optimize("Ofast")

//インクルードなど
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

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

struct Args
{
  ll X, Y; // 1<= X <= Y <= 10^18
  Args()
  {
    cin >> X >> Y;
  }
};

class Solver
{
private:
  /* data */
  pair<ll, ll> range;

public:
  Solver(Args &args);
  ~Solver();
  size_t solve();
  void output(size_t res);
};

Solver::Solver(Args &args) : range({args.X, args.Y})
{
}

Solver::~Solver()
{
}

size_t Solver::solve()
{
  size_t res = 0;
  vector<ll> ans;
  ll last = range.first;
  ans.push_back(last);
  ll cur = last;
  while (cur <= range.second)
  {
    bool is_valid = true;
    FORA(el, ans)
    {
      if (cur % el != 0)
      {
        is_valid = false;
        break;
      }
    }
    // cout << cur << ":" << is_valid << endl;
    if (is_valid)
    {
      last = cur;
      ans.push_back(last);
      cur += cur;
      ++res;
    }
    else
    {
      cur += last;
    }
  }
  return res;
}

void Solver::output(size_t res)
{
  cout << res << endl;
}

int main()
{
  //入力の高速化用のコード
  //ios::sync_with_stdio(false);
  //cin.tie(nullptr);
  Args args;
  Solver s(args);
  size_t ans = s.solve();
  s.output(ans);
}
