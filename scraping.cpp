#include <Python.h>
#include <iostream>
#include <vector>
#include <string>

#include "algorithms.h"
#include "scraping.h"

using namespace std;

vector<const char*> pyTupleToVector (PyObject* incoming) {

	vector<const char*> data;	

	if (PyTuple_Check(incoming)) {
		for (Py_ssize_t i = 0; i < PyTuple_Size(incoming); i++) {
			vector <const char*> currentData;
			PyObject *subTuple = PyTuple_GetItem (incoming, i);

			PyObject* repr = PyObject_Repr (subTuple);
			PyObject* str = PyUnicode_AsEncodedString(repr,"utf-8", "~E~");	
			const char* result = PyBytes_AS_STRING(str);
			
			data.push_back (result);
		}
	}

	return data;
}


vector <vector<string>> getData (char* productName, float min, float max, string storeName) {

	cout << storeName << endl;
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append(\'.\')");
	
	PyObject* myModuleString = PyUnicode_FromString ((char *) "scraping");
	PyObject* myModule = PyImport_Import (myModuleString);

	if (myModule == NULL) {
		PyErr_Print();
		exit (-1);
	}

	string funcInput;

	if (storeName == "amazon") {
		funcInput = "getAmazonItem";
	} else if (storeName == "americanas") {
		funcInput = "getAmericanasItem";
	} else if (storeName == "submarino") {
		funcInput = "getSubmarinoItem";
	} else {
		funcInput = "getBahiaItem";
	}

	char funcTemp[funcInput.size()];
	char* funcName = funcTemp;

	strToConstCharList (funcInput, funcName);

	PyObject* myFunction = PyObject_GetAttrString (myModule, (char*)funcName);
	PyObject* args = PyTuple_Pack (1, PyUnicode_FromString((char *)productName));

	PyObject* myResult = PyObject_CallObject (myFunction, args);

	vector <const char*> result = pyTupleToVector (myResult);

	vector<vector<string>> productsData; 

	for (size_t index = 0; index < result.size(); index++) {
		vector <string> current = constCharToVectorStr (result[index]);

		if (storeName == "mercado livre") {
			try {
				if (stof(current[1]) > min && stof(current[1]) < max) {
					productsData.push_back (current); 
				}
			} catch (invalid_argument& e) {
				cout << "Erro" << endl;
			}
		} else {
			try {
				if (strToFloat(current[1]) > min && strToFloat(current[1]) < max) {
					productsData.push_back (current); 
				}
			} catch (invalid_argument& e){
				cout << "Valor invalido" << endl;
			}
		}
	}

	return productsData;
}
