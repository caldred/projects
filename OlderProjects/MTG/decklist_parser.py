import glob
import numpy as np
import pandas as pd

directory = 'C:\\Users\\Cal\\Documents\\Decklists'

decks = pd.DataFrame()
deckid = 0
for filename in glob.iglob(directory+'\\*'):
    temp = pd.read_csv(filename, sep="\n", header=None)
    temp = temp[0].str.split(" ", n = 1, expand = True)
    temp['deckid'] = deckid
    deckid += 1
    temp['Num'] = temp[0]
    temp['Card'] = temp[1]
    temp = temp.drop(labels = [0,1], axis=1)
    temp['Main'] = 1
    side = False
    for index, row in temp.iterrows():
        if index > 0:
            if temp.loc[index].Card < temp.loc[index-1].Card:
                side = True
            if side:
                temp.loc[index, 'Main'] = 0
    decks = decks.append(temp)
    
print(decks)
