//This tests that face cards are counted for 10

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
	Card jack_spades(Card::JACK,Card::SPADES);
	Card queen_clubs(Card::QUEEN,Card::CLUBS);
	Card ten_clubs(Card::TEN,Card::CLUBS);
	Card seven_spades(Card::SEVEN,Card::SPADES);
	Card eight_diamonds(Card::EIGHT,Card::DIAMONDS);
	Card nine_hearts(Card::NINE,Card::HEARTS);
	Hand hand;

	hand.add_card(jack_spades);
	hand.add_card(two_spades);
	bool draw = test_player->draw(three_clubs, hand);
	assert(draw);
	draw = test_player->draw(ace_diamonds, hand);
	assert(draw);
	draw = test_player->draw(seven_spades, hand);
	assert(draw);
	draw = test_player->draw(four_hearts, hand);
	assert(!draw);

	hand.discard_all();
	hand.add_card(queen_clubs);
	hand.add_card(two_spades);
	draw = test_player->draw(three_clubs, hand);
	assert(draw);
	draw = test_player->draw(jack_spades, hand);
	assert(draw);
	draw = test_player->draw(seven_spades, hand);
	assert(draw);
	draw = test_player->draw(four_hearts, hand);
	assert(!draw);
	return 0; 
}
