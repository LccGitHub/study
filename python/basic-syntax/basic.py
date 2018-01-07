#!/usr/bin/python
# -*- coding:UTF-8 -*-
import sys
import getopt, string
from os import path,makedirs
import os.path

'''
this is commit
'''


"""
this is also commit
"""


print "this is test,你好!"



x = 'a'
y = 'b'

print x
print y

print x,
print y

print x,y


par_int = 100
par_float = 100.0
par_str = "hello"
print par_int
print par_float
print par_str

print sys.argv
print sys.argv[1:]

def usage():
    print 'Usage:'
    print '-h:help'
    print '-3:option'


array=(str(sys.argv[1].split(",")))
print "aray="
filename= path.basename(array[0])
print "filename=" +path.basename(array[0])
print "name=" +path.splitext(filename)[0]


def judy():
    try:
        opts,args = getopt.getopt(sys.argv[1:], 'hi:o', ['help','input=','output='])
    except:
        print '-------------exception-------------------'
        usage()
        sys.exit()
    print "ok!!!!!!!!!!!!!!!!" 
    print opts
    print args
    sys.exit()


judy();
###########Python字符串###################
s="ilovepython"
print s[1:5]

'''
Python列表
List（列表） 是 Python 中使用最频繁的数据类型。

列表可以完成大多数集合类的数据结构实现。它支持字符，数字，字符串甚至可以包含列表（即嵌套）。

列表用 [ ] 标识，是 python 最通用的复合数据类型。

列表中值的切割也可以用到变量 [头下标:尾下标] ，就可以截取相应的列表，从左到右索引默认 0 开始，从右到左索引默认 -1 开始，下标可以为空表示取到头或尾。

加号 + 是列表连接运算符，星号 * 是重复操作。
'''
list=["runoob", 785, "john", 12.3, "sjsjsj", 78]
tinylist=[123, "john"]
print list
print list[1:3]
print list[2:]
print tinylist *2
print list+tinylist

'''
Python元组
元组是另一个数据类型，类似于List（列表）。

元组用"()"标识。内部元素用逗号隔开。但是元组不能二次赋值，相当于只读列表。""
'''

tuple=('runoob', 786, 2.23, 'john', 70.2)
tinytuple=(123,'jonh')
print tuple
print tuple[0]
print tuple[1:3]
print tuple[2:]
print tinytuple*2
print tuple+tinytuple

'''
Python 字典
字典(dictionary)是除列表以外python之中最灵活的内置数据结构类型。列表是有序的对象集合，字典是无序的对象集合。

两者之间的区别在于：字典当中的元素是通过键来存取的，而不是通过偏移存取。

字典用"{ }"标识。字典由索引(key)和它对应的值value组成。
'''
dict={}
dict['one']="this is one"
dict[2]="this is two"
tinydict={'name':'john', 'code':6743, 'dept':'sales'}

print dict['one']
print dict[2]
print tinydict
print tinydict.keys()
print tinydict.values()


