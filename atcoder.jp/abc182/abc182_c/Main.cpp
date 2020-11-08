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
 * 各桁に 0 が出現しないような正の整数 N が与えられます。
 * N の桁数を k とします。N の桁を 0 個以上 k 個未満消して、残った桁をそのままの順序で結合することで 3 の倍数を作りたいです。
 * 3の倍数を作ることができるか判定し、作ることができるなら作るのに必要な最少の消す桁数を求めてください。
 * 
 * 制約
 * - 1≤N<10^18
 * Nは各桁に 0 が出現しない整数
 */
string N;
vll dp;

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  ll k(N.size());
  ll total = 0;
  dp.resize(3);
  FORA(c, N)
  {
    ll i = c - '0';
    dp.at(i % 3)++;
    total += i;
  }
  ll ans(-1);
  if (total % 3 == 0)
  {
    ans = 0;
  }
  else if (total % 3 == 1)
  {
    if (0 < dp.at(1))
    {
      ans = 1;
    }
    else if (1 < dp.at(2))
    {
      ans = 2;
    }
  }
  else if (total % 3 == 2)
  {
    if (0 < dp.at(2))
    {
      ans = 1;
    }
    else if (1 < dp.at(1))
    {
      ans = 2;
    }
  }
  if (k <= ans)
  {
    ans = -1;
  }
  pr(ans);
  return 0;
}
