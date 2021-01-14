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
#include "TableType.h"

using namespace std;
using std::cin; // put under the other using s
using std::cout; // put under the other using s
using std::boolalpha; // put under the other using s

enum DataType {Int, Double, Bool, String};

struct Database {
    unordered_map<string, int> tablenames;
    vector< vector< vector<TableType> > > data;
    vector< vector< map<TableType, vector<int> > > > BSTs;
    vector< vector< unordered_map <TableType, vector<int> > > > hashes;
    vector< unordered_map<string, int> > colnames;
    vector< vector<bool> > BSTexist;
    vector< vector<bool> > hashexist;
    vector< vector<DataType> > coltypes;
    bool quiet;
};

void create(Database &db) {
    string tablename;
    cin >> tablename;
    int n;
    cin >> n;
    vector<string> coltype;
    for(int i = 0; i < n; ++i) {
	string tstr;
	cin >> tstr;
	coltype.push_back(tstr);
    }
    vector<string> colname;
    for(int i = 0; i < n; ++i) {
	string tstr;
	cin >> tstr;
	colname.push_back(tstr);
    }
    if(db.tablenames.count(tablename)){
	cout << "Error: Cannot create already existing table " << tablename << '\n';
	return;
    }
    db.tablenames[tablename] = (int) db.data.size();
    vector< vector<TableType> > temp;
    db.data.push_back(temp);
    vector< map<TableType, vector<int> > > temp2;
    db.BSTs.push_back(temp2);
    db.BSTs.back().resize(n);
    vector<bool> temp3;
    db.BSTexist.push_back(temp3);
    db.BSTexist.back().reserve(n);
    for(int i = 0; i < n; ++i) {
	db.BSTexist.back().push_back(false);
    }
    vector< unordered_map<TableType, vector<int> > > temp4;
    db.hashes.push_back(temp4);
    db.hashes.back().resize(n);
    vector<bool> temp5;
    db.hashexist.push_back(temp5);
    db.hashexist.back().reserve(n);
    for(int i = 0; i < n; ++i) {
	db.hashexist.back().push_back(false);
    }
    unordered_map<string, int> temp6; 
    db.colnames.push_back(temp6);
    for(int i = 0; i < n; ++i) {
	db.colnames.back()[colname[i]] = i;
    }
    vector<DataType> temp7;
    db.coltypes.push_back(temp7);
    for(int i = 0; i < n; ++i) {
	DataType dtype1 = String;
	DataType dtype2 = Int;
	DataType dtype3 = Double;
	DataType dtype4 = Bool;
	switch(coltype[i][0]) {
	case 's':
	    db.coltypes.back().push_back(dtype1);
	    break;
	case 'i':
	    db.coltypes.back().push_back(dtype2);
	    break;
    	case 'd':
	    db.coltypes.back().push_back(dtype3);
	    break;
	case 'b':
	    db.coltypes.back().push_back(dtype4);
	    break;
	}
    }
    cout << "New table " << tablename << " with column(s) ";
    for(int i  = 0; i < n; ++i)
	cout << colname[i] << ' ';
    cout << "created\n";
}

void insertInto(Database &db) {
    string tablename;
    cin >> tablename;
    int entries;
    cin >> entries;
    string junk;
    cin >> junk;
    if(db.tablenames.count(tablename) == 0){
	cout << "Error: " << tablename << " does not name a table in the database\n";
	getline(cin, junk);
	for(int i  = 0; i < entries; ++i) {
	    getline(cin, junk);
	}
	return;
    }
    int table = db.tablenames[tablename];
    int ncols = (int) db.coltypes[table].size();
    int size_init = (int) db.data[table].size();
    for(int i  = 0; i < entries; ++i) {
	vector<TableType> tempv;
	for(int j = 0; j < ncols; ++j) {
	    if(db.coltypes[table][j] == Int) {
		//cout << "reading in an int\n";
		int temp;
		cin >> temp;
		tempv.push_back(TableType(temp));
	    }
	    else if(db.coltypes[table][j] == Double) {
		//cout << "reading in a double\n";
		double temp;
		cin >> temp;
		tempv.push_back(TableType(temp));
	    }
	    else if(db.coltypes[table][j] == String) {
		//cout << "reading in a string\n";
		string temp;
		cin >> temp;
		//cout << "done reading in " << temp << '\n';
		tempv.push_back(TableType(temp));
	    }
	    else if(db.coltypes[table][j] == Bool) {
		//cout << "reading in a bool\n";
		bool temp;
		cin >> temp;
		//cout << "done reading in" << temp << '\n';
		tempv.push_back(TableType(temp));
	    }
	}
	for (int j = 0; j < (int) db.coltypes[table].size(); ++j) {
	    if(db.hashexist[table][j])
		db.hashes[table][j][tempv[j]].push_back((int) db.data[table].size());
	    if(db.BSTexist[table][j]) {
		if(db.BSTs[table][j].count(tempv[j]) == 0) {
		    vector<int> temp;
		    temp.push_back((int) db.data[table].size());
		    db.BSTs[table][j][tempv[j]] = temp;
		}
		else
		    db.BSTs[table][j][tempv[j]].push_back((int) db.data[table].size());
	    }
	}
	db.data[table].push_back(tempv);
    }
    int size_fin = (int) db.data[table].size();
    cout << "Added " << size_fin - size_init << " rows to " << tablename;
    cout << " from position " << size_init << " to " << size_fin - 1 << '\n'; 
}

void fixindex(Database &db, int table, int row) {
    vector<TableType> vtt;
    for(int i = 0; i < (int) db.coltypes[table].size(); ++i)
	vtt.push_back(db.data[table][row][i]);
    for(int i = 0; i < (int) db.coltypes[table].size(); ++i) {
	if(db.hashexist[table][i]) {
	    if(db.hashes[table][i][vtt[i]].size() > 1) {
		for(int j = 0; j < (int) db.hashes[table][i][vtt[i]].size(); ++j) {
		    if(db.hashes[table][i][vtt[i]][j] == row) {
			db.hashes[table][i][vtt[i]].erase(db.hashes[table][i][vtt[i]].begin() + j);
			break;
		    }
		}
	    }
	    else
		db.hashes[table][i].erase(vtt[i]);
	}
	else if(db.BSTexist[table][i]) {
	    if(db.BSTs[table][i][vtt[i]].size() > 1) {
		for(int j = 0; j < (int) db.BSTs[table][i][vtt[i]].size(); ++j) {
		    if(db.BSTs[table][i][vtt[i]][j] == row) {
			db.BSTs[table][i][vtt[i]].erase(db.BSTs[table][i][vtt[i]].begin() + j);
			break;
		    }
		}
	    }
	    else
		db.BSTs[table][i].erase(vtt[i]);
	}
    }
}

void regdelete(Database &db, int table, int col, string op, TableType &value) {
    vector<int> todel;
    for(int i  = 0; i < (int) db.data[table].size(); ++i) {
	switch(op[0]) {
	case '=':
	    if(db.data[table][i][col] == value) {
		todel.push_back(i);
		fixindex(db, table, i);
		}
	     break;
	case '>':
	    if(db.data[table][i][col] > value){
		todel.push_back(i);
		fixindex(db, table, i);
	    }
	    break;
	case '<':
	    if(db.data[table][i][col] < value) {
		todel.push_back(i);
		fixindex(db, table, i);
	    }
	    break;
	}
    }
    for(int i  = 0; i < (int) todel.size(); ++i) {
	db.data[table].erase(db.data[table].begin()+todel[i]-i);
    }
    cout << "Deleted " << todel.size() << " rows from ";
     
}

/*void BSTdelete(Database &db, int table, int col, string op, TableType &value) {
    map<TableType, vector<int> >::iterator start, stop;
    vector<int> todel;
    if(op == ">") {
	start = db.BSTs[table][col].lower_bound(value);
	stop = db.BSTs[table][col].end();
	while(start != stop) {
	    vector<int> temp = start->second;
	    for(int i  = 0; i < (int) temp.size(); ++i) {
		todel.push_back(temp[i]);
	    }
	    ++start;
	}
    }
    else if(op == "<") {
	start = db.BSTs[table][col].begin();
	stop = db.BSTs[table][col].upper_bound(value);
	while(start != stop) {
	    vector<int> temp = start->second;
	    for(int i  = 0; i < (int) temp.size(); ++i) {
		todel.push_back(temp[i]);
	    }
	    ++start;
	}
    }
    for(int i  = 0; i < (int) todel.size(); ++i) {
	db.data[table].erase(db.data[table].begin()+todel[i]);
	fixindex(db, table, todel[i]);
    }
    }*/

void hashdelete(Database &db, int table, int col, TableType &value) {
    vector<int> todel = db.hashes[table][col][value];
    for(int i  = 0; i < (int) todel.size(); ++i) {
	db.data[table].erase(db.data[table].begin()+todel[i]-i);
	fixindex(db, table, todel[i]);
    }
    cout << "Deleted " << todel.size() << " rows from ";   
}

void deleteInt(Database &db, int table, int col, string op) {
    int temp;
    cin >> temp;
    TableType tt(temp);
    if(db.hashexist[table][col] && op == "=")
	hashdelete(db, table, col, tt);
    else if(db.BSTexist[table][col] && op != "=")
	regdelete(db, table, col, op, tt);
    else
	regdelete(db, table, col, op, tt);
}

void deleteDouble(Database &db, int table, int col, string op) {
    double temp;
    cin >> temp;
    TableType tt(temp);
    if(db.hashexist[table][col] && op == "=")
	hashdelete(db, table, col, tt);
    else if(db.BSTexist[table][col] && op != "=")
	regdelete(db, table, col, op, tt);
    else
	regdelete(db, table, col, op, tt);
}

void deleteString(Database &db, int table, int col, string op) {
    string temp;
    cin >> temp;
    TableType tt(temp);
    if(db.hashexist[table][col] && op == "=")
	hashdelete(db, table, col, tt);
    else if(db.BSTexist[table][col] && op != "=")
	regdelete(db, table, col, op, tt);
    else
	regdelete(db, table, col, op, tt);
}

void deleteBool(Database &db, int table, int col, string op) {
    bool temp;
    cin >> temp;
    TableType tt(temp);
    if(db.hashexist[table][col] && op == "=")
	hashdelete(db, table, col, tt);
    else if(db.BSTexist[table][col] && op != "=")
	regdelete(db, table, col, op, tt);
    else
	regdelete(db, table, col, op, tt);
}


void deleteFrom(Database &db) {
    string tablename;
    cin >> tablename;
    string junk;
    cin >> junk;
    string colname;
    cin >> colname;
    string op;
    cin >> op;
    if(db.tablenames.count(tablename) == 0){
	cout << "Error: " << tablename << " does not name a table in the database\n";
	getline(cin, junk);
	return;
    }
    int table = db.tablenames[tablename];
    if(db.colnames[table].count(colname) == 0){
	cout << "Error: " << colname << " does not name a column in " << tablename << "\n";
	getline(cin, junk);
	return;
    }
    int col = db.colnames[table][colname];
    DataType type = db.coltypes[table][col];
    switch(type) {
    case Bool:
	deleteBool(db, table, col, op);
	break;
    case Int:
	deleteInt(db, table, col, op);
	break;
    case Double:
	deleteDouble(db, table, col, op);
	break;
    case String:
	deleteString(db, table, col, op);
	break;
    }
    cout << tablename << '\n';
}



void generateIndex(Database &db) {
    string tablename;
    cin >> tablename;
    string indextype;
    cin >> indextype;
    string junk;
    cin >> junk;
    cin >> junk;
    string colname;
    cin >> colname;
    if(db.tablenames.count(tablename) == 0){
	cout << "Error: " << tablename << " does not name a table in the database\n";
	getline(cin, junk);
	return;
    }
    int table = db.tablenames[tablename];
    if(db.colnames[table].count(colname) == 0){
	cout << "Error: " << colname << " does not name a column in " << tablename << "\n";
	getline(cin, junk);
	return;
    }
    int col = db.colnames[table][colname];
    if(indextype == "hash") {
	for(int i = 0; i  < (int) db.data[table].size(); ++i) {
	    db.hashes[table][col][db.data[table][i][col]].push_back(i);
	}
	db.BSTexist[table][col] = false;
	db.hashexist[table][col] = true;
    }
    else if(indextype == "bst") {
	for(int i = 0; i < (int) db.data[table].size(); ++i) {
	    if(db.BSTs[table][col].count(db.data[table][i][col]) == 0) {
		vector<int> temp;
		temp.push_back(i);
		db.BSTs[table][col][db.data[table][i][col]] = temp;
	    }
	    else {
		db.BSTs[table][col][db.data[table][i][col]].push_back(i);
	    }
	}
	db.BSTexist[table][col] = true;
	db.hashexist[table][col] = false;
    }
    cout << "Created " << indextype << " index for table " << tablename << " on column " << colname << '\n';
}

void hashprint(Database &db, int table, int col, vector<int> pcols, TableType &value) {
    vector<int> toprint = db.hashes[table][col][value];
    if(!db.quiet) {
	for(int i  = 0; i < (int) toprint.size(); ++i) {
	    for(int j  = 0; j < (int) pcols.size(); ++j)
		cout << db.data[table][toprint[i]][pcols[j]] << " ";
	    cout << '\n';
	}
    }
    cout << "Printed " << toprint.size() << " matching rows from ";
}

void BSTprint(Database &db, int table, int col, string op, vector<int> pcols, TableType &value) {
    map<TableType, vector<int> >::iterator start, stop;
    vector<int> toprint;
    if(op == ">") {
	start = db.BSTs[table][col].lower_bound(value);
	stop = db.BSTs[table][col].end();
    }
    else if(op == "<") {
	start = db.BSTs[table][col].begin();
	stop = db.BSTs[table][col].upper_bound(value);
    }
    while(start != stop) {
	vector<int> temp = start->second;
	for(int i  = 0; i < (int) temp.size(); ++i) {
	    toprint.push_back(temp[i]);
	}
	++start;
    }
    if(!db.quiet) {
	for(int i  = 0; i < (int) toprint.size(); ++i) {
	    for(int j  = 0; j < (int) pcols.size(); ++j)
		cout << db.data[table][toprint[i]][pcols[j]] << " ";
	    cout << '\n';
	}
    }
    cout << "Printed " << toprint.size() << " matching rows from ";
}

void regprint(Database &db, int table, int col, string op, vector<int> pcols, TableType &value) {
    vector<int> toprint;
    for(int i  = 0; i < (int) db.data[table].size(); ++i) {
	switch(op[0]) {
	case '=':
	    if(db.data[table][i][col] == value) {
		toprint.push_back(i);
	    }
	    break;
	case '>':
	    if(db.data[table][i][col] > value){
		toprint.push_back(i);
	    }
	    break;
	case '<':
	    if(db.data[table][i][col] < value) {
		toprint.push_back(i);
	    }
	    break;
	}
    }
    if(!db.quiet) {
	for(int i  = 0; i < (int) toprint.size(); ++i) {
	    for(int j  = 0; j < (int) pcols.size(); ++j)
		cout << db.data[table][toprint[i]][pcols[j]] << " ";
	    cout << '\n';
	}
    }
    cout << "Printed " << toprint.size() << " matching rows from ";
}

void printInt(Database &db, int table, int col, vector<int> pcols, string op) {
    int temp;
    cin >> temp;
    TableType tt(temp);
    if(db.hashexist[table][col] && op == "=")
	hashprint(db, table, col, pcols, tt);
    else if(db.BSTexist[table][col] && op != "=")
	BSTprint(db, table, col, op, pcols, tt);
    else
	regprint(db, table, col, op, pcols, tt);
}

void printDouble(Database &db, int table, int col, vector<int> pcols, string op) {
    double temp;
    cin >> temp;
    TableType tt(temp);
    if(db.hashexist[table][col] && op == "=")
	hashprint(db, table, col, pcols, tt);
    else if(db.BSTexist[table][col] && op != "=")
	BSTprint(db, table, col, op, pcols, tt);
    else
	regprint(db, table, col, op, pcols, tt);
}

void printString(Database &db, int table, int col, vector<int> pcols, string op) {
    string temp;
    cin >> temp;
    TableType tt(temp);
    if(db.hashexist[table][col] && op == "=")
	hashprint(db, table, col, pcols, tt);
    else if(db.BSTexist[table][col] && op != "=")
	BSTprint(db, table, col, op, pcols, tt);
    else
	regprint(db, table, col, op, pcols, tt);
}

void printBool(Database &db, int table, int col, vector<int> pcols, string op) {
    bool temp;
    cin >> temp;
    TableType tt(temp);
    if(db.hashexist[table][col] && op == "=")
	hashprint(db, table, col, pcols, tt);
    else if(db.BSTexist[table][col] && op != "=")
	BSTprint(db, table, col, op, pcols, tt);
    else
	regprint(db, table, col, op, pcols, tt);
}

void printAll(Database &db, int table, vector<int> pcols) {
    if(!db.quiet) {
	for(int i  = 0; i < (int) db.data[table].size(); ++i) {
	    for(int j  = 0; j < (int) pcols.size(); ++j)
		cout << db.data[table][i][pcols[j]] << " ";
	    cout << '\n';
	}
    }
    cout << "Printed " << db.data[table].size() << " matching rows from ";
}
void printFrom(Database &db) {
    string tablename;
    cin >> tablename;
    string junk;
    if(db.tablenames.count(tablename) == 0){
	cout << "Error: " << tablename << " does not name a table in the database\n";
	getline(cin, junk);
	return;
    }
    int table = db.tablenames[tablename];
    int ncols;
    cin >> ncols;
    vector<string> pcoln;
    for(int i = 0; i < ncols; ++i) {
	string temp;
	cin >> temp;
	pcoln.push_back(temp);
    }
    vector<int> pcols;
    for(int i = 0; i < ncols; ++i) {
	pcols.push_back(db.colnames[table][pcoln[i]]);
	if(!db.quiet)
	    cout << pcoln[i] << ' ';
    }
    if(!db.quiet)
	cout << '\n';
    cin >> junk;
    if(junk == "ALL") {
	printAll(db, table, pcols);
	cout << tablename << '\n';
	return;
    }
    string colname;
    cin >> colname;
    string op;
    cin >> op;
    if(db.colnames[table].count(colname) == 0){
	cout << "Error: " << colname << " does not name a column in " << tablename << "\n";
	getline(cin, junk);
	return;
    }
    int col = db.colnames[table][colname];
    DataType type = db.coltypes[table][col];
    switch(type) {
    case Bool:
	printBool(db, table, col, pcols, op);
	break;
    case Int:
	printInt(db, table, col, pcols, op);
	break;
    case Double:
	printDouble(db, table, col, pcols, op);
	break;
    case String:
	printString(db, table, col, pcols, op);
	break;
    }
    cout << tablename << '\n';
}

void remove(Database &db) {
    string tablename;
    cin >> tablename;
    string junk;
    if(db.tablenames.count(tablename) == 0){
	cout << "Error: " << tablename << " does not name a table in the database\n";
	getline(cin, junk);
	return;
    }
    cout << "Table " << tablename << " deleted\n";
}

void join(Database &db) {
    string tablename1;
    cin >> tablename1;
    string junk;
    cin >> junk;
    string tablename2;
    cin >> tablename2;
    cin >> junk;
    string colname1;
    cin >> colname1;
    cin >> junk;
    string colname2;
    cin >> colname2;
    cin >> junk;
    cin >> junk;
    int n;
    cin >> n;
    vector<string> pcolnames;
    vector<int> ptables;
    for(int i  = 0; i < n; ++i) {
	string temp;
	cin >> temp;
	int temp2;
	cin >> temp2;
	pcolnames.push_back(temp);
	ptables.push_back(temp2);
    }
    if(db.tablenames.count(tablename1) == 0){
	cout << "Error: " << tablename1 << " does not name a table in the database\n";
	getline(cin, junk);
	return;
    }
    int table1 = db.tablenames[tablename1];
    if(db.colnames[table1].count(colname1) == 0){
	cout << "Error: " << colname1 << " does not name a column in " << tablename1 << "\n";
	getline(cin, junk);
	return;
    }
    int col1 = db.colnames[table1][colname1];
    if(db.tablenames.count(tablename2) == 0){
	cout << "Error: " << tablename2 << " does not name a table in the database\n";
	getline(cin, junk);
	return;
    }
    int table2 = db.tablenames[tablename2];
    if(db.colnames[table2].count(colname2) == 0){
	cout << "Error: " << colname2 << " does not name a column in " << tablename2 << "\n";
	getline(cin, junk);
	return;
    }
    int col2 = db.colnames[table2][colname2];
    vector<int> pcols;
    for(int i  = 0; i < (int) pcolnames.size(); ++i) {
	if(ptables[i] == 1) {
	    if(db.colnames[table1].count(pcolnames[i]) == 0){
		cout << "Error: " << pcolnames[i] << " does not name a column in " << tablename1 << "\n";
		getline(cin, junk);
		return;
	    }
	    pcols.push_back(db.colnames[table1][pcolnames[i]]);
	}
	else {
	    if(db.colnames[table2].count(pcolnames[i]) == 0){
		cout << "Error: " << pcolnames[i] << " does not name a column in " << tablename2 << "\n";
		getline(cin, junk);
		return;
	    }
	    pcols.push_back(db.colnames[table2][pcolnames[i]]);
	}
	if(!db.quiet)
	    cout << pcolnames[i] << ' ';
    }
    if(!db.quiet)
	cout << '\n';
    if(db.hashexist[table2][col2] == false) {
	db.hashes[table2][col2].erase(db.hashes[table2][col2].begin(), db.hashes[table2][col2].end());
	for(int i = 0; i  < (int) db.data[table2].size(); ++i) {
	    db.hashes[table2][col2][db.data[table2][i][col2]].push_back(i);
	}
    }
    size_t count = 0;
    for(int i = 0; i < (int) db.data[table1].size(); ++i) {
	vector<int> res = db.hashes[table2][col2][db.data[table1][i][col1]];
	count += res.size();
	if(!db.quiet) {
	    for(int j  = 0; j < (int) res.size(); ++ j) {
		for(int k  = 0; k < n; ++k) {
		    if(ptables[k] == 1) 
			cout << db.data[table1][i][pcols[k]] << ' ';
		    else
			cout << db.data[table2][res[j]][pcols[k]] << ' ';
		}
		cout << '\n';
	    }					  
	}
    }
    cout << "Printed " << count <<  " rows from joining " << tablename1 << " to " << tablename2 << '\n';
}
	       
int main(int argv, char** argc) {
    Database db;
    db.quiet = false;
    for(int i = 0; i < argv; ++i){
	if(argc[i][1] == 'q')
	    db.quiet = true;
	if(argc[i][1] == '-' && argc[i][2] == 'q')
	    db.quiet = true;
	if(argc[i][1] == 'h')
	    exit(0);
	if(argc[i][1] == '-' && argc[i][2] == 'h')
	    exit(0);
    }
    cin >> boolalpha;
    cout << boolalpha;
    while(true) {
	string command;
	string junk;
	cout << "% ";
	cin >> command;
	switch(command[0]) {
	case 'C':
	    create(db);
	    break;
	case 'I':
	    cin >> junk;
	    insertInto(db);
	    break;
	case 'D':
	    cin >> junk;
	    deleteFrom(db);
	    break;
	case 'G':
	    cin >> junk;
	    generateIndex(db);
	    break;
	case 'R':
	    remove(db);
	    break;
	case 'P':
	    cin >> junk;
	    printFrom(db);
	    break;
	case 'Q':
	    cout << "Thanks for being silly!\n";
	    exit(0);
	    break;
	case 'J':
	    join(db);
	case '#':
	    getline(cin, junk);
	    break;
	default:
	    cout << "Error: unrecoginzed command\n";
	    cout << command[0] << endl;
	    getline(cin, junk);
	    break;
	}
    }
}
