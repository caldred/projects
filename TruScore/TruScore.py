from lxml import etree
import urllib
import numpy as np

year = input('Please enter the desired year: ')
league = input('Please enter the desired league: ')
week = input('Please enter the desired week: ')
print

nteams = 0
ntot = 0
noff = 0
names = []

url = 'http://www51.myfantasyleague.com/'+ str(year) +'/export?TYPE=league&L=' + str(league) + '&W=' + str(week) + '&JSON=0'
r = urllib.urlopen(url)
root = etree.parse(r)

for df in root.xpath('//starters'):
    for attrib in df.attrib:
        if attrib == 'count':
            ntot = int(df.attrib[attrib])
        try:
            if attrib == 'idp_starters':
                noff = ntot - int(df.attrib[attrib])
        except ValueError:
            noff = ntot
            
print "Number of Offensive Starters:", noff
print "Number of Defensive Starters:", ntot-noff

for df in root.xpath('//franchises'):
    for attrib in df.attrib:
        if attrib == 'count':
            nteams = int(df.attrib[attrib])

print "Total Number of Teams:", nteams
print
    
for df in root.xpath('//franchise'):
    for attrib in df.attrib:
        if attrib == 'name':
            names.append(df.attrib[attrib])
            
url = 'http://www51.myfantasyleague.com/'+ str(year) +'/export?TYPE=weeklyResults&L='  + str(league) + '&W=' + str(week) + '&JSON=0'
r = urllib.urlopen(url)
root = etree.parse(r)

scores = np.zeros((nteams,3))
id = -1
j = 0
for df in root.xpath('//franchise'):
    for attrib in df.attrib:
        if attrib == 'id':
            id  = int(df.attrib[attrib])
            scores[j][0] = id - 1
    subfields = df.getchildren()
    i = 0
    for subfield in subfields:
        for attrib in subfield.attrib:
            if attrib == 'score':
                try: 
                    p_score = float(subfield.attrib[attrib])
                except ValueError:
                    p_score = 0
                if i < noff:
                    scores[j][1] += p_score
                elif i < ntot:
                    scores[j][2] += p_score
                i += 1
    j += 1
    
combos = np.zeros(nteams*nteams)
for i in range(nteams):
    for j in range(nteams):
        combos[nteams*i + j] = scores[i][1] - scores[j][2]
combos = np.sort(combos)

percentile = np.zeros(32)
for i in range(nteams):
    if i%2 == 0:
        diff = scores[i][1]-scores[i+1][2]
        percentile[i] = (np.searchsorted(combos, diff)-1)*100/(nteams*nteams)
    else:
        diff = scores[i][1]-scores[i-1][2]
        percentile[i] = (np.searchsorted(combos, diff)-1)*100/(nteams*nteams)
        
nflscores = np.zeros(60)
nflscores = [.92, .92, .97, .97, .97, 2.58, 4.77, 7.11, 7.27, 8.42, 12.43, 12.69, 13.47,
             18.99, 22.58, 23.16, 26.12, 32.74, 33.73, 36.33, 43.21, 46.59,
             48.21, 53.68, 60.4, 61.18, 63.62, 70.24, 73.05, 74.09, 77.43,
             81.96, 82.58, 83.99, 87.48, 88.83, 89.46, 91.23, 93.47, 93.83,
             94.3, 95.6, 96.44, 96.91, 97.27, 98, 98, 98.1, 98.42, 98.83, 98.89,
             99.25, 99.51, 99.56, 99.61, 99.82, 99.93, 99.93, 99.98, 100]
             
results = np.zeros(nteams)
for i in range(nteams):
    results[i] = np.searchsorted(nflscores, percentile[i])

for i in range(nteams/2):
    print names[int(scores[2*i][0])], int(results[2*i])
    print names[int(scores[2*i+1][0])], int(results[2*i+1])
    print