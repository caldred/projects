//This tests hands with an ace counted as a 1

#include "Card.h"
#include "Player.h"
#include <cassert>
#include <cstdlib>

int main() {
	Player *test_player = player_factory("counting");
	Card two_spades(Card::TWO,Card::SPADES);
	Card three_clubs(Card::THREE,Card::CLUBS);
	Card four_hearts(Card::FOUR,Card::HEARTS);
	Card ace_diamonds(Card::ACE,Card::DIAMONDS);
	Card six_hearts(Card::SIX,Card::HEARTS);
	Card ten_clubs(Card::TEN,Card::CLUBS);
	Card seven_spades(Card::SEVEN,Card::SPADES);
	Card nine_hearts(Card::NINE,Card::HEARTS);
	Hand hand;

	hand.add_card(ace_diamonds);
	hand.add_card(two_spades);
	hand.add_card(nine_hearts);
	bool draw = test_player->draw(three_clubs, hand);
	assert(draw);
	draw = test_player->draw(six_hearts, hand);
	assert(!draw);
	draw = test_player->draw(seven_spades, hand);
	assert(draw);
	draw = test_player->draw(four_hearts, hand);
	assert(!draw);

	hand.discard_all();
	hand.add_card(ace_diamonds);
	hand.add_card(two_spades);
	hand.add_card(ten_clubs);
	draw = test_player->draw(ace_diamonds, hand);
	assert(draw);
	draw = test_player->draw(six_hearts, hand);
	assert(!draw);
	draw = test_player->draw(seven_spades, hand);
	assert(draw);
	draw = test_player->draw(two_spades, hand);
	assert(!draw);
	return 0; 
}
