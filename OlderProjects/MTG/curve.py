#from __future__ import division
import numpy as np
import numpy.random as rnd

r = 1.5
decksize = 60
curve = np.array([23,18,19,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0])
turndist = np.array([0,0,0,0,0,1,1,1,1,
                     1,1,1, 1, 1, 1, 1, 1])
deck = np.zeros(0)
for i in range(18):
    for j in range(curve[i]):
        deck = np.append(deck,i)
mana_avg = np.zeros(100)
repeats = 1
for m in range(100):
    mana_used = np.zeros(100000)
    remove = 0
    add = 0
    while remove == add:
        remove = rnd.randint(4)
        while curve[remove] == 0:
            remove = rnd.randint(6)
        add = rnd.randint(6)
    curve[add] += 1
    curve[remove] -= 1
    deck = np.zeros(0)
    for i in range(18):
        for j in range(curve[i]):
            deck = np.append(deck,i)
    for n in range(100000):
        #print "new game"
        rnd.shuffle(deck)

        hand = np.zeros(18)

        for i in range(7):
            hand[deck[i]] += 1

        drawn = 7
        mana = 0
        numT = 0
        rand = rnd.random()
        for i in range(len(turndist)):
            if rand < turndist[i]:
                numT = i
                break
        if hand[0] < 2 or hand[0] > 4:
            #print "mulled to 6"
            hand = np.zeros(18)
            rnd.shuffle(deck)
            for i in range(6):
                hand[deck[i]] += 1
            drawn  = 6
            if hand[0] > 1 and deck[drawn] == 0:
                drawn += 1
                #print "scryed to bottom"
            elif hand[0] < 2 and deck[drawn] != 0:
                drawn += 1
                #print "scryed to bottom"
    
        if hand[0] < 1 or hand[0] > 4:
            #print "mulled to 5"
            hand = np.zeros(18)
            rnd.shuffle(deck)
            for i in range(5):
                hand[deck[i]] += 1
            drawn = 5
            if hand[0] > 1 and deck[drawn] == 0:
                drawn += 1
                #print "scryed to bottom"
            elif hand[0] < 2 and deck[drawn] != 0:
                drawn += 1
                #print "scryed to bottom"

        if hand[0] < 1 or hand[0] > 4:
            #print "mulled to 4"
            hand = np.zeros(18)
            rnd.shuffle(deck)
            for i in range(4):
                hand[deck[i]] += 1
            drawn = 4
            if hand[0] > 1 and deck[drawn] == 0:
                drawn += 1
                #print "scryed to bottom"
            elif hand[0] < 2 and deck[drawn] != 0:
                drawn += 1
                #print "scryed to bottom"
        #print "initial hand", hand
        if rnd.random() > .5:
            numT -= 1
            hand[deck[drawn]] += 1
            drawn += 1
        for i in range(1,numT):
            #print "turn", i
            if i > 1:
                hand[deck[drawn]] += 1
                drawn += 1
                #print "hand", hand
            if hand[0] > 0:
                hand[0] -= 1
                mana += 1
                #print "played land", mana
            if hand[mana] > 0:
                hand[mana] -= 1
                mana_used[n] += mana*(numT-i)
                #print "played", mana, "mana card", "total", mana_used[n]
                continue
            done = False
            for j in range(1, mana/2 + 1):
                if hand[j] > 0 and hand[mana-j] > 0:
                    if not mana == 2*j or hand[j] > 1:
                        hand[j] -= 1
                        mana_used[n] += j*(numT-i)
                        #print "played", j, "mana card", "total", mana_used
                        hand[mana-j] -= 1
                        mana_used[n] += (mana - j)*(numT - i)
                        #print "played", mana - j, "mana card", "total", mana_used
                        mana_used[n] += mana
                        done = True
                        break
            tmana = 0
            if not done:
                for j in range(mana,0,-1):
                    while True:
                        if j > mana - tmana: break
                        if hand[j] > 0:
                            hand[j] -= 1
                            #print "played", j, "mana card"
                            tmana += j
                            mana_used[n] += j*(numT-i)
                        else: break
        mana_used[n] /= numT-1
    mana_avg[m] = np.mean(mana_used)
    kT = .003
    if mana_avg[m] < mana_avg[m-repeats] and m > 0:
        if rnd.random() > np.exp((mana_avg[m]-mana_avg[m-repeats])/kT):
            #print m
            #print curve
            #print "avg mana used", mana_avg[m]
            curve[add] -= 1
            curve[remove] += 1
            repeats += 1
        else: 
            repeats = 1
            print(m)
            print(curve)
            print("avg mana used", mana_avg[m])
    else: 
        repeats = 1
        print(m)
        print(curve)
        print("avg mana used", mana_avg[m])
print(curve)
print(mana_avg[-repeats])