//デバッグ用オプション：-fsanitize=undefined,address

//コンパイラ最適化
#pragma GCC optimize("Ofast")

//インクルードなど
#include <bits/stdc++.h>
#include <atcoder/all>

using namespace std;
using namespace atcoder;

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

template <class T>
void pl(T x) { cout << x << " "; }

template <class T>
void pr(T x) { cout << x << endl; }

template <class T>
void prvec(const vector<T> &a)
{
  REP(i, a.size() - 1)
  {
    cout << a[i] << " ";
  }
  pr(a[a.size() - 1]);
}

template <class T>
void prarr(const arr<T> &a)
{
  REP(i, a.size())
  if (a[i].empty())
    pr("");
  else
    prvec(a[i]);
}

using P = pair<ll, ll>;
void prp(const P &p) { cout << p.first << " " << p.second << endl; }

struct Constants
{
  ll R, B;
  Constants()
  {
    cin >> R >> B;
  }
} C;

struct Args
{
  ll x, y;
  Args()
  {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> x;
    cin >> y;
  }
} args;

struct Solver
{
  ll ans;
  Solver() : ans(0)
  {
  }

  //
  bool ok(ll n)
  {
    // a + b = n
    // x * a + 1 * b <= R
    // 1 * a + y * b <= B
    // x * a + (n - a) <= R
    // (n - b) + y * b <= B
    // a <= (R - n) / (x - 1)
    // b <= (B - n) / (y - 1)
    if (C.R - n < 0)
    {
      return false;
    }
    if (C.B - n < 0)
    {
      return false;
    }
    return n <= (C.R - n) / (args.x - 1) + (C.B - n) / (args.y - 1);
  }

  void solve()
  {
    ll left = 0;
    ll right = 1e18;
    while (1 < right - left)
    {
      ll mid = (left + right) / 2;
      auto &next = ok(mid) ? left : right;
      next = mid;
    }
    //
    ans = ok(right) ? right : left;
  }
  //
  void output()
  {
    pr(ans);
  }
} s;

int main()
{
  s.solve();
  s.output();
  return 0;
}