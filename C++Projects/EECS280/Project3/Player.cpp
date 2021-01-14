#include "Player.h"
#include <cassert>
#include <cstring>
#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;

//REQUIRES name is less than MAX_STR_LEN characters
//MODIFIES player_ptr
//EFFECTS  Initializes Player pointed to by player_ptr with name and an empty
//  hand.
void Player_init(Player *player_ptr, const char *name)
{
    strcpy(player_ptr -> name, name);
    player_ptr -> hand_size = 0;
}

//REQUIRES player_ptr points to an initialized Player
//  player has less than MAX_HAND_SIZE cards
//MODIFIES player_ptr
//EFFECTS  adds Card c to Player's hand
void Player_add_card(Player *player_ptr, const Card *c)
{
    player_ptr -> hand[player_ptr -> hand_size++] = *c;
}

//REQUIRES player_ptr points to an initialized Player
//  round is 1 or 2
//MODIFIES order_up_suit
//EFFECTS If Player wishes to order up a trump suit then return true and
//  change order_up_suit to desired suit.  If Player wishes to pass, then do not
//  modify order_up_suit and return false.  See the spec for strategy.
bool Player_make_trump(const Player *player_ptr, const Card *upcard,
                       const Player *dealer, int round, Suit *order_up_suit)
{
    if(round == 1)
    {
        int facecounter = 0;
        for(int i = 0; i < MAX_HAND_SIZE; ++i)
        {
            const Card *card_ptr = &player_ptr -> hand[i];
            if(Card_is_face(card_ptr) && Card_is_trump(card_ptr, upcard -> suit)) ++facecounter;
        }
        if (facecounter > 1)
        {
            *order_up_suit = upcard -> suit;
            return true;
        }
        return false;
    }
    else if (round == 2)
    {
        if(dealer == player_ptr)
        {
            *order_up_suit = Suit_next(upcard -> suit);
            return true;
        }
        int facecounter = 0;
        for(int i = 0; i < MAX_HAND_SIZE; ++i)
        {
            const Card *card_ptr = &player_ptr -> hand[i];
            if(Card_is_face(card_ptr)
               && player_ptr -> hand[i].suit == Suit_next(upcard -> suit)) ++facecounter;
        }
        if (facecounter > 0)
        {
            *order_up_suit = Suit_next(upcard -> suit);
            return true;
        }
        return false;
    }
    else
    {
        assert(0);
        exit(1);
        return false;
    }
}


//REQUIRES player_ptr points to an initialized Player
//  Player has at least one card
//MODIFIES player_ptr
//EFFECTS  Player adds one card to hand and removes one card from hand.
//  See spec for determining which.
void Player_add_and_discard(Player *player_ptr, const Card *upcard)
{
    Suit trump = upcard -> suit;
    for(int i = 0; i<MAX_HAND_SIZE; ++i)
    {
        const Card *card_ptr = &player_ptr -> hand[i];
        if(Card_compare(card_ptr, upcard, trump) < 0)
        {
            const Card *lowestCard = &player_ptr -> hand[0];
            int lowest = 0;
            for(int j = 1; j<MAX_HAND_SIZE; ++j)
            {
                card_ptr = &player_ptr -> hand[j];
                if(Card_compare(lowestCard, card_ptr, trump) > 0)
                {
                    lowestCard = card_ptr;
                    lowest = j;
                }
            }
            player_ptr -> hand[lowest] = *upcard;
            break;
        }
    }
}

//REQUIRES player_ptr points to an initialized Player
//  Player has at least one card
//MODIFIES player_ptr
//EFFECTS  Leads one Card from Player's hand according to the strategy in the
//  project spec.  "Lead" means to play the first Card in a trick.  The card
//  is removed the player's hand.
Card Player_lead_card(Player *player_ptr, Suit trump)
{
    bool allTrump = true;
    int highest=0;
    const Card *highestCard = &player_ptr -> hand[0];
    for(int i = 0; i < player_ptr -> hand_size; ++i)
    {
        if(!Card_is_trump(&player_ptr -> hand[i], trump)) allTrump = false;
    }
    if(!allTrump)
    {
        for(int i = 0; i < player_ptr -> hand_size; ++i)
        {
            if (!Card_is_trump(&player_ptr ->hand[i], trump))
            {
                highestCard = &player_ptr ->hand[i];
                highest = i;
                break;
            }
        }
        for(int i = highest+1; i < player_ptr -> hand_size; ++i)
        {
            const Card *card_ptr = &player_ptr -> hand[i];
            if(Card_compare(highestCard, card_ptr, trump) < 0 && !Card_is_trump(card_ptr, trump))
            {
                highestCard = card_ptr;
                highest = i;
            }
        }
    }
    else
    {
        highestCard = &player_ptr -> hand[0];
        highest = 0;
        for(int i = 1; i < player_ptr -> hand_size; ++i)
        {
            const Card *card_ptr = &player_ptr -> hand[i];
            if(Card_compare(highestCard, card_ptr, trump) < 0)
            {
                highestCard = card_ptr;
                highest = i;
            }
        }
    }
    Card led_card = player_ptr -> hand[highest];
    for(int i=highest; i < player_ptr -> hand_size - 1; ++i)
    {
        player_ptr -> hand[i] = player_ptr -> hand[i+1];
    }
    player_ptr -> hand[player_ptr->hand_size - 1] = led_card;
    --player_ptr -> hand_size;
    return led_card;
}

//REQUIRES player_ptr points to an initialized Player
//  Player has at least one card
//MODIFIES player_ptr
//EFFECTS  Plays one Card from Player's hand according to the strategy in the
//  project spec.  The card is removed from the player's hand.
Card Player_play_card(Player *player_ptr, const Card *led_card, Suit trump)
{
    Suit led_suit = Card_get_suit(led_card, trump);
    bool able_to_follow = false;
    Card *playCard = &player_ptr->hand[0];
    int numPlayCard = 0;
    for(int i = 0; i < player_ptr -> hand_size; ++i)
    {
        Card *card_ptr = &player_ptr -> hand[i];
        if (Card_get_suit(card_ptr, trump) == led_suit) able_to_follow = true;
    }
    if (able_to_follow)
    {
        Card *card_ptr = &player_ptr->hand[0];
        for(int i = 0; i < player_ptr -> hand_size; ++i)
        {
            card_ptr = &player_ptr -> hand[i];
            if (Card_get_suit(card_ptr, trump) == led_suit)
            {
                playCard = card_ptr;
                numPlayCard = i;
                break;
            }
        }
        for(int i = numPlayCard+1; i < player_ptr -> hand_size; ++i)
        {
			card_ptr = &player_ptr -> hand[i];
            if(Card_compare(playCard, card_ptr, led_card, trump) < 0
               && Card_get_suit(card_ptr, trump) == led_suit)
            {
                playCard = card_ptr;
                numPlayCard = i;
            }
        }
    }
    else
    {
		//cout << "Not able to follow\n";
        playCard = &player_ptr -> hand[0];
        numPlayCard = 0;
        for(int i = 1; i<player_ptr -> hand_size; ++i)
        {
            Card *card_ptr = &player_ptr -> hand[i];
            if(Card_compare(playCard, card_ptr, trump) > 0)
            {
                playCard = card_ptr;
                numPlayCard = i;
            }
        }
    }
    Card played_card = player_ptr -> hand[numPlayCard];
    for(int i=numPlayCard; i < player_ptr -> hand_size - 1; ++i)
    {
        player_ptr -> hand[i] = player_ptr -> hand[i+1];
    }
    player_ptr -> hand[player_ptr->hand_size - 1] = played_card;
    player_ptr -> hand_size += -1;
    return played_card;
}
