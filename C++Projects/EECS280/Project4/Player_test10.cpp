//This is a simple test of the draw function
//With a good hand it should stand.

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
	Hand hand;
	hand.add_card(ten_clubs);
	hand.add_card(ten_clubs);
	bool draw = test_player->draw(ten_clubs, hand);
	assert(!draw);
	return 0;
}
