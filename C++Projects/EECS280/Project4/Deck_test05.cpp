//Tests the shuffle of a cut > 26 at the top, near the middle, and bottom.

#include "Deck.h"
#include "Card.h"
#include <cassert>
#include <iostream>
using namespace std;


int main()
{
    Deck d;
    d.shuffle(33);
		Card before = d.deal();
		assert(before.get_rank() == 7);
		assert(before.get_suit() == 2);
    for(int i = 0; i < 21; ++i)
    {
        d.deal();
    }
    Card after = d.deal();
    assert(after.get_rank() == 5);
    assert(after.get_suit() == 3);
		for(int i = 23; i<51; ++i) d.deal();
		after = d.deal();
		assert(after.get_rank() == 6);
    assert(after.get_suit() == 2);
		return 0;
}
