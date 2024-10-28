import pandas as pd
import matplotlib.pyplot as plt

file_path = 'build/Desktop-Release/data.csv'  
data = pd.read_csv(file_path, header=None) 

# Plot the data
plt.figure(figsize=(10, 6))

plt.plot(data.columns, data.iloc[0], label="original")
plt.plot(data.columns, data.iloc[1], label="NCO (8-bit)")
plt.plot(data.columns, data.iloc[2], label="NCO (8-bit) with linear interpolation")

plt.title("Performance of NCO")
plt.legend()
plt.show()