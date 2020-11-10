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
 * 神からの財産と、母音を取り戻した高橋くんは、AtCoder国の腐敗した政治を正すため、国会議員となろうと決めました。
 * もともと人心掌握術とスピーチに定評があった高橋くんは、何の苦労をすることもなく当選しました。
 * しかし、議員になってからが本番です。国を正すためには、首相に任命される必要があります。
 * 
 * AtCoder国には高橋くんを除いて N 人の国会議員と、M 個の人間関係 (x, y) が存在します。
 * 人間関係 (x, y) とは、議員 x と議員 y が知り合いであることを意味します。
 * 高橋くんは N 人の議員から何人かを選んで派閥を作ろうと企んでいます。
 * 派閥に含まれるすべての議員は互いに知り合いでなければなりません。
 * 高橋くんが作成することができる最大の派閥に属する議員数を求めるプログラムを書いてください。 
 */
ll N, M;
arr<ll> friends;

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> M;
  friends.resize(N, vll(N, 0));
  REP(i, M)
  {
    ll x, y;
    cin >> x >> y;
    friends.at(x - 1).at(y - 1) = 1;
  }

  ll ans(0);
  FOR(S, 1, 1 << N)
  {
    if (__builtin_popcount(S) < ans)
    {
      continue;
    }
    bool ok(true);
    REP(i, N - 1)
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
        if (friends.at(i).at(j) == 0)
        {
          ok = false;
          break;
        }
      }
      if (!ok)
      {
        break;
      }
    }
    //
    if (ok)
    {
      ans = __builtin_popcount(S);
    }
  }
  //
  pr(ans);
}
