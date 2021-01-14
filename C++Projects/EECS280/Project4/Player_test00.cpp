//This is a simple test of the bet function.

#include "Card.h"
#include "Player.h"
#include <cassert>
#include <cstdlib>

int main() {
	Player *test_player = player_factory("counting");
	int wager = test_player->bet(100, 5);
	assert(wager == 5);
	return 0;
}
