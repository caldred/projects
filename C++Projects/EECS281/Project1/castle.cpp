#include <cstdlib>
#include <deque>
#include <vector>
#include <iostream>
#include <string>
#include <cassert>
#include "castle.h"

char readMapType()
{
    char inputType;
    cin >> inputType;
    return inputType;
}

int readRoomSize()
{
    int room_size;
    cin >> room_size;
    return room_size;
}

int readNumRooms()
{
    int num_rooms;
    cin >> num_rooms;
    return num_rooms;
}

void readCastleM(Castle* castle_)
{
    int r_size = castle_->roomSize;
    int r_size_2 = r_size*r_size;
    string line;
    int cnt = 0;
    getline(cin, line);
    if (r_size == 1)
    {
	cout << "no solution\n";
	exit(0);
    }
    do
    {
        getline(cin, line);
	if (line.empty())
	    break;
        if (line[0] == '/' && line[1] =='/' )
        {
	    continue;
	}
	else
	{
            for (char i: line)
            {
		if (i == '.')
		{
		    ++cnt;
		    continue;
		}
		switch(i)
		{
		case 'S':
		    castle_->startLoc = vector<int> {cnt/r_size_2, (cnt/r_size)%r_size, cnt%r_size};
		    castle_->loc[cnt/r_size_2][(cnt/r_size)%r_size][cnt%r_size].type = i;
		    break;
		case 'C': 
		    castle_->endLoc = vector<int> {cnt/r_size_2, (cnt/r_size)%r_size, cnt%r_size};
		    castle_->loc[cnt/r_size_2][(cnt/r_size)%r_size][cnt%r_size].type = i;
		    break;
		case '#':
		case '!':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		    castle_->loc[cnt/r_size_2][(cnt/r_size)%r_size][cnt%r_size].type = i;
		    break;
		default:
		    cerr << "invalid map character\n";
		    exit(1);
		    break;
		}
               ++cnt;
            }
	}
    } while(true);
    return;
}

void readCastleL(Castle* castle_)
{
    string temp;
    string line;
    int index;
    vector<int> locIn;
    getline(cin, line);
    while (true)
    {
	//cout << "top\n";
	index = 0;
	getline(cin, line);
	if (line.empty())
	{
	    //cout << "break\n";
	    break;
	}
	    //cout<<"Not breaking."<<endl;
	if (line[0] == '(')
	{
	    for (char i: line)
	    {
		if (i == '(')
		    continue;
		if (index < 3)
		{
		    if (i == ',')
		    {
			locIn.push_back(atoi(temp.c_str()));
			temp.clear();
			++index;
			continue;
		    }
		    temp.push_back(i);
		}
		else
		{
		    if(temp.empty())
		    {
			switch(i)
			{
			case 'S':
			    castle_->startLoc = vector<int> {locIn[0], locIn[1], locIn[2]};
			    temp.push_back(i);
			    break;
			case 'C': 
			    castle_->endLoc = vector<int> {locIn[0], locIn[1], locIn[2]};
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			case '#':
			case '!':
			case '.':
			    temp.push_back(i);
			    break;
			default:
			    cerr << "invalid map character\n";
			    exit(1);
			}
		    }
		    else 
		    {
			if ((locIn[0] >= castle_->numRooms) || (locIn[1] >= castle_->roomSize) || (locIn[2] >= castle_->roomSize))
			{
			    cerr  << "illegal coordinate\n";
			    exit(1);
			}
			castle_->loc[locIn[0]][locIn[1]][locIn[2]].type = temp[0];
		    }
		}
	    }
	    temp.clear();
	    locIn.clear();
	}
	//cout << "bottom\n";
	line.clear();
    }
    //cout << "returning\n";
    return;
}

void printCastle(Castle* castle_)
{
    ostringstream oss;
    for(int i = 0; i < castle_->numRooms; ++i)
    {
        oss << "//castle room " << i << '\n';
        for (int j = 0; j < castle_->roomSize; ++j)
        {
            for (int k = 0; k < castle_->roomSize; ++k)
            {
                oss << castle_->loc[i][j][k].type;
            }
            oss << '\n';
        }
    }
    cout << oss.str();
    return;
}
