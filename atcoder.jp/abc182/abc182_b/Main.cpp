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
 * 数列 A (A1,A2,A3,…,AN) が与えられます。
 * 正の整数 k の GCD 度を、A1,A2,A3,…,AN のうち k で割り切れるものの数と定義します。
 * 2 以上の整数のうち GCD 度が最大になるものを一つ求めてください。 GCD 度が最大のものが複数ある場合どれを出力しても構いません。
 * 
 * 制約
 * 1≤N≤100
 * 2≤Ai≤1000=
 * 入力は全て整数
 */
ll N;
vll A, primes;
map<ll, ll> gcds;

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  A.resize(N);
  REP(i, N)
  {
    cin >> A.at(i);
  }
  //
  ll n(2);
  while (n <= 1000)
  {
    bool is_prime(true);
    FORA(i, primes)
    {
      if (n % i == 0)
      {
        is_prime = false;
        break;
      }
    }
    if (is_prime)
    {
      primes.push_back(n);
    }
    n++;
  }
  //
  ll ans(0);
  ll max_cnt(0);
  FORA(p, primes)
  {
    ll cnt(0);
    FORA(a, A)
    {
      if (p <= a && a % p == 0)
      {
        cnt++;
      }
    }
    //cout << p << " " << cnt << endl;
    if (max_cnt < cnt)
    {
      ans = p;
      max_cnt = cnt;
    }
  }
  pr(ans);
}
