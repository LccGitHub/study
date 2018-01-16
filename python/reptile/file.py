#!/usr/bin/env python
# -*- coding:utf-8 -*-

import re

classname = ""
functionname = []
functiontype = []
functionparam = []
file = open("../../c++/dbclass.h") 
for line in file:
    l = line.strip()
    if l.startswith("class"):
        pattern = re.compile("^class (.*)")
        temp = re.match(pattern, l)
        if temp:
            classname =  temp.group(1)
            print classname
    else:
        pattern = re.compile("(.*) (.*)\((.*)\);$")
        temp = re.match(pattern, l)
        if temp:
            functionname.append(temp.group(2))
            functiontype.append(temp.group(1))
            functionparam.append(temp.group(3))
        print functiontype
        print functionname
        print functionparam
file.close()


str = ""
function = ""
lenght = len(functiontype)
print lenght

str = '#include"dbclass.h"\n\n\n\n'
for i in range(lenght):
    function = functiontype[i] + " " +classname + "::"+ functionname[i]+"( "+functionparam[i]+ " )\n{\n}\n\n" 
    str = str + function

writef = open("../../c++/dbclass.cpp", "wb+")
writef.write(str)
writef.close()
