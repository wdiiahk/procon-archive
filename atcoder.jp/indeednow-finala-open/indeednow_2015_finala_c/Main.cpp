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

template <typename... Args>
std::string to_str_by(const std::string &fmt, Args... args)
{
  size_t len = std::snprintf(nullptr, 0, fmt.c_str(), args...);
  std::vector<char> buf(len + 1);
  std::snprintf(&buf[0], len + 1, fmt.c_str(), args...);
  return std::string(&buf[0], &buf[0] + len);
}

template <class T>
int popcount(T &a)
{
  int c = 0;
  REP(i, 8 * (int)sizeof(a))
  {
    if ((a >> i) & 1)
      c++;
  }
  return c;
}

template <class T>
void pl(T x) { cout << x << " "; }

template <class T>
void pr(T x) { cout << x << endl; }

template <class T>
void prvec(vector<T> &a)
{
  REP(i, a.size() - 1)
  {
    cout << a[i] << " ";
  }
  pr(a[a.size() - 1]);
}

template <class T>
void prarr(arr<T> &a)
{
  REP(i, a.size())
  if (a[i].empty())
    pr("");
  else
    prvec(a[i]);
}

using P = pair<ll, ll>;
void prp(P &p) { cout << p.first << " " << p.second << endl; }

struct Args
{
  ll N; // 1 <= N <= 50000
  ll M; // 1 <= M <= 50000
  vector<ll> a, b, c, w;
  vector<ll> x, y, z;
  Args()
  {
    cin >> N >> M;
    a = vector<ll>(N);
    b = vector<ll>(N);
    c = vector<ll>(N);
    w = vector<ll>(N);
    REP(i, N)
    {
      cin >> a.at(i) >> b.at(i) >> c.at(i) >> w.at(i);
    }
    x = vector<ll>(M);
    y = vector<ll>(M);
    z = vector<ll>(M);
    REP(i, M)
    {
      cin >> x.at(i) >> y.at(i) >> z.at(i);
    }
  }
};

/*
class Cooporate
{
  ll a;
  ll b;
  ll c;
  ll w;
}
*/

class Solver
{
private:
  /* data */
  Args &args;
  vector<ll> ans;
  ll abc_max;
  vector<arr<ll>> max_salary;
  vector<arr<ll>> memo;

public:
  Solver(Args &args)
      : args(args),
        ans(args.M, 0),
        abc_max(100),
        max_salary(abc_max + 1, arr<ll>(abc_max + 1, vll(abc_max + 1, 0))),
        memo(abc_max + 1, arr<ll>(abc_max + 1, vll(abc_max + 1, 0)))
  {
    REP(i, args.N)
    {
      ll a = args.a.at(i);
      ll b = args.b.at(i);
      ll c = args.c.at(i);
      ll w = args.w.at(i);
      chmax(max_salary[a][b][c], w);
    }
    //
  }

  ll dfs(ll a, ll b, ll c)
  {
    cout << a << ", " << b << ", " << c << endl;
    if (0 < memo.at(a).at(b).at(c))
    {
      return memo.at(a).at(b).at(c);
    }
    ll res;
    if (a == 0 && b == 0 && c == 0)
    {
      res = max_salary.at(a).at(b).at(c);
      memo.at(a).at(b).at(c) = res;
      return res;
    }
    else
    {
      if (0 < a)
      {
        chmax(max_salary.at(a).at(b).at(c), dfs(a - 1, b, c));
      }
      if (0 < b)
      {
        chmax(max_salary.at(a).at(b).at(c), dfs(a, b - 1, c));
      }
      if (0 < c)
      {
        chmax(max_salary.at(a).at(b).at(c), dfs(a, b, c - 1));
      }
      res = max_salary.at(a).at(b).at(c);
      memo.at(a).at(b).at(c) = res;
    }
    return res;
  }

  void solve()
  {
    // dfs(abc_max, abc_max, abc_max);
    REP(i, abc_max + 1)
    {
      REP(j, abc_max + 1)
      {
        REP(k, abc_max + 1)
        {
          if (0 < i)
          {
            chmax(max_salary[i][j][k], max_salary[i - 1][j][k]);
          }
          if (0 < j)
          {
            chmax(max_salary[i][j][k], max_salary[i][j - 1][k]);
          }
          if (0 < k)
          {
            chmax(max_salary[i][j][k], max_salary[i][j][k - 1]);
          }
        }
      }
    }
    //
    REP(i, args.M)
    {
      ll x = args.x.at(i);
      ll y = args.y.at(i);
      ll z = args.z.at(i);
      ans.at(i) = max_salary.at(x).at(y).at(z);
    }
  }

  void output()
  {
    FORA(a, ans)
    {
      pr(a);
    }
  }
};

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  Args args;
  Solver s(args);
  s.solve();
  s.output();
}
