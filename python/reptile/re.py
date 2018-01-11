#!/usr/bin/env python
# -*- coding: UTF-8 -*-

import re

pattern = re.compile(r'hello')

res1 = re.search(pattern, 'kskskhello dhls')
res2 = re.match(pattern, 'helloo CQC!')
res3 = re.match(pattern, 'helo CQC!')
res4 = re.match(pattern, 'kkskhello CQC')

if res1:
    print res1.group()
else:
    print '1 match failed'

if res2:
    print res2.group()
else:
    print '2 math failed'

if res3:
    print res3.group()
else:
    print '3 math failed'

if res4:
    print res4.group()
else:
    print '4 math failed!'


pattern = re.compile(r'\d+')
print re.split(pattern, 'one1two2three3four4five45578six')
print re.findall(pattern, 'one1two2three3four4five45578six')

for m in re.finditer(pattern, 'one1two2three3four4five45789six'):
    print m.group()

pattern = re.compile(r'(\w+) (\w+)')
s = 'i say, hello world!'
print re.sub(pattern, r'\2 \1', s)
print re.subn(pattern, r'\2 \1', s)

def func(m):
    #print m.group()
    return m.group(1).title() + ' ' + m.group(2).title()

print re.sub(pattern, func, s)
print re.subn(pattern, func, s)
