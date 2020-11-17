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

struct Edge
{
  ll to;
};

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll N, M, K, S;
  cin >> N >> M >> K >> S;
  ll PP, Q;
  cin >> PP >> Q;
  vll costs(N, PP);
  //
  set<ll> C;
  REP(i, K)
  {
    ll c;
    cin >> c;
    c--;
    C.insert(c);
    costs.at(c) = INF;
  }
  arr<Edge> edges(N);
  arr<Edge> edges2(N);
  REP(i, M)
  {
    ll a, b;
    cin >> a >> b;
    a--;
    b--;
    if (C.count(a) == 0 && C.count(b) == 0)
    {
      edges.at(a).push_back({b});
      edges.at(b).push_back({a});
    }
    else
    {
      edges2.at(a).push_back({b});
      edges2.at(b).push_back({a});
    }
  }
  // bfs
  set<ll> unsafe;
  if (0 < S)
  {
    FORA(c, C)
    {
      FORA(e, edges2.at(c))
      {
        unsafe.insert(e.to);
      }
    }
  }
  //
  queue<P> q;
  FORA(n, unsafe)
  {
    q.push({n, 1});
    costs.at(n) = Q;
  }
  while (!q.empty())
  {
    auto p = q.front();
    if (S == p.second)
    {
      break;
    }
    q.pop();
    FORA(e, edges.at(p.first))
    {
      if (costs.at(e.to) == Q)
      {
        continue;
      }
      costs.at(e.to) = Q;
      q.push({e.to, p.second + 1});
    }
  }
  //
  priority_queue<P, vector<P>, greater<P>> pq;
  vll d(N, INF);
  d.at(0) = 0;
  pq.push({0, 0});
  bool goal(false);
  while (!goal && !pq.empty())
  {
    P p = pq.top();
    pq.pop();
    ll n0 = p.second;
    if (d.at(n0) < p.first)
    {
      continue;
    }
    FORA(e, edges.at(n0))
    {
      if (e.to == N - 1)
      {
        d.at(e.to) = d.at(n0);
        goal = true;
        break;
      }
      if (chmin(d.at(e.to), d.at(n0) + costs.at(e.to)))
      {
        pq.push({d.at(e.to), e.to});
      }
    }
  }
  //
  ll ans(d.at(N - 1));
  pr(ans);

  return 0;
}
