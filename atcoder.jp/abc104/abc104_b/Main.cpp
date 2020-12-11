//デバッグ用オプション：-fsanitize=undefined,address

//コンパイラ最適化
#pragma GCC optimize("Ofast")

//インクルードなど
#include <bits/stdc++.h>
// #include <atcoder/all>

using namespace std;
// using namespace atcoder;

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

struct Constants
{
  Constants()
  {
  }
} C;

struct Args
{
  string S;
  Args() 
  {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> S;
  }
} args;

struct Solver
{
  bool ans;
  Solver() : ans(true)
  {
  }
  //
  void solve()
  {
    ll N = args.S.length();
    //Sの先頭の文字は大文字の A である。
    if (args.S.at(0) != 'A') {
      ans = false;
      return;
    }
    //Sの先頭から3文字目と末尾から2文字目の間（両端含む）に大文字の C がちょうど 1個含まれる。
    set<ll> ignore({0});
    ll cnt(0);
    FOR(i, 2, N - 1) {
      if (args.S.at(i) == 'C') {
        ignore.insert(i);
        ++cnt;
      }
    }
    if (cnt != 1) {
      ans = false;
      return;
    }
    //以上の A, C を除く Sのすべての文字は小文字である。
    FOR(i, 1, N) {
      if (ignore.find(i) != ignore.end()) {
        continue;
      }
      char c = args.S.at(i);
      if (c < 'a' || 'z' < c) {
        ans = false;
        return;
      }
    }
    ans = true;
  }

  void output()
  {
    pr(ans ? "AC" : "WA");
  }
} s;

int main()
{
  s.solve();
  s.output();
  return 0;
}

