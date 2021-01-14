#include "Player.h"
#include "Deck.h"
#include "rand.h"
#include <cassert>
#include <cstring>
#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

const int MINIMUM = 5;

//MODIFIES: deck, player_ptr;
//EFFECTS: Shuffles deck at 7 randomly generated cuts from 13 to 39.
//         Tells the player that the deck has been shuffled.
void deck_shuffle(Deck* deck, Player* player_ptr)
{
    cout << "Shuffling the deck\n";
    for (int i = 0; i < 7; i++)
    {
	int cut = get_cut();
        cout << "cut at " << cut << endl;
        deck->shuffle(cut);
    }
    player_ptr->shuffled();
}

//EFFECTS: Plays a game of blackjack.
int main(int argc, char* argv[])
{
    int bankroll = atoi(argv[1]);
    int numHands = atoi(argv[2]);
    int wager = MINIMUM;
    int wager_tot = 0;
    Deck deck;
    Hand dealer;
    Hand player;
    Player *player_ptr = player_factory(argv[3]);
    deck_shuffle(&deck, player_ptr);
    int thishand =1;
    while (thishand <= numHands && bankroll > MINIMUM)
    {
        cout << "Hand " << thishand << " bankroll " << bankroll << endl;
        if(deck.cards_remaining() < 20) deck_shuffle(&deck, player_ptr);

        wager = player_ptr->bet(bankroll, MINIMUM);
        wager_tot += wager;
        cout << "Player bets " << wager << endl;

        Card temp = deck.deal();
        player.add_card(temp);
        player_ptr->expose(temp);
        cout << "Player dealt " << temp << endl;
        Card upcard = deck.deal();
        dealer.add_card(upcard);
        player_ptr->expose(upcard);
        cout << "Dealer dealt " << upcard << endl;
        temp = deck.deal();
        player.add_card(temp);
        player_ptr->expose(temp);
        cout << "Player dealt " << temp << endl;
        Card holecard = deck.deal();
        dealer.add_card(holecard);
        if(player.hand_value() == 21)
        {
            cout << "Player dealt natural 21\n";
            bankroll += (wager*3)/2;
        }
        else
        {
            while(player_ptr->draw(upcard, player))
            {
                temp = deck.deal();
                player.add_card(temp);
                player_ptr->expose(temp);
                cout << "Player dealt " << temp << endl;
            }
            cout << "Player's total is " << player.hand_value() << endl;

            if(player.hand_value() > 21)
            {
                cout << "Player busts\n";
                bankroll -= wager;
            }
            else
            {
		cout << "Dealer's hole card is " << holecard << endl;
                player_ptr->expose(holecard);
                while(dealer.hand_value() < 17)
                {
                    temp = deck.deal();
                    dealer.add_card(temp);
                    player_ptr->expose(temp);
                    cout << "Dealer dealt " << temp << endl;
                }
                cout << "Dealer's total is " << dealer.hand_value() << endl;
                if(dealer.hand_value() > 21)
                {
                    cout << "Dealer busts\n";
                    bankroll += wager;
                }
                else if (dealer.hand_value() > player.hand_value())
                {
                    cout << "Dealer wins\n";
                    bankroll -= wager;
                }
                else if (player.hand_value() > dealer.hand_value())
                {
                    cout << "Player wins\n";
                    bankroll += wager;
                }
            }
        }
        ++thishand;
				dealer.discard_all();
				player.discard_all();
    }
	cout << "Player has " << bankroll << " after " << thishand-1 << " hands\n"; 
}
