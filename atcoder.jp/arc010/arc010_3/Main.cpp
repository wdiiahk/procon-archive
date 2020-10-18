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
using vchar = vector<char>;
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
 * m 色のブロックが n 個、1 つずつ順番に落ちてきます。
 * 1 つ落ちてくるたびに、高橋君は落ちてきたそのブロックを取って山に積むか、積まずに捨てるか選べます。
 * ブロックを積む山は 1 つで、ブロックは必ず山の一番上に積まないといけません。
 * 全てのブロックが落ちきった後、出来た山は以下のように評価されます。
 * 
 *     色ボーナス：色ごとに決められた得点が、山に含まれている個数分与えられます。
 *     コンボボーナス：同じ色のブロックが x
 * 
 * 個続いて積まれている場合、コンボボーナス配点 Y に応じて Y×(x−1)
 * 点が与えられます。
 * 全色ボーナス：山の中に m
 * 色のブロックがそれぞれ 1 個以上含まれていると Z
 * 
 *     点が与えられます。
 * 
 * 落ちてくるブロックの種類と順番、またそれぞれ山を評価するための配点が与えられたとき、評価で得ることのできる最高得点を求めなさい。 
 */
struct Args
{
  /**
   * 1 行目に n,m,Y,Z が半角スペースで区切られて与えられる。
   * - nはブロックの個数で 1≦n≦5,000 を満たす。
   * - mはブロックの色の総数で 1≦m≦10 を満たす。
   * - Yはコンボボーナス配点で −100≦Y≦100
   * を満たす。
   * Zは全色ボーナス配点で −10,000≦Z≦10,000を満たす。
   * n,m,Y,Zは全て整数である。
   */
  ll n, m, Y, Z;
  /**
   * 2 行目からの m+1 行目までの m 行で色ボーナスの配点がそれぞれ与えられる。
   * - ciは i(1≦i≦m)番目に与えられるブロックの色である。
   * - piは ciに対する色ボーナスの配点である。
   * - ciは英大文字(A-Z)、pi は −100≦pi≦100を満たす。
   * 配点は重複して与えられない（x≠yならば cx≠cy)
   */
  string colors;
  vll p;
  /**
   * m+2 行目には落ちてくるブロックの順序を表す長さ n の文字列が与えられる。
   * bjは j(1≦j≦n)番目に落ちてくるブロックの色を表している。
   * bjは c1,c2,...,cm のいずれかである。
   */
  string b;
  Args()
  {
    cin >> n >> m >> Y >> Z;
    vchar c = vchar(m);
    p = vll(m);
    REP(i, m)
    {
      cin >> c.at(i) >> p.at(i);
    }
    colors = string(ALL(c));
    cin >> b;
  }
};

class Solver
{
private:
  /* data */
  Args &args;
  ll ans;
  ll state_total;
  bool flip;
  /**
   * dp[i][j]: i, 使用した色の状態(bitDP)、j: 直前の色
   */
  arr<ll> dp0, dp1;

public:
  Solver(Args &args)
      : args(args), ans(0), state_total(1 << args.m), flip(false)
  {
    dp0 = arr<ll>(state_total, vll(args.m, -INF));
    dp1 = arr<ll>(state_total, vll(args.m, -INF));
  }

  bool is_one(ll a, ll b)
  {
    return (a >> b) % 2 == 1;
  }

  ll color2idx(char c)
  {
    return args.colors.find(c);
  }

  ll solve_by_dp()
  {
    dp0.at(0).at(0) = 0;
    FORA(c, args.b)
    {
      auto &cur = (flip) ? dp1 : dp0;
      auto &next = (flip) ? dp0 : dp1;
      next = arr<ll>(state_total, vll(args.m, -INF));
      flip = !flip;
      ll cidx = color2idx(c);
      REP(i, state_total)
      {
        REP(j, args.m)
        {
          if (cur.at(i).at(j) == -INF)
          {
            continue;
          }
          // 捨てた時、直前の色はjのまま
          chmax(next.at(i).at(j), cur.at(i).at(j));
          //
          ll pt = cur.at(i).at(j);
          pt += args.p.at(cidx);
          if (i != 0 && j == cidx)
          {
            pt += args.Y;
          }
          ll nexti = i | (1 << cidx);
          chmax(next.at(nexti).at(cidx), pt);
        }
      }
    }
    auto &cur = (flip) ? dp1 : dp0;
    REP(j, args.m)
    {
      if (cur.at(state_total - 1).at(j) == -INF)
      {
        continue;
      }
      cur.at(state_total - 1).at(j) += args.Z;
    }
    //
    ll ret(0);
    REP(i, state_total)
    {
      REP(j, args.m)
      {
        chmax(ret, cur.at(i).at(j));
      }
    }
    return ret;
  }

  void solve()
  {
    ans = solve_by_dp();
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
