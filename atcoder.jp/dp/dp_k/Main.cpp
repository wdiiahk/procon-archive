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
 * N 個の正整数からなる集合 A={a1,a2,…,aN} があります。 
 * 太郎君と次郎君が次のゲームで勝負します。
 * 最初に、K個の石からなる山を用意します。 
 * 二人は次の操作を交互に行います。 先手は太郎君です。
 * 
 * - Aの元 x をひとつ選び、山からちょうど x 個の石を取り去る。
 * 
 * 先に操作を行えなくなった人が負けです。 
 * 二人が最適に行動すると仮定したとき、どちらが勝つかを判定してください。
 * 
 * 制約
 * 
 * 入力はすべて整数である
 * 1≤N≤100
 * 1≤K≤105
 * 1≤a1<a2<⋯<aN≤K
 */
ll N, K;
vll a;
// i個の石が残っている場合に、先手が勝ちかどうか
vbool dp;

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> K;
  a.assign(N, 0);
  REP(i, N)
  {
    cin >> a.at(i);
  }
  dp.assign(K + 1, false);
  dp.at(0) = false;
  FOR(i, 1, K + 1)
  {
    FORA(x, a)
    {
      if (!(0 <= i - x))
      {
        continue;
      }
      if (!dp.at(i - x))
      {
        dp.at(i) = true;
        break;
      }
    }
  }
  //
  pr(dp.at(K) ? "First" : "Second");

}
