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
 * 問題文
 * 
 * 縦 Hマス, 横 W マスに広がるマス目があり, 各マスは白または黒で塗られている. 
 * 上から i 番目で左から j 番目のマスを (i,j) で表す. すぬけ君は, このマス目を使って
 * 次のようなゲームをしたい. ゲームの開始時点ではマス (1,1) にゲームキャラクター「けぬす君」がいる. 
 * プレイヤーはけぬす君を上下左右の 4 方向のいずれかに 1 マスだけ動かすことを繰り返す. 
 * けぬす君が白いマスだけを通って (H,W) にたどり着けばゲームクリアとなる.
 * ゲームを開始する前に, すぬけ君はいくつかの白いマス目の色を黒に変えることができる. 
 * ただし, マス (1,1) と (H,W) の色を変えることはできず, ゲームを開始するまでにすべての色の変更を行わなければならない.
 * ゲームをクリアしたとき, ゲームの開始前にマスの色を変えた回数がすぬけ君のスコアとなる. 
 * そのとき, すぬけ君が取る可能性のある最大のスコアを求めなさい.
 * ただし, すぬけ君がどのようにマス目の色を変えてもけぬす君が (H,W) にたどり着くことが出来ない場合、−1 と出力しなさい.
 * ただし, 各マスの色の情報は文字 si,j として与えられる. マス (i,j) が最初白で塗られている場合 si,j は . であり, 
 * マス (i,j) が最初黒で塗られている場合 si,j は # である. 
 */
ll H, W;
vector<string> maze;
vector<P> v = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};

ll bfs()
{
  queue<P> q;
  arr<ll> dists(H, vll(W, 0));
  q.push({0, 0});
  dists.at(0).at(0) = 1;
  while (!q.empty())
  {
    auto &p = q.front();
    q.pop();
    ll d = dists.at(p.first).at(p.second);
    FORA(dp, v)
    {
      P next(p.first + dp.first, p.second + dp.second);
      if (next.first < 0 || H <= next.first)
      {
        continue;
      }
      if (next.second < 0 || W <= next.second)
      {
        continue;
      }
      if (maze.at(next.first).at(next.second) == '#')
      {
        continue;
      }
      if (0 < dists.at(next.first).at(next.second))
      {
        continue;
      }
      if (next.first == H - 1 && next.second == W - 1)
      {
        return d + 1;
      }
      dists.at(next.first).at(next.second) = d + 1;
      q.push(next);
    }
  }
  return -1;
}

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> H >> W;
  ll total = 0;
  REP(i, H)
  {
    string line;
    cin >> line;
    maze.push_back(line);
    total += count(ALL(line), '.');
  }
  //
  ll ans = bfs();
  if (ans != -1)
  {
    ans = total - ans;
  }
  pr(ans);

  return 0;
}
