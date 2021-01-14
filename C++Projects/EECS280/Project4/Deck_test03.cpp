//Tests the ability of the program to produce correct outputs
//After shuffling the same deck twice.

#include "Deck.h"
#include "Card.h"
#include <cassert>
#include <iostream>
using namespace std;

int main()
{
    Deck d;
		d.reset();
    d.shuffle(23);
		d.shuffle(23);
    for(int i = 0; i < 22; ++i)
    {
        d.deal();
    }
    Card after = d.deal();
    assert(after.get_rank() == 1);
    assert(after.get_suit() == 3);
		return 0;
}
