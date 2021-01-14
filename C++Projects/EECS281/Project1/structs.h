#include <cstdlib>
#include <deque>
#include <vector>
using namespace std;

struct Space
{
    char type;
    char foundBy;
    Space() : type('.'), foundBy('/')
    {}
    Space(char typeIn) : foundBy('/')
    {type = typeIn;}
};

struct Castle
{
    int numRooms;
    int roomSize;
    vector<vector<vector<Space> > > loc;
    vector<int> startLoc;
    vector<int> endLoc;
    Castle(int roomsIn, int sizeIn)
    {
        numRooms = roomsIn;
        roomSize = sizeIn;
        startLoc.resize(3);
        endLoc.resize(3);
        loc.resize(roomsIn, vector<vector<Space> >(sizeIn,vector<Space>(sizeIn)));
    }
};

