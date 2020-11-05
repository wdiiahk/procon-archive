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
 * N を正整数とします。 長さ N−1 の文字列 s が与えられます。 
 * sは < と > からなります。
 * (1,2,…,N) を並べ替えた順列 (p1,p2,…,pN) であって、次の条件を満たすものは何通りでしょうか？ 
 * 10^9+7で割った余りを求めてください。
 * 
 * - 各 i (1≤i≤N−1) について、s の i 文字目が < の場合は pi<pi+1 であり、
 *   s の i 文字目が > の場合は pi>pi+1 である。
 */
ll N;
string s;
// dp: 左からi番目までの値まで埋めて、i番目の値がそれ以左の値の中で小さい方からj番目である場合の数
arr<ll> dp;
arr<ll> acc;

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  cin >> s;
  acc.assign(N + 1, vll(N + 1, 0));
  dp.assign(N + 1, vll(N + 1, 0));
  dp.at(0).at(0) = 1;

  FOR(i, 1, N)
  {
    acc.at(i - 1).at(0) = 0;
    REP(j, i)
    {
      acc.at(i - 1).at(j + 1) = dp.at(i - 1).at(j);
      acc.at(i - 1).at(j + 1) += acc.at(i - 1).at(j);
      acc.at(i - 1).at(j + 1) %= MOD;
    }

    bool smaller = (s.at(i - 1) == '<');
    REP(j, i + 1)
    {
      if (smaller)
      {
        dp.at(i).at(j) = acc.at(i - 1).at(j);
        /*
        REP(k, j)
        {
          dp.at(i).at(j) += dp.at(i - 1).at(k);
        }
        */
      }
      else
      {
        dp.at(i).at(j) = acc.at(i - 1).at(i) - acc.at(i - 1).at(j) + MOD;
        dp.at(i).at(j) %= MOD;
        /*
        FOR(k, j + 1, i)
        {
          dp.at(i).at(j) += dp.at(i - 1).at(k);
        }
        */
      }
    }
  }
  ll ans(0);
  REP(j, N)
  {
    ans += dp.at(N - 1).at(j);
    ans %= MOD;
  }
  pr(ans);
}
