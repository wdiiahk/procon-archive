class Const:
    N, K = map(int, input().split())
    S = input()


C = Const()


class Solver:
    ans = 0

    def decode(self):
        ret = []
        left = 0
        while (left < C.N):
            right = left
            t = C.S[left]
            while (right < C.N and t == C.S[right]):
                right += 1
            ret.append((t, right - left))
            left = right
        return ret

    def solve(self):
        res = self.decode()
        rem = C.K
        for i, (c, n) in enumerate(res):
            if (rem == 0):
                continue
            if (i % 2 == 0):
                continue
            res[i] = ('R' if c == 'L' else 'L', n)
            rem -= 1
        pre = 'A'
        for c, n in res:
            self.ans += n
            if pre != c:
                self.ans -= 1
            pre = c

    def output(self):
        print(self.ans)


s = Solver()
s.solve()
s.output()
