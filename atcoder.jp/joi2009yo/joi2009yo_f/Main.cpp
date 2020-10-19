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
 * ビンゴカードは N 行 N 列のマス目に区切られており， 各マス目には正整数が 1つずつ書かれている． 
 * それらの整数は全て異なる．
 * マス目に書かれている整数は 1以上 M以下である．
 * ビンゴカードに書かれている N×N個の整数の合計は Sである．
 * どの列を見たときも， 上から下に向かって整数は昇順に並んでいる．
 * どのマス目の整数も， そのマス目より左の列のどの整数よりも大きい．
 * 作ることができるビンゴカードの枚数の最大値を 100000 で割った余りを出力するプログラムを作成せよ．
 */
struct Args
{
  /**
   * 入力は 1 行からなり， その行には
   * ビンゴカードのサイズ N (1≤N≤7) ， 
   * マス目に書かれている整数の上限 M (1≤M≤2000) ， 
   * ビンゴカードに書かれている整数の合計 S (1≤S≤3000) 
   * を表す3つの正整数が空白区切りで書かれている． 
   * ただし， 与えられるどの入力データにおいても， 条件を満たすビンゴカードを 1 枚以上作ることができる．
   */
  ll N, M, S, N2;
  Args()
  {
    cin >> N >> M >> S;
    N2 = N * N;
  }
};

class Solver
{
private:
  /* data */
  Args &args;
  ll ans;
  /**
   * j: position
   * k: sum = a0..ai-1
   */
  arr<ll> dp;

public:
  Solver(Args &args) : args(args), ans(0)
  {
  }

  void solve()
  {
    dp = arr<ll>(args.N2 + 1, vll(args.S + 1, 0));
    dp.at(0).at(0) = 1;
    FOR(i, 1, args.M + 1)
    {
      REPD(j, args.N2 + 1)
      {
        REPD(k, args.S + 1)
        {
          if (1 <= j && i <= k)
          {
            dp.at(j).at(k) += dp.at(j - 1).at(k - i);
            dp.at(j).at(k) %= MAXR;
          }
        }
      }
    }
    ans = dp.at(args.N2).at(args.S);
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
