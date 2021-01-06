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
  ll A, B, X;
  Constants() { cin >> A >> B >> X; }
} C;

struct Args {
  Args() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
  }
} args;

struct Solver {
  double ans;
  Solver() : ans() {}
  double f(double x) {
    if (x <= C.A) {
      return x * C.B / 2;
    }
    double h = double(C.B) - (x - C.A);
    double S1 = h * C.A / 2;
    // double c = sqrt(h * h + C.A * C.A);
    double S2 = (x - C.A) * C.A;
    return S1 + S2;
  }

  //
  void solve() {
    double S = double(C.X) / C.A;
    double left = 0;
    double right = C.A + C.B;
    while (1.e-12 < right - left) {
      double mid = (left + right) / 2;
      if (f(mid) < S) {
        left = mid;
      } else {
        right = mid;
      }
    }
    double x = (abs(S - f(left)) < abs(S - f(right))) ? left : right;
    if (x <= C.A) {
      double c = sqrt(x * x + C.B * C.B);
      ans = acos(x / c);
    } else {
      double h = double(C.B) - (x - C.A);
      double S1 = h * C.A / 2;
      ans = acos(1.0 / sqrt(h / C.A * h / C.A + 1));
    }
  }

  void output() {
    cout << fixed << setprecision(10);
    pr(ans * 180 / M_PI);
  }
} s;

int main() {
  s.solve();
  s.output();
  return 0;
}
