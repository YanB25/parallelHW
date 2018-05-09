import matplotlib.pyplot as plt 
import csv
d = []
s = []
g = []
with open('../log/dummy.log', newline='\n') as csvfile:
    spamreader = csv.reader(csvfile, delimiter=',', quotechar='|')
    for row in spamreader:
        if row[0] == 'dynamic':
            d.append(float(row[-1].strip()))
        if row[0] == 'static':
            s.append(float(row[-1].strip()))
        if row[0] == 'guided':
            g.append(float(row[-1].strip()))
    x = [i+1 for i in range(len(d))]
fig, ax = plt.subplots() 
ax.plot(x, d, label='dynamic')
ax.plot(x, s, label='static')
ax.plot(x, g, label='guided')
ax.legend()
plt.show()