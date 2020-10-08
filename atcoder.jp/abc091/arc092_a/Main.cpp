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
  ll N;
  vector<ll> a;
  vector<ll> b;
  vector<ll> c;
  vector<ll> d;
  Args()
  {
    cin >> N;
    a = vector<ll>(N);
    b = vector<ll>(N);
    REP(i, N)
    {
      cin >> a.at(i) >> b.at(i);
    }
    c = vector<ll>(N);
    d = vector<ll>(N);
    REP(i, N)
    {
      cin >> c.at(i) >> d.at(i);
    }
  }
};

class Solver
{
private:
  /* data */
  ll N;
  vector<pair<ll, ll>> reds;
  vector<pair<ll, ll>> blues;
  vector<bool> used;

public:
  Solver(Args &args) : reds(args.N), blues(args.N), used(args.N, false)
  {
    REP(i, args.N)
    {
      reds.at(i) = {args.a.at(i), args.b.at(i)};
      blues.at(i) = {args.c.at(i), args.d.at(i)};
    }
  }

  ll solve()
  {
    sort(ALL(reds));
    sort(ALL(blues));
    ll ans(0);
    FORA(bpt, blues)
    {
      auto pair_it = reds.end();
      for (auto it = reds.begin(), iend = reds.end(); it != iend; ++it)
      {
        if (bpt.first <= it->first)
        {
          break;
        }
        if (bpt.second <= it->second)
        {
          continue;
        }
        if (pair_it == iend || pair_it->second < it->second)
        {
          pair_it = it;
        }
      }
      //
      if (pair_it != reds.end())
      {
        ans++;
        reds.erase(pair_it);
      }
    }
    return ans;
  }

  void output(ll ans)
  {
    cout << ans << endl;
  }
};

int main()
{
  //入力の高速化用のコード
  //ios::sync_with_stdio(false);
  //cin.tie(nullptr);
  Args args;
  Solver s(args);
  ll ans = s.solve();
  s.output(ans);
}
