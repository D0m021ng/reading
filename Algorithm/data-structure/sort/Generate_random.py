#!/usr/bin/python

import random

fin = open("input_10", "wb")
n = 50000
fin.write(str(n))
fin.write("\n")
for i in range(n):
	rand = random.randint(0, 69999);
	fin.write(str(rand))
	fin.write(" ")
	# print rand