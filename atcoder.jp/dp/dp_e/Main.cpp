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
 * N 個の品物があります。 品物には 1,2,…,N と番号が振られています。 
 * 各 i (1≤i≤N) について、品物 i の重さは wi で、価値は vi です。
 * 太郎君は、N個の品物のうちいくつかを選び、ナップサックに入れて持ち帰ることにしました。 
 * ナップサックの容量は W であり、持ち帰る品物の重さの総和は W 以下でなければなりません。
 * 太郎君が持ち帰る品物の価値の総和の最大値を求めてください。
 */
#define MAXN 100
#define MAXW 1000000000
#define MAXV 1000

ll N, W;
vll w(MAXN + 10, 0), v(MAXN + 10, 0);
// dp: i番目まで選んだ時に価値jとなるものの中で最小の重さ
arr<ll> dp;

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  //
  cin >> N >> W;
  FOR(i, 1, N + 1)
  {
    cin >> w.at(i) >> v.at(i);
  }
  ll total_v = accumulate(ALL(v), 0);
  //
  dp.assign(N + 1, vll(total_v + 1, INF));
  dp.at(0).at(0) = 0;
  FOR(i, 1, N + 1)
  {
    REP(j, total_v + 1)
    {
      dp.at(i).at(j) = dp.at(i - 1).at(j);
      if (0 <= j - v.at(i))
      {
        chmin(dp.at(i).at(j), dp.at(i - 1).at(j - v.at(i)) + w.at(i));
      }
    }
  }
  //
  ll res(0);
  REP(j, total_v + 1)
  {
    if (dp.at(N).at(j) <= W)
    {
      res = j;
    }
  }
  pr(res);
}
