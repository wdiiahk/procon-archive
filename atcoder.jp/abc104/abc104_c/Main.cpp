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
  ll D; // 1 <= D <= 10
  ll G; // 100 <= G
  vector<ll> counts;
  vector<ll> bonus;
};

Args get_args()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  Args args;
  cin >> args.D >> args.G;
  //
  REP(i, args.D)
  {
    int c, b; // 1 <= c <= 100, 100 <= b <= 10^6
    cin >> c >> b;
    args.counts.push_back(c);
    args.bonus.push_back(b);
  }
  return args;
}

ll calc(Args &args, vector<bool> &use_bonus, ll total, ll cnt)
{
  ll remain = args.G - total;
  if (remain <= 0)
  {
    return cnt;
  }
  REPD(i, args.D)
  {
    if (use_bonus.at(i))
    {
      continue;
    }
    ll tmp = min((remain - 1) / 100 / (i + 1) + 1, args.counts.at(i) - 1);
    remain -= (tmp) * (i + 1) * 100;
    cnt += tmp;
    if (remain <= 0)
    {
      return cnt;
    }
  }
  return INF;
}

ll dfs(Args &args, vector<bool> &use_bonus, ll total, ll cnt, ll x, ll &res)
{
  if (x == args.D)
  {
    ll tmp = calc(args, use_bonus, total, cnt);
    chmin(res, tmp);
    return res;
  }
  //
  use_bonus.at(x) = true;
  total += args.counts.at(x) * 100 * (x + 1);
  total += args.bonus.at(x);
  cnt += args.counts.at(x);
  dfs(args, use_bonus, total, cnt, x + 1, res);
  //
  use_bonus[x] = false;
  total -= args.counts.at(x) * 100 * (x + 1);
  total -= args.bonus.at(x);
  cnt -= args.counts.at(x);
  dfs(args, use_bonus, total, cnt, x + 1, res);
  return res;
}

ll solve(Args &args)
{
  ll res(INF);
  vector<bool> use_bonus(args.D);
  dfs(args, use_bonus, 0, 0, 0, res);
  return res;
}

int main()
{
  Args args = get_args();
  ll res = solve(args);
  cout << res << endl;
  return 0;
}
