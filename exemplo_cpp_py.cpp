#define PY_SSIZE_T_CLEAN

#include </usr/include/python3.8/Python.h>
#include <iostream>

using namespace std;

// g++ -I/usr/include/python3.8/ exemplo_cpp_py.cpp -L/usr/lib/python3.8/config-3.8m-x86_64-linux-gnu -lpython3.8 -o output

int main (int argc, char const *argv[]) {
	wchar_t *program = Py_DecodeLocale (argv[0], NULL);

	if (program == NULL) {
		cout << stderr << "Fatal Error: Cannot decode argv[0]" << endl;
		exit (1);
	}

	Py_SetProgramName (program);

	Py_Initialize();

	PyRun_SimpleString (	"from bs4 import BeautifulSoup\n"
				"import requests\n"
				"from urllib.request import urlopen as uReq\n"
				"import time\n"

				"def getUrl (searchTerm):\n"
				"	template = 'https://www.amazon.com.br/s?k={}'\n"
				"	searchTerm = searchTerm.replace(' ', '+')\n"
				"	return template.format(searchTerm)\n"

				"def getItem (item):\n"
				"	foi = False\n"

				"	while (foi == False):\n"
				"		url = getUrl(item)\n"
				"		print (url)\n"
				"		print ('Aguarde...')\n"
				"		load = False\n"
				"		html_text = requests.get(url).text\n"
				"		soup = BeautifulSoup (html_text, 'lxml')\n"
				"		products = soup.find_all ('div', class_ = 'sg-col-4-of-12 s-result-item s-asin sg-col-4-of-16 sg-col sg-col-4-of-20')\n"
				"		print (type(products))\n"
				"		if (products != []):\n"
				"			foi = True\n"

				"	for product in products:\n"
				"		name = product.find('span', class_ = 'a-size-base-plus a-color-base a-text-normal').text\n"
				"		price = True\n"

				"		try:\n"
				"			priceWhole = product.find ('span', class_ = 'a-price-whole').text\n"
				"			priceFraction = product.find ('span', class_ = 'a-price-fraction').text\n"
				"		except:\n"
				"			price = False\n"

				"		if price == True:\n"
				"			print (name)\n"
				"			print (priceWhole + priceFraction)\n"
				"			print ()\n"

				"getItem ('Iphone X')\n"
				"print ('OK')");

	if (Py_FinalizeEx() < 0) {
		exit(120);
	}

	PyMem_RawFree (program);

	return 0;
}
