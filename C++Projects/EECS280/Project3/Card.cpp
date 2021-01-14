/* Card.cpp
 *
 * Represents a single playing card
 *
 */


#include "Card.h"
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;


////////////////////////////////////////////////////////////////////////////////
const char *const SUIT_NAMES[] = {"Spades", "Hearts", "Clubs", "Diamonds"};
const int SUIT_SIZE = 4;
const char *const RANK_NAMES[] = {"Two", "Three", "Four", "Five", "Six",
                                  "Seven", "Eight", "Nine", "Ten", "Jack",
                                  "Queen", "King", "Ace"};
const int RANK_SIZE = 13;


////////////////////////////////////////////////////////////////////////////////
void Suit_print(Suit suit) {
  cout << SUIT_NAMES[suit];
}

Suit Suit_next(Suit suit) {
  switch (suit) {
  case SPADES:   return CLUBS;
  case HEARTS:   return DIAMONDS;
  case CLUBS:    return SPADES;
  case DIAMONDS: return HEARTS;
  default:       assert(0); return SPADES; // should never get here
  }
}


////////////////////////////////////////////////////////////////////////////////
// Card

void Card_init(Card *card_ptr, Rank rank, Suit suit) {
  card_ptr->rank = rank;
  card_ptr->suit = suit;
}

void Card_print(const Card *card_ptr) {
  cout << RANK_NAMES[card_ptr->rank] << " of " << SUIT_NAMES[card_ptr->suit];
}

Suit Card_get_suit(const Card *card_ptr, Suit trump) {
  if (Card_is_left_bower(card_ptr, trump)) return trump;
  return card_ptr->suit;
}

bool Card_is_face(const Card *card_ptr) {
  return
    card_ptr->rank == JACK ||
    card_ptr->rank == QUEEN ||
    card_ptr->rank == KING ||
    card_ptr->rank == ACE;
}

bool Card_is_right_bower(const Card *card_ptr, Suit trump) {
  return card_ptr->rank == JACK && card_ptr->suit == trump; // JACK of trump suit
}

bool Card_is_left_bower(const Card *card_ptr, Suit trump) {
  return card_ptr->rank == JACK &&
    card_ptr->suit == Suit_next(trump); // JACK of trump's color
}

bool Card_is_trump(const Card *card_ptr, Suit trump) {
  return card_ptr->suit == trump ||
    Card_is_left_bower(card_ptr,trump);
}

int Card_compare(const Card *a, const Card *b) {

  // sanity check for NULL pointers
  assert(a);
  assert(b);

  // To simplify debugging and ensure that every correct solution will get the
  // same output, we’ve added an additional rule here.  In addition to being
  // ordered by rank, cards are also ordered by suit.
  return (a->suit + a->rank*SUIT_SIZE)
    -  (b->suit + b->rank*SUIT_SIZE);
}

//REQUIRES 	s points to a null-terminated c-string and names is an array
//			of null-terminating c-strings;
//EFFECTS	Returns the Rank corresponding the input s, prints an error
//			and exits if the string does not correspond to a Rank.
static Rank string2rank(const char *s, const char *const names[])
{
    for (int i=0; i<RANK_SIZE; ++i)
    {
        if (strcmp(s, names[i]) == 0) return static_cast<Rank>(i);
    }
	cout << "error, that is not a valid Rank";
    assert(0); //won't run
    exit(1); //needed if asserts are disabled
}

//REQUIRES 	s points to a null-terminated c-string and names is an array
//			of null-terminating c-strings;
//EFFECTS	Returns the Suit corresponding the input s, prints an error
//			and exits if the string does not correspond to a Suit.
static Suit string2suit(const char *s, const char *const names[])
{
    for (int i=0; i<SUIT_SIZE; ++i)
    {
        if (strcmp(s, names[i]) == 0) return static_cast<Suit>(i);
    }
    assert(0); //won't run
    exit(1); //needed if asserts are disabled
}

void Card_init(Card *card_ptr, const char* rank, const char* suit)
{
    card_ptr -> suit = string2suit(suit, SUIT_NAMES);
    card_ptr -> rank = string2rank(rank, RANK_NAMES);
}

int Card_compare(const Card *a, const Card *b, Suit trump)
{
    int aRank = a->suit + a->rank*SUIT_SIZE;
   int bRank = b->suit + b->rank*SUIT_SIZE;
   if (Card_is_trump(a, trump)) aRank +=200;
   if (Card_is_trump(b, trump)) bRank +=200;
   if (Card_is_right_bower(a, trump)) aRank +=50;
   if (Card_is_left_bower(a, trump)) aRank +=25;
   if (Card_is_right_bower(b, trump)) bRank += 50;
   if (Card_is_left_bower(b, trump)) bRank += 25;
   return aRank-bRank;
}

int Card_compare(const Card *a, const Card *b, const Card *led_card, Suit trump)
{
   int aRank = a->suit + a->rank*SUIT_SIZE;
   int bRank = b->suit + b->rank*SUIT_SIZE;
   if (Card_is_trump(a, trump)) aRank +=200;
   if (Card_is_trump(b, trump)) bRank +=200;
   if (Card_is_right_bower(a, trump)) aRank +=50;
   if (Card_is_left_bower(a, trump)) aRank +=25;
   if (Card_is_right_bower(b, trump)) bRank += 50;
   if (Card_is_left_bower(b, trump)) bRank += 25;
   if (Card_get_suit(a, trump) == Card_get_suit(led_card, trump)) aRank +=100;
   if (Card_get_suit(b, trump) == Card_get_suit(led_card, trump)) bRank +=100;
   return aRank-bRank;
}
