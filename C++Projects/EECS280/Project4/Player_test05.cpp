//This test ensures that after several cards have been revealed
//including those on the edge of ranges for the different count
//categories, if the count should be +2.

#include "Card.h"
#include "Player.h"
#include <cassert>
#include <cstdlib>

int main() {
	Player *test_player = player_factory("counting");
	Card two_spades(Card::TWO,Card::SPADES);
	Card ace_diamonds(Card::ACE,Card::DIAMONDS);
	Card six_hearts(Card::SIX,Card::HEARTS);
	Card ten_clubs(Card::TEN,Card::CLUBS);
	Card seven_spades(Card::SEVEN,Card::SPADES);
	Card nine_hearts(Card::NINE,Card::HEARTS);
	test_player->expose(two_spades);
	test_player->expose(six_hearts);
	test_player->expose(ace_diamonds);
	test_player->expose(ten_clubs);
	test_player->expose(seven_spades);
	test_player->expose(nine_hearts);
	test_player->expose(nine_hearts);
	test_player->expose(two_spades);
	test_player->expose(six_hearts);
	int wager = test_player->bet(8, 5);
	assert(wager == 8);
	return 0;
}
