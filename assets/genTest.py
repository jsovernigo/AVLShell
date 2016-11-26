#!/usr/bin/python

from random import *

prefixes = ["flr","wrn"]

def generate_words(numTests, srange, erange):
    global prefixes
    testCases = []
    if srange > erange: 
        return None
    for i in range(0,numTests):
        post = randint(srange, erange)
        pre = prefixes[randint(0,len(prefixes))-1]
        case = pre
        case += str(post)
        testCases.append(case)

    return testCases

cases = generate_words(10,100,110)

for s in cases:
    print s



