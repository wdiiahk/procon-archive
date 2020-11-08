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
 * 数列 A1,A2,A3,…,AN が与えられます。 この数列は負の要素を含むかもしれません。
 * 数直線上の座標 0 に置かれているロボットが、以下の動作を順に行います。
 * 
 * - 正の向きに A1 進む。
 * - 正の向きに A1進み、正の向きに A2進む。
 * - 正の向きに A1進み、正の向きに A2 進み、正の向きに A3進む。
 * ⋮
 * 正の向きに A1進み、正の向きに A2 進み、正の向きに A3 進み、… 、正の向きに AN進む。
 * 動作開始時から終了時までのロボットの座標の最大値を求めてください。
 * 
 * 制約
 * - 1≤N≤200000
 * −10^8≤Ai≤10^8
 * 入力はすべて整数
 */
ll N;
vll A, acc, dp;

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  A.resize(N);
  acc.resize(N + 1, 0);
  dp.resize(N + 1, 0);
  REP(i, N)
  {
    ll a;
    cin >> a;
    A.at(i) = a;
    acc.at(i + 1) = acc.at(i) + a;
    dp.at(i + 1) = dp.at(i);
    chmax(dp.at(i + 1), acc.at(i + 1));
  }
  //
  ll ans(0);
  ll cur(0);
  REP(i, N + 1)
  {
    chmax(ans, cur + dp.at(i));
    cur += acc.at(i);
  }
  pr(ans);
  return 0;
}
