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

struct Solver
{
  ll N; // 1 <= N <= 100,000
  ll Q; // 1 <= Q <= 200,000
  vector<ll> parents;

  void input()
  {
    cin >> N >> Q;
    parents = vector<ll>(N);
    REP(i, N)
    {
      parents.at(i) = i;
    }
  }

  ll root(ll x)
  {
    ll parent = parents.at(x);
    if (parent == x)
    {
      return x;
    }
    //
    ll ret = root(parent);
    parents.at(x) = ret;
    return ret;
  }

  bool same(ll x, ll y)
  {
    return root(x) == root(y);
  }

  void unite(ll x, ll y)
  {
    x = root(x);
    y = root(y);
    if (x == y)
    {
      return;
    }
    parents.at(x) = y;
  }

  void solve()
  {
    vector<bool> res;
    REP(i, Q)
    {
      ll p, A, B;
      cin >> p >> A >> B;
      if (p == 0)
      {
        unite(A, B);
      }
      else if (p == 1)
      {
        res.push_back(same(A, B));
      }
    }
    output(res);
  }

  void output(vector<bool> &res)
  {
    FORA(ans, res)
    {
      cout << ((ans) ? "Yes" : "No") << endl;
    }
  }
};

int main()
{
  //入力の高速化用のコード
  //ios::sync_with_stdio(false);
  //cin.tie(nullptr);
  Solver s;
  s.input();
  s.solve();
}
