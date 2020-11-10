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

void pd(double x) { cout << fixed << setprecision(10) << x << endl; }

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
 * 座標平面上に N個の町があります。町 i は、座標 ( xi , yi ) に位置しています。
 * 町 i と町 j の間の距離は √(xi−xj)2+(yi−yj)2 です。
 * これらの町を全て 1 回ずつ訪れるとき、町を訪れる経路は全部で N! 通りあります。
 * 1 番目に訪れる町から出発し、2 番目に訪れる町、3 番目に訪れる町、…、を経由し、N 番目に訪れる町に到着するまでの
 * 移動距離 (町から町への移動は直線移動とします) を、その経路の長さとします。
 * これらの N! 通りの経路の長さの平均値を計算してください。
 */
ll N;
vll x, y;
arr<double> dists;

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  //
  cin >> N;
  x.resize(N);
  y.resize(N);
  REP(i, N)
  {
    cin >> x.at(i) >> y.at(i);
  }
  dists.resize(N, vector<double>(N, 0));
  REP(i, N - 1)
  {
    FOR(j, 1, N)
    {
      ll dx = x.at(i) - x.at(j);
      ll dy = y.at(i) - y.at(j);
      double d = sqrt(dx * dx + dy * dy);
      dists.at(i).at(j) = d;
      dists.at(j).at(i) = d;
    }
  }
  //
  vll nums(N);
  iota(ALL(nums), 0);
  ll cnt(0);
  double ans(0);
  do
  {
    ++cnt;
    double d(0);
    REP(i, N - 1)
    {
      ll from = nums.at(i);
      ll to = nums.at(i + 1);
      d += dists.at(from).at(to);
    }
    ans = double(cnt - 1) / cnt * ans + d / cnt;

  } while (next_permutation(ALL(nums)));
  //
  pd(ans);
  return 0;
}
