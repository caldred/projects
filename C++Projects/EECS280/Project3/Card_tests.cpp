/* Card_test00.cpp
 * 
 * Unit tests for Card
 *
 */

#include "Card.h"
#include <cassert>
#include <cstring>
#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;

int main() {
	
	Card AD, KD, QD, JD, TD, ND;
	Card AC, KC, QC, JC, TC, NC;
	Card AH, KH, QH, JH, TH, NH;
	Card AS, KS, QS, JS, TS, NS;
	Card_init(&AD, ACE, DIAMONDS);
	Card_init(&KD, KING, DIAMONDS);
	Card_init(&QD, QUEEN, DIAMONDS);
	Card_init(&JD, JACK, DIAMONDS);
	Card_init(&TD, TEN, DIAMONDS);
	Card_init(&ND, NINE, DIAMONDS);
	Card_init(&AC, ACE, CLUBS);
	Card_init(&KC, KING, CLUBS);
	Card_init(&QC, QUEEN, CLUBS);
	Card_init(&JC, JACK, CLUBS);
	Card_init(&TC, TEN, CLUBS);
	Card_init(&NC, NINE, CLUBS);
	Card_init(&AH, ACE, HEARTS);
	Card_init(&KH, KING, HEARTS);
	Card_init(&QH, QUEEN, HEARTS);
	Card_init(&JH, JACK, HEARTS);
	Card_init(&TH, TEN, HEARTS);
	Card_init(&NH, NINE, HEARTS);
	Card_init(&AS, ACE, SPADES);
	Card_init(&KS, KING, SPADES);
	Card_init(&QS, QUEEN, SPADES);
	Card_init(&JS, JACK, SPADES);
	Card_init(&TS, TEN, SPADES);
	Card_init(&NS, NINE, SPADES);
	Card cards[24] = {AD, AC, AH, AS, KD, KC, KH, KS, QD, QC, QH, QS, JD, JC, JH, JS,
										TD, TC, TH, TS, ND, NC, NH, NS};
	
  ////////////////////////////////////////
  // Suit_next() unit tests
  Suit s = Suit_next(HEARTS);
  assert(s == DIAMONDS);
	s = Suit_next(DIAMONDS);
  assert(s == HEARTS);
	s = Suit_next(SPADES);
  assert(s == CLUBS);
	s = Suit_next(CLUBS);
  assert(s == SPADES);
	
  ////////////////////////////////////////
  // Card_init() unit tests
  Card queen_diamonds;
  Card_init(&queen_diamonds, QUEEN, DIAMONDS);
  assert(queen_diamonds.rank == QUEEN && queen_diamonds.suit == DIAMONDS);

  ////////////////////////////////////////
  // Card_print() unit tests (unchecked)
  //Card_print(&queen_diamonds);
  //cout << endl;

  ////////////////////////////////////////
  // Card_is_right_bower() unit tests
  Card jack_spades, jack_clubs;
  Card_init(&jack_spades, JACK, SPADES);
  Card_init(&jack_clubs, JACK, CLUBS);
  assert(Card_is_right_bower(&jack_spades, SPADES));
  assert(!Card_is_right_bower(&jack_spades, HEARTS));

  ////////////////////////////////////////
  // Card_is_left_bower() unit tests
  assert(Card_is_left_bower(&jack_clubs, SPADES));
  assert(!Card_is_left_bower(&jack_clubs, HEARTS));

  ////////////////////////////////////////
  // Card_is_trump() unit tests
  assert(Card_is_trump(&jack_clubs, SPADES));
  assert(!Card_is_trump(&jack_clubs, HEARTS));

  ////////////////////////////////////////
  // Card_compare() unit tests
  Card ace_diamonds, ace_hearts, jack_diamonds;
  Card_init(&ace_diamonds, ACE, DIAMONDS);
  Card_init(&ace_hearts, ACE, HEARTS);
  Card_init(&jack_diamonds, JACK, DIAMONDS);
  assert(Card_compare(&ace_diamonds, &ace_hearts) > 0);
  assert(Card_compare(&ace_hearts, &ace_diamonds) < 0);
  assert(Card_compare(&ace_diamonds, &jack_diamonds) > 0);

  ////////////////////////////////////////
  // Card_is_face() unit tests
  Card two_spades;
  Card_init(&two_spades, TWO, SPADES);
  assert(Card_is_face(&two_spades) == false);
  assert(Card_is_face(&ace_diamonds) == true);

  ////////////////////////////////////////
  // Card_get_suit() unit tests
  assert(Card_get_suit(&ace_diamonds, HEARTS) == DIAMONDS);
  assert(Card_get_suit(&jack_spades, SPADES) == SPADES);
  assert(Card_get_suit(&jack_spades, CLUBS) ==  CLUBS);
  assert(Card_get_suit(&jack_spades, DIAMONDS) == SPADES);

  ////////////////////////////////////////
  // Card_init() unit tests
  // these tests will pass once you code 
  // void Card_init(Card *card_ptr, Rank rank, Suit suit);
  Card_init(&two_spades, "Two", "Spades");
  assert(two_spades.rank == TWO && two_spades.suit == SPADES);
	for (int i = 0; i<24; ++i)
		assert((int)cards[i].rank == 12-i/4 && (int)cards[i].suit == 3-i%4); 
  ////////////////////////////////////////
  // Card_compare() unit tests
  // these tests will pass once you code
  // int Card_compare(const Card *a, const Card *b, Suit trump);
  assert(Card_compare(&ace_diamonds, &ace_hearts, DIAMONDS) > 0);
  assert(Card_compare(&ace_diamonds, &ace_hearts, HEARTS) < 0);
  assert(Card_compare(&ace_hearts, &ace_diamonds, DIAMONDS) < 0);
  assert(Card_compare(&ace_diamonds, &jack_diamonds, SPADES) > 0);
  assert(Card_compare(&ace_diamonds, &jack_diamonds, DIAMONDS) < 0);
  assert(Card_compare(&jack_clubs, &jack_spades, CLUBS) > 0);
  assert(Card_compare(&jack_clubs, &jack_spades, SPADES) < 0);
	for( int i = 0; i < 24; ++i)
	{
		for (int j = 0; i < 24; ++i)
		{
			if (i!=j)
			{
				//Card_print(&cards[i]);
				//Card_print(&cards[j]);
				if(Card_is_trump(&cards[i], DIAMONDS) && !Card_is_trump(&cards[j], DIAMONDS))
					assert(Card_compare(&cards[i], &cards[j], DIAMONDS) > 0);
				else if(Card_is_trump(&cards[j], DIAMONDS) && !Card_is_trump(&cards[i], DIAMONDS))
					assert(Card_compare(&cards[i], &cards[j], DIAMONDS) < 0);				
				else if(Card_is_trump(&cards[i], DIAMONDS) && Card_is_trump(&cards[j], DIAMONDS))
				{
					if (Card_is_right_bower(&cards[i], DIAMONDS)) assert(Card_compare(&cards[i], &cards[j], DIAMONDS) > 0);
					else if (Card_is_right_bower(&cards[j], DIAMONDS)) assert(Card_compare(&cards[i], &cards[j], DIAMONDS) < 0);
					else if (Card_is_left_bower(&cards[i], DIAMONDS)) assert(Card_compare(&cards[i], &cards[j], DIAMONDS) > 0);
					else if (Card_is_right_bower(&cards[j], DIAMONDS)) assert(Card_compare(&cards[i], &cards[j], DIAMONDS) < 0);
				}
				else if (i<j)	assert(Card_compare(&cards[i], &cards[j], DIAMONDS) > 0);
				else assert(Card_compare(&cards[i], &cards[j], DIAMONDS) < 0);
			}
		}
	}
	for ( int i = 0; i < 24; ++i)
	{
		for(int j = 0; i < 24; ++i)
		{
			if (i!=j)
			{
				if(Card_is_trump(&cards[i], CLUBS) && !Card_is_trump(&cards[j], CLUBS))
					assert(Card_compare(&cards[i], &cards[j], CLUBS) > 0);
				else if(Card_is_trump(&cards[j], CLUBS) && !Card_is_trump(&cards[i], CLUBS))
					assert(Card_compare(&cards[i], &cards[j], CLUBS) < 0);	
				else if(Card_is_trump(&cards[i], CLUBS) && Card_is_trump(&cards[j], CLUBS))
				{
					if (Card_is_right_bower(&cards[i], CLUBS)) assert(Card_compare(&cards[i], &cards[j], CLUBS) > 0);
					else if (Card_is_right_bower(&cards[j], CLUBS)) assert(Card_compare(&cards[i], &cards[j], CLUBS) < 0);
					else if (Card_is_left_bower(&cards[i], CLUBS)) assert(Card_compare(&cards[i], &cards[j], CLUBS) > 0);
					else if (Card_is_right_bower(&cards[j], CLUBS)) assert(Card_compare(&cards[i], &cards[j], CLUBS) < 0);
				}
				else if (i<j)	assert(Card_compare(&cards[i], &cards[j], CLUBS) > 0);
				else assert(Card_compare(&cards[i], &cards[j], CLUBS) < 0);
			}
		}
	}
	for ( int i = 0; i < 24; ++i)
	{
		for (int j = 0; i < 24; ++i)
		{
			if (i!=j)
			{
				if(Card_is_trump(&cards[i], HEARTS) && !Card_is_trump(&cards[j], HEARTS))
					assert(Card_compare(&cards[i], &cards[j], HEARTS) > 0);
				else if(Card_is_trump(&cards[j], HEARTS) && !Card_is_trump(&cards[i], HEARTS))
					assert(Card_compare(&cards[i], &cards[j], HEARTS) < 0);	
				else if(Card_is_trump(&cards[i], HEARTS) && Card_is_trump(&cards[j], HEARTS))
				{
					if (Card_is_right_bower(&cards[i], HEARTS)) assert(Card_compare(&cards[i], &cards[j], HEARTS) > 0);
					else if (Card_is_right_bower(&cards[j], HEARTS)) assert(Card_compare(&cards[i], &cards[j], HEARTS) < 0);
					else if (Card_is_left_bower(&cards[i], HEARTS)) assert(Card_compare(&cards[i], &cards[j], HEARTS) > 0);
					else if (Card_is_right_bower(&cards[j], HEARTS)) assert(Card_compare(&cards[i], &cards[j], HEARTS) < 0);
				}
				else if (i<j)	assert(Card_compare(&cards[i], &cards[j], HEARTS) > 0);
				else assert(Card_compare(&cards[i], &cards[j], HEARTS) < 0);
			}
		}
	}
	for ( int i = 0; i < 24; ++i)
	{
		for (int j = 0; i < 24; ++i)
		{
			if (i!=j)
			{
				if(Card_is_trump(&cards[i], SPADES) && !Card_is_trump(&cards[j], SPADES))
					assert(Card_compare(&cards[i], &cards[j], SPADES) > 0);
				else if(Card_is_trump(&cards[j], SPADES) && !Card_is_trump(&cards[i], SPADES))
					assert(Card_compare(&cards[i], &cards[j], SPADES) < 0);	
				else if(Card_is_trump(&cards[i], SPADES) && Card_is_trump(&cards[j], SPADES))
				{
					if (Card_is_right_bower(&cards[i], SPADES)) assert(Card_compare(&cards[i], &cards[j], SPADES) > 0);
					else if (Card_is_right_bower(&cards[j], SPADES)) assert(Card_compare(&cards[i], &cards[j], SPADES) < 0);
					else if (Card_is_left_bower(&cards[i], SPADES)) assert(Card_compare(&cards[i], &cards[j], SPADES) > 0);
					else if (Card_is_right_bower(&cards[j], SPADES)) assert(Card_compare(&cards[i], &cards[j], SPADES) < 0);
				}
				else if (i<j)	assert(Card_compare(&cards[i], &cards[j], SPADES) > 0);
				else assert(Card_compare(&cards[i], &cards[j], SPADES) < 0);
			}
		}
	}
  ////////////////////////////////////////
  // Card_compare() unit tests
  // these tests will pass once you code
  // int Card_compare(const Card *a, const Card *b, const Card *led_card, Suit trump);
  Card nine_clubs = {NINE, CLUBS};
  Card nine_hearts = {NINE, HEARTS};
  Card nine_diamonds = {NINE, DIAMONDS};
  assert(Card_compare(&ace_diamonds, &ace_hearts, &nine_clubs, DIAMONDS) > 0);
  assert(Card_compare(&ace_diamonds, &ace_hearts, &nine_clubs, HEARTS) < 0);
  assert(Card_compare(&ace_hearts, &ace_diamonds, &nine_clubs, DIAMONDS) < 0);
  assert(Card_compare(&ace_diamonds, &jack_diamonds, &nine_clubs, SPADES) > 0);
  assert(Card_compare(&ace_diamonds, &jack_diamonds, &nine_clubs, DIAMONDS) < 0);
  assert(Card_compare(&jack_clubs, &jack_spades, &nine_diamonds, CLUBS) > 0);
  assert(Card_compare(&jack_clubs, &jack_spades, &nine_diamonds, SPADES) < 0);
  assert(Card_compare(&ace_diamonds, &ace_hearts, &nine_hearts, DIAMONDS) > 0);
  assert(Card_compare(&ace_diamonds, &ace_hearts, &nine_diamonds, HEARTS) < 0);
  assert(Card_compare(&ace_diamonds, &ace_hearts, &nine_hearts, CLUBS) < 0);
  assert(Card_compare(&ace_diamonds, &ace_hearts, &nine_diamonds, CLUBS) > 0);
	Suit upSuit = DIAMONDS;
	Suit trump = DIAMONDS;
	for (int k = 0; k < 4; ++k)
	{
		for (int l = 0; l < 4; ++l)
		{
			for( int i = 0; i < 24; ++i)
			{
				for (int j = 0; i < 24; ++i)
				{
					if (i!=j)
					{
						switch (k)
						{
							case 0: upSuit = DIAMONDS; break;
							case 1: upSuit = CLUBS; break;
							case 2: upSuit = HEARTS; break;
							case 3: upSuit = SPADES; break;
						}
						switch (l)
						{
							case 0: trump = DIAMONDS; break;
							case 1: trump = CLUBS; break;
							case 2: trump = HEARTS; break;
							case 3: trump = SPADES; break;
						}
						if(Card_is_trump(&cards[i], trump) && !Card_is_trump(&cards[j], trump))
							assert(Card_compare(&cards[i], &cards[j], &cards[k], trump) > 0);
						else if(Card_is_trump(&cards[j], trump) && !Card_is_trump(&cards[i], trump))
							assert(Card_compare(&cards[i], &cards[j], &cards[k], trump) < 0);				
						else if(Card_is_trump(&cards[i], trump) && Card_is_trump(&cards[j], trump))
						{
							if (Card_is_right_bower(&cards[i], trump)) 
								assert(Card_compare(&cards[i], &cards[j], &cards[k], trump) > 0);
							else if (Card_is_right_bower(&cards[j], trump)) 
								assert(Card_compare(&cards[i], &cards[j], &cards[k], trump) < 0);
							else if (Card_is_left_bower(&cards[i], trump)) 
								assert(Card_compare(&cards[i], &cards[j], &cards[k], trump) > 0);
							else if (Card_is_right_bower(&cards[j], trump)) 
								assert(Card_compare(&cards[i], &cards[j], &cards[k], trump) < 0);
						}
						else if(Card_get_suit(&cards[i], trump) == upSuit && !(Card_get_suit(&cards[j], trump) == upSuit))
							assert(Card_compare(&cards[i], &cards[j], &cards[k], trump) > 0);
						else if(Card_get_suit(&cards[j], trump) == upSuit && !(Card_get_suit(&cards[i], trump) == upSuit))
							assert(Card_compare(&cards[i], &cards[j], &cards[k], trump) < 0);				
						else if (i<j)	assert(Card_compare(&cards[i], &cards[j], &cards[k], trump) > 0);
						else assert(Card_compare(&cards[i], &cards[j], &cards[k], trump) < 0);
					}
				}
			}
		}
	}	


  // ADD YOUR TEST CASES HERE


  // if we got to the end without calling an assert(), the tests passed
  cout << "Card_test PASS" << endl;

  return 0;
}
