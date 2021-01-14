#include "Player.h"
#include <cstdlib>
#include <cstring>
#include <iostream>

class Simple : public Player
{
    public:
        //EFFECTS:  Creates a player with a bankroll of 0
        Simple() {}

        virtual int bet(int bankroll, int minimum)
        {
            return minimum;
        }
				
				//EFFECTS:	Follows the spec by implementing basic blackjack strategy.
        virtual bool draw(Card dealer, const Hand &player)
        {
            if(!player.hand_is_soft())
            {
                if(player.hand_value() < 12) return true;
                if(player.hand_value() < 13)
                {
                    if(dealer.get_rank() < 5 &&
                       dealer.get_rank() > 1) return false;
                    else return true;
                }
                if(player.hand_value() < 17)
                {
                    if(dealer.get_rank() < 5) return false;
                    else return true;
                }
                else return false;
            }
            else
            {
                if(player.hand_value() < 18) return true;
                if(player.hand_value() < 19)
                {
                    if(dealer.get_rank() == 0 ||
                       dealer.get_rank() == 5 ||
                       dealer.get_rank() == 6) return false;
                    else return true;
                }
                else return false;
            }
        }
				
        virtual void expose(Card c) {return;}

        virtual void shuffled() {return;}

};

class Counting : public Simple
{
protected:
    int count;
public:
    //EFFECTS:  Creates a Counting player with a count of 0
    Counting() : count(0) {}
		
		//EFFECTS: returns a bet of double the minimum if the count is > 2
		//				 or returns the bankroll if the bankroll is < 2*min
    virtual int bet(int bankroll, int minimum)
    {
        if (count < 2) return minimum;
        else if (bankroll < minimum*2) return bankroll;
				else return minimum*2;
    }
		
		//EFFECTS: adds 1 to the count if the card is a 6 or less
		//				 subtracts 1 if the cards is 10 or more.
    virtual void expose(Card c)
    {
        if(c.get_rank() < 5) count++;
        else if(c.get_rank() > 7) count--;
    }
		//EFFECTS: resets the count to 0;
    virtual void shuffled() {count = 0;}
};

const int DECK_SIZE = 52;

class Competitor : public Counting
{
private:
    int cards;
public:
		//EFFECTS: Creates a Competitor with a count of 0 and 52 cards.
    Competitor() {cards = 52;}
		
		//EFFECTS: Returns the optimal bet for the player to make
		// 				 based on the advantage he has in a given hand.
    virtual int bet(int bankroll, int minimum)
    {
        int optimal  = (count*DECK_SIZE/cards - 4)*bankroll/200;
        if(optimal > bankroll/50) optimal = bankroll/50;
        if (optimal < minimum) return minimum;
        else return optimal;
    }
		
		//EFFECTS: implements the counting system, and keeps
		//				 track of how many cards he has seen.
    virtual void expose(Card c)
    {
        if(c.get_rank() < 5) count++;
        else if(c.get_rank() > 7) count--;
				--cards;
    }

		//EFFECTS: resets the counts and cards.
    virtual void shuffled() 
    {				
        count = 0;
				cards = 52;
    }
};

static Simple simp;
static Counting countp;
static Competitor comp;

// REQUIRES: s is a C-string: "simple" "counting" or "competitor"
// EFFECTS: returns a pointer to the specified Player
Player * player_factory(const char * s)
{
    if(strcmp(s,"simple") == 0) return &simp;
    if(strcmp(s,"counting") == 0) return &countp;
    else return &comp;
}
