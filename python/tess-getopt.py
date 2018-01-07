#!/usr/bin/python

import getopt, sys, string, sys, os


def main(argv):
    try:
        opts, args = getopt.getopt(argv,"hi:o:", ["ifile=", "ofile="])
        print("=============opts========")
        print(opts)

        print("=============args========")
        print(args)
    except getopt.GetoptError:
        print "-------------except------------------"

if __name__ == "__main__":
    print sys.argv[1]
    main(sys.argv[1:]);
