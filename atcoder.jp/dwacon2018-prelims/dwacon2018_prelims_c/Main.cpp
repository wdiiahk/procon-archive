//デバッグ用オプション：-fsanitize=undefined,address

//コンパイラ最適化
// #pragma GCC optimize("Ofast")

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

/**
 * N 人のプレイヤーからなるAチームと、M 人のプレイヤーからなるBチームに分かれて戦闘を行います。
 * ニワンゴくんは、 killA と killB から必ずしも一意に deathA と deathB を復元できないことに気が付きました。
 * 与えられた killA と killB に矛盾しない deathA と deathB の組み合わせは何通りあるでしょうか？
 * 答えは非常に大きくなりうるので、 1,000,000,007(109+7) で割った余りを出力してください。
 */
struct Args
{
  ll N, M;
  vll A, B;
  ll total_A, total_B;
  map<ll, ll> groupA, groupB;

  Args()
  {
    cin >> N >> M;
    A = vll(N);
    total_A = 0;
    REP(i, N)
    {
      ll tmp;
      cin >> tmp;
      A.at(i) = tmp;
      total_A += tmp;
      ++groupA[tmp];
    }
    B = vll(M);
    total_B = 0;
    REP(i, M)
    {
      ll tmp;
      cin >> tmp;
      B.at(i) = tmp;
      total_B += tmp;
      ++groupB[tmp];
    }
  }
};

class Solver
{
private:
  /* data */
  Args &args;
  ll ans;
  arr<ll> rec;

public:
  Solver(Args &args) : args(args), ans(0)
  {
  }

  ll decomposition(ll n, ll m)
  {
    rec = arr<ll>(m + 1, vll(n + 1, 0));
    rec.at(0).at(0) = 1;
    FOR(i, 1, m + 1)
    {
      REP(j, n + 1)
      {
        if (0 <= j - i)
        {
          rec.at(i).at(j) = (rec.at(i - 1).at(j) + rec.at(i).at(j - i)) % MOD;
        }
        else
        {
          rec.at(i).at(j) = rec.at(i - 1).at(j);
        }
      }
    }
    return rec.at(m).at(n);
  }

  ll solve_by_dp(map<ll, ll> &group, ll total)
  {
    ll S = group.size();
    bool flip = false;
    vll dp0(total + 1, 0), dp1(total + 1, 0);
    dp0.at(0) = 1;
    FORA(p, group)
    {
      auto &cur = (flip) ? dp1 : dp0;
      auto &next = (flip) ? dp0 : dp1;
      flip = !flip;
      next = vll(total + 1, 0);
      REP(j, total + 1)
      {
        REP(k, j + 1)
        {
          next.at(j) += cur.at(k) * rec.at(p.second).at(j - k);
          next.at(j) %= MOD;
        }
      }
    }
    auto &cur = (flip) ? dp1 : dp0;
    return cur.at(total);
  }

  void solve()
  {
    ll group_max(0);
    FORA(p, args.groupA)
    {
      chmax(group_max, p.second);
    }
    FORA(p, args.groupB)
    {
      chmax(group_max, p.second);
    }
    ll total_max = max(args.total_A, args.total_B);
    decomposition(total_max + 1, group_max + 1);
    ll ans1 = solve_by_dp(args.groupA, args.total_B);
    ll ans2 = solve_by_dp(args.groupB, args.total_A);
    ans = (ans1 * ans2) % MOD;
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
