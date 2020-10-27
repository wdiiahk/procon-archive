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
 * あなたの町にはJOI古本店という老舗の古本屋があり，あなたはJOI古本店をよく利用している．
 * それぞれの本には基準価格が定まっており，JOI古本店に行けばその価格で買い取ってもらえる．
 * JOI古本店では，本を小説・漫画・雑誌など10種類のジャンルに分類して扱っている．
 * ジャンルには1から10までの番号が付けられている．JOI古本店には，同じジャンルの本をまとめて
 * 買い取ってもらうと高値で買い取ってくれるというサービスがある．
 * 具体的には，同じジャンルの本をまとめてT冊買い取ってもらう場合，そのジャンルの本の一冊あたりの
 * 買取価格が基準価格よりT-1円高くなる．
 * 例えば，同じジャンルで基準価格100円，120円，150円の本をまとめてJOI古本店に売ったとすると，
 * 買取価格はそれぞれ102円，122円，152円となる．
 * さて，あなたは一身上の都合で急遽引越しをすることになった．
 * あなたはN冊の本を持っているが，新しい住居にすべての本を持っていくことは困難なため，N冊の本のうちK冊をJOI古本店に売ることにした．
 * 
 * N冊の本それぞれの基準価格とジャンルの番号が与えられるとき，合計買取価格の最大値を求めるプログラムを作成せよ
 */
struct Args
{
  ll N, K;
  arr<ll> books;
  Args()
  {
    cin >> N >> K;
    books.resize(10);
    REP(i, N)
    {
      ll c, g;
      cin >> c >> g;
      books.at(g - 1).push_back(c);
    }
    REP(i, 10)
    {
      sort(ALL(books.at(i)), greater<ll>());
    }
    // prarr(books);
  }
};

class Solver
{
private:
  /* data */
  Args &args;
  ll ans;
  // dp_ij : i番目までのジャンルで、j冊売った時の最大値
  arr<ll> dp;

public:
  Solver(Args &args) : args(args), ans(0)
  {
    dp.resize(11, vll(args.K + 1, 0));
  }
  void calc_dp()
  {
    REP(i, 10)
    {
      auto &target = args.books.at(i);
      ll len = target.size();
      vll cum(len + 1, 0);
      REP(j, min(len, args.K))
      {
        cum.at(j + 1) = cum.at(j) + target.at(j);
      }
      REP(j, args.K + 1)
      {
        REP(k, min(len + 1, args.K - j + 1))
        {
          chmax(dp.at(i + 1).at(j + k), dp.at(i).at(j) + cum.at(k) + (k - 1) * k);
        }
      }
    }
  }
  ll get_ans()
  {
    return dp.at(10).at(args.K);
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
