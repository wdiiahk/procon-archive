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

template <class T>
void pl(T x) { cout << x << " "; }

template <class T>
void pr(T x) { cout << x << endl; }

template <class T>
void prvec(const vector<T> &a)
{
  REP(i, a.size() - 1)
  {
    cout << a[i] << " ";
  }
  pr(a[a.size() - 1]);
}

template <class T>
void prarr(const arr<T> &a)
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
 * 問題
 * 
 * 冬の寒いある日，JOI太郎君は広場にはった薄氷を割って遊ぶことにした． 
 * 広場は長方形で， 東西方向に m個， 南北方向に n 個， つまり， m×n の区画に区切られている． 
 * また， 薄氷が有る区画と無い区画がある． 
 * JOI太郎君は，次のルールにしたがって，薄氷を割りながら区画を移動す ることにした．
 * 
 * - 薄氷があるどの区画からも薄氷を割り始めることができる．
 * - 東西南北のいずれかの方向に隣接し， まだ割られていない薄氷のある区画に移動できる．
 * - 移動した先の区画の薄氷をかならず割る．
 * 
 * JOI太郎君が薄氷を割りながら移動できる区画数の最大値を求めるプログラムを作成せよ． 
 * ただし， 1≤m≤90 ， 1≤n≤90 である． 
 * 与えられる入力データでは， 移動方法は 20 万通りを超えない．
 */
ll M, N;
arr<bool> ice;
vector<P> dv = {
    {-1, 0},
    {1, 0},
    {0, -1},
    {0, 1}};

ll dfs(ll i, ll j)
{
  if (!ice.at(i).at(j))
  {
    return 0;
  }
  ll res(0);
  ice.at(i).at(j) = false;
  FORA(p, dv)
  {
    ll toi = i + p.first;
    ll toj = j + p.second;
    if (toi < 0 || N <= toi)
    {
      continue;
    }
    if (toj < 0 || M <= toj)
    {
      continue;
    }
    chmax(res, dfs(toi, toj));
  }
  ice.at(i).at(j) = true;
  return res + 1;
}

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> M >> N;
  ice.resize(N, vbool(M, false));
  REP(i, N)
  {
    REP(j, M)
    {
      ll v;
      cin >> v;
      ice.at(i).at(j) = (v == 1);
    }
  }
  //
  ll ans(0);
  REP(i, N) {
    REP(j, M) {
      chmax(ans, dfs(i, j));
    }
  }
  pr(ans);
  return 0;

}
