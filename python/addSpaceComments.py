#!/usr/bin/python
# -*- coding:utf-8 -*-


import os
import fileinput


hHead1 = '''/**
 * Copyright @ 2013 - 2014 Suntec Software(Shanghai) Co., Ltd.
 * All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are NOT permitted except as agreed by
 * Suntec Software(Shanghai) Co., Ltd.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 */
/**
''' 

hHead2 = '''* @file '''
hHead3 = '''\n* @brief Declaration file of class '''

hHead4 = '''
 *
 * This file includes the declaration of class '''

hHead5 = ''', and
 * the definitions of the macros, struct, enum and so on.
 *
 * @attention used for C++ only.
 */



'''


cppHeader = '''/**
 * Copyright @ 2013 - 2014 Suntec Software(Shanghai) Co., Ltd.
 * All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are NOT permitted except as agreed by
 * Suntec Software(Shanghai) Co., Ltd.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 */


'''


hplusplus = '''#ifndef __cplusplus
#    error ERROR: This file requires C++ compilation (use a .cpp suffix)
#endif

'''

classDesciptionclassDesciption = '''/**
 * Class Summary description:
 * Class Details description:
 * 
 * @attention:
 * @warning:
 * @warning:
 * @bug:
'''



# add space befor '/*' or '*/' or '//', such as /*adde*/ shoule be /* adde */
def addSpaceInComments(line):
    index = line.find("/*")
    lastindex = line.find("*/")
    indexSlash = line.find("//")

    #print index
    #print lastindex
    #print indexSlash
    #print line
    newline = ""
    # only match format : no /* */ //
    if (index == -1 and lastindex == -1) and indexSlash == -1:
        newline = line
    # only match format: /*ssss*/    
    elif ((index == 0 and line[index+2] != ' ') and (lastindex != -1 and line[lastindex-1] != ' ')):
        newline = line[:index+2] + ' ' + line[index+2:lastindex] + ' ' + line[lastindex:]
    #only math format: ;/*sss*/
    elif ((index >= 1 and line[index+2] != ' ') and (lastindex != -1 and line[lastindex-1] != ' ')):
        newline = line[:index] + ' ' + line[index:index+2] + ' ' + line[index+2:lastindex] + ' ' + line[lastindex:]
    # only /*sss */ or /*lsslsl
    elif (index == 0 and line[index+2] != ' '): 
        newline = line[:index+2] + ' ' + line[index+2:]
    # only ;/*sss */ 
    elif ((index >= 1 and line[index+2] != ' ' ) and (line[index-1] != ' ')):
        newline = line[:index] + ' ' + line[index:index+2] + ' ' + line[index+2:]
    # only ;/*lsslsl
    elif ((index >= 1 and line[index-1] != ' ' )):
        newline = line[:index] + ' ' + line[index:]
    # only math format:/* ddd*/ or sss*/
    elif (lastindex != -1 and line[lastindex-1] != ' '):
        newline = line[:lastindex] + ' ' + line[lastindex:]
    elif indexSlash == 0 and line[indexSlash+2] != ' ':
        newline = line[:indexSlash+2] + ' ' + line[indexSlash+2:]
    elif indexSlash >= 1 and line[indexSlash+2] != ' ':
        newline = line[:indexSlash] + ' ' + line[indexSlash:indexSlash+2] + ' ' + line[indexSlash+2:]
    else :
        newline = line
    return newline


# add space befor ',', such as printf("%s,%d", __func__,__LINE__) shoule be printf("%s, %d", __func__, __LINE__)
def addSpaceBeforComma(line):
    newline = ""
    for index in range(len(line)) :
        if index < len(line)-1 and line[index] == ','  and (line[index+1] != ' ' and line[index+1] != '\n' ):
            newline = newline + line[index] + ' '
        else :
            newline = newline + line[index]
    return newline

# remove extra space befor '(', such as if (a ) shoule be if (a)
def removeSpaceBeforBrackts(line):
    newline = ""
    for index in range(len(line)) :
        if index < len(line)-1 and line[index] == ' '  and (line[index+1] == ')'):
            print line[index]
            # remove ''
        else:
            newline = newline + line[index]
    return newline

''' add header information in .cpp file
/**
 * Copyright @ 2013 - 2014 Suntec Software(Shanghai) Co., Ltd.
 * All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are NOT permitted except as agreed by
 * Suntec Software(Shanghai) Co., Ltd.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 */
/**
 * @file Sample.h                                            
 * @brief Declaration file of class Sample.                   
 *
 * This file includes the declaration of class Sample, and   
 * the definitions of the macros, struct, enum and so on.
 *
 * @attention used for C++ only.
 */
'''
def addHfileHeader(fileName):
    className = os.path.splitext(fileName)[0]
    global hHead1
    global hHead2 
    global hHead3 
    global hHead4 
    global hHead5 
    newline = hHead1 + hHead2 + fileName + hHead3 + className + "." + hHead4 + className+ hHead5
    return newline

''' add header information protect macro in .cpp file
/**
 * Copyright @ 2013 - 2014 Suntec Software(Shanghai) Co., Ltd.
 * All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are NOT permitted except as agreed by
 * Suntec Software(Shanghai) Co., Ltd.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 */
'''
def addCppHeader():
    global cppHeader
    newline = cppHeader
    return newline



''' add header file protect macro in .h file
#ifdef *__H
#deinfe *_H
'''
def addFileContianDefine(fileName):
    className = os.path.splitext(fileName)[0]
    newline = "#ifndef " + className + "_H\n" + "#define" + className + "_H\n"
    return newline

''' add above format context in .h file
#ifndef __cplusplus
#    error ERROR: This file requires C++ compilation (use a .cpp suffix)
#endif
'''
def addHfileCplus():
    global hplusplus
    newline = hplusplus
    return newline


''' add EOF in end of file '''
def addEOF():
    newline = "/* EOF */"
    return newline

def checIsContain(line, word):
    index = line.find(word)
    if index != -1:
        return True
    else:
        return False

def checkIsHfile(fileName):
    return checIsContain(fileName, ".h")

def checkHaveCopyRight(line):
    return checIsContain(line, "Copyright")

def checkHaveEOF(line):
    return checIsContain(line, "EOF")

def checkHaveCplusCplus(line):
    return checIsContain(line, "__cpluscplus")

def addClassDesription():
    global classDesciptionclassDesciption
    newline = classDesciptionclassDesciption
    return newline



def checkAndFixFileCppInt(filePath):
    isHFile = False
    haveCopyright = False
    haveEOF = False
    haveCplusCplus = False

    contex = ""
    base = os.path.basename(filePath)
    if checkIsHfile(base):
        isHFile = True

    for line in fileinput.input(filePath):

    #check if contaion som inforamtion
        if haveEOF == False and checkHaveEOF(line):
            haveEOF = True

        if haveCopyright == False and checkHaveCopyRight(line):
            haveCopyright = True

        if isHFile == True and haveCplusCplus == False and checkHaveCplusCplus(line):
            haveCplusCplus = True

# fix cppin error
        newline = addSpaceInComments(line)
        newline = removeSpaceBeforBrackts(newline)
        newline = addSpaceBeforComma(newline)
        contex = contex + newline
    # for end

# add fixed format
    if isHFile == True and haveCopyright == False and haveCplusCplus == False:
        contex = addHfileHeader(base) + addHfileCplus() + contex
    elif isHFile == False and haveCopyright == False:
        contex = addCppHeader() + contex
    else:
        print "have contain Copyrignt\n"

#write fix context to origianl file
    fo = open(filePath, "w")
    fo.write(contex)
    fo.close()



dirPath = "src/gnss/"
for root, dirs, files in os.walk(dirPath):
    for filesName in files:
        newFileName = dirPath + filesName
        checkAndFixFileCppInt(newFileName)




