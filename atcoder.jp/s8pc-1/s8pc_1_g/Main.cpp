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
 * E869120は, セールスマンである。だから, すべての建物を1度ずつ通って店に戻ってこなければならない。
 * E869120の住む街には, 建物がN 個あり, 道路がM本ある。建物の番号は1-indexedでつけられており, 店は建物1 とする。
 * また, 道路 i は建物siと建物tiを結んでいて, 距離はdi である。
 * しかし, その街は不審者対策として一定の時間を過ぎると道路を閉鎖する。
 * 道路 i は, E869120が出発してから時間 timei 経つと道路が閉鎖される。
 * だから, その道路を通る際, 時間 timei 以内に道路を通り終えなければならない。
 * そのとき, E869120は次のようなことを考えた。
 * 「最短時間で戻ってくる方法の総数はどのくらいあるのだろう？」
 * そこで, 優秀なプログラマーであるあなたにプログラムを作ってもらうことになりました。
 * 最短経路と, 最短時間で戻ってくる方法の総数を求めなさい。
 * ただし, E869120は時間 1 につき距離 1 進む。また, 道路は双方向に移動可能である。
 */
ll N, M;

struct Edge
{
  ll d;
  ll time;
};

arr<Edge> edges;

// 状態: S, last: j
arr<P> dp;

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> M;
  edges.assign(N, vector<Edge>(N, {INF, 0}));
  //
  REP(i, M)
  {
    ll f, t, d, time;
    cin >> f >> t >> d >> time;
    edges.at(f - 1).at(t - 1) = {d, time};
    edges.at(t - 1).at(f - 1) = {d, time};
  }
  //
  arr<P> dp(1 << N, vector<P>(N, {INF, 0}));
  dp.at(0).at(0) = {0, 1};
  FOR(S, 1, 1 << N)
  {
    REP(j, N)
    {
      if ((S >> j) % 2 == 0)
      {
        continue;
      }
      ll T = S - (1 << j);
      REP(k, N)
      {
        ll time = dp.at(T).at(k).first + edges.at(k).at(j).d;
        if (edges.at(k).at(j).time < time)
        {
          continue;
        }
        if (dp.at(S).at(j).first < time)
        {
          continue;
        }
        if (dp.at(S).at(j).first == time)
        {
          dp.at(S).at(j).second += dp.at(T).at(k).second;
          continue;
        }
        dp.at(S).at(j).first = time;
        dp.at(S).at(j).second = dp.at(T).at(k).second;
      }
    }
  }
  P ans(dp.at((1 << N) - 1).at(0));
  if (ans.second == 0)
  {
    pr("IMPOSSIBLE");
  }
  else
  {
    prp(ans);
  }

  return 0;
}
