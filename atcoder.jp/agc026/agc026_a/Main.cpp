#include <bits/stdc++.h>
//#include <atcoder/all>
//
using namespace std;
//using namespace atcoder;
//
using ll = long long;
using ld = long double;
using ull = unsigned long long;
using uint = unsigned int;
using pcc = pair<char, char>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pdd = pair<double, double>;
using tuplis = array<ll, 3>;
using vll = vector<ll>;
template <class T>
using arr = vector<vector<T>>;
template <class T>
using pq = priority_queue<T, vector<T>, greater<T>>;
const ll LINF = 0x1fffffffffffffff;
const ll MINF = 0x7fffffffffff;
const int INF = 0x3fffffff;
const int MOD = 1000000007;
const int MODD = 998244353;
const ld DINF = numeric_limits<ld>::infinity();
const ld EPS = 1e-9;
const ld PI = 3.1415926535897932;
const ll four[] = {0, 1, 0, -1, 0};
const ll eight[] = {0, 1, 1, 0, -1, -1, 1, -1, 0};
#define overload4(_1, _2, _3, _4, name, ...) name
#define overload3(_1, _2, _3, name, ...) name
#define rep1(n) for (ll i = 0; i < n; ++i)
#define rep2(i, n) for (ll i = 0; i < n; ++i)
#define rep3(i, a, b) for (ll i = a; i < b; ++i)
#define rep4(i, a, b, c) for (ll i = a; i < b; i += c)
#define REP(...) overload4(__VA_ARGS__, rep4, rep3, rep2, rep1)(__VA_ARGS__)
#define rrep1(n) for (ll i = (n)-1; i >= 0; i--)
#define rrep2(i, n) for (ll i = (n)-1; i >= 0; i--)
#define rrep3(i, a, b) for (ll i = (b)-1; i >= (a); i--)
#define rrep4(i, a, b, c) for (ll i = a + (b - a - 1) / c * c; i >= a; i -= c)
#define RREP(...) overload4(__VA_ARGS__, rrep4, rrep3, rrep2, rrep1)(__VA_ARGS__)
#define EACH(i, ...) for (auto &&i : __VA_ARGS__)
#define all1(i) begin(i), end(i)
#define all2(i, a) begin(i), begin(i) + a
#define all3(i, a, b) begin(i) + a, begin(i) + b
#define ALL(...) overload3(__VA_ARGS__, all3, all2, all1)(__VA_ARGS__)
#define rall1(i) (i).rbegin(), (i).rend()
#define rall2(i, k) (i).rbegin(), (i).rbegin() + k
#define rall3(i, a, b) (i).rbegin() + a, (i).rbegin() + b
#define RALL(...) overload3(__VA_ARGS__, rall3, rall2, rall1)(__VA_ARGS__)
#define SUM(...) accumulate(all(__VA_ARGS__), 0LL)
#define DSUM(...) accumulate(all(__VA_ARGS__), 0.0L)
#define elif else if
#define unless(a) if (!(a))
#define mp make_pair
#define mt make_tuple
#define INT(...)   \
  int __VA_ARGS__; \
  in(__VA_ARGS__)
#define LL(...)   \
  ll __VA_ARGS__; \
  in(__VA_ARGS__)
#define ULL(...)   \
  ull __VA_ARGS__; \
  in(__VA_ARGS__)
#define STR(...)      \
  string __VA_ARGS__; \
  in(__VA_ARGS__)
#define CHR(...)    \
  char __VA_ARGS__; \
  in(__VA_ARGS__)
#define DBL(...)      \
  double __VA_ARGS__; \
  in(__VA_ARGS__)
#define LD(...)   \
  ld __VA_ARGS__; \
  in(__VA_ARGS__)
#define Sort(a) sort(ALL(a))
#define Rev(a) reverse(ALL(a))
#define Uniq(a) \
  sort(ALL(a)); \
  a.erase(unique(ALL(a)), end(a))
template <class T>
auto max(const T &a)
{
  return *max_element(all(a));
}
template <class T>
auto min(const T &a) { return *min_element(all(a)); }
ll gcd(ll a, ll b)
{
  while (b)
  {
    ll c = b;
    b = a % b;
    a = c;
  }
  return a;
}
ll lcm(ll a, ll b)
{
  if (!a || !b)
    return 0;
  return a * b / gcd(a, b);
}
ll intpow(ll a, ll b)
{
  ll ans = 1;
  while (b)
  {
    if (b & 1)
      ans *= a;
    a *= a;
    b /= 2;
  }
  return ans;
}
ll modpow(ll a, ll b, ll p)
{
  ll ans = 1;
  while (b)
  {
    if (b & 1)
      (ans *= a) %= p;
    (a *= a) %= p;
    b /= 2;
  }
  return ans;
}
template <class T>
bool chmin(T &a, const T &b)
{
  if (a > b)
  {
    a = b;
    return 1;
  }
  return 0;
}
template <class T>
bool chmax(T &a, const T &b)
{
  if (a < b)
  {
    a = b;
    return 1;
  }
  return 0;
}
vector<pll> factor(ull x)
{
  vector<pll> ans;
  for (ll i = 2; i * i <= x; i++)
    if (x % i == 0)
    {
      ans.push_back({i, 1});
      while ((x /= i) % i == 0)
        ans.back().second++;
    }
  if (x != 1)
    ans.push_back({x, 1});
  return ans;
}
vector<ll> divisor(ull x)
{
  vector<ll> ans;
  for (ll i = 1; i * i <= x; i++)
  {
    if (x % i == 0)
    {
      ans.push_back(i);
    }
  }
  RREP(ans.size() - (ans.back() * ans.back() == ll(x)))
  ans.push_back(x / ans[i]);
  return ans;
}
template <class T>
unordered_map<T, ll> press(vector<T> &a)
{
  auto b = a;
  sort(all(b));
  b.erase(unique(all(b)), b.end());
  unordered_map<T, ll> ans;
  REP(b.size())
  ans[b[i]] = i;
  EACH(i, a)
  i = ans[i];
  return ans;
}
template <class T>
map<T, ll> press_map(vector<T> &a)
{
  auto b = a;
  sort(all(b));
  b.erase(unique(all(b)), b.end());
  map<T, ll> ans;
  REP(b.size())
  ans[b[i]] = i;
  EACH(i, a)
  i = ans[i];
  return ans;
}
int scan() { return getchar(); }
void scan(int &a)
{
  if (scanf("%d", &a) != 1)
  {
    printf("input error");
    exit(1);
  }
}
void scan(unsigned &a)
{
  if (scanf("%u", &a) != 1)
  {
    printf("input error");
    exit(1);
  }
}
void scan(long &a)
{
  if (scanf("%ld", &a) != 1)
  {
    printf("input error");
    exit(1);
  }
}
void scan(long long &a)
{
  if (scanf("%lld", &a) != 1)
  {
    printf("input error");
    exit(1);
  }
}
void scan(unsigned long long &a)
{
  if (scanf("%llu", &a) != 1)
  {
    printf("input error");
    exit(1);
  }
}
void scan(char &a)
{
  do
  {
    a = getchar();
  } while (a == ' ' || a == '\n');
}
void scan(float &a)
{
  if (scanf("%f", &a) != 1)
  {
    printf("input error");
    exit(1);
  }
}
void scan(double &a)
{
  if (scanf("%lf", &a) != 1)
  {
    printf("input error");
    exit(1);
  }
}
void scan(long double &a)
{
  if (scanf("%Lf", &a) != 1)
  {
    printf("input error");
    exit(1);
  }
}
void scan(vector<bool> &a)
{
  for (unsigned i = 0; i < a.size(); i++)
  {
    int b;
    scan(b);
    a[i] = b;
  }
}
void scan(char a[])
{
  if (scanf("%s", a) != 1)
  {
    printf("input error");
    exit(1);
  }
}
void scan(string &a) { cin >> a; }
template <class T>
void scan(vector<T> &);
template <class T, size_t size>
void scan(array<T, size> &);
template <class T, class L>
void scan(pair<T, L> &);
template <class T, size_t size>
void scan(T (&)[size]);
template <class T>
void scan(vector<T> &a)
{
  for (auto &&i : a)
    scan(i);
}
template <class T>
void scan(deque<T> &a)
{
  for (auto &&i : a)
    scan(i);
}
template <class T, size_t size>
void scan(array<T, size> &a)
{
  for (auto &&i : a)
    scan(i);
}
template <class T, class L>
void scan(pair<T, L> &p)
{
  scan(p.first);
  scan(p.second);
}
template <class T, size_t size>
void scan(T (&a)[size])
{
  for (auto &&i : a)
    scan(i);
}
template <class T>
void scan(T &a) { cin >> a; }
void in() {}
template <class Head, class... Tail>
void in(Head &head, Tail &...tail)
{
  scan(head);
  in(tail...);
}
void print() { putchar(' '); }
void print(bool a) { printf("%d", a); }
void print(int a) { printf("%d", a); }
void print(unsigned a) { printf("%u", a); }
void print(long a) { printf("%ld", a); }
void print(long long a) { printf("%lld", a); }
void print(unsigned long long a) { printf("%llu", a); }
void print(char a) { printf("%c", a); }
void print(char a[]) { printf("%s", a); }
void print(const char a[]) { printf("%s", a); }
void print(float a) { printf("%.15f", a); }
void print(double a) { printf("%.15f", a); }
void print(long double a) { printf("%.15Lf", a); }
void print(const string &a)
{
  for (auto &&i : a)
    print(i);
}
template <class T>
void print(const vector<T> &);
template <class T, size_t size>
void print(const array<T, size> &);
template <class T, class L>
void print(const pair<T, L> &p);
template <class T, size_t size>
void print(const T (&)[size]);
template <class T>
void print(const vector<T> &a)
{
  if (a.empty())
    return;
  print(a[0]);
  for (auto i = a.begin(); ++i != a.end();)
  {
    putchar(' ');
    print(*i);
  }
}
template <class T>
void print(const deque<T> &a)
{
  if (a.empty())
    return;
  print(a[0]);
  for (auto i = a.begin(); ++i != a.end();)
  {
    putchar(' ');
    print(*i);
  }
}
template <class T, size_t size>
void print(const array<T, size> &a)
{
  print(a[0]);
  for (auto i = a.begin(); ++i != a.end();)
  {
    putchar(' ');
    print(*i);
  }
}
template <class T, class L>
void print(const pair<T, L> &p)
{
  print(p.first);
  putchar(' ');
  print(p.second);
}
template <class T, size_t size>
void print(const T (&a)[size])
{
  print(a[0]);
  for (auto i = a; ++i != end(a);)
  {
    putchar(' ');
    print(*i);
  }
}
template <class T>
void print(const T &a) { cout << a; }
int out()
{
  putchar('\n');
  return 0;
}
template <class T>
int out(const T &t)
{
  print(t);
  putchar('\n');
  return 0;
}
template <class Head, class... Tail>
int out(const Head &head, const Tail &...tail)
{
  print(head);
  putchar(' ');
  out(tail...);
  return 0;
}
#ifdef DEBUG
void err()
{
  putchar('\n');
}
template <class T>
void err(const T &t)
{
  print(t);
  putchar('\n');
}
template <class Head, class... Tail>
void err(const Head &head, const Tail &...tail)
{
  print(head);
  putchar(' ');
  out(tail...);
}
#else
template <class... T>
void err(const T &...)
{
}
#endif
int first(bool i = true)
{
  return out(i ? "first" : "second");
}
int yes(bool i = true) { return out(i ? "yes" : "no"); }
int Yes(bool i = true) { return out(i ? "Yes" : "No"); }
int No() { return out("No"); }
int YES(bool i = true) { return out(i ? "YES" : "NO"); }
int NO() { return out("NO"); }
int Yay(bool i = true) { return out(i ? "Yay!" : ":("); }
int possible(bool i = true) { return out(i ? "possible" : "impossible"); }
int Possible(bool i = true) { return out(i ? "Possible" : "Impossible"); }
int POSSIBLE(bool i = true) { return out(i ? "POSSIBLE" : "IMPOSSIBLE"); }
void Case(ll i) { printf("Case #%lld: ", i); }

struct Constants
{
  ll N;
  Constants()
  {
    in(N);
  }
} C;

struct Args
{
  vll a;
  Args() : a(C.N)
  {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    in(a);
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
    vector<pii> datas;
    ll l(0);
    while (l < C.N)
    {
      ll r = l;
      ll t = args.a.at(l);
      while (r < C.N && args.a.at(r) == t)
      {
        r++;
      }
      datas.emplace_back(t, r - l);
      l = r;
    }
    EACH(p, datas)
    {
      if (p.second < 2)
      {
        continue;
      }
      ans += (p.second) / 2;
    }
  }
  //
  void output()
  {
    out(ans);
  }
} s;

int main()
{
  s.solve();
  s.output();
  return 0;
}
