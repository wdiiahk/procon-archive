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
 * 天使の中に悪魔が紛れ込んだ。あなたは上司にこれを報告しなければならないが、上司は『最大でどれだけ悪魔が紛れ込んだか調査しろ』と命じてきた。
 * 「一体、誰が悪魔なんですかね」
 * あなたが言うと、彼らは『あいつが悪魔だ』と指摘し合った。誰も同じ者を指ささずバラバラの者を指摘していた。
 * どうやら天使は必ず悪魔を、悪魔は必ず天使を指摘しているようだった。
 * 最大で何人の悪魔がいるだろうか。その数を報告してほしい。
 * 
 * ただし、あなたや上司は天使でも悪魔でもなく、入力で与えられる『彼ら』には含まれない。また、『彼ら』はそれぞれ天使か悪魔のどちらかである。
 */
struct Args
{
  ll N;
  vll A;
  Args()
  {
    cin >> N;
    A.assign(N, 0);
    REP(i, N)
    {
      ll tmp;
      cin >> tmp;
      A.at(i) = tmp - 1;
    }
  }
};

struct UnionFind
{
  vll par;
  UnionFind() {}

  void init(ll n)
  {
    par.assign(n, -1);
  }

  ll root(ll x)
  {
    if (par.at(x) < 0)
    {
      return x;
    }
    ll y = root(par.at(x));
    par.at(x) = y;
    return y;
  }

  bool same(ll x, ll y)
  {
    return root(x) == root(y);
  }

  bool unite(ll x, ll y)
  {
    ll rx = root(x);
    ll ry = root(y);
    if (rx == ry)
    {
      return false;
    }
    if (-par.at(rx) < -par.at(ry))
    {
      swap(rx, ry);
    }
    par.at(rx) += par.at(ry);
    par.at(ry) = rx;
    return true;
  }

  ll size(ll x)
  {
    return -par.at(root(x));
  }
};

class Solver
{
private:
  /* data */
  Args &args;
  ll ans;
  UnionFind uf;

public:
  Solver(Args &args) : args(args), ans(0)
  {
    uf.init(2 * args.N);
  }
  void solve()
  {
    REP(i, args.N)
    {
      ll j = args.A.at(i);
      uf.unite(i, j + args.N);
      uf.unite(i + args.N, j);
    }
    ans = get_ans();
  }
  ll get_ans()
  {
    set<ll> st;
    ll ret(0);
    REP(i, args.N)
    {
      if (st.count(uf.root(i)))
      {
        continue;
      }
      st.insert(uf.root(i));
      if (uf.same(i, i + args.N))
      {
        return -1;
      }
      ret += uf.size(i) / 2;
    }
    return ret / 2;

    /*
    ll res(0);
    REP(i, args.N)
    {
      if (uf.same(i, i + args.N))
      {
        return -1;
      }
      chmax(res, uf.size(i));
    }
    return res / 2;
    */
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
