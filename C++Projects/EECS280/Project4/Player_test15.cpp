//This tests hands with a soft count;

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
	Card eight_diamonds(Card::EIGHT,Card::DIAMONDS);
	Card nine_hearts(Card::NINE,Card::HEARTS);
	Hand hand;

	hand.add_card(ace_diamonds);
	hand.add_card(six_hearts);
	bool draw = test_player->draw(three_clubs, hand);
	assert(draw);
	draw = test_player->draw(six_hearts, hand);
	assert(draw);
	draw = test_player->draw(seven_spades, hand);
	assert(draw);
	draw = test_player->draw(four_hearts, hand);
	assert(draw);

	hand.discard_all();
	hand.add_card(ace_diamonds);
	hand.add_card(three_clubs);
	hand.add_card(four_hearts);
	draw = test_player->draw(eight_diamonds, hand);
	assert(!draw);
	draw = test_player->draw(six_hearts, hand);
	assert(draw);
	draw = test_player->draw(seven_spades, hand);
	assert(!draw);
	draw = test_player->draw(two_spades, hand);
	assert(!draw);
	draw = test_player->draw(three_clubs, hand);
	assert(draw);
	draw = test_player->draw(nine_hearts, hand);
	assert(draw);

	hand.discard_all();
	hand.add_card(ace_diamonds);
	hand.add_card(eight_diamonds);
	draw = test_player->draw(three_clubs, hand);
	assert(!draw);
	draw = test_player->draw(six_hearts, hand);
	assert(!draw);
	draw = test_player->draw(seven_spades, hand);
	assert(!draw);
	draw = test_player->draw(four_hearts, hand);
	assert(!draw);

	return 0; 
}
