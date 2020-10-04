//デバッグ用オプション：-fsanitize=undefined,address

//コンパイラ最適化
#pragma GCC optimize("Ofast")

//インクルードなど
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

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

bool dfs(vector<ll> &nos, vector<char> &ops, int x)
{
  if (x == nos.size() - 1)
  {
    ll s = nos.at(0);
    FOR(i, 1, nos.size())
    {
      char op = ops.at(i - 1);
      if (op == '+')
      {
        s += nos.at(i);
      }
      else if (op == '-')
      {
        s -= nos.at(i);
      }
    }
    return (s == 7);
  }
  //
  ops.at(x) = '+';
  if (dfs(nos, ops, x + 1))
  {
    return true;
  }
  ops.at(x) = '-';
  if (dfs(nos, ops, x + 1))
  {
    return true;
  }
  return false;
}

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  string no;
  cin >> no;
  vector<ll> nos;
  for (char c : no)
  {
    int n = c - '0';
    nos.push_back(n);
  }
  vector<char> ops(nos.size() - 1);
  if (dfs(nos, ops, 0))
  {
    cout << nos[0];
    FOR(i, 1, nos.size())
    {
      cout << ops[i - 1] << nos[i];
    }
    cout << "=7" << endl;
    return 0;
  }
  throw runtime_error("Not Found");
}
