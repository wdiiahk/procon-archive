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
 * 今年もすぬけ祭の季節がやってきました。りんごさんは、まず手始めにすぬけ君召喚の儀式を執り行おうと思っています。 
 * 儀式には祭壇が必要で、祭壇は上部、中部、下部の 3つのカテゴリーのパーツ 1 つずつからなります。
 * 祭壇の 3 カテゴリーのパーツがそれぞれ N 個ずつあります。 
 * i 個目の上部のパーツのサイズは Ai 、i 個目の中部のパーツのサイズは Bi 、i 個目の下部のパーツのサイズは Ci です。
 * 
 * 祭壇を作るにあたっては、中部のパーツのサイズは上部のパーツのサイズより真に大きく、
 * 下部のパーツのサイズは中部のパーツのサイズより 真に大きくなければなりません。
 * 逆に、この条件を満たす任意の 3 つのピースを組み合わせて祭壇を作ることができます。
 * りんごさんが作ることのできる祭壇は何種類あるでしょうか。
 * ただし、2つの祭壇が異なるとは、上部、中部、下部に使われるピースのうち 少なくとも 1 つが異なることを言います。
 */
ll N;
vll A, B, C;

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
  sort(ALL(A));
  B.resize(N);
  REP(i, N)
  {
    cin >> B.at(i);
  }
  sort(ALL(B));
  C.resize(N);
  REP(i, N)
  {
    cin >> C.at(i);
  }
  sort(ALL(C));

  //
  ll ans(0);
  FORA(b, B)
  {
    if (b <= A.at(0))
    {
      continue;
    }
    if (C.at(N - 1) <= b)
    {
      break;
    }
    ll Aleft = -1;
    ll Aright = N;
    while (1 < Aright - Aleft)
    {
      ll mid = (Aleft + Aright) / 2;
      if (b <= A.at(mid))
      {
        Aright = mid;
      }
      else
      {
        Aleft = mid;
      }
    }
    ll Cleft = -1;
    ll Cright = N;
    while (1 < Cright - Cleft)
    {
      ll mid = (Cleft + Cright) / 2;
      if (b < C.at(mid))
      {
        Cright = mid;
      }
      else
      {
        Cleft = mid;
      }
    }
    //
    ans += (Aright) * (N - (Cright));
  }
  //
  pr(ans);
  return 0;
}
