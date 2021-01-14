#include <cstdlib>
#include <vector>
#include <utility>
#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <getopt.h>
#include "Eecs281PQ.h"
#include "PoorManPQ.h"
#include "SortedPQ.h"
#include "BinaryPQ.h"
#include "PairingPQ.h"
#include "P2.h"

static struct option longopts[] =
{
    {"help", no_argument, 0, 'h'},
    {"container", required_argument, 0, 'c'},
    {"stats", required_argument, 0, 's'},
    {"median", no_argument, 0, 'm'},
    {0,0,0,0}
};

struct space {
    int x;
    int y;
    int* val;
    space(int xi, int yi, int* vali)
	: x(xi), y(yi), val(vali) {};
};

class Comp {
public:
    bool operator()(const space &a, const space &b) {
	//cerr << a.val << ' ' << *(a.val) << '\n';
	//cerr << b.val << ' ' << *(b.val) << '\n';
	if(*(a.val) > *(b.val))
	    return true;
	if(*(a.val) < *(b.val))
	    return false;
	if(a.y > b.y)
	    return true;
	if(a.y < b.y)
	    return false;
	if(a.x > b.x)
	    return true;
	else
	    return false;
    }
};

class Ecomp {
public:
    bool operator()(vector<int> &a, vector<int> &b) {
	if(a[2] > b[2])
	    return true;
	if(a[2] < b[2])
	    return false;
	if(a[1] > b[1])
	    return true;
	if(a[1] < b[1])
	    return false;
	if(a[0] > b[0])
	    return true;
	else
	    return false;
    }
};

class Hcomp {
public:
    bool operator()(vector<int> &a, vector<int> &b) {
	if(a[2] > b[2])
	    return false;
	if(a[2] < b[2])
	    return true;
	if(a[1] > b[1])
	    return false;
	if(a[1] < b[1])
	    return true;
	if(a[0] < b[0])
	    return true;
	else
	    return false;
    }
};

struct Game {    
    bool stats;
    bool median;
    char pqtype;
    size_t numcleared;
    size_t diffcleared;
    vector< vector<int> > chron;
    Eecs281PQ< int, std::greater<int>> * harder;
    Eecs281PQ< int, std::less<int>> * easier;
    Eecs281PQ< space, Comp> * TNTpq;
    ~Game() {
	delete harder;
	delete easier;
	delete TNTpq;
    }
    Game(bool statsin, bool medianin, char pqtypein)
	: stats(statsin), median(medianin), pqtype(pqtypein), numcleared(0), diffcleared(0) {
	switch(pqtype) {
	case 'p':
	    harder = new PairingPQ<int, std::greater<int>>;
	    easier = new PairingPQ<int, std::less<int>>;
	    TNTpq = new PairingPQ<space, Comp>;
	    break;
	case 'b':
	    harder = new BinaryPQ<int, std::greater<int>>;
	    easier = new BinaryPQ<int, std::less<int>>;
	    TNTpq = new BinaryPQ<space, Comp>;
	    break;
	case 's':
	    harder = new SortedPQ<int, std::greater<int>>;
	    easier = new SortedPQ<int, std::less<int>>;
	    TNTpq = new SortedPQ<space, Comp>;
	    break;
	default:
	    harder = new PoorManPQ<int, std::greater<int>>;
	    easier = new PoorManPQ<int, std::less<int>>;
	    TNTpq = new PoorManPQ<space, Comp>;
	    break;
	}
    }
};	

void clear(int xpos, int ypos, vector< vector< pair<int, bool> > > &mine, Game &game) {
    int val = mine[xpos][ypos].first;
    if(val == 0) 
	return;
    if(game.median) {
	double median = 0;
	if(game.easier->empty() || val <= game.easier->top())
	    game.easier->push(val);
	else
	    game.harder->push(val);
	if(game.easier->size() == game.harder->size() + 2) {
	    int temp = game.easier->top();
	    game.easier->pop();
	    game.harder->push(temp);
	}
	else if(game.easier->size() + 2 == game.harder->size()) {
	    int temp = game.harder->top();
	    game.harder->pop();
	    game.easier->push(temp);
	}
	if(game.easier->size() > game.harder->size())
	    median = (double) game.easier->top();
	else if(game.harder->size() > game.easier->size())
	    median = (double) game.harder->top();
	else
	    median = (double) ((double) game.harder->top() + (double) game.easier->top())/2;
	cout << "Median difficulty of clearing rubble is: " << median << '\n';
    }
    if(game.stats) {
	vector<int> tempv;
	tempv.push_back(xpos);
	tempv.push_back(ypos);
	tempv.push_back(val);
	game.chron.push_back(tempv);
    }
    ++game.numcleared;
    game.diffcleared += val;
    mine[xpos][ypos].first = 0;
}


void clearTNT(int xpos, int ypos, vector< vector< pair<int, bool> > > &mine, Game &game) {
    //cerr << xpos << ' ' << ypos << endl;
    if(game.stats) {
	vector<int> tempv;
	tempv.reserve(3);
	tempv.push_back((int)xpos);
	tempv.push_back((int)ypos);
	tempv.push_back(-1);
	game.chron.push_back(tempv);
    }
    mine[xpos][ypos].first = 0;
    mine[xpos][ypos].second = false;
    if(xpos > 0 && mine[xpos-1][ypos].first != 0) {
	game.TNTpq->push(space(xpos-1,ypos,&(mine[xpos-1][ypos].first)));
    }
    if(xpos < (int)mine.size() - 1 && mine[xpos+1][ypos].first != 0) {
	game.TNTpq->push(space(xpos+1,ypos,&(mine[xpos+1][ypos].first)));
    }
    if(ypos > 0 && mine[xpos][ypos-1].first != 0) {
	game.TNTpq->push(space(xpos,ypos-1,&(mine[xpos][ypos-1].first)));
    }
    if(ypos < (int)mine.size() - 1 && mine[xpos][ypos+1].first != 0)
	game.TNTpq->push(space(xpos,ypos+1,&(mine[xpos][ypos+1].first)));
    while(game.TNTpq->size() > 0) {
	//cerr << "size of PQ " << game.TNTpq->size() << endl;
	xpos = game.TNTpq->top().x;
	ypos = game.TNTpq->top().y;
	game.TNTpq->pop();
	//cerr << xpos << ' ' << ypos << endl;
	if(mine[xpos][ypos].first == -1) {
	    clearTNT(xpos, ypos, mine, game);
	}
	else {
	    clear(xpos, ypos, mine, game);
	}
    }
}


int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    cout << std::fixed << std::setprecision(2);
    int idx = 0;
    int c;
    bool stats = false;
    bool median  = false;
    char pqtype = 'm';
    size_t n = 0;
    string start;
    string stop;
    while ((c = getopt_long(argc, argv, "hc:s:m", longopts, &idx)) != -1)
    {
	switch(c)
	{
	case 0:
	    break;
	case 's':
	    stats = true;
	    n = (size_t)atoi(optarg);
	    break;
	case 'm':
	    median = true;
	    break;
	case 'h':
	    cout << "HELP\n";
	    exit(0);
	case 'c':
	    string temp(optarg);
	    if(temp.compare("BINARY") == 0)
		pqtype = 'b';
	    else if (temp.compare("SORTED") == 0)
		pqtype = 's';
	    else if (temp.compare("POOR_MAN") == 0)
		pqtype = 'm';
	    else if (temp.compare("PAIRING") == 0)
		pqtype = 'p';
	    break;
	}
    }
    string junk;
    char imode;
    cin >> imode;
    if(imode != 'M' && imode != 'R')
	exit(1);
    int minesize;
    cin >> junk;
    cin >> minesize;
    if(minesize <= 0)
	exit(1);
    int xstart, ystart;
    cin >> junk;
    cin >> xstart;
    cin >> ystart;
    if(xstart < 0 || xstart >=minesize || ystart < 0 || ystart >= minesize)
	exit(1);
    vector< vector< pair<int, bool> > > mine;
    stringstream ss;
    if (imode == 'R') {
	int seed;
	cin >> junk;
	cin >> seed;
	int max_rubble;
	cin >> junk;
	cin >> max_rubble;
	int tnt_chance;
	cin >> junk;
	cin >> tnt_chance;
	P2::PR_init(ss, seed, minesize, max_rubble, tnt_chance);
    } // if
    // If map mode is on, read from cin; otherwise read from stringstream
    istream &iss = (imode == 'M') ? cin : ss;
    
    Game game(stats, median, pqtype);
    mine.resize(minesize);
    for(int i = 0; i < minesize; ++i)
	mine[i].reserve(minesize);
    for(int i = 0; i < minesize; ++i) {
	for (int j = 0; j < minesize; ++j) {
	    int temp;
	    iss >> temp;
	    mine[i].push_back(pair<int, bool> (temp, false));
	}
    }
    //int* int_ptr = &(mine[xstart][ystart].first);
    //cerr << int_ptr << ' ' << *int_ptr << '\n';
    space stsp(xstart, ystart,  &(mine[xstart][ystart].first));
    //cerr  << stsp.val << ' ' << *(stsp.val) << '\n';
    Eecs281PQ<space, Comp>* pq;
    switch(pqtype) {
	case 'p':
	    pq = new PairingPQ<space, Comp>;
	    cout << "Using PAIRING priority queue.\n";
	    break;
	case 'b':
	    pq = new BinaryPQ<space, Comp>;
	    cout << "Using BINARY priority queue.\n";
	    break;
        case 's':
	    pq = new SortedPQ<space, Comp>;
	    cout << "Using SORTED priority queue.\n";
	    break;
        default:
	    pq = new PoorManPQ<space, Comp>;
	    cout << "Using POORMAN priority queue.\n";
	    break;
	}
    pq->push(stsp);
    mine[xstart][ystart].second = true;
    while(true) {
	int xpos = pq->top().x;
	int ypos = pq->top().y;
	int val = *pq->top().val;
	pq->pop();
	if(val == -1) {
	    clearTNT(xpos, ypos, mine, game);
	    pq->updatePriorities();
	}
	else
	    clear(xpos, ypos, mine, game);
	if(xpos == 0 || ypos == 0 || xpos == minesize - 1 || ypos == minesize -1) {
	    break;
	}
	if(!mine[xpos-1][ypos].second) {
	    //cerr << &(mine[xpos-1][ypos].first) << ' ' << mine[xpos-1][ypos].first << '\n';
	    pq->push(space(xpos-1, ypos, &(mine[xpos-1][ypos].first)));
	    mine[xpos-1][ypos].second = true;
	}
	if(!mine[xpos+1][ypos].second) {
	    //cerr << &(mine[xpos+1][ypos].first) << ' ' << mine[xpos+1][ypos].first << '\n';
	    pq->push(space(xpos+1, ypos, &(mine[xpos+1][ypos].first)));
	    mine[xpos+1][ypos].second = true;
	}
	if(!mine[xpos][ypos-1].second) {
	    //cerr << &(mine[xpos][ypos-1].first) << ' ' << mine[xpos][ypos-1].first << '\n';
	    pq->push(space(xpos, ypos-1, &(mine[xpos][ypos-1].first)));
	    mine[xpos][ypos-1].second = true;
	}
	if(!mine[xpos][ypos+1].second) {
	    //cerr << &(mine[xpos][ypos+1].first) << ' ' << mine[xpos][ypos+1].first << '\n';
	    pq->push(space(xpos, ypos+1, &(mine[xpos][ypos+1].first)));
	    mine[xpos][ypos+1].second = true;
	}
    }
    cout << "Cleared " << game.numcleared << " tiles containing " << game.diffcleared << " rubble and escaped.\n";
    if(game.stats) {
	cout << "First tiles cleared:\n";
	for(size_t i = 0; i < min(n,game.chron.size()); ++i) {
	    if(game.chron[i][2] == -1)
		cout << "TNT at [" << game.chron[i][0] << ',' << game.chron[i][1] << "]\n";
	    else
		cout << game.chron[i][2] << " at [" << game.chron[i][0] << ',' << game.chron[i][1] << "]\n";
	}
	cout << "Last tiles cleared:\n";
	for(size_t i = game.chron.size() - 1; (int)i >= max((int)game.chron.size() - (int)n, 0); --i) {
	    if(game.chron[i][2] == -1)
		cout << "TNT at [" << game.chron[i][0] << ',' << game.chron[i][1] << "]\n";
	    else
		cout << game.chron[i][2] << " at [" << game.chron[i][0] << ',' << game.chron[i][1] << "]\n";
	}
    
	cout << "Easiest tiles cleared:\n";
	Hcomp hcomp;
	sort(game.chron.begin(), game.chron.end(), hcomp);
	for(size_t i = 0; i < min(n, game.chron.size()); ++i) {
	    if(game.chron[i][2] == -1)
		cout << "TNT at [" << game.chron[i][0] << ',' << game.chron[i][1] << "]\n";
	    else
		cout << game.chron[i][2] << " at [" << game.chron[i][0] << ',' << game.chron[i][1] << "]\n";
	}
	cout << "Hardest tiles cleared:\n";
	for(size_t i = game.chron.size() - 1; (int)i >= max((int)game.chron.size() - (int)n, 0); --i) {
	    if(game.chron[i][2] == -1)
		cout << "TNT at [" << game.chron[i][0] << ',' << game.chron[i][1] << "]\n";
	    else
		cout << game.chron[i][2] << " at [" << game.chron[i][0] << ',' << game.chron[i][1] << "]\n";
	}
    }
    delete pq;
}
