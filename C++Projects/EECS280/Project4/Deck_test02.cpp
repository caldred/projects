//Tests the deal and shuffle functions when the deck is
//cut at a number of < 26.

#include "Deck.h"
#include "Card.h"
#include <cassert>
#include <iostream>
using namespace std;


int main()
{
    Deck d;
    d.shuffle(23);
    for(int i = 0; i < 22; ++i)
    {
        d.deal();
    }
    Card after = d.deal();
    assert(after.get_rank() == 8);
    assert(after.get_suit() == 2);
		for(int i = 23; i<51; ++i) d.deal();
		after = d.deal();
		assert(after.get_rank() == 12);
    assert(after.get_suit() == 3);
		return 0;
}
