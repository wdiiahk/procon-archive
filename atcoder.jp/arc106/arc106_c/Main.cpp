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
void prp(const P &p) { cout << p.first << " " << p.second << endl; }

/**
 * 2 つの区間 [L1:R1],[L2:R2] について, L1≤R2 かつ L2≤R1 であるとき, 
 * この 2つの区間が交わると定義します。
 * 以下の問題 P を考えます。
 * 
 * 入力: N  個の区間 [L1:R1],⋯,[LN:RN] 
 *      L1,L2,⋯,LN,R1,R2,⋯,RN は全て異なる。
 * 出力: どの 2 つの区間も交わらないように選べる区間の最大数
 * 
 * 高橋君は、以下のように動作するプログラムを実装しました。
 * 
 * Ri の値が昇順となるように, 入力された区間を 
 * [Lp1:Rp1],[Lp2:Rp2],⋯,[LpN:RpN] と並び替える。 
 * i=1,2,⋯,N について、以下を行う。
 * これまでに選んだどの区間とも交わらないならば、 [Lpi:Rpi] を選ぶ。
 * 選んだ区間の数を出力する。
 * 
 * 一方、青木君は、以下のように動作するプログラムを実装しました。 
 * Li の値が昇順となるように, 入力された区間を [Lp1:Rp1],[Lp2:Rp2],⋯,[LpN:RpN] と並び替える。
 * i=1,2,⋯,N について、以下を行う。
 * これまでに選んだどの区間とも交わらないならば、 [Lpi:Rpi] を選ぶ。
 * 選んだ区間の数を出力する。
 * 
 * 整数 N,M が与えられます。 N 個の区間から成る問題 P の入力であって、
 * (高橋君のプログラムが出力する値) − (青木君のプログラムが出力する値) = M
 * となるものを構築してください。
 */
struct Args
{
  ll N, M;
  Args()
  {
    cin >> N >> M;
  }
};

class Solver
{
private:
  /* data */
  Args &args;
  vector<P> ans;

public:
  Solver(Args &args) : args(args), ans(0)
  {
  }
  void solve()
  {
    if (args.M == 0)
    {
      REP(i, args.N)
      {
        ll s(1 + 2 * i);
        ll e(s + 1);
        ans.push_back({s, e});
      }
      return;
    }
    //
    if (args.M < 0 || (args.N - args.M) < 2)
    {
      ans.push_back({-1, -1});
      return;
    }
    //
    ans.push_back({1, 10 * args.M});
    REP(i, args.M + 1)
    {
      ll s(2 + 2 * i);
      ll e(s + 1);
      ans.push_back({s, e});
    }
    REP(i, args.N - args.M - 2)
    {
      ll s(10 * args.M + 1 + 2 * i);
      ll e(s + 1);
      ans.push_back({s, e});
    }
  }
  void output()
  {
    FORA(p, ans)
    {
      if (p.first == -1)
      {
        pr(p.first);
      }
      else
      {

        prp(p);
      }
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
