//Tests the reset, shuffle, and deal functions simply.

#include "Deck.h"
#include "Card.h"
#include <cassert>
#include <iostream>
using namespace std;


int main()
{
    Deck d;
 
		d.shuffle(22);		

    d.reset();

    Card before = d.deal();
    d.shuffle(26); // Should replace the dealt card before shuffling

    d.deal(); // Throw one away
    Card after = d.deal(); // Should be the same as before.

    assert(before.get_rank() == after.get_rank());
    assert(before.get_suit() == after.get_suit());
    return 0;}
