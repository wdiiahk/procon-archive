//デバッグ用オプション：-fsanitize=undefined,address

//コンパイラ最適化
#pragma GCC optimize("Ofast")

//インクルードなど
#include <bits/stdc++.h>
//#include <atcoder/all>

using namespace std;
//using namespace atcoder;

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
  ll N;
  string K;
  Constants()
  {
    cin >> K;
    N = K.length();
  }
} C;

struct Args
{
  Args()
  {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
  }
} args;

struct Solver
{
  ll ans;
  arr<vll> dp;
  Solver() : ans(0), dp(C.N + 1, arr<ll>(2, vll(1 << 3, 0)))
  {
  }
  //
  void solve()
  {
    /*
    arr<ll> aa(C.N + 1, vll(2, 0));
    aa.at(0).at(0) = 1;
    const ll exact(0), smaller(1);
    FOR(digit, 1, C.N + 1)
    {
      ll x = C.K.at(digit - 1) - '0';
      // smaller -> smaller
      REP(n, 10)
      {
        aa.at(digit).at(smaller) += aa.at(digit - 1).at(smaller);
      }
      // exact -> smaller
      REP(n, x)
      {
        aa.at(digit).at(smaller) += aa.at(digit - 1).at(exact);
      }
      // exact -> exact
      aa.at(digit).at(exact) += aa.at(digit - 1).at(exact);
    }
    */
    const vll nlist({3, 5, 7});
    const ll exact(0), smaller(1);
    dp.at(0).at(exact).at(0) = 1;
    FOR(digit, 1, C.N + 1)
    {
      dp.at(digit).at(smaller).at(0) = 1;
    }

    FOR(digit, 1, C.N + 1)
    {
      ll x = C.K.at(digit - 1) - '0';
      // smaller -> smaller
      REP(j, 3)
      {
        ll mask = (1 << j);
        REP(S, 1 << 3)
        {
          dp.at(digit).at(smaller).at(S | mask) += dp.at(digit - 1).at(smaller).at(S);
        }
      }
      // exact -> smaller
      REP(j, 3)
      {
        if (x <= nlist.at(j))
        {
          continue;
        }
        ll mask = (1 << j);
        REP(S, 1 << 3)
        {
          dp.at(digit).at(smaller).at(S | mask) += dp.at(digit - 1).at(exact).at(S);
        }
      }
      // exact -> exact
      REP(j, 3)
      {
        if (x != nlist.at(j))
        {
          continue;
        }
        ll mask = (1 << j);
        REP(S, 1 << 3)
        {
          dp.at(digit).at(exact).at(S | mask) += dp.at(digit - 1).at(exact).at(S);
        }
      }
    }
    ll S(1 << 3);
    S--;
    ans += dp.at(C.N).at(exact).at(S);
    ans += dp.at(C.N).at(smaller).at(S);
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
