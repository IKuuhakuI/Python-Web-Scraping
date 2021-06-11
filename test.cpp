#include <Python.h>

#include <iostream>

using namespace std;

/*
string pyObjectToString (PyObject* inputString) {

	char* converted = PyBytes_AsString (inputString);

	return converted;
}
*/

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


	//string result = PyFloat_AsDouble (myResult);

	//cout << result << endl;

	Py_Finalize(); 
	return 0;
}
