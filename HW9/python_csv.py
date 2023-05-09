import csv
import numpy as np
import matplotlib.pyplot as plt

t = [] # column 0
data1 = [] # column 1

with open('sigA.csv') as f:
    # open the csv file
    reader = csv.reader(f)
    for row in reader:
        # read the rows 1 one by one
        t.append(float(row[0])) # leftmost column
        data1.append(float(row[1])) # second column

data = np.array(data1)

data_fft = np.fft.fft(data1)

fs = len(t) / max(t)
hsize = np.round(len(t)/2).astype(int)
f = np.linspace(0, fs/2, hsize)

# N_maf
# sigA : 10
# sigB : 80
# sigC : 50
# sigD : 10

# N_maf = 50
# data_pad = np.concatenate((np.zeros(N_maf-1), data))
# data_maf = []

# for i in range(np.size(data)):

#     data_maf.append(np.mean(data_pad[i:i+N_maf]))

# data_maf = np.array(data_maf)
# data_fft_maf = np.fft.fft(data_maf)

# A
# sigA : 0.9
# sigB : 0.99
# sigC : 0.99
# sigD : 0.8

# avg = 0
# data_iir = []
# A = 0.8
# B = 1 - A

# for i in range(np.size(data)):

#     avg = A * avg + B * data[i]
#     data_iir.append(avg)

# data_iir = np.array(data_iir)
# data_fft_iir = np.fft.fft(data_iir)

# fs = 10000 Hz
# cutoff = 500 Hz
# bandwidth = 500 Hz
# window = blackman
# 93 coefficients

h = [
    0.000000000000000000,
    0.000002974501611384,
    0.000011630961589138,
    0.000022967232209164,
    0.000030716225059778,
    0.000026214839732923,
    0.000000000000000000,
    -0.000055973251773900,
    -0.000145723873974251,
    -0.000266615935880751,
    -0.000407198371448263,
    -0.000546075600414797,
    -0.000652361272314452,
    -0.000688147432914718,
    -0.000613179612975004,
    -0.000391575659878668,
    0.000000000000000001,
    0.000563732118198938,
    0.001273013656973618,
    0.002067373906878073,
    0.002851563067893035,
    0.003500082348355214,
    0.003867862608841334,
    0.003806962971094718,
    0.003188176579066728,
    0.001925429347868523,
    -0.000000000000000002,
    -0.002518961647177853,
    -0.005461249814074702,
    -0.008552964568398333,
    -0.011426676391665728,
    -0.013645225159174835,
    -0.014738246181366184,
    -0.014248680591636921,
    -0.011784851782051391,
    -0.007072431628762949,
    0.000000000000000003,
    0.009347935765629322,
    0.020675604354698812,
    0.033481714360691445,
    0.047087359848541926,
    0.060684558865161380,
    0.073401325498431910,
    0.084376989102916758,
    0.092839977176476990,
    0.098179693861485506,
    0.100004559152954045,
    0.098179693861485506,
    0.092839977176476990,
    0.084376989102916772,
    0.073401325498431910,
    0.060684558865161380,
    0.047087359848541920,
    0.033481714360691452,
    0.020675604354698819,
    0.009347935765629319,
    0.000000000000000003,
    -0.007072431628762950,
    -0.011784851782051391,
    -0.014248680591636925,
    -0.014738246181366184,
    -0.013645225159174839,
    -0.011426676391665735,
    -0.008552964568398330,
    -0.005461249814074704,
    -0.002518961647177854,
    -0.000000000000000002,
    0.001925429347868524,
    0.003188176579066726,
    0.003806962971094720,
    0.003867862608841335,
    0.003500082348355213,
    0.002851563067893038,
    0.002067373906878075,
    0.001273013656973618,
    0.000563732118198938,
    0.000000000000000001,
    -0.000391575659878668,
    -0.000613179612975004,
    -0.000688147432914718,
    -0.000652361272314452,
    -0.000546075600414798,
    -0.000407198371448264,
    -0.000266615935880751,
    -0.000145723873974251,
    -0.000055973251773899,
    0.000000000000000000,
    0.000026214839732923,
    0.000030716225059778,
    0.000022967232209164,
    0.000011630961589138,
    0.000002974501611384,
    0.000000000000000000,
]

N_fir = 93
data_pad = np.concatenate((np.zeros(N_fir-1), data))

data_fir = np.convolve(data_pad, h, mode="valid")


data_fir = np.array(data_fir)
data_fft_fir = np.fft.fft(data_fir)

plt.subplot(2,1,1)
plt.plot(t, data, "k")
plt.plot(t, data_fir, "r")
plt.xlabel("Time")
plt.ylabel("Signal")
plt.title("cutoff = 500 Hz, bandwidth = 500 Hz, Blackman")

plt.subplot(2,1,2)
plt.plot(f, np.log(data_fft[:hsize]), "k")
plt.plot(f, np.log(data_fft_fir[:hsize]), "r")
plt.xlabel("Frequency")
plt.ylabel("FFT")

plt.show()

