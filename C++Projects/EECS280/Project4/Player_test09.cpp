//This is another check of the shuffled function.


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
	test_player->expose(two_spades);
	test_player->expose(two_spades);
	int wager = test_player->bet(100, 5);
	assert(wager == 10);
	return 0;
}
