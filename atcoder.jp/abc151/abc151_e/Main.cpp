//デバッグ用オプション：-fsanitize=undefined,address

//コンパイラ最適化
#pragma GCC optimize("Ofast")

//インクルードなど
#include <bits/stdc++.h>
#include <atcoder/all>

using namespace std;
using namespace atcoder;

namespace
{

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

  //
  template <typename T>
  void for_enum(T &container, std::function<bool(int, typename T::value_type &)> op)
  {
    int idx = 0;
    for (auto &value : container)
    {
      if (!op(idx++, value))
      {
        break;
      }
    }
  }

  template <typename S, typename T>
  map<S, T> group_by(T &container, std::function<S(typename T::value_type &)> op)
  {
    map<S, T> grouped;
    for (auto &value : container)
    {
      grouped[op(value)].push_back(value);
    }
    return grouped;
  }

  template <class Container, class Transform>
  Container fmap(const Container &c, Transform f)
  {
    Container r;
    r.reserve(c.size());
    transform(ALL(c), back_inserter(r), f);
    return r;
  }

  template <class Container, class Predicate>
  Container ffilter(const Container &c, Predicate f)
  {
    Container r;
    std::copy_if(ALL(c), back_inserter(r), f);
    return r;
  }

  template <class Container, class InitialT, class BinaryOp>
  InitialT freduce(const Container &c, InitialT v, BinaryOp op)
  {
    return accumulate(ALL(c), v, op);
  }

} // namespace
// const P udlr[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

struct Constants
{
  ll N, K;
  Constants()
  {
    cin >> N >> K;
  }
} C;

struct Args
{
  vll a;
  Args() : a(C.N)
  {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> a;
    sort(ALL(a));
  }
} args;

using mint = modint1000000007;

struct Solver
{
  ll ans;
  vector<mint> facts;
  Solver() : ans(0), facts(C.N + 1)
  {
    facts.at(0) = 1;
    facts.at(1) = 1;
    FOR(i, 2, C.N + 1)
    {
      facts.at(i) = facts.at(i - 1) * i;
    }
  }
  ll nCk(ll n, ll k)
  {
    if (n == 0 || k == 0)
    {
      return 1;
    }
    mint res = facts.at(n) * (facts.at(k).inv()) * (facts.at(n - k).inv());
    return res.val();
  }

  //
  void solve()
  {
    if (C.N == 1 || C.K == 1)
    {
      return;
    }
    vector<mint> acc(C.N + 1, 0);
    REP(i, C.N)
    {
      acc.at(i + 1) = acc.at(i) + args.a.at(i);
    }

    mint res(0);
    FOR(len, C.K - 2, C.N - 1)
    {
      ll k = (C.K - 2);
      ll fac = nCk(len, k);
      mint p = acc.at(C.N) - acc.at(len + 1);
      mint m = acc.at(C.N - len - 2 + 1);
      res += fac * (p - m);
      /*
      REP(l, C.N - C.K + 1)
      {
        ll r = len + l + 1;
        if (C.N <= r)
        {
          break;
        }
        res += fac * (args.a.at(r) - args.a.at(l));
      }
      */
    }
    ans = res.val();
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
