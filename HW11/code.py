from ulab import numpy as np

import time

t = np.linspace(0, 3.14*20, 1024)

t = np.arange(1024)

a = np.sin(t) + np.sin(3*t) + np.sin(5*t)

retval = np.fft.fft(a)

for i in range(1024) :

    mag = np.sqrt(retval[0][i] * retval[0][i] + retval[1][i] * retval[1][i])

    print("(" + str(mag) + ",)")

    time.sleep(.05)
