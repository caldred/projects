//Test of the bet function with an alternative minimum

#include "Card.h"
#include "Player.h"
#include <cassert>
#include <cstdlib>

int main() {
	Player *test_player = player_factory("counting");
	int wager = test_player->bet(100, 8);
	assert(wager == 8);
	return 0;
}
