#!/usr/bin/env python

import getopt, sys, string, sys
from os import path, makedirs
import os.path

a = False
b = False
c = False
flag = False
d = False
e = False

print "#############"
print str(sys.argv[1])
filename_path_array=(str(sys.argv[1])).split(",")
filename_path = str(filename_path_array[0])
filename = path.basename(filename_path)
name = path.splitext(filename)[0]
print filename_path
print filename
print name
print filename_path.split('\\')
print filename_path.split('\\')[-1].split('/')[-1].split('.crt')[0]
print "---------------"

def main(argv):
    try:
        opts, args = getopt.getopt(argv,"abch", ["help", "flag", "a", "b", "c"])
        print("=============opts========")
        print "opts %s" %opts

        print("=============args========")
        print(args)
    except getopt.GetoptError:
        print "-------------except------------------"

"""
    for (opt,args) in opts:
        global a
        global b
        global c
        global flag
        global d
        global e
        if opt in ("-h", "--help")
            #usage()
        elif opt in '--flag'
            flag = True
            a = 'shared'
        elif opt in '--c'
            c = True
"""

if __name__ == "__main__":
    print sys.argv[1]
    main(sys.argv[1:]);
