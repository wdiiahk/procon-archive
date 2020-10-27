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
 * K 理事長は，JOI 市の中心部にある JOI ピザ店の常連客である．
 * 彼はある事情に より，今月から節約生活を始めることにした．
 * そこで彼は，JOI ピザ店で注文できる ピザのうち， 1 ドルあたりのカロリーが最大となるようなピザを注文し たいと思った．
 * このようなピザを「最高のピザ」と呼ぶことにしよう．「最高のピザ 」は 1 種類とは限らない．
 * 
 * JOI ピザでは N 種類のトッピングから何種類かを自由に選び，基本の生地の上に載せたものを注文することができる．
 * 同種のトッピングを 2 つ以上載せることはできない．生地にトッピングを 1 種類も載せないピ ザも注文できる．
 * 生地の値段は A ドルであり，トッピングの値段はいず れも B ドルである．ピザの値段は，生地の値段と載せたトッピングの値 段の合計である．
 * すなわち，トッピングを k 種類 (0≤k≤N) 載せたピザの値段は A+k×B ドルである．
 * ピザ全体の カロリーは，生地のカロリーと載せたトッピングのカロリーの合計である．
 * 生地の値段とトッピングの値段，および，生地と各トッピングのカロリーの値が与えられたとき，
 * 「最高のピザ」の 1ドルあたりのカロリー数を求めるプ ログラムを作成せよ．
 * 
 */

struct Args
{
  ll N;
  ll A, B;
  ll C;
  vll D;
  Args()
  {
    cin >> N;
    cin >> A >> B;
    cin >> C;
    D.resize(N);
    REP(i, N)
    {
      cin >> D.at(i);
    }
    sort(ALL(D));
  }
};

class Solver
{
private:
  /* data */
  Args &args;
  ll ans;

public:
  Solver(Args &args) : args(args), ans(0)
  {
  }
  void solve()
  {
    ll total = args.A;
    ll calories = args.C;
    double average = double(calories) / total;
    REPD(i, args.N)
    {
      double cur = double(calories + args.D.at(i)) / (total + args.B);
      if (average < cur)
      {
        calories += args.D.at(i);
        total += args.B;
        average = cur;
      }
      else
      {
        break;
      }
    }
    ans = ll(average);
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
