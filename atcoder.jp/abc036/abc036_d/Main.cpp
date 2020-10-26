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
 * N 個の島があります。 島には 1 から N までの番号がついています。 
 * また、N−1 個の橋があります。 i 番目の橋は ai 番の島と bi 番の島をつないでいます。 
 * どの島からどの島へも橋をいくつか経由して到達できることがわかっています。
 * 
 * すぬけ君は、それぞれの島を白または黒に塗ることにしました。 
 * ただし、両端の島が黒で塗られているような橋があってはいけません。 
 * 色の塗り方が何通りあるか、109+7 で割った余りを求めてください。 
 */
struct Args
{
  ll N;
  arr<ll> edges;
  Args()
  {
    cin >> N;
    edges.resize(N);
    REP(i, N - 1)
    {
      ll a, b;
      cin >> a >> b;
      edges.at(a - 1).push_back(b - 1);
      edges.at(b - 1).push_back(a - 1);
    }
  }
};

class Solver
{
private:
  /* data */
  Args &args;
  ll ans;
  arr<ll> dp;

public:
  Solver(Args &args) : args(args), ans(0)
  {
    dp.resize(args.N, vll(2, -1));
  }
  ll dfs(ll i, ll color, ll p = -1)
  {
    if (0 <= dp.at(i).at(color))
    {
      return dp.at(i).at(color);
    }
    ll res(1);
    FORA(c, args.edges.at(i))
    {
      if (c == p)
      {
        continue;
      }
      if (color == 0)
      {
        res *= (dfs(c, 0, i) + dfs(c, 1, i));
      }
      else
      {
        res *= dfs(c, 0, i);
      }
      res %= MOD;
    }
    // cout << i << " " << color << " = " << res << endl;
    return dp.at(i).at(color) = res;
  }

  void solve()
  {
    ans = dfs(0, 0) + dfs(0, 1);
    ans %= MOD;
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
