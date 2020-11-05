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
 * N 本の花が横一列に並んでいます。 各 i (1≤i≤N) について、左から i 番目の花の高さは 
 * hi で、美しさは ai です。 ただし、h1,h2,…,hN はすべて相異なります。 
 * 太郎君は何本かの花を抜き去ることで、次の条件が成り立つようにしようとしています。
 * 
 * - 残りの花を左から順に見ると、高さが単調増加になっている。
 * 
 * 残りの花の美しさの総和の最大値を求めてください。
 */
ll N;
vll h, a;
vector<P> flowers;

// i番目を利用した際の美しさの総和の最大。
vll dp;

vll bit;

void set_val(ll ind, ll val)
{
  ind++;
  while (ind <= N)
  {
    chmax(bit.at(ind), val);
    ind += ind & -ind;
  }
}

ll get_val(ll ind)
{
  ll res(0);
  ind++;
  while (0 < ind)
  {
    res = max(res, bit.at(ind));
    ind -= ind & -ind;
  }
  return res;
}

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  h.assign(N + 10, 0);
  REP(i, N)
  {
    cin >> h.at(i);
  }
  a.assign(N + 10, 0);
  REP(i, N)
  {
    cin >> a.at(i);
  }
  flowers.resize(N);
  REP(i, N)
  {
    flowers.at(i) = {h.at(i), i};
  }
  sort(ALL(flowers));
  //
  bit.assign(N + 10, 0);
  dp.assign(N + 1, 0);
  FORA(f, flowers)
  {
    ll i = f.second;
    dp.at(i) = a.at(i);
    dp.at(i) = get_val(i - 1) + a.at(i);
    set_val(i, dp.at(i));
    /*
    REP(j, i)
    {
      dp.at(i) = max(dp.at(i), dp.at(j) + a.at(i));
    }
    */
  }

  ll ans(0);
  FORA(x, dp)
  {
    chmax(ans, x);
  }
  pr(ans);
}
