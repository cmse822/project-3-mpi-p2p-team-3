import pandas as pd
import matplotlib.pyplot as plt 

df2 = pd.read_csv('Part4_Data_2.txt', sep=',')
df4 = pd.read_csv('Part4_Data_4.txt', sep=',')
df8 = pd.read_csv('Part4_Data_8.txt', sep=',')
df16 = pd.read_csv('Part4_Data_16.txt', sep=',')
df32 = pd.read_csv('Part4_Data_32.txt', sep=',')
df64 = pd.read_csv('Part4_Data_64.txt', sep=',')
df128 = pd.read_csv('Part4_Data_128.txt', sep=',')

plt.figure(figsize=(14, 8))

plt.plot(df2['Bytes'].iloc[2:12], df2['Bandwidth'].iloc[2:12], marker='o', linestyle='-', color='blue', label='2 processes')
plt.plot(df4['Bytes'].iloc[2:12], df4['Bandwidth'].iloc[2:12], marker='s', linestyle='-', color='red', label='4 processes')
plt.plot(df8['Bytes'].iloc[2:12], df8['Bandwidth'].iloc[2:12], marker='s', linestyle='-', color='green', label='8 processes')
plt.plot(df16['Bytes'].iloc[2:12], df16['Bandwidth'].iloc[2:12], marker='s', linestyle='-', color='orange', label='16 processes')
plt.plot(df32['Bytes'].iloc[2:12], df32['Bandwidth'].iloc[2:12], marker='s', linestyle='-', color='black', label='32 processes')
plt.plot(df64['Bytes'].iloc[2:12], df64['Bandwidth'].iloc[2:12], marker='s', linestyle='-', color='pink', label='64 processes')
plt.plot(df128['Bytes'].iloc[2:12], df128['Bandwidth'].iloc[2:12], marker='s', linestyle='-', color='gray', label='128 processes')

plt.xlabel('Message Size (Bytes)')
plt.ylabel('Bandwidth (MB/s)')
plt.title('Bandwidth vs Message Size with Different Numbers of Processes (Non-Blocking, log scale)')

plt.xscale('log', base=2)
plt.yscale('log')

plt.legend()
plt.grid(True)
plt.show()


plt.figure(figsize=(14, 8))

plt.plot(df2['Bytes'], df2['TransferTime'], marker='o', linestyle='-', color='blue', label='2 processes')
plt.plot(df4['Bytes'], df4['TransferTime'], marker='s', linestyle='-', color='red', label='4 processes')
plt.plot(df8['Bytes'], df8['TransferTime'], marker='s', linestyle='-', color='green', label='8 processes')
plt.plot(df16['Bytes'], df16['TransferTime'], marker='s', linestyle='-', color='orange', label='16 processes')
plt.plot(df32['Bytes'], df32['TransferTime'], marker='s', linestyle='-', color='black', label='32 processes')
plt.plot(df64['Bytes'], df64['TransferTime'], marker='s', linestyle='-', color='pink', label='64 processes')
plt.plot(df128['Bytes'], df128['TransferTime'], marker='s', linestyle='-', color='grey', label='128 processes')

plt.xlabel('Message Size (Bytes)')
plt.ylabel('Latency(sec)')
plt.title('Latency vs Message Size with Different Numbers of Processes (Non-Blocking, log scale)')

plt.xscale('log', base=2)
plt.yscale('log')

plt.legend()
plt.grid(True)
plt.show()

#comparison
plt.figure(figsize=(14, 8))
df33 = pd.read_csv('/mnt/home/zhan2204/CMSE822/project-3-mpi-p2p-team-3/Part3_Data_32.txt', sep=',')
df44 = pd.read_csv('/mnt/home/zhan2204/CMSE822/project-3-mpi-p2p-team-3/Part4_Data_32.txt', sep=',')

plt.plot(df33['Bytes'], df33['Bandwidth'], marker='o', linestyle='-', color='blue', label='Blocking')
plt.plot(df44['Bytes'].iloc[2:12], df44['Bandwidth'].iloc[2:12], marker='o', linestyle='-', color='red', label='Non-Blocking')


plt.xlabel('Message Size (Bytes)')
plt.ylabel('Bandwidth (MB/s)')
plt.title('Bandwidth vs Message Size for Blocking and Non-Blocking MPI Ring Shift(32 processes,log scale)')

plt.xscale('log', base=2)
plt.yscale('log')

plt.legend()
plt.grid(True)
plt.show()

#figure comparison 
plt.figure(figsize=(14, 8))
df33 = pd.read_csv('/mnt/home/zhan2204/CMSE822/project-3-mpi-p2p-team-3/Part3_Data_32.txt', sep=',')
df44 = pd.read_csv('/mnt/home/zhan2204/CMSE822/project-3-mpi-p2p-team-3/Part4_Data_32.txt', sep=',')

plt.plot(df33['Bytes'], df33['TransferTime'], marker='o', linestyle='-', color='blue', label='Blocking')
plt.plot(df44['Bytes'].iloc[2:12], df44['TransferTime'].iloc[2:12], marker='o', linestyle='-', color='red', label='Non-Blocking')


plt.xlabel('Message Size (Bytes)')
plt.ylabel('Bandwidth (MB/s)')
plt.title('Lantency vs Message Size for Blocking and Non-Blocking MPI Ring Shift(32 processes,log scale)')

plt.xscale('log', base=2)
plt.yscale('log')

plt.legend()
plt.grid(True)
plt.show()