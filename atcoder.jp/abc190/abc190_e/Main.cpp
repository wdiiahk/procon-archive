//デバッグ用オプション：-fsanitize=undefined,address

//コンパイラ最適化
#pragma GCC optimize("Ofast")

//インクルードなど
#include <bits/stdc++.h>
#include <atcoder/all>

using namespace std;
using namespace atcoder;

typedef long long ll;
using vint = vector<int>;
using vll = vector<ll>;
using vbool = vector<bool>;
using vs = vector<string>;
using P = pair<ll, ll>;
using vp = vector<P>;
template <class T>
using arr = vector<vector<T>>;

//マクロ
#define REP(i, n) for (ll i = 0; i < ll(n); i++)
#define REPD(i, n) for (ll i = n - 1; i >= 0; i--)
#define FOR(i, a, b) for (ll i = a; i < ll(b); i++)
#define FORD(i, a, b) for (ll i = a; i >= ll(b); i--)
#define FORA(i, I) for (const auto &i : I)
#define ALL(x) x.begin(), x.end()
#define SIZE(x) ll(x.size())
#define INF 100000000000000

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

template <typename T1, typename T2>
pair<T1, T2> operator+(const pair<T1, T2> &l, const pair<T1, T2> &r) { return {l.first + r.first, l.second + r.second}; }
template <typename T1, typename T2>
pair<T1, T2> operator-(const pair<T1, T2> &l, const pair<T1, T2> &r) { return {l.first - r.first, l.second - r.second}; }
template <typename T>
pair<T, T> operator*(const pair<T, T> &l, const T &r) { return {l.first * r, l.second * r}; }
template <typename T>
pair<T, T> operator/(const pair<T, T> &l, const T &r) { return {l.first / r, l.second / r}; }

template <typename T>
istream &operator>>(istream &is, vector<T> &vec)
{
  for (auto &v : vec)
    is >> v;
  return is;
}
template <typename T>
ostream &operator<<(ostream &os, const vector<T> &vec)
{
  os << "[";
  for (auto v : vec)
    os << v << ",";
  os << "]";
  return os;
}

template <typename T>
ostream &operator<<(ostream &os, const deque<T> &vec)
{
  os << "deq[";
  for (auto v : vec)
    os << v << ",";
  os << "]";
  return os;
}

template <typename T>
ostream &operator<<(ostream &os, const set<T> &vec)
{
  os << "{";
  for (auto v : vec)
    os << v << ",";
  os << "}";
  return os;
}

template <typename T>
ostream &operator<<(ostream &os, const unordered_set<T> &vec)
{
  os << "{";
  for (auto v : vec)
    os << v << ",";
  os << "}";
  return os;
}
template <typename T>
ostream &operator<<(ostream &os, const multiset<T> &vec)
{
  os << "{";
  for (auto v : vec)
    os << v << ",";
  os << "}";
  return os;
}
template <typename T>
ostream &operator<<(ostream &os, const unordered_multiset<T> &vec)
{
  os << "{";
  for (auto v : vec)
    os << v << ",";
  os << "}";
  return os;
}
template <typename T1, typename T2>
istream &operator>>(istream &is, pair<T1, T2> &pa)
{
  is >> pa.first >> pa.second;
  return is;
}
template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &pa)
{
  os << "(" << pa.first << "," << pa.second << ")";
  return os;
}
template <typename... Ts>
istream &operator>>(istream &is, tuple<Ts...> &theTuple)
{
  apply([&is](Ts &...tupleArgs) { ((is >> tupleArgs), ...); }, theTuple);
  return is;
}
template <typename... Ts>
ostream &operator<<(ostream &os, const tuple<Ts...> &theTuple)
{
  apply([&os](const Ts &...tupleArgs) {
    os << '(';
    size_t n(0);
    ((os << tupleArgs << (++n < sizeof...(Ts) ? "," : "")), ...);
    os << ')';
  },
        theTuple);
  return os;
}
template <typename TK, typename TV>
ostream &operator<<(ostream &os, const map<TK, TV> &mp)
{
  os << "{";
  for (auto v : mp)
    os << v.first << "=>" << v.second << ",";
  os << "}";
  return os;
}
template <typename TK, typename TV>
ostream &operator<<(ostream &os, const unordered_map<TK, TV> &mp)
{
  os << "{";
  for (auto v : mp)
    os << v.first << "=>" << v.second << ",";
  os << "}";
  return os;
}

struct Constants
{
  ll N, M;
  ll K;
  Constants()
  {
    cin >> N >> M;
  }
} C;

struct Args
{
  arr<ll> edge;
  Args() : edge(C.N)
  {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    REP(i, C.M)
    {
      ll a, b;
      cin >> a >> b;
      a--;
      b--;
      edge.at(a).push_back(b);
      edge.at(b).push_back(a);
    }
    cin >> C.K;
  }
} args;

struct Solver
{
  ll ans;
  vll c;
  arr<ll> dp;
  map<P, ll> memo;
  Solver() : ans(INF), c(C.K), dp(1 << C.K, vll(C.K, INF))
  {
    cin >> c;
    for (auto &a : c)
    {
      a--;
    }
  }

  vll bfs(ll s)
  {
    vll cost(C.N, INF);
    queue<ll> q;
    q.push(s);
    cost.at(s) = 0;
    while (!q.empty())
    {
      auto p = q.front();
      q.pop();
      FORA(to, args.edge.at(p))
      {
        if (chmin(cost.at(to), cost.at(p) + 1))
        {
          q.push(to);
        }
      }
    }
    REP(i, C.K)
    {
      cost.at(i) = cost.at(c.at(i));
    }
    cost.resize(C.K);
    return cost;
  }

  //
  void solve()
  {
    arr<ll> dist(C.K);
    REP(i, C.K)
    {
      dist.at(i) = bfs(c.at(i));
    }
    dp.at(0).at(0) = 0;
    REP(i, C.K)
    {
      dp.at(1 << i).at(i) = 1;
    }
    FOR(S, 1, 1 << C.K)
    {
      REP(j, C.K)
      {
        ll mask = (1 << j);
        if ((S & mask) != mask)
        {
          continue;
        }
        REP(k, C.K)
        {
          if (j == k)
          {
            continue;
          }
          ll mask2 = (1 << k);
          if ((S & mask2) != mask2)
          {
            continue;
          }
          ll d = dist.at(k).at(j);
          chmin(dp.at(S).at(j), dp.at(S ^ mask).at(k) + d);
        }
      }
    }
    ll S(1 << C.K);
    S--;
    ans = *min_element(ALL(dp.at(S)));
    if (ans == INF)
    {
      ans = -1;
    }
  }
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
