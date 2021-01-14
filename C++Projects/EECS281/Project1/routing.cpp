#include <cstdlib>
#include <deque>
#include <vector>
#include <iostream>
#include <sstream>
#include "routing.h"
using namespace std;

bool discoverable(const Space *space_)
{
    return (space_->foundBy == '/' && space_->type != '!' && space_->type != '#');
}

void findPathS(Castle *castle_, bool map)
{
    ostringstream oss;
    deque<Space*> deck;
    Space *firstSpace = &castle_->loc[castle_->startLoc[0]][castle_->startLoc[1]][castle_->startLoc[2]];
    deck.push_front(firstSpace);
    deque<vector<int> > locs;
    locs.push_front(castle_->startLoc);
    vector<int> current;
    while (true)
    {
	if(deck.empty())
	{
	    cout << "no solution\n";
	    exit(1);
	}
        current = locs.front();
	//cout << current[0] << current[1] << current[2] << endl;
        Space *temp = deck.front();
        deck.pop_front();
        locs.pop_front();
        if (temp->type != '.' && temp->type != 'S')
        {
            int newRoom = temp->type - '0';
            if (newRoom < castle_->numRooms)
            {
                Space *test = &castle_->loc[newRoom][current[1]][current[2]];
                if(discoverable(test))
                {
		    char newChar = (char) ('0' + current[0]);
		    test->foundBy = newChar;
                    deck.push_front(test);
                    current[0] = newRoom;
                    locs.push_front(current);
		}
                if (test->type == 'C')
                {
                    break;
                }
            }
        }
        else
        {
            if(current[1] - 1 >= 0)
            {
                Space *test = &castle_->loc[current[0]][--current[1]][current[2]];
                if(discoverable(test))
                {
                    test->foundBy = 's';
                    deck.push_front(test);
                    locs.push_front(current);
                    if (test->type == 'C')
                    {
                        break;
                    }
                }
                current[1]++;
            }
            if(current[2] + 1 < castle_->roomSize)
            {
                Space *test = &castle_->loc[current[0]][current[1]][++current[2]];
                if(discoverable(test))
                {
                    test->foundBy = 'w';
                    deck.push_front(test);
                    locs.push_front(current);
                    if (test->type == 'C')
                    {
                        break;
                    }
                }
                current[2]--;
            }
            if(current[1] + 1 < castle_->roomSize)
            {
                Space *test = &castle_->loc[current[0]][++current[1]][current[2]];
                if(discoverable(test))
                {
                    test->foundBy = 'n';
                    deck.push_front(test);
                    locs.push_front(current);
                    if (test->type == 'C')
                    {
                        break;
                    }
                }
                current[1]--;
            }
            if(current[2] - 1 >= 0)
            {
                Space *test = &castle_->loc[current[0]][current[1]][--current[2]];
                if(discoverable(test))
                {
                    test->foundBy = 'e';
                    deck.push_front(test);
                    locs.push_front(current);
                    if (test->type == 'C')
                    {
                        break;
                    }
                }
                current[2]++;
            }
        }
    }
    Space *prev = &castle_->loc[current[0]][current[1]][current[2]];
    Space *next = prev;
    vector<vector<int> > path;
    vector<char> types;
    bool done = false;
    while(!done)
    {
        switch(prev->foundBy)
        {
            case 'n' :  next = &castle_->loc[current[0]][--current[1]][current[2]];
                        if(next->type == 'S') done = true;
                        next->type = 's';
                        break;
            case 'e' :  next = &castle_->loc[current[0]][current[1]][++current[2]];
                        if(next->type == 'S') done = true;
                        next->type = 'w';
                        break;
            case 's' :  next = &castle_->loc[current[0]][++current[1]][current[2]];
                        if(next->type == 'S') done = true;
                        next->type = 'n';
                        break;
            case 'w' :  next = &castle_->loc[current[0]][current[1]][--current[2]];
                        if(next->type == 'S') done = true;
                        next->type = 'e';
                        break;
            case '0' :  next = &castle_->loc[0][current[1]][current[2]];
                        if(next->type == 'S') done = true;
                        next->type = 'p';
                        current[0] = 0;
                        break;
            case '1' :  next = &castle_->loc[1][current[1]][current[2]];
                        if(next->type == 'S') done = true;
                        next->type = 'p';
			current[0] = 1;
                        break;
            case '2' :  next = &castle_->loc[2][current[1]][current[2]];
                        if(next->type == 'S') done = true;
                        next->type = 'p';
                        current[0] = 2;
                        break;
            case '3' :  next = &castle_->loc[3][current[1]][current[2]];
                        if(next->type == 'S') done = true;
                        next->type = 'p';
                        current[0] = 3;
                        break;
            case '4' :  next = &castle_->loc[4][current[1]][current[2]];
                        if(next->type == 'S') done = true;
			next->type = 'p';
                        current[0] = 4;
                        break;
            case '5' :  next = &castle_->loc[5][current[1]][current[2]];
                        if(next->type == 'S') done = true;
                        next->type = 'p';
                        current[0] = 5;
                        break;
            case '6' :  next = &castle_->loc[6][current[1]][current[2]];
                        if(next->type == 'S') done = true;
                        next->type = 'p';
                        current[0] = 6;
                        break;
            case '7' :  next = &castle_->loc[7][current[1]][current[2]];
                        if(next->type == 'S') done = true;
                        next->type = 'p';
                        current[0] = 7;
                        break;
            case '8' :  next = &castle_->loc[8][current[1]][current[2]];
                        if(next->type == 'S') done = true;
			next->type = 'p';
                        current[0] = 8;
                        break;
            case '9' :  next = &castle_->loc[9][current[1]][current[2]];
                        if(next->type == 'S') done = true;
                        next->type = 'p';
                        current[0] = 9;
                        break;
        }
	types.push_back(next->type);
	path.push_back(current);
        prev = next;
    }
    cout << castle_->roomSize << endl;
    cout << castle_->numRooms << endl;
    if(!map)
    {
	vector< vector<int> >::reverse_iterator row;
	vector<int>::iterator col;
	int n = 1;
	cout << "//path taken\n";
	for (row = path.rbegin(); row != path.rend(); row++) 
	{
	    oss << '(';
	    for (col = row->begin(); col != row->end(); col++) 
	    {
		oss << *col << ',';
	    }
	    oss << types[types.size()-n++];
	    oss << ")\n";
	}
    }
    cout << oss.str();
    return;
}

void findPathQ(Castle *castle_, bool map)
{
    ostringstream oss;
    deque<Space*> deck;
    Space *firstSpace = &castle_->loc[castle_->startLoc[0]][castle_->startLoc[1]][castle_->startLoc[2]];
    deck.push_back(firstSpace);
    deque<vector<int> > locs;
    locs.push_back(castle_->startLoc);
    vector<int> current;
    while (true)
    {
	if(deck.empty())
	{
	    cout << "no solution\n";
	    exit(1);
	}
        current = locs.front();
	//cout << current[0] << current[1] << current[2] << endl;
        Space *temp = deck.front();
        deck.pop_front();
        locs.pop_front();
        if (temp->type != '.' && temp->type != 'S')
        {
            int newRoom = temp->type - '0';
            if (newRoom < castle_->numRooms)
            {
                Space *test = &castle_->loc[newRoom][current[1]][current[2]];
                if(discoverable(test))
                {
		    char newChar = (char) ('0' + current[0]);
		    test->foundBy = newChar;
                    deck.push_back(test);
                    current[0] = newRoom;
                    locs.push_back(current);
		}
                if (test->type == 'C')
                {
                    break;
                }
            }
        }
        else
        {
            if(current[1] - 1 >= 0)
            {
                Space *test = &castle_->loc[current[0]][--current[1]][current[2]];
                if(discoverable(test))
                {
                    test->foundBy = 's';
                    deck.push_back(test);
                    locs.push_back(current);
                    if (test->type == 'C')
                    {
                        break;
                    }
                }
                current[1]++;
            }
            if(current[2] + 1 < castle_->roomSize)
            {
                Space *test = &castle_->loc[current[0]][current[1]][++current[2]];
                if(discoverable(test))
                {
                    test->foundBy = 'w';
                    deck.push_back(test);
                    locs.push_back(current);
                    if (test->type == 'C')
                    {
                        break;
                    }
                }
                current[2]--;
            }
            if(current[1] + 1 < castle_->roomSize)
            {
                Space *test = &castle_->loc[current[0]][++current[1]][current[2]];
                if(discoverable(test))
                {
                    test->foundBy = 'n';
                    deck.push_back(test);
                    locs.push_back(current);
                    if (test->type == 'C')
                    {
                        break;
                    }
                }
                current[1]--;
            }
            if(current[2] - 1 >= 0)
            {
                Space *test = &castle_->loc[current[0]][current[1]][--current[2]];
                if(discoverable(test))
                {
                    test->foundBy = 'e';
                    deck.push_back(test);
                    locs.push_back(current);
                    if (test->type == 'C')
                    {
                        break;
                    }
                }
                current[2]++;
            }
        }
    }
    Space *prev = &castle_->loc[current[0]][current[1]][current[2]];
    Space *next = prev;
    vector<vector<int> > path;
    vector<char> types;
    bool done = false;
    while(!done)
    {
        switch(prev->foundBy)
        {
            case 'n' :  next = &castle_->loc[current[0]][--current[1]][current[2]];
                        if(next->type == 'S') done = true;
                        next->type = 's';
                        break;
            case 'e' :  next = &castle_->loc[current[0]][current[1]][++current[2]];
                        if(next->type == 'S') done = true;
                        next->type = 'w';
                        break;
            case 's' :  next = &castle_->loc[current[0]][++current[1]][current[2]];
                        if(next->type == 'S') done = true;
                        next->type = 'n';
                        break;
            case 'w' :  next = &castle_->loc[current[0]][current[1]][--current[2]];
                        if(next->type == 'S') done = true;
                        next->type = 'e';
                        break;
            case '0' :  next = &castle_->loc[0][current[1]][current[2]];
                        if(next->type == 'S') done = true;
                        next->type = 'p';
                        current[0] = 0;
                        break;
            case '1' :  next = &castle_->loc[1][current[1]][current[2]];
                        if(next->type == 'S') done = true;
                        next->type = 'p';
			current[0] = 1;
                        break;
            case '2' :  next = &castle_->loc[2][current[1]][current[2]];
                        if(next->type == 'S') done = true;
                        next->type = 'p';
                        current[0] = 2;
                        break;
            case '3' :  next = &castle_->loc[3][current[1]][current[2]];
                        if(next->type == 'S') done = true;
                        next->type = 'p';
                        current[0] = 3;
                        break;
            case '4' :  next = &castle_->loc[4][current[1]][current[2]];
                        if(next->type == 'S') done = true;
			next->type = 'p';
                        current[0] = 4;
                        break;
            case '5' :  next = &castle_->loc[5][current[1]][current[2]];
                        if(next->type == 'S') done = true;
                        next->type = 'p';
                        current[0] = 5;
                        break;
            case '6' :  next = &castle_->loc[6][current[1]][current[2]];
                        if(next->type == 'S') done = true;
                        next->type = 'p';
                        current[0] = 6;
                        break;
            case '7' :  next = &castle_->loc[7][current[1]][current[2]];
                        if(next->type == 'S') done = true;
                        next->type = 'p';
                        current[0] = 7;
                        break;
            case '8' :  next = &castle_->loc[8][current[1]][current[2]];
                        if(next->type == 'S') done = true;
			next->type = 'p';
                        current[0] = 8;
                        break;
            case '9' :  next = &castle_->loc[9][current[1]][current[2]];
                        if(next->type == 'S') done = true;
                        next->type = 'p';
                        current[0] = 9;
                        break;
        }
	types.push_back(next->type);
	path.push_back(current);
        prev = next;
    }
    cout << castle_->roomSize << endl;
    cout << castle_->numRooms << endl;
    if(!map)
    {
	vector< vector<int> >::reverse_iterator row;
	vector<int>::iterator col;
	int n = 1;
	cout << "//path taken\n";
	for (row = path.rbegin(); row != path.rend(); row++) 
	{
	    oss << '(';
	    for (col = row->begin(); col != row->end(); col++) 
	    {
		oss << *col << ',';
	    }
	    oss << types[types.size()-n++];
	    oss << ")\n";
	}
    }
    cout << oss.str();
    return;
}
