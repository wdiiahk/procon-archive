//デバッグ用オプション：-fsanitize=undefined,address

//コンパイラ最適化
#pragma GCC optimize("Ofast")

//インクルードなど
#include <bits/stdc++.h>
//#include <atcoder/all>

using namespace std;
//using namespace atcoder;

typedef long long ll;
using vint = vector<int>;
using vll = vector<ll>;
using vbool = vector<bool>;
using vs = vector<string>;
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
  ll H, W;
  Constants()
  {
    cin >> H >> W;
  }
} C;

struct Args
{
  vs a;
  Args() : a(C.H)
  {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    REP(i, C.H)
    {
      cin >> a.at(i);
    }
  }
} args;

struct Solver
{
  ll ans;
  Solver() : ans(0)
  {
  }
  //
  void solve()
  {
    vector<P> starts;
    REP(i, C.H)
    {
      REP(j, C.W)
      {
        if (args.a.at(i).at(j) != '#')
        {
          starts.push_back({i, j});
        }
      }
    }

    vector<P> dv = {
        {-1, 0}, {0, -1}, {0, 1}, {1, 0}};
    FORA(s, starts)
    {
      arr<ll> dist(C.H, vll(C.W, -1));
      queue<P> q;
      q.push(s);
      dist.at(s.first).at(s.second) = 0;
      while (!q.empty())
      {
        auto p = q.front();
        q.pop();
        FORA(v, dv)
        {
          ll h = p.first + v.first;
          ll w = p.second + v.second;
          if (h < 0 || C.H <= h)
          {
            continue;
          }
          if (w < 0 || C.W <= w)
          {
            continue;
          }
          if (args.a.at(h).at(w) == '#') {
            continue;
          }
          if (0 <= dist.at(h).at(w))
          {
            continue;
          }
          q.push({h, w});
          ll d = dist.at(p.first).at(p.second) + 1;
          dist.at(h).at(w) = d;
          chmax(ans, d);
        }
      }
    }
  }
  //
  void output()
  {
    pr(ans);
  }
} s;

int main()
{
  s.solve();
  s.output();
  return 0;
}
