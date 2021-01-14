#include "Deck.h"
#include <cassert>
#include <cstring>
#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>

Deck::Deck()
{
    for(int s = 0; s < 4; ++s)
    {
        for(int r = 0; r < 13; ++ r)
        {
            cards[13*s+r] = Card(static_cast<Card::Rank>(r),
                                 static_cast<Card::Suit>(s));
        }
    }
		next = &cards[0];
}

void Deck::reset()
{
    for(int s = 0; s < 4; ++s)
    {
        for(int r = 0; r < 13; ++ r)
        {
            cards[13*s+r] = Card(static_cast<Card::Rank>(r),
                                 static_cast<Card::Suit>(s));
        }
    }
    next = &cards[0];
}

void Deck::shuffle(int n)
{
    Card right[DECK_SIZE];
    Card left[DECK_SIZE];
    for (int i = 0; i < n; ++i)
    {
        left[i] = cards[i];
    }
    for(int i = n; i<DECK_SIZE; ++i)
    {
        right[i-n] = cards[i];
    }
    if(n<=DECK_SIZE/2)
    {
        for(int i = 0; i < n*2; ++i)
        {
            if(!(i%2)) cards[i] = right[i/2];
            else cards[i] = left[i/2];
        }
        for(int i = n*2; i < DECK_SIZE; ++i)
        {
            cards[i] = right[i-n];
        }
    }
    else
    {
        for(int i = 0; i < (DECK_SIZE-n)*2; ++i)
        {
            if(!(i%2))cards[i] = right[i/2];
            else cards[i] = left[i/2];
        }
        for(int i = (DECK_SIZE-n)*2; i < DECK_SIZE; ++i)
        {
            cards[i] = left[i-(DECK_SIZE-n)];
        }
    }
    next = &cards[0];
}

Card Deck::deal()
{
    return *next++;
}

int Deck::cards_remaining() const
{
    return &cards[DECK_SIZE-1] - next+1;
}
