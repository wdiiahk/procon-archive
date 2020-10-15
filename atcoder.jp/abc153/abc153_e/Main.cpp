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
  ll H;            // 1 <= H <= 10^4
  ll N;            // 1<= N <= 10^3
  vector<ll> A, B; // 1 <= A,B <=10^4
  Args()
  {
    cin >> H >> N;
    A = vll(N);
    B = vll(N);
    REP(i, N)
    {
      cin >> A.at(i) >> B.at(i);
    }
  }
};

class Solver
{
private:
  /* data */
  Args &args;
  ll ans;
  unordered_map<ll, ll> memo;
  ll hp_max;
  ll cnt;

public:
  Solver(Args &args) : args(args), ans(0), hp_max(1000), cnt(0)
  {
  }

  ll dfs(ll i, ll hp)
  {
    ++cnt;
    if (hp <= 0)
    {
      return 0;
    }
    if (i == args.N && 0 < hp)
    {
      return INF;
    }
    ll key = i * args.H + hp;
    if (memo.count(key))
    {
      return memo.at(key);
    }
    ll res = min(dfs(i + 1, hp), dfs(i, hp - args.A.at(i)) + args.B.at(i));
    /*
    ll res(INF);
    ll kmax = hp / args.A.at(i) + 1;
    REP(k, kmax)
    {
      ll res1 = dfs(i + 1, hp - k * args.A.at(i)) + args.B.at(i);
      chmin(res, res1);
    }
    */
    memo[key] = res;
    return res;
  }

  void solve()
  {
    REPD(i, args.N)
    {
      REP(hp, args.H + 1)
      {
        ans = dfs(i, hp);
      }
    }
    //ans = dfs(0, args.H);
  }
  void output()
  {
    pr(ans);
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
