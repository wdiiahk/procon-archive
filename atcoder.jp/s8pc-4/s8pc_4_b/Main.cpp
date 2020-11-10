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
 * N 個の建物が左から右へと一直線上に並んでいます。
 * 左から i 番目の建物は色 i で塗られており、高さは現在 ai です。 
 * 高橋君は市長である。彼はカラフルなものが好きなので、左から見たときに 
 * K 色以上の色の建物が見えるという条件を満たしてほしいと思いました。
 * 
 * 現在の状況から、建物の高さを増やすことができます。しかし、高さを 1 増やすごとに 1 円かかります。また、高さを減らすことはできません。
 * そのとき、高橋君の目的を達成するために必要な金額を求めなさい。
 * ただし、「建物 i が見える」とは、建物jの高さ ≥ 建物iの高さ (j<i) となるような j が存在しないのと同じものとします。
 */
ll N, K;
vll a;

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> K;
  a.resize(N);
  REP(i, N)
  {
    cin >> a.at(i);
  }
  ll ans(INF);
  K--; //一番左はいつも見える
  REP(S, 1 << (N - 1))
  {
    if (__builtin_popcount(S) < K)
    {
      continue;
    }
    ll cost(0);
    ll last = a.at(0);
    FOR(i, 1, N)
    {
      if ((S >> (i - 1)) % 2 == 0)
      {
        if (last < a.at(i))
        {
          last = a.at(i) + 1;
        }
        continue;
      }
      if (last < a.at(i))
      {
        last = a.at(i);
      }
      else
      {
        last++;
        cost += last - a.at(i);
      }
    }
    //
    chmin(ans, cost);
  }
  //
  pr(ans);
  return 0;
}
