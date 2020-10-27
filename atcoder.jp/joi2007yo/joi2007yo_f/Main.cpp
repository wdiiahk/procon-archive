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
 * 太郎君の住んでいる JOI 市は， 南北方向にまっすぐに伸びる a 本の道路と， 
 * 東西方向にまっすぐに伸びる b 本の道路により， 碁盤の目の 形に区分けされている．
 * 
 * 南北方向の a本の道路には， 西から順に 1,2,...,a の番号が付けられている． 
 * また， 東西方向の b 本の道路には， 南か ら順に 1,2,...,b の番号が付けられている． 
 * 西から i 番目の南北方向の道路と， 南から j 番目の東西方向の道路が交わる交差点を (i,j) で表す．
 * 
 * 太郎君は， 交差点 (1,1) の近くに住んでおり， 交差点 (a,b) の近くの JOI 高校に自転車で通っている． 
 * 自転車は道路に沿ってのみ移動 することができる． 
 * 太郎君は， 通学時間を短くするため， 東または北にのみ向かって移動して通学している．
 * 
 * 現在， JOI 市では， n 個の交差点 (x1,y1),(x2,y2),⋯,(xn,yn) で工事を行っている． 太郎君は工事中の交差点を通るこ とができない．
 * 太郎君が交差点 (1,1) から交差点 (a,b) まで， 工事 中の交差点を避けながら， 東または北にのみ向かって移動して通学する方法は何通りあるだろうか． 
 * 太郎君の通学経路の個数 m を求めるプログラムを作成せよ．
 */
struct Args
{
  ll a, b;
  ll n;
  arr<ll> ngs;
  Args()
  {
    cin >> a >> b;
    cin >> n;
    ngs.resize(b, vll(a, 0));
    REP(i, n)
    {
      ll x, y;
      cin >> x >> y;
      ngs.at(y - 1).at(x - 1) = 1;
    }
  }
};

class Solver
{
private:
  /* data */
  Args &args;
  ll ans;
  arr<ll> dp;

public:
  Solver(Args &args) : args(args), ans(0)
  {
    dp.resize(args.b, vll(args.a, 0));
  }
  void solve()
  {
    vector<P> v = {{-1, 0}, {0, -1}};
    dp.at(0).at(0) = 1;
    REP(i, args.b)
    {
      REP(j, args.a)
      {
        if (args.ngs.at(i).at(j))
        {
          continue;
        }
        FORA(dv, v)
        {
          ll prei = i + dv.first;
          ll prej = j + dv.second;
          if (prei < 0 || prej < 0)
          {
            continue;
          }
          dp.at(i).at(j) += dp.at(prei).at(prej);
        }
      }
    }
    ans = get_ans();
  }
  ll get_ans()
  {
    return dp.at(args.b - 1).at(args.a - 1);
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
