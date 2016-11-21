#include <gtest/gtest.h>
#include <iostream>
#include "Env.hpp"
#include "neuron.hpp"
#include <vector>

using namespace std;

class EnvTest : public ::testing::Test {
 protected:
	virtual void SetUp() { 
  }
	Env network;
};

TEST_F(EnvTest,TestNumberOfNeuronsCreated) {
	EXPECT_EQ(1350, network.number_of_neurons()) ;
}
	
TEST_F(EnvTest, TestNumberOfNeuronsForGraph) {
	vector<Neuron*> vect(network.graph_fifty_neurons());
	EXPECT_EQ(50, vect.size()) ;
} 


TEST(reset,reset_potential) {
	Neuron neuron(1,1,true,true,1); //valeurs obligatoires pour création d'un neurone mais sans importance
	EXPECT_EQ(10, neuron.get_potential()) ;
}

TEST(reset, state) {
	Neuron neuron(1,1,true,true,1);
	neuron.set_neuron_as_inactive();
	neuron.reset();
	EXPECT_TRUE(neuron.is_active_state()) ;
}


TEST_F(EnvTest,neuron_excitatory) {
	vector<Neuron*> vect(network.get_neurons_());
	for (unsigned int i(250); i<1250; ++i) {
		EXPECT_TRUE(vect[i]->is_excitatory()) ;
	}
}
 
TEST_F(EnvTest,neuron_inhibitory) {
	vector<Neuron*> vect(network.get_neurons_());
	for (unsigned int i(0); i<250; ++i) {
		EXPECT_FALSE(vect[i]->is_excitatory()) ;
	}
}

TEST(new_connection, TestAddConnectionToNeuron) {
	Neuron neur1(1,1,true,true,1);
	Neuron neur2(2,1,true,true,1);
	Neuron* neur(&neur2);
	cout << "nombre de connections de neur1: "<< neur1.get_connections_().size() << endl;
	neur1.add_connection(neur);
	cout << "nombre de connections de neur1: "<< neur1.get_connections_().size() << endl;
	EXPECT_EQ(1, neur1.get_connections_().size()) ;
}

TEST(new_connection, TestIsANewConnection) {
	Neuron neur1(1,1,true,true,1);
	Neuron neur2(2,1,true,true,1);
	Neuron* neur2_(&neur2);
	
	EXPECT_TRUE(neur1.is_a_new_connection(neur2.get_numero()));
	neur1.add_connection(neur2_);
	EXPECT_FALSE(neur1.is_a_new_connection(neur2.get_numero()));
	EXPECT_FALSE(neur1.is_a_new_connection(neur1.get_numero()));
}



	
	
int main(int ac, char* av[])
{
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}



