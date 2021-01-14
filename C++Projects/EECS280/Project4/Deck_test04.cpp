//Tests the cards_remaining()  and reset() functions;
#include "Deck.h"
#include "Card.h"
#include <cassert>
#include <iostream>
using namespace std;

int main()
{
    Deck d;
		int cards = d.cards_remaining();
		assert(cards==52);

		d.deal();
		cards = d.cards_remaining();
		assert(cards==51);

		for(int i=0; i<50; ++i) d.deal();
		cards = d.cards_remaining();
		assert(cards==1);

		d.reset();
		cards = d.cards_remaining();
		assert(cards==52);
		return 0;
}
