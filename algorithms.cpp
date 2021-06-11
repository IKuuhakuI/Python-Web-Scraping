#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<string> strToVector (const char* incoming) {
	vector <string> result;

	string current = incoming;

	int which = 0;

	int nameStart, nameEnd, priceStart, priceEnd;

	for (size_t index = 0; which < 4 && index < current.size(); index++) {
		if (current[index] == '\'') {
			if (which == 0) {
				nameStart = index;
			} else if (which == 1) {
				nameEnd = index;
			} else if (which == 2) {
				priceStart = index;
			} else {
				priceEnd = index;
			}

			which++;
		}
	}

	string name = current.substr (nameStart + 1, nameEnd - nameStart - 1);
	string price = current.substr (priceStart + 1, priceEnd - priceStart - 1);

	result.push_back(name);
	result.push_back(price);
	return result;
}
