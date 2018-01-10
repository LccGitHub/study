#!/usr/bin/env python
# -*- coding: UTF-8 -8-

import cookielib
import urllib2
import urllib


filename = 'cookie-result.txt'
cookie = cookielib.MozillaCookieJar(filename)    # this is set for get cookie by file
#cookie = cookielib.CookieJar()
handler = urllib2.HTTPCookieProcessor(cookie)
postdata = urllib.urlencode({'用户名':'cjckck','密码':'111111'})
opener = urllib2.build_opener(handler)
response = opener.open("https://passport.csdn.net/account/login?ref=toolbar", postdata)
for item in cookie:
    print 'Name = ' + item.name
    print 'Vaule = ' + item.value
cookie.save(ignore_discard=True, ignore_expires = True) # this is set for save cookie to file

request = "http://oa-center/default.aspx"
response = opener.open(request)
print response.read()
#----------------------------------------------
cookie = cookielib.MozillaCookieJar()    # this is set for get cookie by file
cookie.load('cookie-result.txt', ignore_discard=True, ignore_expires = True) # this is set for save cookie to file
#cookie = cookielib.CookieJar()
request = urllib2.Request("http://my.csdn.net/?ref=toolbar")
handler = urllib2.HTTPCookieProcessor(cookie)
opener = urllib2.build_opener(handler)
response = opener.open(request)
#print response.read()
