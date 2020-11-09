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
 * 1,2,...,Nと番号づけられている N 人の生徒から成るグループが，「全国統一カラオケコンテスト」に出場することとなりました．
 * このコンテストで歌える曲は，曲 1，曲 2，...，曲 M の M 曲あります．
 * また，番号 i の生徒が曲 j を歌うと，必ず Ai,j 点を取ります．
 * 
 * さて，コンテストのルールは，以下のようになります．
 * M 曲の中から 2 つの曲を選ぶ．（それぞれ T1 と T2とする．）
 * それぞれの生徒が，曲 T1 と曲 T2 の両方を歌う．
 * 各生徒の得点は，その生徒が歌った 2 つの曲の点数のうち高い方となる．
 * グループの得点は，生徒 1,2,...,N の得点の合計となる．
 * そのとき，グループの得点として考えられる最大の値を求めてください．
 * 
 * 制約
 * - 1≤N≤100
 * - 2≤M≤100
 * - 0≤Ai,j≤100 000 000
 * 入力はすべて整数
 */
ll N, M;
arr<ll> A;

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> M;
  A.resize(N, vll(M, 0));
  REP(i, N)
  {
    REP(j, M)
    {
      cin >> A.at(i).at(j);
    }
  }
  //
  ll ans(0);
  REP(i, M - 1)
  {
    FOR(j, 1, M)
    {
      ll pt(0);
      REP(k, N)
      {
        pt += max(A.at(k).at(i), A.at(k).at(j));
      }
      chmax(ans, pt);
    }
  }
  pr(ans);
  return 0;
}
