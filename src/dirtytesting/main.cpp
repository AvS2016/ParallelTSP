#include <iostream>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include <sstream>
#include <string>
#include <vector>
#include <boost/serialization/vector.hpp>
#include <data/Path.hpp>

namespace mpi = boost::mpi;

std::string toString(tsp::Path &v)
{
    std::stringstream tmp;
    for(int i : v) {
        tmp << i << ",";
    }

    return tmp.str();
}


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
    mpi::environment env(argc, argv);
    mpi::communicator world;

    if(world.rank() == 0) {
        world.send(1, 0, tsp::Path({1, 2, 3, 4}));
        tsp::Path msg;
        world.recv(1, 1, msg);
        std::cout << toString(msg) << "!" << std::endl;
    } else {
        tsp::Path msg;
        world.recv(0, 0, msg);
        std::cout << toString(msg) << ", ";
        std::cout.flush();
        world.send(0, 1, tsp::Path({5, 6, 7, 8}));
    }




    /*
    while (true)
    {
        std::cout << "I am 	process " << world.rank() << " of " << world.size()
               << "." << std::endl;
        sleep(1);
    }
    *
    */







    return 0;



}
