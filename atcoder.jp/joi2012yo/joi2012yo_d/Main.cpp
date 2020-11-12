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
#define MOD 10000         //10^9+7:合同式の法
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
 * あなたはパスタが大好物であり，毎日，晩御飯にパスタを作って食べている．
 * あなたはトマトソース，クリームソース，バジルソースの 3種類のパスタを 作ることができる．
 * N日間の晩御飯の予定を考えることにした．それぞれの日に 3 種類のパスタから 1 種類を選ぶ．
 * ただし，同じパスタが続くと飽きてしまうので， 3 日以上連続して同じパスタを選んではいけない．
 * また ， N 日のうちの K日分のパスタはすでに決めてある．
 * 
 * 入力として Nの値と， K 日分のパスタの情報が与えられたとき，条件をみたす予定が
 * 何通りあるかを 10000 で割った余りを求め るプログラムを作成せよ．
 */
ll N, K;
map<ll, ll> sources;
// i日目、j日同じソースが続いて、kが最終ソースの種類である通りの数。
vector<arr<ll>> dp;

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> K;
  REP(i, N)
  {
    ll a, b;
    cin >> a >> b;
    sources[a] = b - 1;
  }
  //
  dp.assign(N + 2, arr<ll>(3, vll(3, 0)));
  if (sources.count(1))
  {
    ll kind = sources.at(1);
    dp.at(1).at(1).at(kind) = 1;
  }
  else
  {
    REP(kind, 3)
    {
      dp.at(1).at(1).at(kind) = 1;
    }
  }
  //
  FOR(i, 1, N)
  {
    ll yotei = sources.count(i + 1) ? sources.at(i + 1) : -1;
    REP(k, 3)
    {
      if (yotei == -1 || yotei == k)
      {
        REP(l, 3)
        {
          if (k == l)
          {
            dp.at(i + 1).at(2).at(k) += dp.at(i).at(1).at(k);
            dp.at(i + 1).at(2).at(k) %= MOD;
          }
          else
          {
            dp.at(i + 1).at(1).at(k) += dp.at(i).at(1).at(l);
            dp.at(i + 1).at(1).at(k) += dp.at(i).at(2).at(l);
            dp.at(i + 1).at(1).at(k) %= MOD;
          }
        }
      }
    }
  }
  //
  ll ans(0);
  REP(j, 3)
  {
    REP(k, 3)
    {
      ans += dp.at(N).at(j).at(k);
    }
    ans %= MOD;
  }
  //
  pr(ans);
  return 0;
}
