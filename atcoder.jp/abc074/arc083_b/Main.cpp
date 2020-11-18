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

ll N;
arr<ll> A;

bool is_ok(arr<ll> &dp, arr<ll> &A)
{
  REP(k, N)
  {
    REP(i, N)
    {
      REP(j, N)
      {
        chmin(dp.at(i).at(j), dp.at(i).at(k) + dp.at(k).at(j));
      }
    }
  }
  ll ans(0);
  REP(i, N - 1)
  {
    FOR(j, i + 1, N)
    {
      if (A.at(i).at(j) != dp.at(i).at(j))
      {
        return false;
      }
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
  A.assign(N, vll(N, 0));
  arr<ll> dp(N, vll(N, 0));
  REP(i, N)
  {
    REP(j, N)
    {
      ll a;
      cin >> a;
      A.at(i).at(j) = a;
      dp.at(i).at(j) = a;
    }
  }
  if (!is_ok(dp, A))
  {
    pr(-1);
    return 0;
  }
  ll res(0);
  REP(i, N)
  {
    REP(j, N)
    {
      bool ok(false);
      REP(k, N)
      {
        if (k != i && k != j && A.at(i).at(k) + A.at(k).at(j) == A.at(i).at(j))
        {
          ok = true;
          break;
        }
      }
      if (!ok)
      {
        res += A.at(i).at(j);
      }
    }
  }
  pr(res/2);
  return 0;
}
