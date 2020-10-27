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
#define MOD 100000        //10^9+7:合同式の法
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
 * JOIさんが住むカナダのある都市は，南北方向にまっすぐに伸びる w 本の道路と，
 * 東西方向にまっすぐに伸びる h 本の道路により，碁盤の目 の形に区分けされている．
 * 
 * 南北方向の w 本の道路には，西から順に 1,2,...,w の番号が付けられている．
 * また，東西方向の h 本の道路には，南から順 に 1,2,...,h の番号が付けられている．
 * 西から i 番目 の南北方向の道路と，南から j 番目の東西方向の道路が交わる交差点を (i,j) で表す．
 * 
 * JOIさんは，交差点 (1,1) の近くに住んでおり，交差点 (w,h) の近くの会社に車で通っている．
 * 車は道路に沿ってのみ移動することができる．
 * JOIさんは，通勤時間を短くするため，東または北にのみ向かって移動して通勤している．
 * また，この都市では，交通事故を減らすために，次のような交通規則が設けられている：
 * 
 * - 交差点を曲がった車は，その直後の交差点で曲がることは出来ない．
 * 
 * すなわち，交差点で曲がったあとに 1 ブロックだけ進んで再び曲がることは許されない．
 * 
 * このとき，JOIさんの通勤経路は何通り考えられるだろうか．
 * wと h が与えられたとき，JOIさんの通勤経路の個数を 100000 で割った余りを出力するプログラムを作成せよ．
 */
struct Args
{
  ll w, h;
  Args()
  {
    cin >> w >> h;
  }
};

class Solver
{
private:
  /* data */
  Args &args;
  ll ans;
  arr<arr<ll>> dp; // 頂点(i, j) + 方向index(k) と　状態 S (0: 曲がれない, 1: 曲がれる)

public:
  Solver(Args &args) : args(args), ans(0)
  {
    dp.resize(args.w, vector<arr<ll>>(args.h, arr<ll>(2, vll(2, 0))));
  }
  void calc_dp()
  {
    dp.at(0).at(0).at(0).at(1) = 1;
    dp.at(0).at(0).at(1).at(1) = 1;
    //
    vector<P> v = {
        {1, 0},
        {0, 1}};

    REP(i, args.w)
    {
      REP(j, args.h)
      {
        if (0 <= j - 1)
        {
          dp.at(i).at(j).at(0).at(0) += dp.at(i).at(j - 1).at(1).at(1);
          dp.at(i).at(j).at(1).at(1) += dp.at(i).at(j - 1).at(1).at(0);
          dp.at(i).at(j).at(1).at(1) += dp.at(i).at(j - 1).at(1).at(1);
        }
        if (0 <= i - 1)
        {
          dp.at(i).at(j).at(0).at(1) += dp.at(i - 1).at(j).at(0).at(0);
          dp.at(i).at(j).at(0).at(1) += dp.at(i - 1).at(j).at(0).at(1);
          dp.at(i).at(j).at(1).at(0) += dp.at(i - 1).at(j).at(0).at(1);
        }
        //
        REP(k, 2)
        {
          REP(S, 2)
          {
            dp.at(i).at(j).at(k).at(S) %= MOD;
          }
        }
      }
    }
  }
  ll get_ans()
  {
    ll total = 0;
    REP(S, 2)
    {
      total += dp.at(args.w - 2).at(args.h - 1).at(0).at(S);
    }
    REP(S, 2)
    {
      total += dp.at(args.w - 1).at(args.h - 2).at(1).at(S);
    }
    return total % MOD;
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
