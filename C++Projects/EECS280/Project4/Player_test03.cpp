//This test ensures that the count is reset to 0 after shuffling.

#include "Card.h"
#include "Player.h"
#include <cassert>
#include <cstdlib>

int main() {
	Player *test_player = player_factory("counting");
	Card two_spades(Card::TWO,Card::SPADES);
	test_player->expose(two_spades);
	test_player->expose(two_spades);
	test_player->shuffled();
	int wager = test_player->bet(100, 5);
	assert(wager == 5);
	return 0;
}
