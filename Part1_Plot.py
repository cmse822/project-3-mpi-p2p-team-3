import pandas as p
import matplotlib.pyplot as plt
plt.rc('xtick', labelsize=20) 
plt.rc('ytick', labelsize=20) 

data = p.read_csv("Part1_Data_dev-intel18.txt")
data2 = p.read_csv("Part1_Data_dev-amd20.txt")

fig, ax = plt.subplots(figsize =(14, 8))
ax.set_title("Comparing Blocking on Two Different Hardwares",  fontsize = 30)
ax.set_ylabel("Average Communication Time (seconds)", fontsize = 25)
ax.set_xlabel("Message Size (Bytes)",  fontsize = 25)
ax.set_yscale('log')
ax.set_xscale('log')

ax.plot(data["Bytes"],data["TransferTime"], color = "red", label = "Dev-intel18")
ax.plot(data2["Bytes"],data2["TransferTime"], color = "blue", label = "Dev-amd20")
plt.legend(fontsize= 20)
plt.savefig("Part1.5.png")

fig, ax = plt.subplots(figsize =(14, 8))
ax.set_title("Comparing Blocking on Two Different Hardwares",  fontsize = 30)
ax.set_ylabel("Average Communication Time (seconds)", fontsize = 25)
ax.set_xlabel("Message Size (Bytes)",  fontsize = 25)
ax.set_yscale('log')
ax.set_xscale('log')

ax.plot(data["Bytes"],data["Bandwidth"], color = "red", label = "Dev-intel18")
ax.plot(data2["Bytes"],data2["Bandwidth"], color = "blue", label = "Dev-amd20")
plt.legend(fontsize= 20)
plt.savefig("Part1.5_BandWidth.png")

# ax2.set_ylabel("Bandwidth", color = "blue",  fontsize = 25)
# ax2.set_yscale('log')
# ax2.plot(data["Bytes"],data["Bandwidth"], color = "blue") # , label = "Bandwidth"

