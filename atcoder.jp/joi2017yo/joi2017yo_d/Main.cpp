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

ll N, M;
vll T, counts;
// 状態Sの順で埋めた時の変更が必要な数
vll dp;
arr<ll> acc;

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> M;
  //T.assign(N, 0);
  counts.assign(M, 0);
  acc.assign(M, vll(N + 1, 0));
  REP(i, N)
  {
    ll t;
    cin >> t;
    //T.at(i) = t - 1;
    counts.at(t - 1) += 1;
    REP(j, M)
    {
      ll extra((t - 1) == j ? 0 : 1);
      acc.at(j).at(i + 1) = acc.at(j).at(i) + extra;
    }
  }
  //
  dp.assign(1 << M, INF);
  dp.at(0) = 0;
  REP(S, (1 << M) - 1)
  {
    ll start(0);
    REP(i, M)
    {
      if ((S >> i) & 1 == 1)
      {
        start += counts.at(i);
      }
    }
    //
    REP(j, M)
    {
      if ((S >> j) & 1 == 1)
      {
        continue;
      }
      ll end = start + counts.at(j);
      ll cost = acc.at(j).at(end) - acc.at(j).at(start);
      chmin(dp.at(S | (1 << j)), dp.at(S) + cost);
    }
  }
  //
  ll ans(dp.at((1 << M) - 1));
  pr(ans);

  return 0;
}
