import pandas as pd
import matplotlib.pyplot as plt
from scipy import signal
import numpy as np

file_path = 'build/Desktop-Release/data.csv'  
data = pd.read_csv(file_path, header=None) 

# Plot the data
plt.figure(figsize=(10, 6))
plt.style.use("seaborn-v0_8")

plt.subplot(2, 1, 1)
plt.plot(data.columns, data.iloc[0], label="original")
plt.plot(data.columns, data.iloc[1], label="NCO (8-bit)")
plt.plot(data.columns, data.iloc[2], label="NCO (8-bit) with linear interpolation")
plt.title("Performance of NCO")
plt.legend()

plt.subplot(2, 1, 2)
fs = 1

f_original, Pxx_original = signal.welch(data.iloc[0].to_numpy(), fs, nperseg=1000)
Pxx_original = 10*np.log10(Pxx_original)

f_nco, Pxx_nco = signal.welch(data.iloc[1].to_numpy(), fs, nperseg=1000)
Pxx_nco = 10*np.log10(Pxx_nco)

f_nco_interp, Pxx_nco_interp = signal.welch(data.iloc[2].to_numpy(), fs, nperseg=1000)
Pxx_nco_interp = 10*np.log10(Pxx_nco_interp)

plt.plot(f_original, Pxx_original, label="original")
plt.plot(f_nco, Pxx_nco, label="NCO (8-bit)")
plt.plot(f_nco_interp, Pxx_nco_interp, label="NCO (8-bit) with linear interpolation")
plt.legend()
plt.title("Welch Spectrum")

plt.show()