#!/usr/bin/env python

"""client_sim.py:  Acts as an http client and establishes a connection with the esp2866.  It then sends a request
                    for potentiometer values and prints the reponse"""

__author__ = "Joshua Hannan"

import os
import sys

import httplib


def main():
    url = '192.168.1.244'
    # Establishes connection with an http server
    h1 = httplib.HTTPConnection(url)

    # sends a request for information
    h1.request("GET",url)

    # puts the response in an object
    r1 = h1.getresponse()

    # prints the response's metadata and contents
    print(r1.status, r1.reason)
    data1 = r1.read()
    print(data1)
    # my code here

if __name__ == "__main__":
    main()

