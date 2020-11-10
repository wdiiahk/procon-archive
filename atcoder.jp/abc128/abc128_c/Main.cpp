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
 * on と off の状態を持つ N 個の スイッチと、M 個の電球があります。
 * スイッチには 1 から N の、電球には 1 から M の番号がついています。
 * 電球 i は ki 個のスイッチに繋がっており、スイッチ si1,si2,...,siki のうち 
 * on になっているスイッチの個数を 2 で割った余りが pi に等しい時に点灯します。
 * 全ての電球が点灯するようなスイッチの on/off の状態の組み合わせは何通りあるでしょうか。
 */
ll N, M;
arr<ll> s;
vll p;

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> M;
  s.resize(M, vll(N, 0));
  REP(i, M)
  {
    ll k;
    cin >> k;
    REP(j, k)
    {
      ll n;
      cin >> n;
      s.at(i).at(n - 1) = 1;
    }
  }
  p.resize(M);
  REP(i, M)
  {
    cin >> p.at(i);
  }
  //
  ll ans(0);
  REP(S, 1 << N)
  {
    bool ok(true);
    REP(i, M)
    {
      bool is_even(true);
      REP(j, N)
      {
        if ((S >> j) % 2 == 0)
        {
          continue;
        }
        if (s.at(i).at(j) == 1)
        {
          is_even = !is_even;
        }
      }
      if ((p.at(i) == 0 && !is_even) || (p.at(i) == 1 && is_even))
      {
        ok = false;
        break;
      }
    }
    if (ok)
    {
      ans++;
    }
  }
  pr(ans);
  return 0;
}
