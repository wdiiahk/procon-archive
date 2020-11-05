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
 * N 羽のうさぎたちがいます。 うさぎたちには 1,2,…,N と番号が振られています。
 * 各 i,j (1≤i,j≤N) について、うさぎ i と j の相性が整数 ai,j によって与えられます。 
 * ただし、各 i (1≤i≤N) について ai,i=0 であり、各 i,j (1≤i,j≤N) について ai,j=aj,iです。
 * 太郎君は、N 羽のうさぎたちをいくつかのグループへ分けようとしています。 
 * このとき、各うさぎはちょうど 1 つのグループに属さなければなりません。 
 * グループ分けの結果、各 i,j (1≤i<j≤N) について、
 * うさぎ i と j が同じグループに属するならば、太郎君は ai,j 点を得ます。
 * 太郎君の総得点の最大値を求めてください。
 */
ll N;
arr<ll> a;
vll dp, cost;

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  a.assign(N, vll(N, 0));
  REP(i, N)
  {
    REP(j, N)
    {
      cin >> a.at(i).at(j);
    }
  }
  cost.assign(1 << N, 0);
  REP(S, 1 << N)
  {
    REP(i, N)
    {
      if ((S >> i) % 2 == 0)
      {
        continue;
      }
      FOR(j, i + 1, N)
      {
        if ((S >> j) % 2 == 0)
        {
          continue;
        }
        cost.at(S) += a.at(i).at(j);
      }
    }
  }

  //
  dp.assign(1 << N, -INF);
  dp.at(0) = 0;
  FOR(S, 1, 1 << N)
  {
    for (ll T = S; T > 0; T = (T - 1) & S)
    {
      chmax(dp.at(S), dp.at(S - T) + cost.at(T));
    }
  }
  //
  pr(dp.at((1 << N) - 1));
}
