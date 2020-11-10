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
 * IOI製菓では， 創業以来の伝統の製法で煎餅（せんべい）を焼いている． 
 * この伝統の製法は， 炭火で一定時間表側を焼き， 表側が焼けると裏返して， 
 * 炭火で一定時間裏側を焼くというものである． 
 * この伝統を守りつつ， 煎餅を機械で焼いている． 
 * この機械は縦 R (1≦R≦10) 行, 横 C (1≦C≦10000) 列の長方形状に煎餅を並べて焼く． 
 * 通常は自動運転で， 表側が焼けたら一斉に煎餅を裏返し裏側を焼く．
 * ある日， 煎餅を焼いていると， 煎餅を裏返す直前に地震が起こり何枚かの煎餅が裏返ってしまった． 
 * 幸いなことに炭火の状態は適切なままであったが， これ以上表 側を焼くと創業以来の伝統で定められている焼き時間を超えてしまい， 
 * 煎餅の表側が焼けすぎて商品として出荷できなくなる． 
 * そこで， 急いで機械をマニュアル操作に 変更し， まだ裏返っていない煎餅だけを裏返そうとした． 
 * この機械は， 横の行を何行か同時に裏返したり縦の列を何列か同時に裏返したりすることはできるが， 
 * 残念なことに， 煎餅を 1 枚ごと裏返すことはできない．
 * 裏返すのに時間がかかると， 地震で裏返らなかった煎餅の表側が焼けすぎて商品 として出荷できなくなるので， 
 * 横の何行かを同時に 1 回裏返し， 引き 続き， 縦の何列かを同時に 1 回裏返して， 表側を焼きすぎずに両面を 焼くことのできる煎餅， 
 * つまり， 「出荷できる煎餅」の枚数をなるべく多くするこ とにした． 
 * 横の行を 1 行も裏返さない，あるいは， 縦の列を 1 列も裏返さない場合も考えることにする． 
 * 出荷できる煎餅の枚数の最大値を出 力するプログラムを書きなさい．
 * 地震の直後に， 煎餅が次の図のような状態になったとする． 
 * 黒い丸が表側が焼ける状態を， 白い丸が裏側が焼ける状態を表している．
 */
ll R, C;
vll a;

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> R >> C;
  a.resize(C, 0);
  REP(i, R)
  {
    REP(j, C)
    {
      ll x;
      cin >> x;
      if (x == 1)
      {
        a.at(j) += (1 << (i));
      }
    }
  }
  //

  ll ans(0);
  REP(S, 1 << R)
  {
    ll cnt(0);
    REP(i, C)
    {
      ll s = S ^ a.at(i);
      ll tmp = __builtin_popcount(s);
      cnt += max(tmp, R - tmp);
    }
    chmax(ans, cnt);
  }
  pr(ans);
}
