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
 * JOIピザでは，市の中心部を通る全長dメートルの環状線の沿線上でピザの宅配販売を行っている．
 * JOIピザは，環状線上にn個の店舗S1;···;Snを持つ．本店はS1である．
 * S1からSiまで，時計回りに環状線を移動したときの道のりをdiメートルとおく．
 * d2;···;dnは1以上d−1以下の整数である．d2;···;dnは全て異なる．
 * ピザの注文を受けると,ピザが冷めないように，宅配先までの移動距離がもっとも短い店舗でピザを焼き宅配する．
 * 宅配先の位置は0以上d−1以下の整数kで表される．これは，本店S1から宅配先までに時計回りで環状線を
 * 移動したときの道のりがkメートルであることを意味する．
 * ピザの宅配は環状線に沿って行われ，それ以外の道を通ることは許されない．
 * ただし，環状線上は時計回りに移動しても反時計回りに移動してもよい．
 * 
 * 宅配先1にもっとも近い店舗はS2なので，店舗S2から宅配する．
 * このとき，店舗からの移動距離は1である．また，宅配先2にもっとも近い店舗はS1(本店)なので，
 * 店舗S1(本店)から宅配する．このとき，店舗からの移動距離は2である．
 * 環状線の全長d，JOIピザの店舗の個数n，注文の個数m,本店以外の位置を表すn−1個の整数d2;···;dn，
 * 宅配先の場所を表す整数k1;···;kmが与えられたとき，各注文に対する宅配時の移動距離
 * (すなわち，最寄店舗から宅配先までの道のり)の全注文にわたる総和を求めるプログラムを作成せよ．
 */
ll D;
ll N;
ll M;
vll d;
vll k;

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> D;
  cin >> N;
  cin >> M;
  d.resize(N + 1, 0);
  FOR(i, 1, N)
  {
    cin >> d.at(i);
  }
  d.at(N) = D;
  sort(ALL(d));
  //
  k.resize(M, 0);
  REP(i, M)
  {
    cin >> k.at(i);
  }
  //
  ll ans(0);
  FORA(x, k)
  {
    ll l = 0;
    ll r = N;
    while (1 < r - l)
    {
      ll mid = (r + l) / 2;
      if (x <= d.at(mid))
      {
        r = mid;
      }
      else
      {
        l = mid;
      }
    }
    //
    ll cost = min(abs(d.at(l) - x), abs(x - d.at(r)));
    ans += cost;
  }
  pr(ans);

  return 0;
}
