import matplotlib.pyplot as plt 
import csv
import pandas as pd 
import numpy as np
table=[]
with open('../log/cache.log', newline='\n') as csvfile:
    spamreader = csv.reader(csvfile, delimiter=',', quotechar='|')
    for row in spamreader:
        table.append([i.strip() for i in row])

df = pd.DataFrame(table, columns=["testcase", "useOMP", "time", "threadnum", "collapse"])
one = df[df.testcase== '0'][df.collapse == '1']
two = df[df.testcase== '0'][df.collapse == '2']
three = df[df.testcase== '0'][df.collapse == '3']
#print(one['time'].tolist())
fig, ax = plt.subplots()
sample = [float(i) for i in one['time'].tolist()]
ax.plot([i for i in range(128)], one['time'].tolist(), label="one")
ax.plot([i for i in range(128)], two['time'].tolist(), label="two")
ax.plot([i for i in range(128)], three['time'].tolist(), label="three")
plt.xlabel('num of threads')
plt.ylabel('time(ms)')
print(min(sample))
print(max(sample))
#plt.yticks(np.arange(min(sample), max(sample), (max(sample)-min(sample)) / 20))
plt.yticks(np.arange(1, 300, 20))
# print(np.arange(0.0004, 0.001, step=0.0001))
# plt.yticks(np.arange(0.0004, 0.001, step=0.0001))
ax.legend()
plt.show()