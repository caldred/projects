import numpy as np

pool_size = 1000000000000000
p_win = np.loadtxt("p_win.in")
p_pick = np.loadtxt("p_pick.in")
p_win = (6*p_win + p_pick)/7
teams = np.loadtxt("teams.in", dtype = "string", delimiter = "\n")
adj = np.array([.013, .0604, .05, .131, .26, 0])
adj = np.array([.01, .02, .04, .08, .16, 0])

tmp = np.zeros(64)
index = np.zeros(64)
for i in range(64):
    if i%16 == 0:
        index[i] = 0
    elif i%8 == 0:
        index[i] = 1
    elif i%4 == 0:
        index[i] = 3 - index[i-4]
    elif i%2 == 0:
        index[i] = 7 - index[i-2]
    else:
        index[i] = 15 - index[i-1]
    tmp[i] = index[i]+16*int(i/16)
index = tmp

def invin(ind):
    if ind%16 == 0: return 1+16*int(ind/16)-1
    if ind%16 == 1: return 9+16*int(ind/16)-1
    if ind%16 == 2: return 13+16*int(ind/16)-1
    if ind%16 == 3: return 5+16*int(ind/16)-1
    if ind%16 == 4: return 7+16*int(ind/16)-1
    if ind%16 == 5: return 15+16*int(ind/16)-1
    if ind%16 == 6: return 11+16*int(ind/16)-1
    if ind%16 == 7: return 3+16*int(ind/16)-1
    if ind%16 == 8: return 4+16*int(ind/16)-1
    if ind%16 == 9: return 12+16*int(ind/16)-1
    if ind%16 == 10: return 16+16*int(ind/16)-1
    if ind%16 == 11: return 8+16*int(ind/16)-1
    if ind%16 == 12: return 6+16*int(ind/16)-1
    if ind%16 == 13: return 14+16*int(ind/16)-1
    if ind%16 == 14: return 10+16*int(ind/16)-1
    if ind%16 == 15: return 2+16*int(ind/16)-1
    
def noone(pool_size, p_win, p_pick, pick):
    p_noone = np.zeros((6,32))
    for k in range(6):
        for i in range(2**(5-k)):
            for j in range(2**(k+1)):
                if index[2**(k+1)*i+j] != pick:
                    p_noone[k][i] += p_win[index[2**(k+1)*i+j]][k]*(1-p_pick[index[2**(k+1)*i+j]][k])**pool_size
    return p_noone

def values(pool_size, p_win, p_pick, rnd):
    v_winner = np.zeros((6,64))
    store_size = np.zeros((6,64))
    for i in range(64):
        eff_size = pool_size
        for j in range(rnd,-1,-1):
            p_noone = noone(eff_size, p_win, p_pick, i)
            v_winner[j][i] = p_win[i][j] / (1 + eff_size * p_pick[i][j])
            #v_winner[j][i] += p_noone[j][int(invin(i)/2**(j+1))] / (eff_size+1)
            v_winner[j][i] *= 2**j*eff_size
            store_size[j][i] = eff_size
            eff_size = (p_noone[j][invin(i)/2**(j+1)]+p_pick[i][j]-p_noone[j][invin(i)/2**(j+1)]*p_pick[i][j])*eff_size
            eff_size += (1-p_noone[j][invin(i)/2**(j+1)])*adj[5-j]*(store_size[j][i]-eff_size)
    s_value = np.zeros(64)
    size = np.zeros(64)
    for i in range(64):
        s_value[i] = sum(v_winner[:,i])
        size[i] = store_size[rnd-1][i]
    return s_value, size  

#print values(pool_size, p_win, p_pick, 4)

def copyto(A, B):
    for i in range(len(B)):
        A[i] = B[i]

def bracket(pool_size, p_win, p_pick, prev_pick):
    print
    print "*************NEW BRACKET************"
    value = np.zeros((6,64))
    size = np.zeros(64)
    last_round = np.zeros(32)
    picks = np.zeros((6,32))
    eff_size = pool_size
    for i in range(16):
        last_round[i] = 64
    for i in range(5,-1,-1):
        value[i], size = values(eff_size, p_win, p_pick, i)
        eff_size = 0
        min_value = min(value[i])
        for j in range(64):
            value[i][j] /= (prev_pick[i][j]*2**(i-5)+1)
        temp = np.zeros(64)
        for j in range(64):
            temp[j] = value[i][index[j]]
        copyto(value[i], temp)
        if i != 5:
            temp = np.zeros(64)
            for j in range(2**(4-i)):
                temp[j] = invin(last_round[j])
            for j in range(2**(4-i)):
                last_round[j] = temp[j]
        for j in range(2**(5-i)):
            if 2**(i+1)*j <= last_round[j/2] and last_round[j/2] < 2**(i+1)*(j+1):
                picks[i][j] = index[last_round[j/2]]
            else:
                #print teams[index[np.argmax(value[i,2**(i+1)*j:2**(i+1)*(j+1)])+2**(i+1)*j]]
                picks[i][j] = index[np.argmax(value[i,2**(i+1)*j:2**(i+1)*(j+1)])+2**(i+1)*j]
            prev_pick[i][picks[i][j]] += 1
        print
        print "ROUND", i+1
        print
        for j in range(2**(5-i)):
            last_round[j] = picks[i][j]
            print teams[picks[i][j]]
            eff_size += 1/size[picks[i][j]]
        eff_size = 2**(5-i)/eff_size
    return picks

prev_pick = np.zeros((6,64))

for i in range(1):
    bracket(pool_size, p_win, p_pick, prev_pick)
