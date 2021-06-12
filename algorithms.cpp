#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include <algorithm>

#include "algorithms.h"

using namespace std;

string completeURL (string storeName, string initialURL) {
	string finalURL = "www." + storeName + ".com.br" + initialURL;

	return finalURL;
}

void strToConstCharList (string incoming, char* &output) {

	strcpy (output, incoming.c_str());
}

float strToFloat (string incoming) {

	incoming.erase (remove(incoming.begin(), incoming.end(), '.'), incoming.end());

	incoming.replace (incoming.find(","), 1, ".");

	return stof (incoming);
}

vector<string> constCharToVectorStr (const char* incoming) {
	vector <string> result;

	string current = incoming;

	int which = 0;

	int nameStart, nameEnd, priceStart, priceEnd;
	int linkStart, linkEnd, storeStart, storeEnd;

	for (size_t index = 0; which < 8 && index < current.size(); index++) {
		if (current[index] == '\'') {
			if (which == 0) {
				nameStart = index;
			} else if (which == 1) {
				nameEnd = index;
			} else if (which == 2) {
				priceStart = index;
			} else if (which == 3) {
				priceEnd = index;
			} else if (which == 4) {
				linkStart = index;
			} else if (which == 5) {
				linkEnd = index;
			} else if (which == 6) {
				storeStart = index;
			} else if (which == 7) {
				storeEnd = index;
			}

			which++;
		}
	}

	string name = current.substr (nameStart + 1, nameEnd - nameStart - 1);
	string price = current.substr (priceStart + 1, priceEnd - priceStart - 1);
	string link = current.substr (linkStart + 1, linkEnd - linkStart - 1);
	string store = current.substr (storeStart + 1, storeEnd - storeStart - 1);

	result.push_back(name);
	result.push_back(price);
	result.push_back(link);
	result.push_back(store);
	return result;
}

int checkEmptySpaces (string incoming) {
	bool notEmpty = false;

	size_t index = 0;

	if (incoming == "") {
		return -1;
	} else if (incoming[0] != ' ') {
		cout << "Aqui" << endl;
		notEmpty = true;
	}
	
	while (index < (incoming.size() - 1) && incoming[index] == ' ') {
		if (incoming[index + 1] != ' ') {
			cout << "Char: " << incoming[index + 1] << endl;
			notEmpty = true;
		}
		index ++;
	}

	if (notEmpty == false) {
		index = -1;
	} else {
		cout << "Index: " << index << endl;
		cout << "Char: " << incoming[index] << endl;
	}

	return index;
}
