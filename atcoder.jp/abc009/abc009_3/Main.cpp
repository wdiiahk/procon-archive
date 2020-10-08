//デバッグ用オプション：-fsanitize=undefined,address

//コンパイラ最適化
#pragma GCC optimize("Ofast")

//インクルードなど
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

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

struct Args
{
  ll N; // 0 <= N <= 100
  ll K; // 0 <= K <= N
  string S;
  Args()
  {
    cin >> N >> K;
    cin >> S;
  }
};

class Solver
{
private:
  /* data */
  ll N;
  ll K;
  string S;
  vector<char> sorted;
  vector<char> alpha_list;

public:
  Solver(Args &args);
  ~Solver();
  string solve();
  void output(string res);
  ll diff_exactly(string lhs, vector<char> &rhs, int from, int to);
  ll diff(string lhs, vector<char> &rhs, int from, int to);
};

Solver::Solver(Args &args) : N(args.N), K(args.K), S(args.S), sorted(args.N), alpha_list(26)
{
  REP(i, args.N)
  {
    sorted.at(i) = S.at(i);
  }
  sort(ALL(sorted));
  REP(i, 26)
  {
    char c = 'a' + i;
    alpha_list.at(i) = c;
  }
}

Solver::~Solver()
{
}

ll Solver::diff_exactly(string lhs, vector<char> &rhs, int from, int to)
{
  ll ret(0);
  FOR(i, from, to)
  {
    if (lhs.at(i) != rhs.at(i))
    {
      ++ret;
    }
  }
  return ret;
}

ll Solver::diff(string lhs, vector<char> &rhs, int from, int to)
{
  unordered_map<char, ll> lhs_cnts, rhs_cnts;
  FOR(i, from, to)
  {
    lhs_cnts[lhs.at(i)]++;
    rhs_cnts[rhs.at(i)]++;
  }
  ll res(to - from);
  FORA(c, alpha_list)
  {
    ll m = min(lhs_cnts[c], rhs_cnts[c]);
    res -= m;
  }
  return res;
}

string Solver::solve()
{
  if (K == 0)
  {
    return S;
  }
  vector<ll> ans(N, -1);
  REP(i, N)
  {
    ll cur = i;
    bool is_found = false;
    REP(j, N)
    {
      if (0 <= ans.at(j))
      {
        continue;
      }
      vector<char> buf(N);
      ll remain = cur;
      ans.at(j) = cur;
      REP(k, N)
      {
        char c = sorted.at(k);
        ll idx = ans.at(k);
        if (idx < 0)
        {
          remain++;
          buf.at(remain) = c;
        }
        else
        {
          buf.at(idx) = c;
        }
      }
      ll diff01 = diff_exactly(S, buf, 0, cur + 1);
      ll diff02 = diff(S, buf, cur + 1, N);
      if (diff01 + diff02 <= K)
      {
        is_found = true;
        break;
      }
      ans.at(j) = -1;
    }
    if (!is_found)
    {
      break;
    }
  }
  vector<char> buf(N, '?');
  REP(i, N)
  {
    ll idx = ans.at(i);
    if (idx < 0)
    {
      buf.at(i) = '?';
    }
    else
    {
      buf.at(idx) = sorted.at(i);
    }
  }
  return string(ALL(buf));
}

void Solver::output(string res)
{
  cout << res << endl;
}

int main()

{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  Args args;
  Solver s(args);
  string res = s.solve();
  s.output(res);
}
