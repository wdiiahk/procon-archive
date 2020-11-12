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
 * 問題
 * 
 * 現在カザフスタンがある地域には，古くは「シルクロード」と呼ばれる交易路があった．
 * シルクロード上には N+1 個の都市があり，西から順に都市 0, 都市 1, ... , 都市 N と番号がつけられている．
 * 都 市 i−1 と都市 i の間の距離 (1≤i≤N) は Di である．
 * 貿易商である JOI 君は，都市 0 から出発して，都市を順番に経由し ，都市 N まで絹を運ぶことになった．
 * 都市 0 から都市 N まで M 日以内に移動しなければならない．
 * JOI 君は，それぞれの日の行動として，以下の 2 つのうちいずれか 1 つを選ぶ ．
 * 
 * 移動： 現在の都市から 1つ東の都市へ 1 日かけて移動する．
 * 現在都市 i−1 (1≤i≤N) にいる場合は，都市 i に移動する．
 * 待機： 移動を行わず，現在いる都市で 1 日待機する．
 * 
 * 移動は大変であり，移動するたびに疲労度が溜まっていく．
 * シルクロードでは日毎に天候の変動があり，天候が悪い日ほど移動には苦労を要する．
 * JOI 君が絹を運ぶのに使える M 日間のうち j 日目 (1≤j≤M) の天候の悪さは Cj であることが分かってい る．
 * 都市 i−1 から都市 i (1≤i≤N) に j 日目 (1≤j≤M) に移動する場合，疲労度が Di×Cjだけ溜まってしまう．
 * 移動を行わず待機している日は疲労 度は溜まらない．
 * JOI 君は，それぞれの日の行動をうまく選ぶことで，できるだけ疲労度を溜めずに移動したい．
 * JOI 君が M日以内に都市 N に移動するときの ，移動を開始してから終了するまでに溜まる疲労度の合計の最小値を求めよ．
 */
ll N, M;
vll D, C;

// i番目の都市に、j日目についた時の疲労度
arr<ll> dp;

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> M;
  D.assign(N, INF);
  REP(i, N)
  {
    cin >> D.at(i);
  }
  C.assign(M, 0);
  REP(i, M)
  {
    cin >> C.at(i);
  }
  //
  dp.assign(N + 1, vll(M + 1, INF));
  REP(j, M + 1)
  {
    dp.at(0).at(j) = 0;
  }

  FOR(i, 1, N + 1)
  {
    ll d = D.at(i - 1);
    FOR(j, 1, M + 1)
    {
      chmin(dp.at(i).at(j), dp.at(i).at(j - 1));
      chmin(dp.at(i).at(j), dp.at(i - 1).at(j - 1) + d * C.at(j - 1));
    }
  }
  //
  ll ans(INF);
  REP(j, M + 1)
  {
    chmin(ans, dp.at(N).at(j));
  }
  pr(ans);
}
