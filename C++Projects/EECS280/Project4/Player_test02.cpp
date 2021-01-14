//This test ensures that a count of +1 doesn't affect the wager

#include "Card.h"
#include "Player.h"
#include <cassert>
#include <cstdlib>

int main() {
	Player *test_player = player_factory("counting");
	Card two_spades(Card::TWO,Card::SPADES);
	test_player->expose(two_spades);
	int wager = test_player->bet(100, 5);
	assert(wager == 5);
	return 0;
}
