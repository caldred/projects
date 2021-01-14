/* Player_test00.cpp
 * 
 * Unit tests for Player
 *
 */

#include "Player.h"
#include "Card.h"
#include <cassert>
#include <cstring>
#include <iostream>
using namespace std;

// REQUIRES: player_ptr->handsize == MAX_HAND_SIZE, since we don't know how 
//           discarded / played cards are being dealt with
// MODIFIES:
// EFFECTS: Returns true if *card_ptr is in player_ptr->hand, false otherwise
bool Player_has_card_in_hand(const Card* card_ptr, const Player* player_ptr) {
  for (int i = 0; i < player_ptr->hand_size; i++) {
    if (Card_compare(card_ptr, &player_ptr->hand[i]) == 0) {
      return true;
    }
  }
  return false;
}

int main() {

  ////////////////////////////////////////
  // Player_init() unit tests
  Player alice;
  Player_init(&alice, "Alice");
  assert( strcmp(alice.name, "Alice") == 0 );
  assert( alice.hand_size == 0 );
  

  ////////////////////////////////////////
  // Player_add_card() unit tests

  // Create player Bob and give him an awesome hand for Spades trump
  Card awesome_spades_hand[MAX_HAND_SIZE] = 
    { {TEN, SPADES},
      {KING, SPADES},
      {ACE, SPADES},
      {JACK, CLUBS},
      {JACK, SPADES}, };
  Player bob;
  Player_init(&bob, "Bob");
  for (int i=0; i<MAX_HAND_SIZE; ++i) {
    Player_add_card(&bob, &awesome_spades_hand[i]);
    assert(bob.hand_size == i+1);
  }

  // Check that Bob's hand actually has all those spades
  assert(bob.hand_size == MAX_HAND_SIZE);
  for (int i=0; i<MAX_HAND_SIZE; ++i)
    assert(Player_has_card_in_hand(awesome_spades_hand + i, &bob));


  ////////////////////////////////////////
  // Player_make_trump() unit tests

  // Bob should order up Spades if the upcard is a low Spade
  Card nine_spades;
  Card_init(&nine_spades, NINE, SPADES);
  Suit order_up_suit = SPADES;
  bool bob_response = Player_make_trump
    (&bob,            //Player calling trump
     &nine_spades,    //upcard
     &bob,            //Bob is also the dealer
     1,               //first round
     &order_up_suit   //suit ordered up
     );
  assert(bob_response == true);
  assert(order_up_suit == SPADES);

  Card nine_clubs;
  Card_init(&nine_clubs, NINE, CLUBS);
  order_up_suit = SPADES;
  bob_response = Player_make_trump
    (&bob,            //Player calling trump
     &nine_clubs,    //upcard
     &bob,            //Bob is also the dealer
     1,               //first round
     &order_up_suit   //suit ordered up
     );
  assert(bob_response == true);
  assert(order_up_suit == CLUBS);

  Card nine_hearts;
  Card_init(&nine_hearts, NINE, HEARTS);
  order_up_suit = HEARTS;
  bob_response = Player_make_trump
    (&bob,            //Player calling trump
     &nine_hearts,    //upcard
     &bob,            //Bob is also the dealer
     1,               //first round
     &order_up_suit   //suit ordered up
     );
  assert(bob_response == false);
  assert(order_up_suit == HEARTS);


  ////////////////////////////////////////
  // Player_add_and_discard() unit tests

  // Bob will throw away the upcard if it's lower than the cards in his hand
  Player_add_and_discard(&bob, &nine_spades);
  assert(bob.hand_size == 5);
  for (int i=0; i<bob.hand_size; ++i)
    assert(Player_has_card_in_hand(awesome_spades_hand + i, &bob));

  // Bob will pick up the Queen of Spades, since it's higher than his lowest
  Card queen_spades;
  Card_init(&queen_spades, QUEEN, SPADES);
  Player_add_and_discard(&bob, &queen_spades);
  assert(bob.hand_size == 5);
  assert(Player_has_card_in_hand(&queen_spades, &bob)); //ensure he picked it up
  for (int i=1; i<bob.hand_size; ++i) //ignore that first Ten Spades
    assert(Player_has_card_in_hand(awesome_spades_hand + i, &bob));

  ////////////////////////////////////////
  // Card Player_lead_card() unit tests

  // Bob has the right bower, the max, which he should play if spades is led
  Card card_led = Player_lead_card(&bob, SPADES);
  Card jack_spades;
  Card_init(&jack_spades, JACK, SPADES);
  assert(Card_compare(&card_led, &jack_spades) == 0); //check led card
  assert(bob.hand_size == 4); //should have one less card
  assert(!Player_has_card_in_hand(&jack_spades, &bob)); //check discarded

  ////////////////////////////////////////
  // Player_play_card() unit tests

  // Bob has all spades, so he should play the min if Diamonds is led
  Card nine_diamonds = {NINE, DIAMONDS};
  Card card_played = Player_play_card
    (&bob,            //Bob plays the card
     &nine_diamonds,  //Diamonds is led
     SPADES);         //Spades is trump
  assert(Card_compare(&card_played, &queen_spades) == 0);

  // ADD YOUR TESTS HERE

  // if we got to the end without calling an assert(), the tests passed
  cout << "Player_test PASS" << endl;

  return 0;
}
