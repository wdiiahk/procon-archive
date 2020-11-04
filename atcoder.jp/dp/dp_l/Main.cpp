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
 * 太郎君と次郎君が次のゲームで勝負します。
 * 
 * 最初に、数列 a=(a1,a2,…,aN) が与えられます。 
 * aが空になるまで、二人は次の操作を交互に行います。 先手は太郎君です。
 * aの先頭要素または末尾要素を取り除く。 
 * 取り除いた要素を x とすると、操作を行った人は x点を得る。
 * 
 * ゲーム終了時の太郎君の総得点を X、次郎君の総得点を Y とします。 
 * 太郎君は X−Y を最大化しようとし、次郎君は X−Y を最小化しようとします。
 * 
 * 二人が最適に行動すると仮定したとき、X−Y を求めてください。
 */

ll N;
vll a;
arr<ll> dp;

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  //
  a.assign(N, 0);
  REP(i, N)
  {
    cin >> a.at(i);
  }
  //
  dp.assign(N + 1, vll(N + 1, 0));
  FOR(width, 1, N + 1)
  {
    REP(l, N)
    {
      ll r = l + width;
      if (N < r)
      {
        break;
      }
      if (width % 2 == N % 2) // tarou
      {
        dp.at(l).at(r) = max(
            dp.at(l + 1).at(r) + a.at(l),
            dp.at(l).at(r - 1) + a.at(r - 1));
      }
      else
      {
        dp.at(l).at(r) = min(
            dp.at(l + 1).at(r) - a.at(l),
            dp.at(l).at(r - 1) - a.at(r - 1));
      }
    }
  }

  pr(dp.at(0).at(N));

  return 0;
}