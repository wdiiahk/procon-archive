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
 * ゲームは○×ゲームをベースにしており、以下の要領でゲームが行われます。
 * ゲームは縦 3マス、横 3マスの盤面を使います。
 * ゲーム開始時点ではどのマスにも文字が書かれていません。
 * 挨拶した後、直大くんから始めて交互に文字を書いていきます。
 * 文字は盤面上のまだ文字が書かれていないマスの上にのみ書くことができます。
 * そのようなマスが複数ある場合は好きな 1箇所を選んで書きます。
 * 書く文字は、直大くんが○、直子さんが×です。
 * 合わせて 9回文字を書いた時点で、すべてのマスが埋まります。
 * その後、得点計算を行い、得点の高い方が勝ちます。
 * 得点計算は以下の方法で行われます。
 * ここで、盤面の左上のマスをマス (1,1)とし、左上から下に i−1(1≦i≦3) マス、
 * 右に j−1(1≦j≦3) マス進んだところにあるマスをマス (i,j)と呼ぶことにします。
 * 1≦i≦2 および 1≦j≦3 を満たすすべての整数組 (i,j) に対して、
 * マス (i,j) とマス (i+1,j) に書かれているマスを見て、同じ文字が書かれていたなら直大くんに、
 * 違う文字が書かれていたなら直子さんに bi,j点が入る。
 * 1≦i≦3および 1≦j≦2 を満たすすべての整数組 (i,j) に対して、
 * マス (i,j) とマス (i,j+1) に書かれているマスを見て、同じ文字が書かれていたなら直大くんに、
 * 違う文字が書かれていたなら直子さんに ci,j点が入る。
 * 直大くんも直子さんも、最終的に得られる自分の得点ができるだけ多くなるようにゲームを行います。
 * 両者が最善を尽くしたときのそれぞれの得点を計算してください。
 */
struct Args
{
  ll H, W;
  arr<ll> b, c;
  ll total;
  Args()
  {
    H = 3;
    W = 3;
    b = arr<ll>(H - 1, vll(W, 0));
    total = 0;
    REP(i, H - 1)
    {
      REP(j, W)
      {
        ll tmp;
        cin >> tmp;
        b.at(i).at(j) = tmp;
        total += tmp;
      }
    }
    //
    c = arr<ll>(H, vll(W - 1, 0));
    REP(i, H)
    {
      REP(j, W - 1)
      {
        ll tmp;
        cin >> tmp;
        c.at(i).at(j) = tmp;
        total += tmp;
      }
    }
  }
};

class Solver
{
private:
  /* data */
  Args &args;
  P ans;
  arr<ll> dp;
  arr<ll> board;

public:
  Solver(Args &args) : args(args), ans({0, 0})
  {
    board.resize(3, vll(3, -1));
  }
  ll calc_score()
  {
    ll res(0);
    REP(i, args.H)
    {
      REP(j, args.W)
      {
        if (i < args.H - 1)
        {
          if (board.at(i).at(j) == board.at(i + 1).at(j))
          {
            res += args.b.at(i).at(j);
          }
        }
        if (j < args.W - 1)
        {
          if (board.at(i).at(j) == board.at(i).at(j + 1))
          {
            res += args.c.at(i).at(j);
          }
        }
      }
    }
    //
    return res;
  }

  ll dfs(int n)
  {
    if (n == 9)
    {
      return calc_score();
    }
    //
    bool my_turn = (n % 2 == 0);
    ll res = (my_turn) ? 0 : INF;
    REP(i, args.H)
    {
      REP(j, args.W)
      {
        if (0 <= board.at(i).at(j))
        {
          continue;
        }
        board.at(i).at(j) = my_turn ? 0 : 1;
        if (my_turn)
        {
          chmax(res, dfs(n + 1));
        }
        else
        {
          chmin(res, dfs(n + 1));
        }
        board.at(i).at(j) = -1;
      }
    }
    return res;
  }

  void solve()
  {
    ll ans0 = dfs(0);
    ans = {ans0, args.total - ans0};
  }
  void output()
  {
    pr(ans.first);
    pr(ans.second);
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
