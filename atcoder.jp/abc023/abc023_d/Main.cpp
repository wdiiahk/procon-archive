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
 * 高橋君は最近、射撃にハマっている。
 * 高橋君は N 個の風船すべてを射撃で割り、得られる得点をできるだけ小さくする競技に参加している。
 * 風船には 1 から N までの番号が付けられていて、風船 i(1≦i≦N) は
 * 競技開始時に高度 Hi のところにあり、1 秒経過するにつれて高度が Si だけ増加する。
 * 高橋君は競技開始時に 1 個風船を割ることができ、
 * そこから 1 秒ごとに 1 個の風船を割ることができる。
 * どの順番で風船を割るのかは高橋君が自由に決定できる。
 * どの風船についても、その風船を割ることによるペナルティが発生する。
 * ペナルティはその風船が割られたときの高度と等しい整数値となる。
 * 高橋君が最終的に得る得点は N個の風船のペナルティのうちの最大値となる。
 * 高橋君が得ることのできる得点として考えられる最小値を求めよ。
 */
ll N;
vll H, S;
ll maxH, maxS;

bool is_ok(ll x)
{
  vll limits(N);
  REP(i, N)
  {
    ll t = (x - H.at(i) + S.at(i)) / S.at(i) - 1;
    limits.at(i) = t;
  }
  sort(ALL(limits));
  REP(i, N)
  {
    if (limits.at(i) < i)
    {
      return false;
    }
  }
  return true;
}

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  H.resize(N);
  S.resize(N);
  REP(i, N)
  {
    cin >> H.at(i) >> S.at(i);
    chmax(maxH, H.at(i));
    chmax(maxS, S.at(i));
  }
  //
  ll left = 0;
  ll right = maxH + N * maxS;
  while (1 < right - left)
  {
    ll mid = (left + right) / 2;
    if (is_ok(mid))
    {
      right = mid;
    }
    else
    {
      left = mid;
    }
  }
  //
  pr(right);
  return 0;
}
