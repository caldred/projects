#include <cstdlib>
#include <deque>
#include <sstream>
#include "structs.h"

using namespace std;

char readMapType();

int readRoomSize();

int readNumRooms();

void readCastleM(Castle* castle_);

void readCastleL(Castle* castle_);

void printCastle(Castle* castle_);
