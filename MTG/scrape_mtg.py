import requests
from bs4 import BeautifulSoup
import numpy as np

def factorial(n):
    if n == 0: return 1
    else: return n*factorial(n-1)

const_rds = [4,5,6,7,8,12,13,14,15,16]
player1 = []
player2 = []
result = []

for i in const_rds:
    if i < 9: day = 1
    else: day = 2
    r = requests.get('http://magic.wizards.com/en/events/coverage/ptemn/round-' + str(i) + '-results-2016-08-0' + str(day+4))
    print i
    soup = BeautifulSoup(r.text, 'lxml')

    table = soup.find(class_='sortable-table')
    for row in table.find_all('tr')[1:]:
        col = row.find_all('td')
    
        player1.append(col[1].string.strip())
        player2.append(col[5].string.strip())
        result.append(col[3].string.strip())

decks = {u'Gerschenson, Immanuel': 'Temur Emerge', 
         u'Yukuhiro, Ken': 'RG Ramp', 
         u'Carvalho, Pedro': 'UR Visions', 
         u'Nikolich, Benjamin': 'RW Humans', 
         u'(10) Larsson, Joel': 'Jund Delirium', 
         u'(6) M\xfcller, Martin': 'Jund Delirium', 
         u'Takahashi, Yuta': 'Bant Company', 
         u'Tiu, Oliver': 'GB Delirium', 
         u'Brown, Andrew': 'Temur Emerge', 
         u'Cheon, Paul': 'Bant Company', 
         u'Jensen, William': 'Temur Emerge', 
         u'Mori, Katsuhiro': 'Bant Company', 
         u'(16) Sigrist, Mike': 'GB Delirium', 
         u'Karsten, Frank': 'Temur Emerge', 
         u'(5) Scott-Vargas, Luis': 'Bant Company', 
         u'Ball, Nick': 'Naya Legendary', 
         u'(19) Blohon, Lukas': 'BW Control', 
         u'Chronopoulos, Bill': 'Bant Company', 
         u'Froehlich, Eric': 'GB Delirium', 
         u'Matsumoto, Yuki': '4c Emerge', 
         u'Ochoa, David': 'Bant Company',
         u'Rios, Justin': 'BW Control',
         u'Smith, Nathan': 'GB Delirium',
         u'(14) Strasky, Ondrej': 'UB Zombies',
         u'Collier, Jim': '4c Emerge',
         u'(7) Dama da Rosa, Paulo Vitor': 'GB Delirium',
         u'Dang, Martin': 'Jund Delirium',
         u'Deltour, Louis': 'Jund Delirium',
         u'Del Moral Leon, Antonio': 'Eldrazi',
         u'Dezani, Jeremy': 'BW Control',
         u'Fennell, Christopher': 'GB Delirium',
         u'(18) Finkel, Jon': 'Temur Emerge',
         u'Guillenea, Juan': 'BW Control',
         u'Inoue, TORU': 'RG Ramp',
         u'Janik, Maciej': '4c Emerge',
         u'Kumagai, Riku': 'Bant Company',
         u'Lai, Pak Yin': 'Bant Company',
         u'Lantto, Magnus': 'Jund Delirium',
         u'Lopez, Rodrigo': 'Bant Company',
         u'McLaren, Shaun': 'Bant Company',
         u'Schnayer, David': 'Esper Control',
         u'Tao, Jiachen': 'GB Delirium',
         u'(2) Turtenwald, Owen': 'Temur Emerge',
         u'Wilson, Jacob': 'GB Delirium',
         u'Wu, Allen': 'GB Delirium',
         u'Johnson, Alexander': 'GB Delirium',
         'Orange, Gregory': 'GB Delirium',
         'Pardee, Samuel': 'GB Delirium',
         'Cathro, Daniel': 'UB Zombies',
         'Dickmann, Patrick': 'Rites Company',
         'Holiday, Nathan': 'Bant Company',
         '(24) Lee, Shi Tian': 'Bant Company',
         'Levy, Raphael': 'BW Control',
         'Nakamura, Shuhei': 'GB Delirium',
         'Nielsen, Simon': 'Jund Delirium',
         'Sajgalik, Eduardo': 'Bant Company',
         'Soorani, Shaheen': 'GB Delirium',
         'Takahashi, Zen': 'Naya Legendary',
         'Alter, Scott': 'GB Delirium',
         'Burnham, Harrison': 'Bant Company',
         'Channing, George': 'Bant Company',
         'De Rosa, Antonino': 'RG Ramp',
         'Dominguez, Javier': 'Bant Company',
         '(15) Duke, Reid': 'RG Ramp', 
         '(21) Floch, Ivan': 'GB Delirium',
         'Ichikawa, Yuuki': '4c Emerge',
         'Ikawa, Yoshihiko': 'RG Ramp',
         'Juza, Martin': 'BW Control',
         'Kowalski, Grzegorz': '4c Emerge',
         'Ksandr, Jan': 'UW Spirits',
         'Lipp, Scott': 'GB Delirium',
         'Mackl, Valentin': 'Rites Company',
         'Mansell, Austin': 'Bant Company',
         'Medrano, Adonnys': 'Bant Company',
         'Mines, David': '4c Emerge',
         'Polak-Rottmann, Oliver': 'Jund Delirium',
         'Reed, David': 'BW Control',
         'Rubin, Ben': 'RG Ramp',
         'Severa, Matt': 'Bant Company',
         'Sullivan, Adrian': 'GB Delirium',
         '(12) Watanabe, Yuuya': 'RG Ramp',
         'Wiznitzer, Aryeh': 'GB Delirium',
         'Yu, Jarvis': 'Temur Emerge',
         'Zatlkaj, Matej': 'Jund Delirium'}

matchup_grid = np.zeros((8,8))
count = 0
for i in range(len(player1)):
    deck1 = decks.get(player1[i])
    deck2 = decks.get(player2[i])
    if deck1 and deck2: 
        j = -1
        k = -1
        if deck1 == 'GB Delirium': j = 0
        if deck2 == 'GB Delirium': k = 0
        if deck1 == 'Bant Company': j = 1
        if deck2 == 'Bant Company': k = 1
        if deck1 == '4c Emerge': j = 2
        if deck2 == '4c Emerge': k = 2
        if deck1 == 'BW Control': j = 3
        if deck2 == 'BW Control': k = 3
        if deck1 == 'UB Zombies': j = 4
        if deck2 == 'UB Zombies': k = 4
        if deck1 == 'Temur Emerge': j = 5
        if deck2 == 'Temur Emerge': k = 5
        if deck1 == 'Jund Delirium': j = 6
        if deck2 == 'Jund Delirium': k = 6
        if deck1 == 'RG Ramp': j = 7
        if deck2 == 'RG Ramp': k = 7
        #if j < 0: print 'deck not found:', deck1
        #if k < 0: print 'deck not found:', deck2
        if j >= 0 and k >= 0:
            if result[i] == 'Won 2-0': 
                matchup_grid[j][k] += 1
                print deck1, 'beats', deck2
            if result[i] == 'Won 2-1': 
                matchup_grid[j][k] += 1
                matchup_grid[k][j] += 0
                print deck1, 'beats', deck2
            if result[i] == 'Draw 1-1':
                matchup_grid[j][k] += 1
                matchup_grid[k][j] += 1
            if result[i] == 'Lost 1-2': 
                matchup_grid[k][j] += 1
                matchup_grid[j][k] += 0
                print deck2, 'beats', deck1
            if result[i] == 'Lost 0-2': 
                matchup_grid[k][j] += 1
                print deck2, 'beats', deck1

print 'GB Delirium, Bant Company, 4c Emerge, BW Control, UB Zombies, Temur Emerge, Jund Delirium, RG Ramp'

print matchup_grid
print count
newgrid = np.zeros((8,8))
for i in range(8):
    for j in range(8):
        a = matchup_grid[i][j]
        b = matchup_grid[j][i]
        newgrid[i][j] = int(100*(matchup_grid[i][j]+1)/(matchup_grid[i][j]+matchup_grid[j][i]+2))
        #newgrid[i][j] = int(100*factorial(a+b+2)*factorial(a+2)/(factorial(a+1)*factorial(a+b+3)))
print newgrid
