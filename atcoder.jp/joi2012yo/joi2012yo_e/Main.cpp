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
 * JOI 社の建物は図のような 1 辺 1 メートルの正六角形をつなぎ合わせた形である．
 * クリスマスが近づいているので，JOI 社では建物の壁面を イルミネーションで
 * 飾り付けることにした．
 * ただし，外から見えない部分にイルミネ ーションを施すのは無駄なので，
 * イルミネーションは外から建物の中を通らずに行く ことのできる壁面にのみ飾り付けることにした．
 * 上の図は上空から見た JOI 社の建物の配置の例である．
 * 正六角形内の数字は座標 を表す．灰色の正六角形は建物がある場所を表し，
 * 白色の正六角形は建物がない場所 を表す．
 * この例では，赤の実線で示される部分がイルミネーションで飾り付けを行う 壁面となり，
 * その壁面の長さの合計は 64メートルとなる．
 * JOI 社の建物の配置を表す地図が与えられたとき，飾り付けを行う壁面の長さの
 * 合計を求めるプログラムを作成せよ．
 * ただし，地図の外側は自由に行き来できるものと し，
 * 隣接した建物の間は通ることはできないものとする．
 */
ll W, H;
arr<bool> site;

arr<P> v = {
    {{-1, -1}, {-1, 0}, {0, -1}, {0, 1}, {1, -1}, {1, 0}},
    {{-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, 0}, {1, 1}}};

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> W >> H;
  site.resize(H + 2, vbool(W + 2, false));
  FOR(i, 1, H + 1)
  {
    FOR(j, 1, W + 1)
    {
      ll v;
      cin >> v;
      site.at(i).at(j) = (v == 1);
    }
  }
  //
  //
  arr<ll> dists(H + 2, vll(W + 2, 0));
  queue<P> q;
  q.push({0, 0});
  dists.at(0).at(0) = 1;
  //
  ll ans(0);
  while (!q.empty())
  {
    auto &p = q.front();
    q.pop();
    ll d = dists.at(p.first).at(p.second);
    FORA(dp, v.at(p.first % 2))
    {
      P next(p.first + dp.first, p.second + dp.second);
      if (next.first < 0 || H + 2 <= next.first)
      {
        continue;
      }
      if (next.second < 0 || W + 2 <= next.second)
      {
        continue;
      }
      if (0 < dists.at(next.first).at(next.second))
      {
        continue;
      }
      if (site.at(next.first).at(next.second))
      {
        ans++;
        continue;
      }
      dists.at(next.first).at(next.second) = d + 1;
      q.push(next);
    }
  }
  //
  pr(ans);
  return 0;
}
