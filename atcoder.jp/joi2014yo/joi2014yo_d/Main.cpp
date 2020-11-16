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
#define MOD 10007         //10^9+7:合同式の法
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
 * IOI 高校のプログラミング部には，J 君と O 君と I 君の 3人の部員がいる． 
 * プログラミング部では，部活のスケジュールを組もうとしている．
 * 今， N 日間の活動のスケジュールを決めようとしている． 
 * 各活動日 のスケジュールとして考えられるものは，各部員については
 * 活動に参加するかどうか の 2 通りがあり，部としては全部で 8 通りある． 
 * 
 * 部室の鍵はただ 1 つだけであり，最初は J 君が持っている． 
 * 各活動日には，その日の活動に参加する部員のうちのいずれか 1 人が鍵を持っている必要
 * があり，活動後に参加した部員のいずれかが鍵を持って帰る．
 * プログラミング部では，活動日には毎回必ず活動が行われるように，あらかじめ各活動日の責任者を定めた． 
 * 責任者は，必ずその日の活動に出席しなければならない．
 * スケジュールを決めようとしている日数と，各活動日の責任者が誰であるかの情報が与えられた時，
 * すべての活動日に部活動を行うことができるようなスケジュール表
 * として考えられるものの数を 10007 で割った余りを求めるプログラムを 作成せよ． 
 * 
 * ただし，部活の終了時に鍵を持って帰る部員は，その日の活動に参加している部員の誰でもよく，
 * 最終日は誰が鍵を持って帰ってもよいものとする．
 */
ll N;
vll manajors;
// i日目, 最後の状態がS
arr<ll> dp;

void add(ll &a, ll b)
{
  a += b;
  if (MOD <= a)
  {
    a -= MOD;
  }
}

int main()
{
  //入力の高速化用のコード
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  manajors.assign(N, 0);
  string tmp;
  cin >> tmp;
  vector<char> m2i = {'J', 'O', 'I'};
  REP(i, N)
  {
    char c = tmp.at(i);
    REP(j, 3)
    {
      if (c == m2i.at(j))
      {
        manajors.at(i) = j;
        break;
      }
    }
  }
  //
  dp.assign(N + 1, vll(8, 0));
  dp.at(0).at(1) = 1;
  REP(i, N)
  {
    ll m = manajors.at(i);
    REP(S, 1 << 3)
    {
      if ((S >> m) % 2 == 0)
      {
        continue;
      }
      REP(T, 1 << 3)
      {
        if ((S & T) == 0)
        {
          continue;
        }
        add(dp.at(i + 1).at(S), dp.at(i).at(T));
      }
    }
  }

  //
  ll ans(0);
  REP(S, 1 << 3)
  {
    add(ans, dp.at(N).at(S));
  }
  pr(ans);
  return 0;
}
