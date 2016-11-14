#include <gtest/gtest.h>
#include <iostream>
#include "Env.hpp"
#include "neuron.hpp"



TEST(nb_of_neurons,TestNumberOfNeuronsCreated) {
	Env network;
	EXPECT_EQ(1350, network.number_of_neurons()) ;
	
	}




int main(int ac, char* av[])
{
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}

