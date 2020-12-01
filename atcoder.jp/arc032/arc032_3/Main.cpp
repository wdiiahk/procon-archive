//デバッグ用オプション：-fsanitize=undefined,address

//コンパイラ最適化
#pragma GCC optimize("Ofast")

//インクルードなど
#include <bits/stdc++.h>
//#include <atcoder/all>

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
  ll N;
  Constants() { cin >> N; }
} C;

struct Args {
  vector<P> jobs;
  ll max_t;
  vint sorted;
  Args() : jobs(C.N), max_t(0), sorted(C.N) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    REP(i, C.N) {
      ll a, b;
      cin >> a >> b;
      jobs.at(i).first = a;
      jobs.at(i).second = b;
      chmax(max_t, b);
      sorted.at(i) = i;
    }

    sort(ALL(sorted), [&](int l, int r) {
      if (jobs.at(l).second == jobs.at(r).second) {
        return jobs.at(l).first < jobs.at(r).first;
      }
      return jobs.at(l).second < jobs.at(r).second;
    });
  }
} args;

struct BIT {
public:
  BIT(int n) : _n(n), data(n, {0, INF}) {}

  void set(int p, P x) {
    assert(0 <= p && p < _n);
    p++;
    while (p <= _n) {
      auto &t = data[p - 1];
      if (t.first == x.first) {
        chmin(t.second, x.second);
      } else if (t.first < x.first) {
        t = x;
      }
      p += p & -p;
    }
  }

  void debug(int n) {
    REP(i, n + 1) {
      cout << i << " ";
      prp(data.at(i));
    }
  }

  int _n;
  std::vector<P> data;

  P query(int r) {
    P ret(0, INF);
    while (r > 0) {
      if (ret.first == data[r - 1].first) {
        chmin(ret.second, data[r - 1].second);
      } else if (ret.first < data[r - 1].first) {
        ret = data[r - 1];
      }
      r -= r & -r;
    }
    return ret;
  }
};

struct Solver {
  vll ans;
  vector<P> dp;
  BIT bit;
  Solver() : ans(), dp(args.max_t + 1, {0, INF}), bit(1 << 20) {}
  //
  void solve() {
    REPD(n, C.N) {
      int i = args.sorted.at(n);
      auto &cur = args.jobs.at(i);
      int rem_b = args.max_t - cur.first;
      int rem_e = args.max_t - cur.second;
      P tmpmax = bit.query(rem_e + 1);
      bit.set(rem_b, {tmpmax.first + 1, i});
    }
    ll cur = args.max_t - 0 + 1;
    while (0 <= cur) {
      P res = bit.query(cur);
      if (res.first == 0) {
        break;
      }
      ans.push_back(res.second + 1);
      cur = args.max_t - args.jobs.at(res.second).second + 1;
    }
  }

  void output() {
    pr(ans.size());
    prvec(ans);
  }

} s;

int main() {
  s.solve();
  s.output();
  return 0;
}
