#
import pandas as pd
import matplotlib.pyplot as plt 

df2 = pd.read_csv('Part3_Data_2.txt', sep=',')
df4 = pd.read_csv('Part3_Data_4.txt', sep=',')
df8 = pd.read_csv('Part3_Data_8.txt', sep=',')
df16 = pd.read_csv('Part3_Data_16.txt', sep=',')
df32 = pd.read_csv('Part3_Data_32.txt', sep=',')
df64 = pd.read_csv('Part3_Data_64.txt', sep=',')
df128 = pd.read_csv('Part3_Data_128.txt', sep=',')

plt.figure(figsize=(14, 8))

plt.plot(df2['Bytes'], df2['Bandwidth'], marker='o', linestyle='-', color='blue', label='2 processes')
plt.plot(df4['Bytes'], df4['Bandwidth'], marker='s', linestyle='-', color='red', label='4 processes')
plt.plot(df8['Bytes'], df8['Bandwidth'], marker='s', linestyle='-', color='green', label='8 processes')
plt.plot(df16['Bytes'], df16['Bandwidth'], marker='s', linestyle='-', color='orange', label='16 processes')
plt.plot(df32['Bytes'], df32['Bandwidth'], marker='s', linestyle='-', color='black', label='32 processes')
plt.plot(df64['Bytes'], df64['Bandwidth'], marker='s', linestyle='-', color='pink', label='64 processes')
plt.plot(df128['Bytes'], df128['Bandwidth'], marker='s', linestyle='-', color='gray', label='128 processes')

plt.xlabel('Message Size (Bytes)')
plt.ylabel('Bandwidth (MB/s)')
plt.title('Bandwidth vs Message Size with Different Numbers of Processes (Blocking, log scale)')

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
plt.title('Latency vs Message Size with Different Numbers of Processes (Blocking, log scale)')

plt.xscale('log', base=2)
plt.yscale('log')

plt.legend()
plt.grid(True)
plt.show()