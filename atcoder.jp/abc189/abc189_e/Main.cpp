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
#define INF 1000000000000 //10^12:∞

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
  apply([&is](Ts &... tupleArgs) { ((is >> tupleArgs), ...); }, theTuple);
  return is;
}
template <typename... Ts>
ostream &operator<<(ostream &os, const tuple<Ts...> &theTuple)
{
  apply([&os](const Ts &... tupleArgs) {
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

template <typename T>
void reset(vector<T> &v, const T reset_to)
{
  for (auto &x : v)
    x = reset_to;
}
inline int popcount(const unsigned int x) { return __builtin_popcount(x); }

ll nC2(ll n)
{
  return n * (n - 1) / 2;
}

//const int intinf = numeric_limits<int>::max();
// const ll INF = numeric_limits<ll>::max();
const P udlr[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
//
//

struct Constants
{
  ll N, M, Q;
  ll a;
  Constants()
  {
    cin >> N;
  }
} C;

struct Args
{
  vp x;
  vp op;
  vp q;
  Args() : x(C.N)
  {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    REP(i, C.N)
    {
      cin >> x.at(i).first >> x.at(i).second;
    }
    cin >> C.M;
    op.resize(C.M);
    REP(i, C.M)
    {
      cin >> op.at(i).first;
      if (op.at(i).first == 3 || op.at(i).first == 4)
      {
        cin >> op.at(i).second;
      }
    }
    cin >> C.Q;
    q.resize(C.Q);
    REP(i, C.Q)
    {
      ll a, b;
      cin >> a >> b;
      q.at(i) = {a, b - 1};
    }
  }
} args;

struct Solver
{
  arr<ll> ans;
  vector<arr<ll>> acc;
  Solver() : ans(C.Q, vll(2)), acc(C.M + 1, arr<ll>(3, vll(3, 0)))
  {
    acc.at(0).at(0).at(0) = 1;
    acc.at(0).at(1).at(1) = 1;
    acc.at(0).at(2).at(2) = 1;
    REP(i, C.M)
    {
      auto op = args.op.at(i);
      arr<ll> c(3, vll(3));
      switch (op.first)
      {
      case 1:
        c.at(0).at(1) = 1;
        c.at(1).at(0) = -1;
        c.at(2).at(2) = 1;
        break;
      case 2:
        c.at(0).at(1) = -1;
        c.at(1).at(0) = 1;
        c.at(2).at(2) = 1;
        break;
      case 3:
        c.at(0).at(0) = -1;
        c.at(1).at(1) = 1;
        c.at(0).at(2) = 2 * op.second;
        c.at(2).at(2) = 1;
        break;
      case 4:
        c.at(0).at(0) = 1;
        c.at(1).at(1) = -1;
        c.at(1).at(2) = 2 * op.second;
        c.at(2).at(2) = 1;
        break;
      default:
        break;
      }
      REP(j, 3)
      {
        REP(k, 3)
        {
          REP(l, 3)
          {
            acc.at(i + 1).at(j).at(k) +=  c.at(j).at(l) * acc.at(i).at(l).at(k);
          }
        }
      }
    }
  }
  //
  void solve()
  {
    REP(i, C.Q)
    {
      auto q = args.q.at(i);
      auto p = args.x.at(q.second);
      vll v({p.first, p.second, 1});
      REP(j, 2)
      {
        REP(k, 3)
        {
          ans.at(i).at(j) += acc.at(q.first).at(j).at(k) * v.at(k);
        }
      }
    }
  }
  //
  void output()
  {
    prarr(ans);
  }
} s;

int main()
{
  s.solve();
  s.output();
  return 0;
}
