#include <cstdlib>
#include <deque>
#include <vector>
#include <iostream>
#include <string>
#include <cassert>
#include <getopt.h>
#include "routing.h"

using namespace std;

static struct option longopts[] =
{
    {"stack", no_argument, 0, 's'},
    {"queue", no_argument, 0, 'q'},
    {"help", no_argument, 0, 'h'},
    {"output", required_argument, 0, 'o'},
    {0,0,0,0}
};

void castleHelp()
{
    cout << "HELP\n";
    exit(0);
}


int main(int argc, char *argv[])
{
    ios_base::sync_with_stdio(false);
    int idx = 0;
    int c;
    bool map = true;
    bool stack = false;
    bool queue = false;
    while ((c = getopt_long(argc, argv, "sqho:", longopts, &idx)) != -1) 
    {
	switch (c)
	{
	case 0:
	    break;
	case 's':
	    stack = true;
	    break;
	case 'q':
	    queue = true;
	    break;
	case 'h':
	    castleHelp();
	    break;
	case 'o':
	    if(optarg[0] == 'L')
	    {
		map = false;
	    }
	    break;
	}
    }
    if(stack == queue)
	castleHelp();
    char inputType = readMapType();
    int rSize = readRoomSize();
    int nRooms = readNumRooms();
    Castle myCastle(nRooms, rSize);
    if (inputType == 'M')
	readCastleM(&myCastle);
    else
	readCastleL(&myCastle);
    if(stack)
	findPathS(&myCastle, map);
    else
	findPathQ(&myCastle, map);
    if(map)
	printCastle(&myCastle);
    return 0;
}
