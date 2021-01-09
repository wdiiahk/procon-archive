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
  vll a;
  ll total;
  Args() : a(C.N), total(0) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    REP(i, C.N) {
      cin >> a.at(i);
      total += a.at(i);
    }
  }
} args;

struct Solver {
  ll ans;
  Solver() : ans() {}

  /*
  vll bit;
  void set_val(ll ind, ll val) {
    ind++;
    while (ind <= C.N) {
      chmax(bit.at(ind), val);
      ind += ind & -ind;
    }
  }

  ll get_val(ll ind) {
    ll res(0);
    ind++;
    while (0 < ind) {
      res = max(res, bit.at(ind));
      ind -= ind & -ind;
    }
    return res;
  }
  */

  void solve() {
    priority_queue<ll, vll, less<ll>> pq;
    FORA(a, args.a) { pq.push(a); }
    ll s(0);
    REP(_, C.M) {
      auto v = pq.top();
      pq.pop();
      s += v - v/2;
      pq.push(v / 2);
    }
    ans = args.total - s;
  }

  void output() { pr(ans); }
} s;

int main() {
  s.solve();
  s.output();
  return 0;
}
