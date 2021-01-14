//This test ensures that if the bankroll is less than double
//the minimum, then if the count is >1 then the bet function
//should return the amount in the bankroll;


#include "Card.h"
#include "Player.h"
#include <cassert>
#include <cstdlib>

int main() {
	Player *test_player = player_factory("counting");
	Card two_spades(Card::TWO,Card::SPADES);
	test_player->expose(two_spades);
	test_player->expose(two_spades);
	int wager = test_player->bet(8, 5);
	assert(wager == 8);
	return 0;
}
