#!/usr/bin/env python
# -*- coding UTF-8 -*-

import urllib
import urllib2


#------------------------set proxy---------------------------------------
enable_proxy = True
proxy_handler = urllib2.ProxyHandler({"http":'http://some-proxy.com:8080'})
null_proxy_handler = urllib2.ProxyHandler({})

if enable_proxy:
    opener = urllib2.build_opener(proxy_handler)
else:
    opener = urllib2.build_opener(proxy_handler)

urllib2.install_opener(opener)
#--------------------------------------------------------------------------------

value = {"username":"15275995159@163.com", "password":"xxxx"}
user_agent = 'Mozilla/5.0 (Windows NT 6.1; WOW64)'
headers = {'User-Agent':user_agent, 'Referer':'https://passport.csdn.net/account/login?ref=toolbar'}
data = urllib.urlencode(value)
url = "https://passport.csdn.net/account/login?ref=toolbar"   #/this is post
geturl = url + "?" + data #this is get
request = urllib2.Request(url, data, headers)
#request.get_method = lambda: 'PUT'   # or 'DELET' this is set for PUT and DELETE
response = urllib2.urlopen(request,timeout = 10)  #timeout is set timeout
#print response.read()
print geturl

request = urllib2.Request("https://cuiqinllgcai.com/961.html")
#urllib2.urlopen(request)
#'''
try:
    urllib2.urlopen(request)
    print "OK"
#except urllib2.HTTPError, e:
#    print "------except------"
#    print e.code
except urllib2.URLError, e:
    print "------except URL error------"
    print e.reason
#'''



