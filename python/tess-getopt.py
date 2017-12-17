#!/bin/python

import getopt, sys, string


def main(argv):
    try:
        opts, args = getopt.getpt(agrv,"hi:o:", ["ifile=", "ofile="])

if __name__ == "__main__":
    print sys.argv[1]
    main(sys.argv[1:]);
