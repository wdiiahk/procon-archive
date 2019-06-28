# -*- coding: utf-8 -*-
import sys
codes = input()

pre = ''
for code in codes:
  if pre == code:
    print('Bad')
    sys.exit()
  pre = code
print('Good')
