from __future__ import division
import numpy as np
import pandas as pd
import math
import scipy as sp

def f(x, u1, u2):
    s1 = .5*np.sqrt(428/17-u1/3)*np.sqrt(u1)
    s2 = .5*np.sqrt(428/17-u2/3)*np.sqrt(u2)
    if s1 == 0: s1 = .001
    if s2 == 0: s2 = .001
    y1 = 1/(s1*np.sqrt(2*np.pi))*np.exp(-.5*((x-u1)/s1)**2)
    y2 = 1/(s2*np.sqrt(2*np.pi))*np.exp(-.5*((x-u2)/s2)**2)
    if x > u1:
        return y2
    if x < u2:
        return y1
    else:
        return min(y1, y2)
    

df = pd.read_csv("cfb2017.csv")
fbs_teams = np.loadtxt("fbs_teams.csv", dtype = "str", delimiter = '\n')

for index, row in df.iterrows():
    winner = df.loc[index, 'Winner']
    if winner[0] == '(' and winner[2] == ')':
        winner = winner[4:]
    if winner[0] == '(' and winner[3] == ')':
        winner = winner[5:]
    df.loc[index, 'Winner'] = winner
    loser = df.loc[index, 'Loser']
    if loser[0] == '(' and loser[2] == ')':
        loser = loser[4:]
    if loser[0] == '(' and loser[3] == ')':
        loser = loser[5:]
    df.loc[index, 'Loser'] = loser

team_hash = {}
for i in range(len(fbs_teams)):
    team_hash[fbs_teams[i]] = i

res = np.zeros(len(fbs_teams)+1)

for x in range(1):
        
    w = 0
    v = 14
    hfa = 2.41
    nit = 100    
    
    tot = np.zeros(len(fbs_teams)+1)
    opponents = np.empty((len(fbs_teams)+1,),dtype=object)
    for i in range(len(opponents)):
        opponents[i] = []
        
    for index, row in df.iterrows():
        winner = row['Winner']
        winner = team_hash.setdefault(winner, len(fbs_teams))
        loser = row['Loser']
        loser = team_hash.setdefault(loser, len(fbs_teams))
        opponents[winner].append(loser)
        opponents[loser].append(winner)
        """MOV = row['Pts'] - row['Pts.1']
        if row['Away'] == '@':
            MOV += hfa
        else:
            MOV -= hfa
        if row['Away'] == 'n':
            MOV += hfa
        points = w + (1-w)*math.erf(MOV/(v*math.sqrt(2)))"""
        integ, err = sp.integrate.quad(f, -np.inf, np.inf, args=(min(row['Pts'],204/3),min(row['Pts.1'],204/3)), epsabs = .001)
        points = w + (1-w)*(1 - integ/2)
        tot[winner] += points
        tot[loser] += 1-points
    
    for i in range(len(tot)):
        tot[i] /= len(opponents[i])
        
    scores = np.zeros((len(tot), nit))
    
    for i in range(len(scores)):
        scores[i][0] = tot[i]
    
    for i in range(1,nit):
        s = 0
        if i == 1:
            s = 1
        if i == 2:
            s = -1
        for j in range(len(scores)):
            for k in range(len(opponents[j])):
                scores[j][i] += min(max(scores[opponents[j][k]][i-1], scores[j][i-1]-.5), scores[j][i-1]+.5)
            scores[j][i] += s * scores[j][0]
            scores[j][i] /= len(opponents[j]) + s
        lim = np.mean(scores[:,i])
    
    """for i in range(len(tot)-1):
        print str(fbs_teams[i]) + ',' + str(scores[i][0])  + ',' + str(scores[i][1])  + ',' + str(scores[i][2])"""
    
    
    for i in range(len(scores)):        
        res[i] += sum(scores[i])-(lim*(nit-1))
    
    """for i in range(len(tot)-1):
        print str(fbs_teams[i]) + ',' + str(tot[i])
    print "Unranked" + ',' + str(tot[-1])"""

for i in range(len(tot)-1):
    print str(fbs_teams[i]) + ',' + str(res[i])
print "Unranked" + ',' + str(tot[-1])


    
    
    
    
    
    
    
    
    