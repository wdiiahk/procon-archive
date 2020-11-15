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

ll N, K;
//
arr<ll> T;
arr<map<ll, ll>> dp;

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> K;
  T.assign(N, vll(N, 0));
  REP(i, N)
  {
    REP(j, N)
    {
      cin >> T.at(i).at(j);
    }
  }
  //
  dp.assign(1 << N, vector<map<ll, ll>>(N));
  dp.at(0).at(0)[0] = 1;
  FOR(i, 1, N)
  {
    ll time = T.at(0).at(i);
    dp.at(1 << i).at(i)[time] = 1;
  }

  FOR(S, 1, 1 << N)
  {
    REP(i, N)
    {
      if ((S >> i) % 2 == 0)
      {
        continue;
      }
      ll preS = S - (1 << i);
      REP(j, N)
      {
        if ((S >> j) % 2 == 0)
        {
          continue;
        }
        FORA(p, dp.at(preS).at(j))
        {
          ll time = p.first + T.at(i).at(j);
          dp.at(S).at(i)[time] += p.second;
        }
      }
    }
  }
  //
  ll ans(dp.at((1 << N) - 1).at(0)[K]);
  pr(ans);
  return 0;
}
