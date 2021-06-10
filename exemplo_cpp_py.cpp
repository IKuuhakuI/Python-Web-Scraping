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

	PyRun_SimpleString ("print('Hello World')\n"
			    "print('O Jogo')");

	if (Py_FinalizeEx() < 0) {
		exit(120);
	}

	PyMem_RawFree (program);

	return 0;
}
