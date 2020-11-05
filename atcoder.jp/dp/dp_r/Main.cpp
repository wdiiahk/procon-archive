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
 * N 頂点の単純有向グラフ G があります。 頂点には 1,2,…,N と番号が振られています。
 * 各 i,j (1≤i,j≤N) について、頂点 i から j への有向辺の有無が
 * 整数 ai,j によって与えられます。 
 * ai,j=1 ならば頂点 i から j への有向辺が存在し、ai,j=0 ならば存在しません。
 * G の長さ K の有向パスは何通りでしょうか？ 
 * 10^9+7 で割った余りを求めてください。 ただし、同じ辺を複数回通るような有向パスも数えるものとします。
 */
ll N, K;
arr<ll> a;
struct Matrix
{
  arr<ll> val;
  Matrix() : val(N, vll(N, 0))
  {
  }
};

Matrix operator*(const Matrix &a, const Matrix &b)
{
  Matrix c;
  REP(i, N)
  {
    REP(j, N)
    {
      REP(k, N)
      {
        c.val.at(i).at(j) += (a.val.at(i).at(k) * b.val.at(k).at(j)) % MOD;
        c.val.at(i).at(j) %= MOD;
      }
    }
  }
  return c;
}

Matrix matrix_power(const Matrix &a, ll p)
{
  if (p == 0)
  {
    Matrix I;
    REP(i, I.val.size())
    {
      I.val.at(i).at(i) = 1;
    }
    return I;
  }
  //
  auto res = matrix_power(a, p / 2);
  res = res * res;
  if (p % 2 == 1)
  {
    res = res * a;
  }
  return res;
}

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> K;
  a.assign(N, vll(N, 0));
  REP(i, N)
  {
    REP(j, N)
    {
      cin >> a.at(i).at(j);
    }
  }
  //
  Matrix A;
  A.val = a;
  Matrix A_k = matrix_power(A, K);
  ll ans(0);
  REP(i, N)
  {
    REP(j, N)
    {
      ans += A_k.val.at(i).at(j);
      ans %= MOD;
    }
  }
  pr(ans);
}
