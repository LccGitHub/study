#!/usr/bin/env python
# -*- coding:utf-8 -*-

import sys
import getopt, string
from os import path,makedirs
import os.path
import re

classname = ""
def importH(h_file_name):
    global classname
    file = open(h_file_name, "rb")
    hMatrix = HMatrix()
    for line in file:
        l = line.strip()
        if l.startswith("class"):
            print l
            print len(l)
            #pattern = re.compile("^class (.*) [^;]$")
            pattern = re.compile("^class (.*)")
            temp = re.match(pattern, l)
            if temp:
                hMatrix.addClassName(temp.group(1))
                classname = temp.group(1)
                print classname
                print len(classname)
        elif l.startswith(hMatrix.getClassName()):
            pattern = re.compile("(.*);$")
            temp = re.match(pattern, l)
            if temp:
                hMatrix.addConstrName(temp.group(1))
        elif l.startswith("~"):
            pattern = re.compile("(.*);$")
            temp = re.match(pattern, l)
            if temp:
                hMatrix.addDeconstrName(temp.group(1))
        else:
             pattern = re.compile("(.*) (.*)\((.*)\);$")
             temp = re.match(pattern, l)
             if temp:
                 hMatrix.addFuncType(temp.group(1))
                 hMatrix.addFuncName(temp.group(2))
                 hMatrix.addFuncParam(temp.group(3))
    file.close()
    return hMatrix

class HMatrix:
    def __init__(self):
        self._className = ""
        self._functiontype = []
        self._functionname = []
        self._functionparam = []
        self._function = []
        self._construction = ""
        self._deconstruction = ""
    def addClassName(self, value):
        self._className =value
    def addConstrName(self, value):
        print value
        self._construction =value
    def addDeconstrName(self, value):
        self._deconstruction =value
    def addFuncType(self, value):
        self._functiontype.append(value)
    def addFuncName(self, value):
        self._functionname.append(value)
    def addFuncParam(self, value):
        self._functionparam.append(value)
    def getClassName(self):
        return self._className
    def GetFunctionC(self):
        self._function.append(self._className + "::" + self._construction + "\n{\n}\n")
        self._function.append(self._className + "::" + self._deconstruction + "\n{\n}\n")
        for i in range(len(self._functionname)):
            str = ""
            str = self._functiontype[i] + " " + self._className + "::" + self._functionname[i] + "("+ self._functionparam[i] + ")\n{\n}\n\n"
            self._function.append(str)
        return self._function





