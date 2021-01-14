#include "Game.h"
#include <cassert>
#include <cstring>
#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

const char *const SUIT_NAMES[] = {"Spades", "Hearts", "Clubs", "Diamonds"};
const char *const RANK_NAMES[] = {"Two", "Three", "Four", "Five", "Six",
                                  "Seven", "Eight", "Nine", "Ten", "Jack",
                                  "Queen", "King", "Ace"};

//REQUIRES pack_filename file contains a well-formed Euchre pack
//MODIFIES game_ptr, stdout
//EFFECTS  Initializes Game pointed to by game_ptr, including initializing
//  the Pack and each Player.
void Game_init(Game *game_ptr, const char *pack_filename, bool shuffle,
               int points_to_win, const char *const player_names[])
{
    Pack pack;
    Pack_init(&pack, pack_filename);
    Player player0;
    Player_init(&player0, player_names[0]);
    Player player1;
    Player_init(&player1, player_names[1]);
    Player player2;
    Player_init(&player2, player_names[2]);
    Player player3;
    Player_init(&player3, player_names[3]);
    game_ptr -> pack = pack;
    game_ptr -> shuffle = shuffle;
    for (int i = 0; i < NUM_PARTNERSHIPS; ++i) game_ptr -> score[i] = 0;
    game_ptr -> points_to_win = points_to_win;
    game_ptr -> players[0] =  player0;
    game_ptr -> players[1] =  player1;
    game_ptr -> players[2] =  player2;
    game_ptr -> players[3] =  player3;
}
//REQUIRES 	game_ptr points to an initialized Game
//MODIFIES 	game_ptr
//EFFECTS 	adds the top numCard cards to the hand of the next player to be dealt 
//			cards
void deal_helper(Game *game_ptr, const int hand, const int numCard, const int deal)
{
    for (int i = 0; i < numCard; ++i)
    {
        Card newCard = Pack_deal_one(&game_ptr -> pack);
        Card *card_ptr = &newCard;
        Player *player_ptr = &game_ptr -> players[(deal+hand)%NUM_PLAYERS];
        Player_add_card(player_ptr, card_ptr);
    }
}

//REQUIRES 	game_ptr points to an initialized Game
//MODIFIES 	game_ptr, stdout
//EFFECTS 	prints out the dealer to stdout and calls deal_helper to add the
//			correct number of cards to players' hands
void dealCards(Game *game_ptr, const int hand)
{
    cout << game_ptr->players[hand%NUM_PLAYERS].name << " deals" << endl;
    deal_helper(game_ptr, hand, 3, 1);
    deal_helper(game_ptr, hand, 2, 2);
    deal_helper(game_ptr, hand, 3, 3);
    deal_helper(game_ptr, hand, 2, 4);
    deal_helper(game_ptr, hand, 2, 5);
    deal_helper(game_ptr, hand, 3, 6);
    deal_helper(game_ptr, hand, 2, 7);
    deal_helper(game_ptr, hand, 3, 8);
	Card topcard = *game_ptr->pack.next;
}
//REQUIRES 	game_ptr points to an initialized Game
//MODIFIES  game_ptr
//EFFECTS	if shuffle is enabled, shuffles the deck. Also, resets the pack to the 
//			first card
void shuffle(Game* game_ptr)
{
    if (game_ptr->shuffle) Pack_shuffle(&game_ptr->pack);
    Pack_reset(&game_ptr->pack);
}

//REQUIRES	game_ptr points to an initialized Game
//MODIFIES	game_ptr, stdout
//EFFECTS	prints the upcard to stdout, and determines whether each player will 
//			pass or order up, and print that to stdout. When a player does order 
//			up, the dealer adds the upcard to his and hand and discards his lowest
//			card. Then return the number corresponding to the player who ordered
//			up trump. 
int makeTrump(Game* game_ptr, const int hand, Suit *trump)
{
	Card *upcard = game_ptr->pack.next;
    Card_print(upcard);
    cout << " turned up" << endl;
    *trump = SPADES;
    for (int round = 1; round < 3; ++round)
    {
        for (int i = 0; i<NUM_PLAYERS; ++i)
        {
            Player *active_player = &game_ptr->players[(i+hand+1)%NUM_PLAYERS];
            Player *dealer = &game_ptr->players[hand%NUM_PLAYERS];
            if (Player_make_trump(active_player, upcard, dealer, round, trump))
            {
                cout << active_player->name << " orders up " << SUIT_NAMES[*trump] << endl;
                cout << endl;
				if(round == 1)
				{ 
					//cout << "Adding and Discarding\n";						
					Player_add_and_discard(dealer, upcard);
				}
                return (i+hand+1)%NUM_PLAYERS;
            }
            else
            {
                cout << active_player->name << " passes" << endl;
            }
        }
    }
    assert(0);
    return 0;
}

//REQUIRES  game_ptr points to an initialized Game
//MODIFIES  game_ptr, stdout
//EFFECTS	Plays one trick in a game of euchre. Determines according to the spec
//			which card each play should play and prints that to stdout. The winner 
//			is also determined according to who played the highest card. Return
//			the number corresponding the index of the winning player.
int play_trick(Game *game_ptr, int prvWin, Suit trump)
{
    Card cards[NUM_PLAYERS];
    cards[0] = Player_lead_card(&game_ptr->players[prvWin], trump);
    cout << RANK_NAMES[cards[0].rank] << " of " << SUIT_NAMES[cards[0].suit];
    cout << " led by " << game_ptr->players[prvWin].name << endl;
    for (int i = 1; i < NUM_PLAYERS; ++i)
    {
        cards[i] = Player_play_card(&game_ptr->players[(prvWin+i)%NUM_PLAYERS], &cards[0], trump);
        cout << RANK_NAMES[cards[i].rank] << " of " << SUIT_NAMES[cards[i].suit];
        cout << " played by " << game_ptr->players[(prvWin+i)%NUM_PLAYERS].name << endl;
    }
    Card high_card = cards[0];
    int highest = 0;
    for(int i = 1; i < NUM_PLAYERS; ++i)
    {
        if (Card_compare(&high_card, &cards[i], &cards[0], trump) < 0)
        {
            high_card = cards[i];
            highest = i;
        }
    }
    cout << game_ptr->players[(highest+prvWin)%NUM_PLAYERS].name << " takes the trick" << endl << endl;
    return (prvWin+highest)%NUM_PLAYERS;
}

//REQUIRES	game_ptr points to an initialized Game
//MODIFIES	game_ptr, stdout
//EFFECTS	Determines which partnership won the hand, and how many points to award
//			them, and prints that to stdout. Also prints the team total points
//			up to and including the immediately preceding hand.
void add_points(Game* game_ptr, int tricksWon[], int maker)
{
    if (tricksWon[0] > tricksWon[1])
    {
        Player winner1 = game_ptr->players[0];
        Player winner2 = game_ptr->players[2];
        cout << winner1.name << " and " << winner2.name << " win the hand" << endl;
        if (maker == 0 || maker == 2)
        {
            if (tricksWon[0] == 5)
            {
                game_ptr->score[0]+=2;
                cout << "march!" << endl;
            }
            else ++game_ptr->score[0];
        }
        else
        {
            game_ptr-> score[0]+=2;
            cout << "euchred!" << endl;
        }
    }
    else
    {
        Player winner1 = game_ptr->players[1];
        Player winner2 = game_ptr->players[3];
        cout << winner1.name << " and " << winner2.name << " win the hand" << endl;
        if (maker == 1 || maker == 3)
        {
            if (tricksWon[1] == 5)
            {
                game_ptr->score[1]+=2;
                cout << "march!" << endl;
            }
            else ++game_ptr->score[1];
        }
        else
        {
            game_ptr-> score[1]+=2;
            cout << "euchred!" << endl;
        }
    }
    cout << game_ptr->players[0].name << " and " << game_ptr->players[2].name;
    cout << " have " << game_ptr->score[0] << " points" << endl;
    cout << game_ptr->players[1].name << " and " << game_ptr->players[3].name;
    cout << " have " << game_ptr->score[1] << " points" << endl;
    cout << endl;
}

//REQUIRES 	game_ptr points to an initialized game
//MODIFIES 	stdout
//EFFECTS	prints out the cards currently contained in the players' hands.
void print_hands(Game *game_ptr)
{
    cout << "Alice's Hand" << endl;
    for (int i = 0; i<game_ptr->players[0].hand_size; ++i)
    {
        Card_print(&game_ptr->players[0].hand[i]);
        cout << endl;
    }
    cout << endl;
    cout << "Bob's Hand" << endl;
    for (int i = 0; i<game_ptr->players[1].hand_size; ++i)
    {
        Card_print(&game_ptr->players[1].hand[i]);
        cout << endl;
    }
    cout << endl;
    cout << "Cathy's Hand" << endl;
    for (int i = 0; i<game_ptr->players[2].hand_size; ++i)
    {
        Card_print(&game_ptr->players[2].hand[i]);
        cout << endl;
    }
    cout << endl;
    cout << "Drew's Hand" << endl;
    for (int i = 0; i<game_ptr->players[3].hand_size; ++i)
    {
        Card_print(&game_ptr->players[3].hand[i]);
        cout << endl;
    }
    cout << endl;
}
//REQUIRES game_ptr points to an initialized Game
//MODIFIES game_ptr, stdout
//EFFECTS  Plays one game of Euchre
void Game_play(Game *game_ptr)
{
    int hand = 0;
    Suit trump;
    int tricks_won[NUM_PARTNERSHIPS];
	tricks_won[0] = 0;
	tricks_won[1] = 0;
    while(game_ptr->score[0] < game_ptr->points_to_win &&
          game_ptr->score[1] < game_ptr->points_to_win)
    {
        cout << "Hand " << hand << endl;
        shuffle(game_ptr);
        dealCards(game_ptr, hand);
        int maker = makeTrump(game_ptr, hand, &trump);
		//print_hands(game_ptr);
        int winner = (hand+1)%4;
        for (int i = 0; i < MAX_HAND_SIZE; ++i)
        {
            winner = play_trick(game_ptr, winner, trump);
			//print_hands(game_ptr);
            if (winner == 0 || winner == 2) tricks_won[0] = tricks_won[0] + 1;
            else tricks_won[1] = tricks_won[1] + 1;
        }
		//cout << "Alice and Cathy won " << tricks_won[0] << " tricks" << endl;
		//cout << "Bob and Drew won " << tricks_won[1] << " tricks" << endl;
        add_points(game_ptr, tricks_won, maker);
		tricks_won[0] = 0;
		tricks_won[1] = 0;
        ++hand;
    }
    if (game_ptr->score[0] > game_ptr->score[1])
        cout << game_ptr->players[0].name  << " and "  << game_ptr->players[2].name <<" win!"<<endl;
    else
        cout << game_ptr->players[1].name  << " and "  << game_ptr->players[3].name <<" win!"<<endl;
}
