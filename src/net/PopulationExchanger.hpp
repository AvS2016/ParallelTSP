#ifndef NET_POPULATIONEXCHANGER_HPP_
#define NET_POPULATIONEXCHANGER_HPP_

// external libs
#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>

// internal libs
#include "genetic/Population.hpp"

namespace tsp {

	class PopulationExchanger {
	private:
		boost::mpi::environment env_;
		boost::mpi::communicator world_;
		unsigned int exchangeCount_;
	public:
		PopulationExchanger(int argc, char **argv);
		~PopulationExchanger();

		void exchange (Population &p);


		void setExchangeCount(unsigned int count);
	};

}

#endif
