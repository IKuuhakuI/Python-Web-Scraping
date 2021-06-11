#include <vector>
#include <string>
#include <iostream>

#include "algorithms.h"
#include "scraping.h"

using namespace std;

int main (int argc, char* argv[]) {
	Py_Initialize ();

	string input = "Iphone 11";
	char test[input.length()];

	char *result = test;

 	strToConstCharList (input, result);

	if (result != NULL) {
		cout << result << endl;
	} else {
		cout << "erro" << endl;
	}

	vector <vector<string>> data = getAmazonData (result, 1000, 5000);

	float price; 	
	for (size_t i = 0; i < data.size(); i++) {
		price = strToFloat (data[i][1]);
		cout << data[i][1] << endl;
		cout << price << endl;
		cout << endl;
	}

	Py_Finalize ();
}
