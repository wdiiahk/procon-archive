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
 * N 個の足場があります。 足場には 1,2,…,N と番号が振られています。 
 * 各 i (1≤i≤N) について、足場 i の高さは hi です
 * 最初、足場 1にカエルがいます。 
 * カエルは次の行動を何回か繰り返し、足場 N まで辿り着こうとしています。
 * 足場 i にいるとき、足場 i+1 または i+2 へジャンプする。 
 * このとき、ジャンプ先の足場を j とすると、コスト |hi−hj|を支払う。
 * カエルが足場 Nに辿り着くまでに支払うコストの総和の最小値を求めてください。
 */

ll N(110000);
vll h(110000, 0), dp(110000, 0);

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  //
  cin >> N;
  REP(i, N)
  {
    cin >> h.at(i);
  }

  dp.at(0) = 0;
  FOR(i, 1, N)
  {
    dp.at(i) = dp.at(i - 1) + abs(h.at(i) - h.at(i - 1));
    if (0 <= i - 2)
    {
      chmin(dp.at(i), dp.at(i - 2) + abs(h.at(i) - h.at(i - 2)));
    }
  }
  //
  pr(dp.at(N - 1));
  return 0;
}
