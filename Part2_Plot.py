import pandas as p
import matplotlib.pyplot as plt
plt.rc('xtick', labelsize=20) 
plt.rc('ytick', labelsize=20) 

data = p.read_csv("Part2_Data.txt")
data2 = p.read_csv("Part2_Data_sep_nodes.txt")

fig, ax = plt.subplots(figsize =(14, 8))
ax.set_title("Transfer Time for Non-Blocking Pingpong",  fontsize = 30)
ax.set_ylabel("Average Communication Time (seconds)", fontsize = 25)
ax.set_xlabel("Message Size (Bytes)",  fontsize = 25)
ax.set_yscale('log')
ax.set_xscale('log', base=2)

ax.plot(data["Bytes"],data["TransferTime"], color = "red", label='Non-Blocking')
ax.plot(data2["Bytes"],data2["TransferTime"], color = "red", marker='o', label='Non-Blocking, sep. nodes')
plt.legend(fontsize= 20)
plt.savefig("Part2.5.png")

fig, ax = plt.subplots(figsize =(14, 8))
ax.set_title("Bandwidth for Non-Blocking Pingpong",  fontsize = 30)
ax.set_ylabel("Bandwidth", fontsize = 25)
ax.set_xlabel("Message Size (Bytes)",  fontsize = 25)
ax.set_yscale('log')
ax.set_xscale('log', base=2)

ax.plot(data["Bytes"],data["Bandwidth"], color = "red", label='Non-Blocking')
ax.plot(data2["Bytes"],data2["Bandwidth"], color = "red", marker='o', label='Non-Blocking, sep. nodes')
plt.legend(fontsize= 20)
plt.savefig("Part2.5_BandWidth.png")

# ax2.set_ylabel("Bandwidth", color = "blue",  fontsize = 25)
# ax2.set_yscale('log')
# ax2.plot(data["Bytes"],data["Bandwidth"], color = "blue") # , label = "Bandwidth"

