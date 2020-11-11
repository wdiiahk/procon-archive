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
 * 問題
 * 
 * 今年も JOI 町のチーズ工場がチーズの生産を始め，ねずみが巣から顔を出した．
 * JOI 町は東西南北に区画整理されていて，各区画は巣，チーズ工場，障害物，空き地のいずれかである．
 * ねずみは巣から出発して全てのチーズ工場を訪れチーズを 1 個ずつ食べる．
 * 
 * この町には， N 個のチーズ工場があり，どの工場も １ 種類のチーズだけを生産している．
 * チーズの硬さは工場によって異なっており，硬さ 1 から N までのチーズを生産するチーズ工場が
 * ちょうど 1つずつある．
 * ねずみの最初の体力は 1 であり，チーズを 1 個食べるごとに体力が 1 増える．
 * ただし，ねずみは自分の体力よりも硬いチーズを 食べることはできない．
 * 
 * ねずみは，東西南北に隣り合う区画に 1 分で移動することができるが，
 * 障害物の区画には入ることができない．
 * チーズ工場をチーズを食べずに通り過ぎる こともできる．
 * すべてのチーズを食べ終えるまでにかかる最短時間を求めるプログラ ムを書け．
 * ただし，ねずみがチーズを食べるのにかかる時間は無視できる．
 */
ll H, W, N;
vector<string> lines;
vector<P> goals;
vector<P> dv = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

ll bfs(const P &s, const P &g)
{
  queue<P> q;
  q.push(s);
  arr<ll> times(H, vll(W, 0));
  times.at(s.first).at(s.second) = 1;
  while (!q.empty())
  {
    auto &p = q.front();
    q.pop();
    ll t = times.at(p.first).at(p.second);
    FORA(v, dv)
    {
      P n(p.first + v.first, p.second + v.second);
      if (n.first < 0 || H <= n.first)
      {
        continue;
      }
      if (n.second < 0 || W <= n.second)
      {
        continue;
      }
      if (lines.at(n.first).at(n.second) == 'X')
      {
        continue;
      }
      if (g.first == n.first && g.second == n.second)
      {
        return t;
      }
      if (0 < times.at(n.first).at(n.second))
      {
        continue;
      }
      times.at(n.first).at(n.second) = t + 1;
      q.push(n);
    }
  }
  return -1;
}

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> H >> W >> N;
  lines.resize(H);
  goals.resize(N + 1);
  REP(i, H)
  {
    string line;
    cin >> line;
    lines.at(i) = line;
    ll j(-1);
    if ((j = line.find('S')) != string::npos)
    {
      goals.at(0) = {i, j};
    }
    FOR(n, 1, 10)
    {
      char c = '0' + n;
      if ((j = line.find(c)) != string::npos)
      {
        goals.at(n) = {i, j};
      }
    }
  }
  //
  ll ans(0);
  REP(i, N)
  {
    ans += bfs(goals.at(i), goals.at(i + 1));
  }
  pr(ans);
}
