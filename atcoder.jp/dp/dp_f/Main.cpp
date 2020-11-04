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
 * 文字列 s および t が与えられます。 
 * s の部分列かつ t の部分列であるような文字列のうち、最長のものをひとつ求めてください。
 */
string S;
string T;

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> S;
  cin >> T;
  //
  ll NS(S.size());
  ll NT(T.size());
  //
  arr<ll> dp(NS + 1, vll(NT + 1, 0));
  REP(i, NS)
  {
    REP(j, NT)
    {
      if (S.at(i) == T.at(j))
      {
        dp.at(i + 1).at(j + 1) = dp.at(i).at(j) + 1;
      }
      else
      {
        dp.at(i + 1).at(j + 1) = max(dp.at(i).at(j + 1), dp.at(i + 1).at(j));
      }
    }
  }
  //
  vbool selections(NS, false);
  ll i = NS;
  ll j = NT;
  while (0 < i && 0 < j)
  {
    if (dp.at(i).at(j) == dp.at(i - 1).at(j))
    {
      --i;
    }
    else if (dp.at(i).at(j) == dp.at(i).at(j - 1))
    {
      --j;
    }
    else
    {
      selections.at(i - 1) = true;
      --i;
      --j;
    }
  }
  //
  string ans;
  REP(i, NS)
  {
    if (selections.at(i))
    {
      ans += S.at(i);
    }
  }
  pr(ans);
}
