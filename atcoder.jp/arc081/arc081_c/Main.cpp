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

/**
 * 文字列 S に対して，その文字列を構成する文字を 0 文字以上取り除き，
 * 残った文字を元の順番で並べて得られる文字列を S の部分列と呼びます． 
 * たとえば，arc や artistic や (空文字列) は artistic の部分列ですが，
 * abc や ci は artistic の部分列ではありません．
 * 英小文字からなる文字列 Aが与えられます． 
 * このとき，英小文字からなる文字列で，A の部分列ではないようなもののうち，
 * 最も短いものを求めてください． 
 * 
 * ただし，そのようなものが複数ある場合には，辞書順で最小のものを求めてください．
 */
struct Args
{
  string A;
  ll N;
  Args()
  {
    cin >> A;
    N = A.length();
  }
};

class Solver
{
private:
  /* data */
  Args &args;
  string ans;
  arr<ll> next;
  /**
   * 【DP 定義】
   * dp[i] := i 文字目以降について「部分文字列とならない」最短の文字列長
   * (今までの通常の「部分文字列数え上げ DP」と異なり、必ずしも i 文字目自体を採用しなくてもよいです)
   * 
   * 【DP 遷移】
   * dp[i]= min_c(dp[next[i][c]+1]+1)
   * (ii 文字目以降について最初に選ぶべき文字の種類を 'a'〜'z' で場合分けしています)
   * 
   * 【DP 初期化】
   * dp[n]=1
   */
  vll dp;
  vector<char> recon;

public:
  Solver(Args &args) : args(args), ans("")
  {
    next.resize(args.N + 2, vll(26, args.N + 1));
    REPD(i, args.N)
    {
      REP(j, 26)
      {
        next.at(i).at(j) = next.at(i + 1).at(j);
      }
      next.at(i).at(args.A.at(i) - 'a') = i;
    }
    //
    dp.resize(args.N + 1, INF);
    recon.resize(args.N + 1, 'a');
  }

  void calc_dp()
  {
    dp.at(args.N) = 1;
    REPD(i, args.N)
    {
      REP(j, 26)
      {
        if (next.at(i).at(j) == args.N + 1)
        {
          if (1 < dp.at(i))
          {
            dp.at(i) = 1;
            recon.at(i) = 'a' + j;
          }
          continue;
        }
        //
        if (chmin(dp.at(i), dp.at(next.at(i).at(j) + 1) + 1))
        {
          recon.at(i) = 'a' + j;
        }
      }
    }
  }

  string get_ans()
  {
    string res = "";
    ll index = 0;
    while (index <= args.N)
    {
      res += recon[index];
      index = next.at(index).at(recon.at(index) - 'a') + 1;
    }
    return res;
  }

  void solve()
  {
    calc_dp();
    ans = get_ans();
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
