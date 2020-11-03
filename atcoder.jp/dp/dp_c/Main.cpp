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
 * 明日から太郎君の夏休みが始まります。 
 * 太郎君は夏休みの計画を立てることにしました。
 * 夏休みは N 日からなります。
 * 各 i (1≤i≤N) について、i 日目には太郎君は次の活動のうちひとつを選んで行います。
 * A: 海で泳ぐ。 幸福度 ai を得る。
 * B: 山で虫取りをする。 幸福度 bi を得る。
 * C: 家で宿題をする。 幸福度 ci を得る。
 * 太郎君は飽き性なので、2 日以上連続で同じ活動を行うことはできません。
 * 太郎君が得る幸福度の総和の最大値を求めてください。
 */

#define MAXN 110000
ll N;
arr<ll> dp(MAXN, vll(3, 0));
vll A(MAXN), B(MAXN), C(MAXN);

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  REP(i, N)
  {
    cin >> A.at(i) >> B.at(i) >> C.at(i);
  }
  //
  FOR(i, 1, N + 1)
  {
    REP(j, 3)
    {
      ll happy(0);
      REP(from, 3)
      {
        if (j == from)
        {
          continue;
        }
        if (j == 0)
        {
          chmax(happy, dp.at(i - 1).at(from) + A.at(i - 1));
        }
        else if (j == 1)
        {
          chmax(happy, dp.at(i - 1).at(from) + B.at(i - 1));
        }
        else if (j == 2)
        {
          chmax(happy, dp.at(i - 1).at(from) + C.at(i - 1));
        }
      }
      dp.at(i).at(j) = happy;
    }
  }
  //
  ll ans(0);
  REP(j, 3)
  {
    chmax(ans, dp.at(N).at(j));
  }
  pr(ans);
}
