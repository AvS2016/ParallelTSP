#include <iostream>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>

using namespace std;
namespace mpi = boost::mpi;

int main(int argc, char **argv) //int argc, char **argv
{
/*
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
	secondvalue = 200;
	cout << "firstvalue is " << firstvalue << '\n';
	cout << "secondvalue is " << secondvalue << '\n';

*/
	// MPI tests
	 mpi::environment env{argc, argv};
	 mpi::communicator world;

	 while (true)
	 {
	     std::cout << "I am 	process " << world.rank() << " of " << world.size()
	            << "." << std::endl;
	     sleep(1);
	 }


	return 0;



}
