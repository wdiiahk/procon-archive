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
 * 筑駒パ研は，近い将来，パ研戦争に臨むことになりました．そのために，軍旗を作ることになりました．
 * 旗のデザインは縦に 5 個，横に N 個に分かれた 5×N のマス目で表されます．
 * 上から i 行目，左から j 列目のマスを，(i,j) で表すことにします．
 * 現在，旗のそれぞれのマスは赤・青・白・黒のいずれかで塗られています．
 * より具体的には，マス (i,j) は色 Si,j で塗られています．
 * ただし，Si,jは R, B, W, # のいずれかで，それぞれ赤・青・白・黒で塗られていることを表しています．
 * 
 * E869120 君は，パ研軍旗を、次の条件を満たすように青・白・赤で塗り替えたいです．
 * - N 個の列すべてにおいて，その列の 5 マスが「全部青」「全部白」「全部赤」のいずれかである
 * - どの隣り合った 2つの列も，色が異なる
 * ただし，黒いマスがあったら条件を満たさないことに注意してください．
 * 
 * 以下が，条件を満たす旗と条件を満たさない旗の例です．
 * 例 1は条件を満たします．
 * 例 2は，例えば左から 2 番目の列で青と白のマスがあり，5つ全部同じになっている必要があるという条件を満たしません．
 * 例 3は，例えば左から 3 番目の列と左から 4番目の列の色が同じなので，条件を満たしません．
 * 例 4は，例えば左から 5番目の色が黒になっているので，条件を満たしません．
 * 
 * E869120 君は，旗の作成時間を短くするため，できるだけ塗り替えるマスの個数を少なくしたいです．
 * 最小でいくつのマスを塗り替える必要があるか求めるプログラムを書いてください． 
 */
ll N;
arr<char> flags;
// i列目、j:最後の色のコスト
arr<ll> dp;

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  flags.assign(N, vector<char>(5));
  REP(j, 5)
  {
    string line;
    cin >> line;
    REP(i, N)
    {
      flags.at(i).at(j) = line.at(i);
    }
  }
  //
  dp.assign(N + 1, vll(4, INF));
  REP(j, 4)
  {
    dp.at(0).at(j) = 0;
  }

  vector<char> colors = {'R', 'B', 'W', '#'};
  FOR(i, 1, N + 1)
  {
    map<char, ll> counts;
    FORA(c, flags.at(i - 1))
    {
      counts[c] += 1;
    }
    REP(to, 3)
    {
      ll costs = 5 - counts[colors.at(to)];
      REP(from, 3)
      {
        if (to != from)
        {
          chmin(dp.at(i).at(to), dp.at(i - 1).at(from) + costs);
        }
      }
    }
  }
  //
  ll ans(INF);
  REP(to, 3)
  {
    chmin(ans, dp.at(N).at(to));
  }
  pr(ans);
  return 0;
}
