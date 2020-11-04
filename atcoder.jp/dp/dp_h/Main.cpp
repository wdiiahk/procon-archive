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
 * 縦 H 行、横 W 列のグリッドがあります。 上から i 行目、左から j 列目のマスを (i,j)で表します。
 * 各 i,j (1≤i≤H, 1≤j≤W) について、マス (i,j) の情報が文字 ai,j によって与えられます。 
 * ai,j が . ならばマス (i,j) は空マスであり、ai,j が # ならばマス (i,j) は壁のマスです。 
 * マス (1,1) および (H,W) は空マスであることが保証されています。
 * 太郎君は、マス (1,1) から出発し、右または下に隣り合う空マスへの移動を繰り返すことで、
 * マス (H,W) まで辿り着こうとしています。
 * マス (1,1) から (H,W) までの太郎君の経路は何通りでしょうか？ 
 * 答えは非常に大きくなりうるので、10^9+7 で割った余りを求めてください。
 */
ll H, W;
vector<string> maze;
arr<ll> dp;

void add(ll &a, ll b)
{
  a += b;
  if (MOD <= a)
  {
    a -= MOD;
  }
}

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> H >> W;
  maze.assign(H, "");
  REP(i, H)
  {
    cin >> maze.at(i);
  }
  //
  dp.assign(H, vll(W, 0));
  dp.at(0).at(0) = 1;
  REP(i, H)
  {
    REP(j, W)
    {
      if (maze.at(i).at(j) == '#')
      {
        continue;
      }
      if (0 <= i - 1)
      {
        add(dp.at(i).at(j), dp.at(i - 1).at(j));
      }
      if (0 <= j - 1)
      {

        add(dp.at(i).at(j), dp.at(i).at(j - 1));
      }
    }
  }
  //
  pr(dp.at(H - 1).at(W - 1));
}
