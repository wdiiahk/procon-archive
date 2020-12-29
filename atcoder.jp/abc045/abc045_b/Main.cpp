//デバッグ用オプション：-fsanitize=undefined,address

//コンパイラ最適化
#pragma GCC optimize("Ofast")

//インクルードなど
#include <bits/stdc++.h>
// #include <atcoder/all>

using namespace std;
// using namespace atcoder;

typedef long long ll;
using vint = vector<int>;
using vll = vector<ll>;
using vs = vector<string>;
using vbool = vector<bool>;
template <class T> using arr = vector<vector<T>>;

//マクロ
// forループ
//引数は、(ループ内変数,動く範囲)か(ループ内変数,始めの数,終わりの数)、のどちらか
// Dがついてないものはループ変数は1ずつインクリメントされ、Dがついてるものはループ変数は1ずつデクリメントされる
// FORAは範囲for文(使いにくかったら消す)
#define REP(i, n) for (ll i = 0; i < ll(n); i++)
#define REPD(i, n) for (ll i = n - 1; i >= 0; i--)
#define FOR(i, a, b) for (ll i = a; i < ll(b); i++)
#define FORD(i, a, b) for (ll i = b - 1; i >= ll(a); i--)
#define FORA(i, I) for (const auto &i : I)
// xにはvectorなどのコンテナ
#define ALL(x) x.begin(), x.end()
#define SIZE(x) ll(x.size())
//定数
#define INF 1000000000000 // 10^12:∞
#define MOD 1000000007 // 10^9+7:合同式の法
#define MAXR 100000 // 10^5:配列の最大のrange

// aよりもbが大きいならばaをbで更新する
// (更新されたならばtrueを返す)
template <typename T> bool chmax(T &a, const T &b) {
  if (a < b) {
    a = b; // aをbで更新
    return true;
  }
  return false;
}
// aよりもbが小さいならばaをbで更新する
// (更新されたならばtrueを返す)
template <typename T> bool chmin(T &a, const T &b) {
  if (a > b) {
    a = b; // aをbで更新
    return true;
  }
  return false;
}

template <class T> void pl(T x) { cout << x << " "; }

template <class T> void pr(T x) { cout << x << endl; }

template <class T> void prvec(const vector<T> &a) {
  REP(i, a.size() - 1) { cout << a[i] << " "; }
  pr(a[a.size() - 1]);
}

template <class T> void prarr(const arr<T> &a) {
  REP(i, a.size())
  if (a[i].empty())
    pr("");
  else
    prvec(a[i]);
}

using P = pair<ll, ll>;
void prp(const P &p) { cout << p.first << " " << p.second << endl; }

struct Constants {
  ll NA, NB, NC;
  string SA, SB, SC;
  Constants() {
    cin >> SA >> SB >> SC;
    NA = SA.length();
    NB = SB.length();
    NC = SC.length();
  }
} C;

struct Args {
  Args() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
  }
} args;

struct Solver {
  char ans;
  Solver() : ans() {}
  //
  void solve() {
    ll i(-1), j(-1), k(-1);
    char turn('a');
    while (i < C.NA && j < C.NB && k < C.NC) {
      switch (turn) {
      case 'a':
        i++;
        if (i == C.NA) {
          ans = 'A';
          return;
        }
        turn = C.SA.at(i);
        break;
      case 'b':
        j++;
        if (j == C.NB) {
          ans = 'B';
          return;
        }
        turn = C.SB.at(j);
        break;
      case 'c':
        k++;
        if (k == C.NC) {
          ans = 'C';
          return;
        }
        turn = C.SC.at(k);
        break;
      default:
        break;
      }
    }
  }

  void output() { pr(ans); }
} s;

int main() {
  s.solve();
  s.output();
  return 0;
}
