#include "Pack.h"
#include <cassert>
#include <cstring>
#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;
const char *const SUIT_NAMES[] = {"Spades", "Hearts", "Clubs", "Diamonds"};
const int SUIT_SIZE = 4;
const char *const RANK_NAMES[] = {"Two", "Three", "Four", "Five", "Six",
                                  "Seven", "Eight", "Nine", "Ten", "Jack",
                                  "Queen", "King", "Ace"};
const int RANK_SIZE = 13;

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

void Pack_init(Pack* pack_ptr, const char* pack_filename)
{
    string filename = pack_filename;
    ifstream filestream;
    filestream.open( filename.c_str() );
    if ( !filestream.is_open() )
    {
        cout << "open failed" << endl;
        exit(1);
    }
    string word;
    string temp[PACK_SIZE*3+1];
    int i = 0;
    while ( filestream >> word )
    {
        temp[i] = word;
        ++i;
    }
    for (int j = 0; j < PACK_SIZE*3; j++)
    {
		if(temp[j]!="")
		{
			if(j%3==0) pack_ptr -> cards[j/3].rank = string2rank(temp[j].c_str(), RANK_NAMES);
		   	if(j%3==2) pack_ptr -> cards[j/3].suit = string2suit(temp[j].c_str(), SUIT_NAMES);
		}
		else
		{
			cout << "bad pack input file" << endl;
			exit(1);
		}	
    }
	if(temp[PACK_SIZE*3] != "")
	{
		cout << "bad pack input file" << endl;
		exit(1);
	}	
    pack_ptr -> next = pack_ptr -> cards;
    filestream.close();
}

Card Pack_deal_one(Pack *pack_ptr)
{
    return *pack_ptr -> next++;
}

void Pack_reset(Pack *pack_ptr)
{
    pack_ptr -> next = pack_ptr -> cards;
}

void Pack_shuffle(Pack *pack_ptr)
{
    Card temp[PACK_SIZE];
    for (int i = 0; i < PACK_SIZE; i++) temp[i] = pack_ptr -> cards[i];
    for (int i = 0; i < 17; i++) pack_ptr -> cards[i+7] = temp[i];
    for (int i = 0; i < 7; i++) pack_ptr -> cards[i] = temp[i+17];
    for (int i = 0; i < PACK_SIZE; i++) temp[i] = pack_ptr -> cards[i];
    for (int i = 0; i < 17; i++) pack_ptr -> cards[i+7] = temp[i];
    for (int i = 0; i < 7; i++) pack_ptr -> cards[i] = temp[i+17];
    for (int i = 0; i < PACK_SIZE; i++) temp[i] = pack_ptr -> cards[i];
    for (int i = 0; i < 17; i++) pack_ptr -> cards[i+7] = temp[i];
    for (int i = 0; i < 7; i++) pack_ptr -> cards[i] = temp[i+17];
    Pack_reset(pack_ptr);
}
