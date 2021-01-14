#include "Game.h"
#include <cassert>
#include <cstring>
#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;

//REQUIRES
//MODIFIES
//EFFECTS	Reads in input from the command line and uses that info to initialize
//				A Game and play that game
int main(int argc, char* argv[])
{
    bool shuffle;
    Game game;
    char* names[4];
    char* pack_filename = argv[1];
    if (strcmp(argv[2], "shuffle") == 0) shuffle = true;
    else if (strcmp(argv[2], "noshuffle") == 0) shuffle = false;
    else
		{ 
				cout << "error, please input 'shuffle' or 'noshuffle'" << endl;	
				assert(0);
				exit(1);
		}
    int pts2win = atoi(argv[3]);
    for (int i=0; i < 4; ++i)
    {
        names[i] = argv[4+i];
    }
	for (int i = 0; i <argc; ++i)
	{
		cout << argv[i] << " ";
	}
	cout << endl;
    Game_init(&game, pack_filename, shuffle, pts2win, names);
    Game_play(&game);
    return 0;
}
