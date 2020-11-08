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
 * H 行 W 列のマス目があります。このマス目の i 行目 j 列目のマスをマス (i,j) と呼ぶことにします。
 * このマス目の上には N 個の電球と M 個のブロックが置かれていて、i 個目の電球はマス (Ai,Bi) に、i 個目のブロックはマス (Ci,Di) に置かれています。一つのマスにある電球とブロックは合計で高々一つです。
 * 全ての電球は、ブロックが置かれているマスに到達するまで届く光を上下左右の 4 方向に放ちます。電球が置かれているマス自身にも光が届くものとします。
 * マス目上のブロックの置かれていないマスのうち電球の光が届くものの数を求めてください。 
 */
ll H, W, N, M;
vector<P> p;
arr<ll> dp0, dp1;

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> H >> W >> N >> M;
  dp0.resize(H, vll(W, -1));
  dp1.resize(H, vll(W, -1));
  //
  p.resize(N);
  REP(i, N)
  {
    ll a, b;
    cin >> a >> b;
    p.at(i) = {a - 1, b - 1};
  }
  REP(i, M)
  {
    ll c, d;
    cin >> c >> d;
    dp0.at(c - 1).at(d - 1) = 1;
    dp1.at(c - 1).at(d - 1) = 1;
  }
  //
  FORA(pt, p)
  {
    ll i = pt.first;
    ll j = pt.second;
    REP(k, W)
    {
      ll nj = j - k;
      if (nj < 0)
      {
        break;
      }
      if (dp0.at(i).at(nj) != -1)
      {
        break;
      }
      dp0.at(i).at(nj) = 0;
    }
    REP(k, W)
    {
      ll nj = j + k + 1;
      if (W <= nj)
      {
        break;
      }
      if (dp0.at(i).at(nj) != -1)
      {
        break;
      }
      dp0.at(i).at(nj) = 0;
    }
  }
  //
  //
  FORA(pt, p)
  {
    ll i = pt.first;
    ll j = pt.second;
    REP(k, H)
    {
      ll ni = i - k;
      if (ni < 0)
      {
        break;
      }
      if (dp1.at(ni).at(j) != -1)
      {
        break;
      }
      dp1.at(ni).at(j) = 0;
    }
    REP(k, H)
    {
      ll ni = i + k + 1;
      if (H <= ni)
      {
        break;
      }
      if (dp1.at(ni).at(j) != -1)
      {
        break;
      }
      dp1.at(ni).at(j) = 0;
    }
  }
  //
  ll ans(0);
  REP(i, H)
  {
    REP(j, W)
    {
      if (dp0.at(i).at(j) == 0 || dp1.at(i).at(j) == 0)
      {
        ans++;
      }
    }
  }
  pr(ans);
}
