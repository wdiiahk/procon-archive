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
#define FORD(i, a, b) for (ll i = a; i >= ll(b); i--)
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
  ll N, M;
  Constants() { cin >> N >> M; }
} C;

struct Args {
  vll a, b;
  Args() : a(C.N), b(C.M) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    REP(i, C.N) { cin >> a.at(i); }
    REP(i, C.M) { cin >> b.at(i); }
  }
} args;

struct Solver {
  ll ans;
  Solver() : ans(INF) {}
  void recursive_comb(int *indexes, int s, int rest) {
    if (rest == 0) {
      ll cost(0);
      REP(i, args.a.size()) {
        ll l = args.a.at(i);
        ll r = args.b.at(indexes[i]);
        if (l != r) {
          ++cost;
        }
      }
      chmin(ans, cost);
    } else {
      if (s < 0)
        return;
      recursive_comb(indexes, s - 1, rest);
      indexes[rest - 1] = s;
      recursive_comb(indexes, s - 1, rest - 1);
    }
  }

  // nCkの組み合わせに対して処理を実行する
  void foreach_comb(int n, int k) {
    int indexes[k];
    recursive_comb(indexes, n - 1, k);
  }

  //
  void solve() {
    arr<ll> dp(C.N, vll(C.M, 0));
    REP(i, C.N) {
      REP(j, C.M) {
        if (args.a.at(i) == args.b.at(j)) {
          if (i == 0 && j == 0) {
            dp.at(i).at(j) = 0;
          }
          else if (i == 0) {
            dp.at(i).at(j) = j;
          }
          else if (j == 0) {
            dp.at(i).at(j) = i;
          }
          else {
            dp.at(i).at(j) = dp.at(i - 1).at(j - 1);
            chmin(dp.at(i).at(j), dp.at(i).at(j-1) + 1);
            chmin(dp.at(i).at(j), dp.at(i - 1).at(j) + 1);
          }
        }
        else {
          if (i == 0 && j == 0) {
            dp.at(i).at(j) = 1;
          }
          else if (i == 0) {
            dp.at(i).at(j) = dp.at(i).at(j-1) + 1;
          }
          else if (j == 0) {
            dp.at(i).at(j) = dp.at(i - 1).at(j) + 1;
          }
          else {
            dp.at(i).at(j) = dp.at(i - 1).at(j - 1) + 1;
            chmin(dp.at(i).at(j), dp.at(i).at(j-1) + 1);
            chmin(dp.at(i).at(j), dp.at(i - 1).at(j) + 1);
          }
        }
      }
    }
    // 
    ans = dp.at(C.N - 1).at(C.M - 1);
  }

  void output() { pr(ans); }
} s;

int main() {
  s.solve();
  s.output();
  return 0;
}
