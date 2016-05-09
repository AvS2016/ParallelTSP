#include <iostream>
using namespace std;

int main(int argc, char **argv)
{

	// Loops are fine
	for(int i = 0; i<=10; i++){

		cout << i << endl;

	}


	// Pointers are fine exampleurl: http://www.cplusplus.com/doc/tutorial/pointers/
	// quit familiar to C
	int firstvalue, secondvalue;
	int * mypointer;
	mypointer = &firstvalue;
	*mypointer = 10;
	mypointer = &secondvalue;
	*mypointer = 20;
	cout << "firstvalue is " << firstvalue << '\n';
	cout << "secondvalue is " << secondvalue << '\n';

	mypointer = &firstvalue;
	*mypointer = 100;
	cout << "firstvalue is " << firstvalue << '\n';
	cout << "secondvalue is " << secondvalue << '\n';
	return 0;


    return 0;
}
