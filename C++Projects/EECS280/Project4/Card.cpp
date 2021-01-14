#include "Card.h"

#include <cstdlib>

Card::Card()
: rank(TWO), suit(SPADES) {}

Card::Card(Rank rank_in, Suit suit_in)
: rank(rank_in), suit(suit_in) {}

Card::Rank Card::get_rank() const
{
    return rank;
}

Card::Suit Card::get_suit() const
{
    return suit;
}

const char *const SUIT_NAMES[] = {"Spades", "Hearts", "Clubs", "Diamonds"};
const char *const RANK_NAMES[] = {"Two", "Three", "Four", "Five", "Six",
                                  "Seven", "Eight", "Nine", "Ten", "Jack",
                                  "Queen", "King", "Ace"};
//EFFECTS: Writes the Card to the stream
//  for example "Two of Spades"
std::ostream& operator<< (std::ostream& os, const Card& c)
{
    os << RANK_NAMES[c.get_rank()] <<" of "<< SUIT_NAMES[c.get_suit()];
    return os;
}

