import numpy as np

n = np.loadtxt("all.txt", usecols=(0,))
name = np.loadtxt("all.txt", usecols=(0,), delimiter = '\n', dtype="string")

for i in range(len(name)):
    name[i] = name[i][2:]
    if name[i][0] == ' ':
        name[i] = name[i][1:]

dict = {}
copies = {}
deckcnt = 0
sideboard = True
count = np.zeros(60)
cardcnt = 0
entrycnt = 0
for i in range(len(name)):
    if name[i][0] < name[i-1][0]:
        #print cardcnt
        if cardcnt < 30: sideboard = False
        else: sideboard = True
        cardcnt = 0
    cardcnt += n[i]
    if(sideboard):
        if(copies.has_key(n[i])):
            copies[n[i]] += 1
        else:
            copies[n[i]] = 1
        if(dict.has_key(name[i])):
            dict[name[i]] += n[i]
        else:
            dict[name[i]] = n[i]
        

res = dict.items()
res2 = copies.items()

#print len(res)

for i in range(len(res)):
    print(res[i])

print(res2)
#print count