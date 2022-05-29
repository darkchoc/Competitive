import numpy as np
import math
import sys
import random

y=[0]*200;
a=[0]*200;
b=[0]*200;
c=[0]*200;

for i in range(0,200):
	a[i] = random.uniform(1.0, 10.0)
	b[i] = random.uniform(10.0, 100.0)
	c[i] = random.uniform(5.0, 30.0)
	y[i] = 10*a[i] + 2*b[i] - 7*c[i]

data_file = open(sys.argv[1], 'w')

for i in range(0,200):
	row=""
	row+= str(y[i]) + " " + str(a[i]) + " " + str(b[i]) + " " + str(c[i])
	data_file.write('%s\n'%(row))

data_file.close()	
