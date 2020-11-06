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

/**
 * 問題文
 * 
 * 縦 H 行、横 W 列のグリッドがあります。 上から i 行目、左から j 列目のマスを (i,j) で表します。
 * グリッドのうち、N 個のマス (r1,c1),(r2,c2),…,(rN,cN) は壁のマスであり、
 * それら以外のマスはすべて空マスです。 
 * マス (1,1) および (H,W) は空マスであることが保証されています。
 * 
 * 太郎君は、マス (1,1) から出発し、右または下に隣り合う空マスへの移動を
 * 繰り返すことで、マス (H,W) まで辿り着こうとしています。
 * 
 * マス (1,1) から (H,W) までの太郎君の経路は何通りでしょうか？ 
 * 10^9+7 で割った余りを求めてください
 * 
 * 制約
 * 
 * 入力はすべて整数である。
 * 2≤H,W≤10^5
 * 1≤N≤3000
 * 1≤ri≤H
 * 1≤ci≤W
 * マス (ri,ci)はすべて相異なる。
 * マス (1,1)および (H,W) は空マスである。
 */
ll H, W, N;

vector<P> wall;
arr<ll> dp(3300, vll(2, 0));

vll fact(1100000), invfact(1100000), inv(1100000);
void init()
{
  fact.at(0) = 1;
  FOR(i, 1, 1100000)
  {
    fact.at(i) = fact.at(i - 1) * i % MOD;
  }
  // MOD / i * i + MOD % i = MOD
  // MOD / i * i + MOD % i = 0
  // MOD / i * i = - MOD % i;
  // inv[MOD/i] * inv[i] = - inv[MOD % i]
  // inv[i] = -inv[MOD % i] * (MOD / i);
  inv.at(1) = 1;
  FOR(i, 2, 1100000)
  {
    inv.at(i) = -inv.at(MOD % i) * (MOD / i) % MOD;
    if (inv.at(i) < 0)
    {
      inv.at(i) += MOD;
    }
  }
  //
  invfact.at(0) = 1;
  FOR(i, 1, 1100000)
  {
    invfact.at(i) = invfact.at(i - 1) * inv.at(i) % MOD;
  }
}

ll nCk(ll n, ll k)
{
  return (fact.at(n) * invfact.at(k) % MOD) * invfact.at(n - k) % MOD;
}

ll route(const P &a, const P &b)
{
  ll x = b.first - a.first;
  ll y = b.second - a.second;
  if (x < 0 || y < 0)
  {
    return 0;
  }
  return nCk(x + y, x);
}

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  init();
  cin >> H >> W >> N;
  wall.push_back(P(1, 1));
  REP(i, N)
  {
    ll x, y;
    cin >> x >> y;
    wall.push_back(P(x, y));
  }
  sort(ALL(wall));

  dp.at(0).at(0) = 1;
  FOR(i, 1, N + 1)
  {
    REP(j, i)
    {
      dp.at(i).at(0) += dp.at(j).at(1) * route(wall.at(j), wall.at(i));
      dp.at(i).at(0) %= MOD;
      dp.at(i).at(1) += dp.at(j).at(0) * route(wall.at(j), wall.at(i));
      dp.at(i).at(1) %= MOD;
    }
  }

  P goal = P(H, W);
  ll ban = 0;
  FOR(i, 1, N + 1)
  {
    ban -= dp.at(i).at(0) * route(wall.at(i), goal) % MOD;
    ban += dp.at(i).at(1) * route(wall.at(i), goal) % MOD;
    ban %= MOD;
  }

  ll ans = (nCk(H + W - 2, H - 1) - ban) % MOD;
  if (ans < 0)
    ans += MOD;
  pr(ans);
}
