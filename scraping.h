#include <vector>
#include <string>
#include <Python.h>

using namespace std;

vector <const char*> pyTupleToVector (PyObject*);

vector <vector<string>> getAmazonData (char *, float, float);
