#include <Python.h>
#include <iostream>
#include <vector>
#include <string>

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


int main(int argc, char* argv[])
{
	Py_Initialize();  
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append(\'.\')");
	
	PyObject* myModuleString = PyUnicode_FromString ((char *) "amazon");
	PyObject* myModule = PyImport_Import (myModuleString);

	if (myModule == NULL) {
		PyErr_Print();
		exit (-1);
	}

	PyObject* myFunction = PyObject_GetAttrString (myModule, (char*)"getItem");
	PyObject* args = PyTuple_Pack (1, PyUnicode_FromString((char *)"Iphone 11"));

	PyObject* myResult = PyObject_CallObject (myFunction, args);

	// vector<vector<const char*>> result = pyTupleToVector (myResult);
	vector <const char*> result = pyTupleToVector (myResult);

	cout << result[0] << endl;

	//cout << result << endl;

	Py_Finalize(); 
	return 0;
}

