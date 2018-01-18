#!/usr/bin/env python
# -*- coding:utf-8 -*-

import sys
import getopt, string
from os import path,makedirs
import os.path
import re
from importH import *

str = ""
function = ""

classname = ""
functionname = []
functiontype = []
functionparam = []

h_file_name = ""
c_file_name = ""
def readFile():
    file = open(h_file_name, "rb")
    for line in file:
        l = line.strip()
        if l.startswith("class"):
            pattern = re.compile("^class (.*)[:].*[^;]$")
            temp = re.match(pattern, l)
            if temp:
                global classname
                classname =  temp.group(1)
                print classname
        else:
             pattern = re.compile("(.*) (.*)\((.*)\);$")
             temp = re.match(pattern, l)
             if temp:
                 functionname.append(temp.group(2))
                 functiontype.append(temp.group(1))
                 functionparam.append(temp.group(3))
                 #print functiontype
                 #print functionname
                 #print functionparam
    file.close()


def generateCode():
    global str
    str = '#include"dbclass.h"\n\n\n\n'
    lenght = len(functiontype)
    print lenght
    for i in range(lenght):
        function = functiontype[i] + " " +classname + "::"+ functionname[i]+"( "+functionparam[i]+ " )\n{\n}\n\n"
        str = str + function


def writeFile():
    getCfilepath()
    print c_file_name
    writef = open(getCfilepath(), "wb+")
    print writef.mode
    writef.write(str)
    writef.close()

def getCfilepath():
    c_file_name = re.sub(r'.h$', '.cpp', h_file_name)
    print c_file_name
    return c_file_name
def usage():
        """
        Help for the command line parser.
        """
        print 'cpp file Generator.'
        print 'Usage:'
        print ' -h: help'
        print ' -i: file'
        print ' --help: help'
        print ' --in: help'
        sys.exit(1)

def Entry():
    EntryParams()
    getCfilepath()
    hmatrix = importH(h_file_name)
    global str
    str = '#include"dbclass.h"\n\n'
    for i in range(len(hmatrix.GetFunctionC())):
        str = str + hmatrix.GetFunctionC()[i]
    #readFile()
    #generateCode()
    writeFile()

def EntryParams():
    try:
            opts, args = getopt.getopt(sys.argv[1:],'hi:', ['in=', 'help'])
            print opts
    except:
            print '------------exception------------'
            usage()

    for (opt,arg) in opts:
        global h_file_name

        if opt in ['-h', '--help']:
            usage()
        elif opt in ['-i', '--in']:
            if arg != "":
                h_file_name = arg
            else:
                h_file_name = None

if __name__ == '__main__':
    Entry()
    #print h_file_name

