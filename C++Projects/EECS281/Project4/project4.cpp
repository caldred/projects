#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iostream>
#include <map>
#include <utility>
#include <string>
#include <cassert>
#include <unordered_map>
#include <cctype>
#include <numeric>
#include <fstream>
#include <sstream>
#include <deque>
#include <iomanip>

using namespace std;

struct vertex {
    int x;
    int y;
    bool diff;
    bool v;
    double d;
    int p;
    vertex(int x_in, int y_in, bool diff_in) : 
	x(x_in), y(y_in), diff(diff_in), v(false), d(numeric_limits<double>::infinity())
    {}
};

void camp_input(vector< pair<double, int> > &states, double &budget) {
    string junk;
    cin >> junk;
    cin >> junk;
    cin >> junk;
    cin >> junk;
    int n;
    cin >> n;
    if(n < 0)
	exit(1);
    cin >> junk;
    cin >> junk;
    cin >> junk;
    cin.ignore(256,'$');
    cin >> budget;
    for (int i  = 0; i < n; ++i) {
	cin.ignore(256,'$');
	double cost;
	cin >> cost;
	if (cost <= 0)
	    exit(1);
	int value;
	cin >> value;
	if (value < 0)
	    exit(1);
	pair<double, int> temp (cost, value);
	states.push_back(temp);
    }
}

void mst_input(vector<vertex> &coords, double &dfac) {
    string junk;
    cin >> junk >> junk >> junk >> junk;
    int n;
    cin >> n;
    if(n <= 0)
	exit(1);
    for(int i = 0; i < n; ++i) {
	int x;
	cin >> x;
	int y;
	cin >> y;
	vertex temp(x,y, false);
	coords.push_back(temp);
    }
    cin >> junk >> junk >> junk;
    int m;
    cin >> m;
    if(m < 0)
	exit(1);
    cin >> junk >> junk;
    cin >> dfac;
    if(dfac <=0)
	exit(1);
    for(int i  = 0; i < m; ++i) {
	int temp;
	cin >> temp;
	if(temp < 0 || temp >= n)
	    exit(1);
	coords[temp].diff = true;;
    }
}

void tsp_input(vector< pair<int, int> > &v, vector<int> &luum) {
    string junk;
    cin >> junk >> junk >> junk >> junk;
    int n;
    cin >> n;
    if(n < 0)
	exit(1);
    for(int i = 0; i < n; ++i) {
	int x;
	cin >> x;
	int y;
	cin >> y;
	pair<int, int> temp(x,y);
	v.push_back(temp);
    }
    cin >> junk >> junk >> junk;
    for(int i = 0; i < n; ++i) {
	int x;
	cin >> x;
	if(x < 0  || x >= n)
	    exit(1);
	luum.push_back(x);
    }
    vector<int> copy = luum;
    sort(copy.begin(), copy.end());
    for(int i  = 0; i < (int) copy.size(); ++i) {
	if(copy[i] != i)
	    exit(1);
    }
}

int greedy(vector< pair<double, int> > &states, double budget, vector<bool> &pack, vector<int> &rank) {
    int res = 0;
    int k = 0;
    while(k < (int) states.size()) {
	if(budget > states[rank[k]].first) {
	    budget -= states[rank[k]].first;	
	    res += states[rank[k]].second;
	    pack[k] = true;
	}
	++k;
    }
    return res;
}

int bigGreedy(vector< pair<double, int> > &states, double budget) {
    int res = 0;
    vector<bool> eligible (states.size(), true);
    while(true) {
	int biggest = 0;
	int bigi = -1;
	for(int i  = 0; i < (int) states.size(); ++i) {
	    if(eligible[i] && states[i].second > biggest) {
		biggest = states[i].second;
		bigi = i;
	    }
	}
	if(bigi == -1)
	    break;
	budget -= states[bigi].first;
	if(budget < 0)
	    break;
	eligible[bigi] = false;
	++res;
    }
    return res;
}

int smallGreedy(vector< pair<double, int> > &states, double budget) {
    int res = 0;
    vector<bool> eligible (states.size(), true);
    while(true) {
	double smallest = numeric_limits<double>::infinity();
	int smalli = -1;
	for(int i  = 0; i < (int) states.size(); ++i) {
	    if(eligible[i] && states[i].first < smallest) {
		smallest = states[i].first;
		smalli = i;
	    }
	}
	if(smalli == -1)
	    break;
	budget -= states[smalli].first;
	if(budget < 0)
	    break;
	eligible[smalli] = false;
	++res;
    }
    return res;
}
	

double greedy(vector< pair<double, int> > &states, int value, vector<int> &rank, int k) {
    double res = 0;
    while(k < (int) states.size()) {
	if(value > states[rank[k]].second) {
	    value -= states[rank[k]].second;	
	    res += states[rank[k]].first;
	}
	else {
	    res += states[rank[k]].first*value/states[rank[k]].second;
	    break;
	}
	++k;
    }
    return max(0.0, res);
}   

//	all_possible(states, budget, value, maxvalue, pack, maxpack, rank, leastitems);

void all_possible(vector< pair<double, int> > &states, double budget, int value, int &max_value, vector<bool> pack, vector<bool> &max_pack, vector<int> &rank, int k) {
    if(k == (int) states.size()) return;
    if(budget < 0) {
	//cout << k << '\n';
	return;
    }
    if(value < max_value && greedy(states, max_value-value, rank, k) > budget) {
	//cout << k << '\n';
	return;
    }
    if(value > max_value) {
	max_value = value;
	max_pack = pack;
    }
    pack[k] = false;
    ++k;
    all_possible(states, budget, value, max_value, pack, max_pack, rank, k);
    --k;
    pack[k] = true;
    budget -= states[rank[k]].first;
    value += states[rank[k]].second;
    ++k;
    all_possible(states, budget, value, max_value, pack, max_pack, rank, k);
}

int find_min_d(vector<vertex> &v) {
    double min = numeric_limits<double>::infinity();
    int res = (int) v.size();
    for(int i = 0; i < (int) v.size(); ++i) {
	if(!v[i].v && v[i].d < min) {
	    min = v[i].d;
	    res = i;
	}
    }
    return res;
}

double dist(vector<vertex> &v, int i, int j, double fac) {
    long double xd = v[i].x - v[j].x;
    long double yd = v[i].y - v[j].y;
    //xd = xd * xd;
    //yd = yd * yd;
    long double distance  = sqrt(xd*xd+yd*yd);
    if(v[i].diff) distance *= fac;
    if(v[j].diff) distance *= fac;
    return (double) distance;
}

void update_d(vector<vertex> &v, int i, double fac) {
    for(int j  = 0; j < (int)v.size(); ++j) {
	if(!v[j].v) {
	    double d = dist(v, i, j, fac);
	    if(d < v[j].d) {
		v[j].d = d;
		v[j].p = i;
	    }
	}	    
    }
}

double MST(vector<vertex> &v, double fac) {
    v[0].d = 0;
    double distance = 0;
    for(int i = 0; i < (int) v.size(); ++i) {
	int min_d = find_min_d(v);
	v[min_d].v = true;
	distance += v[min_d].d;
	update_d(v, min_d, fac);
	/*cout << "i\tv\td\tp\tdiff\n";
	for(int j = 0; j < (int) v.size(); ++j) {
	    cout << j << '\t' << v[j].v << '\t' << v[j].d << '\t' << v[j].p << '\t' << v[j].diff << '\n';
	    }*/
    }
    return distance;
}

void makeDM(vector< vector<double> > &DM, vector< pair<int, int> > &v) {
    DM.resize(v.size());
    for(int i = 0; i < (int) DM.size(); ++i) {
	DM[i].resize(v.size());
    }
    for(int i = 0; i < (int) v.size(); ++i) {
	for(int j  = 0; j < (int) v.size(); ++j) {
	    int dx = v[i].first - v[j].first;
	    int dy = v[i].second - v[j].second;
	    DM[i][j] = sqrt(dx*dx + dy*dy);
	}
    }
}

double TSPMST(vector< vector <double> > &DM, deque<int> &unused) {
    int size = (int) unused.size();
    vector<double> ds (size, numeric_limits<double>::infinity());
    vector<bool> vs (size, false);
    vector<int> ps (size, -1);
    double distance = 0;
    ds[0] = 0;
    for(int i = 0; i < size; ++i) {
	int inmin = size;
	double min = numeric_limits<double>::infinity();
	for(int j = 0; j < size; ++j) {
	    if(!vs[j] && ds[j] < min) {
		min = ds[j];
		inmin = j;
	    }
	}
	vs[inmin] = true;
	distance += min;
	//cout << "distance is " << distance << endl;
	for(int j  = 0; j < (int) size; ++j) {
	    if(!vs[j]) {
		double d = DM[unused[inmin]][unused[j]];
		if(d < ds[j]) {
		    ds[j] = d;
		    ps[j] = inmin;
		}
	    }	    
	}
    }
    return distance;
}

double connect(vector< vector<double> > &DM, deque<int> &unused, int last) {
    double minto0 = numeric_limits<double>::infinity();
    double mintolast = numeric_limits<double>::infinity();
    for(int i = 0; i < (int) unused.size(); ++i) {
	if(DM[0][unused[i]] < minto0)
	    minto0 = DM[0][unused[i]];
	if(DM[last][unused[i]] < mintolast)
	    mintolast = DM[last][unused[i]];
    }
    return minto0 + mintolast;
}

void TSP(vector< vector <double> > &DM, deque<int> &unused, vector<int> &path, double pathd, vector<int> &bestp, double &bestd) {
    if (unused.empty()) {
	pathd += DM[0][path.back()];
	//cout << pathd << '\n';
	if(pathd < bestd) {
	    //cout << "new best\n";
	    bestp = path;
	    bestd = pathd;
	}
	return;
    }
    /*for(auto i : path)
	cout << i << ' ';
    //cout << '\t' << pathd;
    cout << '\n';*/
    //double estleft = TSPMST(DM, unused);
    //estleft += connect(DM, unused, path.back());
    //cout << estleft << '\n';
    if(pathd + TSPMST(DM, unused) + connect(DM, unused, path.back()) >= bestd)
	return;
    int unsz = (int) unused.size();
    for (int k = 0; k != unsz; ++k) {
	double d = DM[unused.front()][path.back()];
	pathd += d;
	path.push_back(unused.front());
	unused.pop_front();
	TSP(DM, unused, path, pathd, bestp, bestd);
	unused.push_back(path.back());
	path.pop_back();
	pathd -= d;
    }
}
	    
int main(int argv, char** argc) {
    cout << setprecision(2); // Always show 2 decimal places
    cout << fixed; // Disable scientific notation for large numbers
    bool campaign = false;
    bool mst = false;
    bool tsp = false;
    if(argv > 1) {
	if(argc[2][0] == 'C')
	    campaign = true;
	else if(argc[2][0] == 'M')
	    mst = true;
	else if(argc[2][0] == 'P')
	    tsp = true;
    }
    if(campaign) {
	double budget = 0;
	vector <pair<double, int> > states;
	camp_input(states, budget);
	vector<bool> pack (states.size(), false);
	vector<bool> maxpack (states.size(), false);
	vector<double> ratios (states.size(), 0);
	vector<int> rank (states.size(), 0);
	for(int i = 0; i < (int) states.size(); ++i)
	    ratios[i] = (double) states[i].second/states[i].first;
	vector<bool> elg (states.size(), true);
	for(int i  = 0; i < (int) rank.size(); ++i) {
	    double bestr = 0;
	    int besti  = -1;
	    for(int j = 0; j < (int) ratios.size(); ++j) {
		if(elg[j] && ratios[j] > bestr) {
		    bestr = ratios[j];
		    besti = j;
		}
	    }
	    rank[i] = besti;
	    elg[besti] = false;
	}
	int maxvalue = greedy(states, budget, maxpack, rank);
	int leastitems = bigGreedy(states, budget);
	/*int mostitems = smallGreedy(states, budget);
	cout << "Max value: " << maxvalue << endl;
	cout << "least items: " << leastitems << endl;
	cout << "most items: " << mostitems << endl;*/
	int value = 0;
	for(int i = 0; i <  leastitems; ++i) {
 	    pack[i] = true;
	    value += states[rank[i]].second;
	    budget -= states[rank[i]].first;
	}
	all_possible(states, budget, value, maxvalue, pack, maxpack, rank, leastitems);
	cout << "Expected number of votes on Election day: ";
	cout << maxvalue << '\n';
	cout << "Senator Lukefahr should campaign in the following states:\n";
	vector<int> res;
	for(int i = 0; i < (int) maxpack.size(); ++i) {
	    if(maxpack[i])
		res.push_back(rank[i]); 
	}
	sort(res.begin(), res.end());
	for(auto i: res)
	    cout << i << '\n';
    }
    if(mst) {
	vector<vertex> v;
	double fac = 0;
	mst_input(v, fac);
	double distance = MST(v, fac);
	cout << "Total distance: " << distance << '\n';
	cout << "Trade routes:\n";
	for(int i = 1; i < (int) v.size(); ++i) {
	    if(i < v[i].p)
		cout << i << ' ' << v[i].p << '\n';
	    else
		cout << v[i].p << ' ' << i << '\n';
	}
    }
    if(tsp) {
	vector< pair<int, int> > v;
	vector<int> luum;
	tsp_input(v, luum);
	vector< vector<double> > DM;
	makeDM(DM, v);
	vector<int> path;
	path.push_back(0);
	deque<int> unused;
	for(int i = 1; i < (int) v.size(); ++i)
	    unused.push_back(i);
	double distance  = 0;
	for(int i = 1; i < (int) v.size(); ++i)
	    distance += DM[luum[i]][luum[i-1]];
	distance += DM[luum[0]][luum.back()];
	//cout << distance << '\n';
	TSP(DM, unused, path, 0, luum, distance);
	cout << "The total campaign length is: " << distance << "\n";
	cout << "Lukefahr should visit each state in the following order:\n";
	for(auto i: luum)
	    cout << i << '\n';
    }
    return 0;
}

