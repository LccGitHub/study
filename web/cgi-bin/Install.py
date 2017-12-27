#!/usr/bin/python

import cgi
import os

def main():
    print "Content-type: text/html"
    print "" 
    message = '{\"installResult\":\"installFail\"}'
    message = '{\"installResult\":\"installSuccess\"}'

    print message

main()

